import json
from os import path

import requests

from utils import (
    log,
    success
)

from api_utils import (
    augment_api_fields,
    build_url
)

FILTER_FILEPATH = path.join(
    path.dirname(path.realpath(__file__)),
    '_generated_filters.json'
)


class FilterSet(object):
    def __init__(self, questions_filter, answers_filter):
        self.Questions = questions_filter
        self.Answers = answers_filter


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
    filter_name = response_data['items'][0]['filter']
    return filter_name


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
    filter_name = response_data['items'][0]['filter']
    return filter_name


def create_filter_file():
    qn_filter = create_question_filter()
    ans_filter = create_answer_filter()
    with open(FILTER_FILEPATH, 'w') as output_file:
        output_file.truncate()
        output_file.write(json.dumps({
            'questions': qn_filter,
            'answers': ans_filter
        }, indent=2))
    success('Wrote custom filters to {}'.format(FILTER_FILEPATH))


def ensure_updated_filters():
    if (
        path.exists(FILTER_FILEPATH) and
        path.getmtime(path.realpath(__file__)) < path.getmtime(FILTER_FILEPATH)
    ):
        return

    log('Filter file outdated; Rebuilding...')
    create_filter_file()
    return


def load_filter_file():
    ensure_updated_filters()

    with open(FILTER_FILEPATH, 'r') as input_file:
        data = json.loads(input_file.read())
    return FilterSet(data['questions'], data['answers'])
