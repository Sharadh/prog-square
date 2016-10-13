import os

import click

from main import process


@click.group()
def cli():
    pass


@cli.command()
@click.argument('input-dir', type=click.Path(exists=True))
def order(input_dir):
    input_dirpath = os.path.realpath(input_dir)
    process(input_dirpath)


if __name__ == '__main__':
    cli()
