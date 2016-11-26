import os

import yaml


def split_meta_source(data):
    yaml_start = data.index('---')
    yaml_end = data.index('...') + 3
    meta = yaml.load(data[yaml_start:yaml_end])
    source = data[yaml_end:]
    return meta, source


def get_name_from_filename(filename):
    parts = filename.split('_')
    return ' '.join([
        part.title() for part in parts[1:]
    ])


def convert_py(path_to_dir, author, primary_reference):
    num_files_converted = 0
    for filename in os.listdir(path_to_dir):
        filepath = os.path.join(path_to_dir, filename)
        with open(filepath, 'r') as input_file:
            code = input_file.read()

        base, ext = os.path.splitext(filename)
        if ext != '.py':
            continue
        meta = {
            'name': get_name_from_filename(base),
            'language': ext[1:],
            'created_on': os.path.getmtime(filepath),
            'created_by': author,
            'retrieved_from': '',
            'references': [primary_reference]
        }

        output_filename = '{}.p2'.format(base)
        output_filepath = os.path.join(path_to_dir, output_filename)
        with open(output_filepath, 'w') as output_file:
            output_file.write('---\n{}...\n'.format(
                yaml.dump(meta, default_flow_style=False)))
            output_file.write(code)

        num_files_converted += 1
    return num_files_converted
