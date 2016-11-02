import os
import json

import click

from main import process
from utils import success, warn


@click.group()
def cli():
    pass


def sanitize_paths(input_dir, output_file):
    output_filepath = output_file or '{}-output.json'.format(os.path.basename(input_dir))

    # Get paths relative to module root, which is one directory higher...
    [input_dirpath, output_filepath] = map(
        lambda f: os.path.realpath(os.path.join('..', f)),
        [input_dir, output_filepath]
        )

    if not os.path.exists(input_dirpath):
        raise ValueError('Source directory {} does not exist.'.format(input_dirpath))

    return input_dirpath, output_filepath


@cli.command()
@click.argument('input-dir', type=click.Path())
@click.option('--output', '-o', type=click.Path())
@click.option('--debug/--no-debug', default=False)
def order(input_dir, output, debug):
    try:
        input_dirpath, output_filepath = sanitize_paths(input_dir, output)
    except ValueError as e:
        warn('Error: {}. Exiting.'.format(e.message))
        return

    graph_d3_data = process(input_dirpath, debug)

    if os.path.exists(output_filepath):
        warn('Overwriting the existing file at {}'.format(output_filepath))

    with open(output_filepath, 'w') as output_file:
        output_file.truncate()
        output_file.write(json.dumps(graph_d3_data, indent=2))

    success('Wrote partial ordering graph of {} to {}'.format(input_dirpath, output_filepath))


if __name__ == '__main__':
    cli()
