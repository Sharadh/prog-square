P2: Programming Progressions
====

# Introduction
## Mission
To help educators and learners understand the *progression of skills* involved in transitioning from beginner to expert for any given programming problem set.

## Components
1. `scr/cli.py`: Entry point for the various sub-components. Exposes a number of sub-commands. To see them, type:
```
. ./venv/bin/activate
cd src
python cli.py --help
```
To see the usage of any subcommand, (e.g the `order` task) type:
```
python cli.py order --help
```
Documentation specific to how each subcommand works can be seen in the appropriate submodules. 
2. `src/visalize/app.py`: Minimal Flask-app that serves the static files, as well as generated graph, snippets, etc.

# Partial Ordering
See the [`order`](./src/order) module for details on the partial ordering.

# Getting Started
## Prerequisites
We use [GNU Make](https://www.gnu.org/software/make/) for... well, Makefile stuff. The code runs on Python 2.7, and the `Makefile` assumes `virtualenv` is installed. The `Makefile` uses UNIX-like paths: this may cause compatibility issues with certain Windows environments.

## Installing
Clone the repository, and run `make`
```
git clone git@github.com:Sharadh/prog-square.git
make run
```
This will create the `venv`, install required packages (hat-tip to [pip-tools](https://github.com/nvie/pip-tools) for dependency compiling and management), and compute the partial ordering graph for the default dataset.

To start a web-server that lets you visualize the partial ordering generated:
```
make serve
```
This starts a web-server at `localhost:5000` by default. Navigate to `http://localhost:5000/home`.

There is also a convenience endpoint that bundles the two above steps
```
make visualize
```

To run on a different dataset, just modify the `SOURCE` environment variable inline with the `make` command
```
SOURCE=data/hello make
```

The default dataset is the `practice-python` dataset of ~20 problems and their solutions.

### Running on StackOverflow posts
The repository also exposes `make` targets to retrieve the most recent StackOverflow posts tagged `python`. To run the ordering analysis on these tasks, first pull the code snippets (into the `data/so_temp` directory), and then visualize this source.
```
make pull_so_recent
SOURCE=data/so_temp make visualize
```

## Tests
There's no easy way to say this... tests are not up yet. Stay tuned (or better still, contribute some unit-tests!)

Currently, the only tests that are run are from the `make lint` endpoint: this runs the `pep8` and `flake8` linters against the `*.py` files in the `src` directory.

# License
This project is licensed under the MIT license - see the LICENSE.md file for details

# Contributors
* [Sharadh Krishnamurthy](https://github.com/Sharadh)
* [Eric Anderson](http://www.cs.cornell.edu/~eland/)
