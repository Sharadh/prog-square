from datetime import datetime, timedelta
from io import StringIO

from lxml import etree
import requests

from order.source_handler import check_source
from utils import (
    log,
    success,
    warn
)

from api_utils import (
    build_url,
    MAX_PAGE_SIZE,
    ANSWER_BATCH_SIZE
)
from custom_filters import load_filter_file
from snippet import Snippet

parser = etree.HTMLParser()


def check_source_and_warn(source, link):
    if not check_source(source):
        log('-----')
        warn('Error parsing snipppet from {}'.format(link))
        log(source)
        log('-----\n')
        return False
    return True


def get_snippets(html_string):
    tree = etree.parse(StringIO(html_string), parser)
    block_tags = tree.findall('.//pre/code')
    code_snippets = [el.text for el in block_tags]
    return code_snippets


def fetch_recent_questions(num_questions, from_time, to_time, tags, page_num, filter_name):
    page_num = page_num or 1
    request_page_size = min(MAX_PAGE_SIZE, num_questions)

    url = build_url(
        'questions',
        site='stackoverflow',
        sort='activity',
        order='desc',
        tagged=['python'] + tags,
        fromdate=from_time,
        todate=to_time,
        pagesize=request_page_size,
        page=page_num,
        filter=filter_name
    )
    response = requests.get(url)
    response_data = response.json()
    log('Quota Remaining: {} of {}'.format(
        response_data.get('quota_remaining', '?'),
        response_data.get('quota_max', '?')))
    return response_data['items'], response_data['has_more']


def fetch_answers(answer_ids, filter_name):
    url = build_url(
        'answers/{}'.format(';'.join(answer_ids)),
        site='stackoverflow',
        filter=filter_name
    )
    response = requests.get(url)
    response_data = response.json()
    log('Quota Remaining: {} of {}'.format(
        response_data.get('quota_remaining', '?'),
        response_data.get('quota_max', '?')))
    return response_data['items']


def fetch_snippets(num_snippets, start_time, end_time, extra_tags):
    """
    Fetches snippets from StackOverflow by looking at 'python' questions
    in the time-period specified, and retrieving `<pre><code>` code blocks
    from these questions (and their answers, where applicable)

    Note that currently the number of snippets returned is not the same as
    the number requested: it depends on the number of retrieved questions with
    a code block, as well as the number with an accepted answer with a code block
    """
    filters = load_filter_file()

    snippets = []
    answer_ids = []

    questions_retrieved = 0
    page_num = 1
    while questions_retrieved < num_snippets:
        questions, has_more = fetch_recent_questions(
            num_questions=(num_snippets - questions_retrieved),
            from_time=start_time,
            to_time=end_time,
            tags=extra_tags,
            page_num=page_num,
            filter_name=filters.Questions
        )
        current_time = datetime.utcnow()
        for q in questions:
            snippets += [
                Snippet(
                    snippet_id=q['question_id'],
                    code=block,
                    url=q['link'],
                    author='stack-overflow',
                    retrieved_at=current_time,
                    additional_url=None
                )
                for block in get_snippets(q['body'])
                if check_source_and_warn(block, q['link'])]
            answer_ids.append(q.get('accepted_answer_id', None))

        questions_retrieved += len(questions)
        page_num += 1
        if not has_more:
            warn('No more questions to fetch: Terminating')
            break

    # Filter out `None` accepted_answer_id's
    answer_ids = [str(ans_id) for ans_id in answer_ids if ans_id]

    log('Retrieving {} accepted answers for analysis...'.format(len(answer_ids)))
    for i in range(0, len(answer_ids), ANSWER_BATCH_SIZE):
        batch = answer_ids[i:i + ANSWER_BATCH_SIZE]
        answers = fetch_answers(batch, filters.Answers)
        for a in answers:
            snippets += [
                Snippet(
                    snippet_id=a['answer_id'],
                    code=block,
                    url=a['link'],
                    author='stack-overflow',
                    retrieved_at=current_time,
                    additional_url=None
                )
                for block in get_snippets(a['body'])
                if check_source_and_warn(block, q['link'])]

    success('Retrieved {} snippets'.format(len(snippets)))
    return snippets


def main():
    current_time = datetime.utcnow()
    fetch_snippets(
        num_snippets=50,
        start_time=(current_time - timedelta(weeks=1)),
        end_time=current_time,
        extra_tags=[]
    )


if __name__ == '__main__':
    main()
