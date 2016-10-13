Project Scope
====

This document describes the scope of the "Automatic Programming Skill Map" project. The project is advisor is [Eric Anderson](http://www.cs.cornell.edu/~eland/), and the student working on this project is [Sharadh Krishnamurthy](https://github.com/Sharadh). The project is for the Fall 2016 semester, for 4 credits.

## Mission
To help educators and learners understand the *progression of skills* involved in transitioning from beginner to expert for any given programming problem set.

## Components
1. To automatically generate a "skill tree" of various skills involved in solving a programming problem set.
2. To display this tree in a format that is easy for learners and educators to consume.

## Skill Tree Generation
Initially, the scope of the project will be limited to *syntactic skills*, that is, elements of syntax that are required to solve various problems. While this is not exhaustive, it provides a good starting point to understand the *progression of skills* involved.

Semantic knowledge (i.e, arrays used as input vs. arrays used to memoize computed values) will be of tremendous value, and will be considered for future work (or now, if time permits!).

## Method
The super-rough method proposed to generate the skill tree is as follows:
```py
meta = {}
for problem in problem_set:
    syntax_tree = read_ast(problem)
    
    # Assume a simple unigram model
    counts = {}
    for token in syntax_tree:
        try:
            counts[token] = counts[token] + 1
        except KeyError:
            counts[token] = 1

    meta[problem.name] = counts

skill_tree = topological_sort(meta)
```

## Work Items
* Obtain a reasonable problem set.
    + Ideally, pull this from one of the  major online programming judges
    + Else, hand-curate a reasonably large set of problems
    + Alternatively, take these from problem sets from assignments in the CS 2110 series
* Use the standard compiler (`clang++` for C++, or python built-in) to parse a problem code.
* Do some basic NLP-style frequency counting.
    - Should this be unigram/bigram/...?
* Sort the problem set in order of "A contained in B", that is, partial ordering of the entire problem set

## Updates
* [sk]: Update 4 Oct 16 - Happy with logic. Next step: get large and interesting data. Try:
    * StackOverflow / Reddit for <Question, Snipper> pairs
        - Research xkcd-related script to pull answers from SO
    * CodeAcademy; Hour of Code : open datasets?
    * Code.org: Mail for research related access 
