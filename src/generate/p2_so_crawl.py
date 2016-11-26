from os import path

import yaml

from so_crawl.crawl import fetch_snippets


def _get_name_from_question_link(full_link):
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


def _get_filepath_for_snippet(snippet, path_to_dir):
    # First, throw away the anchor part of the link...
    anchor_pos = snippet.url.find('#')
    if anchor_pos >= 0:
        full_link = snippet.url[:anchor_pos]
    else:
        full_link = snippet.url

    # Now, get the final part of link, and use as filename
    # To be safe, make sure to use utf8 for filepath compatibility
    link = path.basename(full_link).encode('utf-8')
    filename = '{}.p2'.format(link)
    filepath = path.join(path_to_dir, filename)

    # Lets make sure we aren't overwriting an existing file
    # To be safe, lets bound the number of attempts to a reasonable number like 100
    # (Bonus: This also makes the code more func-y, without loop counters)
    for i in xrange(100):
        if not path.exists(filepath):
            break
        filename = '{}({})'.format(link, i + 1)
        filepath = path.join(path_to_dir, filename)

    # By design, if 100 attempts fail to find a unique filepath,
    # the 100th duplicate is overwritten...
    return filepath


def _snippet_to_source(snippet):
    title = _get_name_from_question_link(snippet.url)
    meta = {
        'name': title,
        'language': 'py',
        'created_on': snippet.retrieved_at,
        'created_by': snippet.author,
        'retrieved_from': snippet.url,
        'references': [snippet.extra_url]
    }
    yaml_meta = yaml.dump(meta, default_flow_style=False)
    return u'---\n{}...\n{}'.format(yaml_meta, snippet.code)


def pull_snippets(num_snippets, start_time, end_time, extra_tags, save_to_dir):
    snippets = fetch_snippets(num_snippets, start_time, end_time, extra_tags)
    for snippet in snippets:
        full_source = _snippet_to_source(snippet)

        output_filepath = _get_filepath_for_snippet(snippet, save_to_dir)
        with open(output_filepath, 'w') as output_file:
            # Encode Late: Convert string to utf8 just before writing
            output_file.write(full_source.encode('utf-8'))
    return len(snippets)
