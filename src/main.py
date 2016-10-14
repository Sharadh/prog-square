import ast
import json
import os

from ast_visitors import CountingVisitor
from disjoint_set import Forest
from program_meta import ProgramMeta, ProgramMetaGroup
from graph import Graph
from graph_utils import topological_sort


def get_file_meta(filepath):
    file = open(filepath, 'r')
    source = file.read()
    root = ast.parse(source)

    counter = CountingVisitor()
    counter.visit(root)

    return ProgramMeta(filepath, counter.counts)


def decompose_to_scc(programs):
    # This does a O(V^2) preprocessing pass on the data, which may be
    # an issue. If this becomes a problem, implement a proper O(V+E)
    # SCC algo, but that may not help if E = O(V^2)
    f = Forest([program.pid for program in programs])
    for p1 in programs:
        for p2 in programs:
            if p1 is p2:
                continue

            if p1 == p2:
                f.union(p1.pid, p2.pid)

    minimal_programs = {}
    for program in programs:
        pid = f.find_set(program.pid)
        try:
            program_group = minimal_programs[pid]
        except KeyError:
            program_group = minimal_programs[pid] = ProgramMetaGroup([])
        program_group.add(program)

    return minimal_programs.values()


def process(path_to_dir):
    g = Graph()
    programs = []
    program_to_vertex = {}
    for filename in os.listdir(path_to_dir):
        filepath = os.path.join(path_to_dir, filename)
        meta = get_file_meta(filepath)
        programs.append(meta)

    programs = decompose_to_scc(programs)
    for program_meta in programs:
        vertex_id = g.add_vertex(program_meta)
        program_to_vertex[program_meta.pid] = vertex_id

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
    print graph_to_json(g)


def graph_to_json(graph):
    data = {'nodes': [], 'links': []}
    for _, vertex in enumerate(graph.V):
        data['nodes'].append({
            'id': vertex.uid,
            'name': vertex.data.name
        })
        for vid in vertex.adj:
            to_vertex = graph.V[vid]
            data['links'].append({
                'source': vertex.uid,
                'target': to_vertex.uid
            })
    return json.dumps(data, indent=2)
