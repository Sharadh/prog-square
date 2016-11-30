order: Module Overview
---
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
This logic is implemented in `main.py`. See `source_handler.py`, `program_info.py`, `graph.py`, and `graph_utils.py` for details.

## Preprocessing
Topological sort only works on a Directed Acyclic Graph (DAG); unfortunately, we aren't assured that the dataset holds this quality. Specifically, if two programs `A, B` have exactly the same tokens and counts then `A <= B` and `B <= A` both hold, and the partial ordering graph is cyclic.

In general, we break such cycles by decomposing the dataset into Strongly Connected Components (SCCs). This is done by building up a disjoint-set forest; see `disjoint_set.py` for details.

## Input Format
This module expects files to be in following format:
```
---
<yaml_attribute_name>: <attribute_value>
[...]
...
print "Hello World!"
```
This format is formally parsed in `split_meta_source` in `p2_convert.py`. There is a case to be made that this could be refactored into either a `generate.utils` or the top level `utils`.
