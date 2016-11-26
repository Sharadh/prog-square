import json
import os

from generate.p2_convert import split_meta_source
from utils import warn

from disjoint_set import Forest
from graph import Graph
from graph_utils import topological_sort
from program_info import ProgramInfo, ProgramInfoGroup
from source_handler import count_tokens


def get_program_info(filepath):
    file = open(filepath, 'r')
    data = file.read()

    meta, source = split_meta_source(data)

    token_counts = count_tokens(source)

    return ProgramInfo(filepath, token_counts, meta)


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
            program_group = minimal_programs[pid] = ProgramInfoGroup([])
        program_group.add(program)

    return minimal_programs.values()


def process(path_to_dir, debug):
    g = Graph()
    programs = []
    program_to_vertex = {}
    for filename in os.listdir(path_to_dir):
        _, extension = os.path.splitext(filename)
        if extension != '.p2':
            continue

        filepath = os.path.join(path_to_dir, filename)
        try:
            meta = get_program_info(filepath)
        except SyntaxError as e:
            warn('Error processing "{}" at {}:{}\n{}'.format(
                filename, e.lineno, e.offset, e.text))
            continue

        programs.append(meta)

    programs = decompose_to_scc(programs)
    for program in programs:
        vertex_id = g.add_vertex(program)
        program_to_vertex[program.pid] = vertex_id

    for i in xrange(len(programs)):
        for j in xrange(i + 1, len(programs)):
            first, second = programs[i], programs[j]
            first_vid, second_vid = program_to_vertex[first.pid], program_to_vertex[second.pid]

            if first in second:
                g.add_edge((first_vid, second_vid))
            if second in first:
                g.add_edge((second_vid, first_vid))

    if debug:
        debug_dump(g)

    return graph_to_d3_dict(g)


def debug_dump(graph):
    print graph
    print [graph.V[x].data for x in topological_sort(graph)]
    print json.dumps(graph_to_d3_dict(graph), indent=2)


def graph_to_d3_dict(graph):
    """Exports the graph in a format understandable
    by the d3.js library. This means the following:

    - Replace all vertex-ids with the ids implicit in the
    ordering of vertices within the `nodes` array
    - Change edge ids to reflect the new vertex ids
    - Augment each node with a `depth` attribute for
    rendering in a pleasing partial order
    """

    # Calculate depth by traversing the topologically
    # sorted graph once, from start to end...
    # Note that depth starts from 1: this is useful to
    # distinguish lack of depth from starting-depth.
    ordered_graph = topological_sort(graph)
    new_ids = {}
    depth = {vid: 1 for vid in ordered_graph}
    for i, vid in enumerate(ordered_graph):
        new_ids[vid] = i
        vertex_depth = depth[vid]
        for to_vertex_id in graph.V[vid].adj:
            depth[to_vertex_id] = max(
                depth[to_vertex_id],
                vertex_depth + 1
                )

    data = {'nodes': [], 'links': []}
    filepaths = {}
    for vid in ordered_graph:
        vertex = graph.V[vid]
        filepaths[new_ids[vertex.uid]] = vertex.data.filepath
        data['nodes'].append({
            'id': new_ids[vertex.uid],
            'name': vertex.data.name,
            'depth': depth[vertex.uid]
        })
        for vid in vertex.adj:
            to_vertex = graph.V[vid]
            data['links'].append({
                'source': new_ids[vertex.uid],
                'target': new_ids[to_vertex.uid]
            })

    return data, filepaths
