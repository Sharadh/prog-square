import os

import yaml


def get_name_from_filename(filename):
    parts = filename.split('_')
    return ' '.join([
        part.title() for part in parts[1:]
    ])


def main():
    path_to_dir = os.path.realpath('../data/practice-python')
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
            'created_by': 'p2-contributor',
            'retrieved_from': '',
            'references': ['http://www.practicepython.org/']
        }

        output_filename = '{}.p2'.format(base)
        output_filepath = os.path.join(path_to_dir, output_filename)
        with open(output_filepath, 'w') as output_file:
            output_file.write('---\n{}...\n'.format(
                yaml.dump(meta, default_flow_style=False)))
            output_file.write(code)


if __name__ == '__main__':
    main()
