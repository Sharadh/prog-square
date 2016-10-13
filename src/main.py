import ast
import os

from ast_visitors import CountingVisitor
from program_meta import ProgramMeta
from graph import Graph
from graph_utils import topological_sort

DIR_PATH = os.path.join(
    os.path.dirname(os.path.dirname(os.path.realpath(__file__))),
    'data/hello'
)


def process_file(filepath):
    file = open(filepath, 'r')
    source = file.read()
    root = ast.parse(source)

    counter = CountingVisitor()
    counter.visit(root)

    return ProgramMeta(filepath, counter.counts)


def process(path_to_dir):
    g = Graph()
    programs = []
    program_to_vertex = {}
    for filename in os.listdir(path_to_dir):
        filepath = os.path.join(path_to_dir, filename)
        meta = process_file(filepath)

        vertex_id = g.add_vertex(meta)
        program_to_vertex[meta.pid] = vertex_id
        programs.append(meta)

    for i in xrange(len(programs)):
        for j in xrange(i + 1, len(programs)):
            first, second = programs[i], programs[j]
            first_vid, second_vid = program_to_vertex[first.pid], program_to_vertex[second.pid]
            if first in second:
                g.add_edge((first_vid, second_vid))
            if second in first:
                g.add_edge((second_vid, first_vid))

    print g
    print [g.V[x].data for x in topological_sort(g)]

if __name__ == '__main__':
    process(DIR_PATH)
