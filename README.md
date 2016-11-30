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
Currently, the logic focuses on *syntactic skills*, that is, elements of syntax that are required to solve various problems. While this is not exhaustive, it provides a good starting point to understand the *progression of skills* involved.

Semantic knowledge (i.e, arrays used as input vs. arrays used to memoize computed values) will be of tremendous value, and will be considered for future work.

## High Level Logic
The super-rough method proposed to generate the skill tree is as follows:
```py
meta = {}
for problem in problem_set:
    syntax_tree = read_ast(problem)
    meta[problem.name] = get_token_counts(syntax_tree)

skill_tree = topological_sort(meta)
```
This logic is implemented in `main.py`. See `ast_visitors.py`, `program_meta.py`, `graph.py`, and `graph_utils.py` for details.

## Preprocessing
Topological sort only works on a Directed Acyclic Graph (DAG); unfortunately, we aren't assured that the dataset holds this quality. Specifically, if two programs `A, B` have exactly the same tokens and counts then `A <= B` and `B <= A` both hold, and the partial ordering graph is cyclic.

In general, we break such cycles by decomposing the dataset into Strongly Connected Components (SCCs). This is done by building up a disjoint-set forest; see `disjoint_set.py` for details.

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
