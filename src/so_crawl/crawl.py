from datetime import datetime, timedelta
from io import StringIO

from lxml import etree
import requests

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

parser = etree.HTMLParser()

MAX_QUESTION_NUM = 50
REQUEST_PAGE_SIZE = min(MAX_PAGE_SIZE, MAX_QUESTION_NUM)


def get_snippets(html_string):
    tree = etree.parse(StringIO(html_string), parser)
    code_snippets = [el.text for el in tree.iter() if el.tag == 'code']
    return code_snippets


def fetch_recent_questions(page_num, filter_name):
    page_num = page_num or 1
    url = build_url(
        'questions',
        site='stackoverflow',
        sort='activity',
        order='desc',
        tagged=['python'],
        fromdate=(datetime.utcnow() - timedelta(weeks=1)),
        todate=datetime.utcnow(),
        pagesize=REQUEST_PAGE_SIZE,
        page=page_num,
        filter=filter_name
    )
    response = requests.get(url)
    response_data = response.json()
    return response_data['items'], response_data['has_more']


def fetch_answers(answer_ids, filter_name):
    url = build_url(
        'answers/{}'.format(';'.join(answer_ids)),
        site='stackoverflow',
        filter=filter_name
    )
    response = requests.get(url)
    response_data = response.json()
    return response_data['items']


def main():
    filters = load_filter_file()

    snippets = []
    answer_ids = []

    questions_retrieved = 0
    page_num = 1
    while questions_retrieved < MAX_QUESTION_NUM:
        questions, has_more = fetch_recent_questions(page_num, filters.Questions)
        for q in questions:
            snippets += get_snippets(q['body'])
            answer_ids.append(q.get('accepted_answer_id', None))

        questions_retrieved += len(questions)
        page_num += 1
        if not has_more:
            warn('No more questions to fetch: Terminating')
            break

    log('Retrieving {} accepted answers for analysis...'.format(len(answer_ids)))
    answer_ids = [str(ans_id) for ans_id in answer_ids if ans_id]
    for i in range(0, len(answer_ids), ANSWER_BATCH_SIZE):
        batch = answer_ids[i:i + ANSWER_BATCH_SIZE]
        answers = fetch_answers(batch, filters.Answers)
        for a in answers:
            snippets += get_snippets(a['body'])

    success('Retrieved {} snippets'.format(len(snippets)))


if __name__ == '__main__':
    main()
