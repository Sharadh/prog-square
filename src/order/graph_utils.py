

class Colors(object):
    WHITE = 'W'
    GRAY = 'G'
    BLACK = 'B'


def _dfs_visit(graph, vertex, data):
    vertex_data = data[vertex.uid]
    if vertex_data['color'] is not Colors.WHITE:
        return

    data['__tick'] += 1
    vertex_data['start'] = data['__tick']
    vertex_data['color'] = Colors.GRAY
    for vid in vertex.adj:
        next_vertex = graph.V[vid]
        _dfs_visit(graph, next_vertex, data)
    vertex_data['end'] = data['__tick']
    vertex_data['color'] = Colors.BLACK


def dfs(graph):
    data = {
        vertex.uid: {
            'color': Colors.WHITE,
            'start': -1,
            'end': -1
        }
        for vertex in graph.V
    }
    data['__tick'] = 0

    for vertex in graph.V:
        _dfs_visit(graph, vertex, data)

    del data['__tick']
    return data


def topological_sort(graph):
    data = dfs(graph)
    return sorted(data, key=lambda x: data[x]['end'], reverse=True)
