"""graph.py

Makes the graph abstraction. Stores edges as adjacency
lists of vertices.
"""


class Vertex(object):
    def __init__(self, uid, data):
        self._uid = uid
        self._data = data
        self._adj = set([])

    @property
    def data(self):
        return self._data

    @property
    def uid(self):
        return self._uid

    @property
    def adj(self):
        return self._adj

    def add_edge(self, to_id):
        self._adj.add(to_id)


class Graph(object):
    NEXT_VID = 0

    def __init__(self):
        self.V = []

    def add_vertex(self, vertex_data):
        """Add vertex with given data. Return added vertex id.
        """
        new_vertex = Vertex(self.NEXT_VID, vertex_data)
        self.V.append(new_vertex)
        self.NEXT_VID += 1
        return new_vertex.uid

    def add_vertices(self, vertex_data_list):
        vids = []
        for item in vertex_data_list:
            vids.append(self.add_vertex(item))
        return vids

    def add_edge(self, edge):
        """Add edge between the two vids in the tuple `edge`.
        """
        (from_vertex, to_vertex) = edge
        self.V[from_vertex].add_edge(to_vertex)

    def add_edges(self, edge_list):
        for edge in edge_list:
            self.add_edge(edge[0], edge[1])

    def __repr__(self):
        output = []
        for vertex in self.V:
            output.append("{} --> {}".format(vertex.data, [self.V[vid].data for vid in vertex.adj]))
        return '\n'.join(output)
