from datetime import datetime, timedelta
from os import path

import yaml

from so_crawl.crawl import fetch_snippets


def get_name_from_question_link(full_link):
    # First, throw away the anchor part of the link...
    anchor_pos = full_link.find('#')
    if anchor_pos >= 0:
        full_link = full_link[:anchor_pos]

    # Now, get the final part of link, and convert to title
    link = path.basename(full_link)
    parts = link.split('-')
    return ' '.join([
        part.title() for part in parts
    ])


def get_filename_for_snippet(snippet):
    # First, throw away the anchor part of the link...
    anchor_pos = snippet.url.find('#')
    if anchor_pos >= 0:
        full_link = snippet.url[:anchor_pos]
    else:
        full_link = snippet.url

    # Now, get the final part of link, and use as filename
    link = path.basename(full_link)
    return '{}.p2'.format(link)


def snippet_to_source(snippet):
    title = get_name_from_question_link(snippet.url)
    meta = {
        'name': title,
        'language': 'py',
        'created_on': snippet.retrieved_at,
        'created_by': snippet.author,
        'retrieved_from': snippet.url,
        'references': [snippet.extra_url]
    }
    yaml_meta = yaml.dump(meta, default_flow_style=False)
    return '---\n{}...\n{}'.format(yaml_meta, snippet.code)


def pull_snippets(num_snippets, start_time, end_time, extra_tags, save_to_dir):
    snippets = fetch_snippets(num_snippets, start_time, end_time, extra_tags)
    for snippet in snippets:
        full_source = snippet_to_source(snippet)

        output_filename = get_filename_for_snippet(snippet)
        output_filepath = path.join(save_to_dir, output_filename)
        with open(output_filepath, 'w') as output_file:
            output_file.write(full_source)


if __name__ == '__main__':
    current_time = datetime.utcnow()
    pull_snippets(
        num_snippets=50,
        start_time=(current_time - timedelta(weeks=1)),
        end_time=current_time,
        extra_tags=[],
        save_to_dir=path.realpath('../data/so_temp')
    )
