import os
import json

import click

from main import process
from utils import success, warn


@click.group()
def cli():
    pass


def sanitize_paths(input_dir, output_file, manifest_file):
    output_filepath = output_file or '{}-output.json'.format(os.path.basename(input_dir))
    manifest_filepath = manifest_file or '{}-manifest.json'.format(os.path.basename(input_dir))

    # Get paths relative to module root, which is one directory higher...
    [input_dirpath, output_filepath, manifest_filepath] = map(
        lambda f: os.path.realpath(os.path.join('..', f)),
        [input_dir, output_filepath, manifest_filepath]
        )

    if not os.path.exists(input_dirpath):
        raise ValueError('Source directory {} does not exist.'.format(input_dirpath))

    return input_dirpath, output_filepath, manifest_filepath


@cli.command()
@click.argument('input-dir', type=click.Path())
@click.option('--output', '-o', type=click.Path())
@click.option('--manifest', '-m', type=click.Path())
@click.option('--debug/--no-debug', default=False)
def order(input_dir, output, manifest, debug):
    try:
        paths = sanitize_paths(input_dir, output, manifest)
        input_dirpath, output_filepath, manifest_filepath = paths
    except ValueError as e:
        warn('Error: {}. Exiting.'.format(e.message))
        return

    graph_d3_data, manifest_data = process(input_dirpath, debug)

    if os.path.exists(output_filepath):
        warn('Overwriting the existing file at {}'.format(output_filepath))

    if os.path.exists(manifest_filepath):
        warn('Overwriting the existing file at {}'.format(manifest_filepath))

    with open(output_filepath, 'w') as output_file:
        output_file.truncate()
        output_file.write(json.dumps(graph_d3_data, indent=2))

    with open(manifest_filepath, 'w') as manifest_file:
        manifest_file.truncate()
        manifest_file.write(json.dumps(manifest_data, indent=2))

    success('Wrote partial ordering graph of {} to {}'.format(input_dirpath, output_filepath))
    success('Created manifest file at {}'.format(manifest_filepath))


if __name__ == '__main__':
    cli()
