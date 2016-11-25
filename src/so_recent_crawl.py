from datetime import datetime, timedelta
from io import StringIO

from lxml import etree
import requests

from utils import (
    log,
    success,
    warn
)

parser = etree.HTMLParser()

BASE_URL = 'http://api.stackexchange.com/2.2'
COMMON_WRAPPER_FIELDS = frozenset([
    ".has_more",
    ".items",
    ".quota_max",
    ".quota_remaining"
])
MAX_QUESTION_NUM = 50
REQUEST_PAGE_SIZE = min(100, MAX_QUESTION_NUM)  # 100 is the stackexchange API limit
ANSWER_BATCH_SIZE = 100  # Limit set by stackexchange API


def augment_api_fields(fields):
    all_fields = set(COMMON_WRAPPER_FIELDS)
    all_fields.update(fields)
    return all_fields


def create_question_filter():
    url = build_url(
        'filters/create',
        include=augment_api_fields([
            'question.accepted_answer_id',
            'question.body',
            'question.link',
            'question.question_id',
            'question.score',
            'question.tags',
            'question.title'
        ]),
        base='none',
        unsafe=False,
        )
    response = requests.get(url)
    response_data = response.json()
    success('Question Filter: {}'.format(response_data['items'][0]['filter']))


def create_answer_filter():
    url = build_url(
        'filters/create',
        include=augment_api_fields([
            'answer.answer_id',
            'answer.creation_date',
            'answer.body',
            'answer.is_accepted',
            'answer.link',
            'answer.question_id',
            'answer.score',
        ]),
        base='none',
        unsafe=False,
        )
    response = requests.get(url)
    response_data = response.json()
    success('Answer Filter: {}'.format(response_data['items'][0]['filter']))


def seconds_since_epoch(datetime_value):
    epoch = datetime(1970, 1, 1)
    seconds = (datetime_value - epoch).total_seconds()
    return long(seconds)


def build_url(entity, **kwargs):
    arg_array = []
    for arg_name, value in kwargs.iteritems():
        if not value:
            continue
        if isinstance(value, datetime):
            final_value = seconds_since_epoch(value)
        elif isinstance(value, basestring):
            final_value = str(value)
        else:
            try:
                _ = iter(value)
                final_value = ';'.join([str(v) for v in value])
            except:
                final_value = str(value)
        arg_array.append('{}={}'.format(arg_name, final_value))

    arg_string = '&'.join(sorted(arg_array))
    url = '{}/{}?{}'.format(BASE_URL, entity, arg_string)
    return url


def get_snippets(html_string):
    tree = etree.parse(StringIO(html_string), parser)
    code_snippets = [el.text for el in tree.iter() if el.tag == 'code']
    return code_snippets


def fetch_recent_questions(page_num):
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
        filter='!0DsNFtRPIGBtsQIK'
    )
    response = requests.get(url)
    response_data = response.json()
    return response_data['items'], response_data['has_more']


def fetch_answers(answer_ids):
    url = build_url(
        'answers/{}'.format(';'.join(answer_ids)),
        site='stackoverflow',
        filter='!.pwhrSbrwo-(EVXDB1O*'
    )
    response = requests.get(url)
    response_data = response.json()
    return response_data['items']


def main():
    snippets = []
    answer_ids = []

    questions_retrieved = 0
    page_num = 1
    while questions_retrieved < MAX_QUESTION_NUM:
        questions, has_more = fetch_recent_questions(page_num)
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
        answers = fetch_answers(batch)
        for a in answers:
            snippets += get_snippets(a['body'])

    print snippets


if __name__ == '__main__':
    main()
