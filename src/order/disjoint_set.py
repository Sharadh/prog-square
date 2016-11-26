"""Implements the disjoint set as
a tree and performs union-by-rank.
As described in Introduction to Algorithms by Cormen et. al
(Affectionately: CLRS)
"""


class Node(object):
    def __init__(self, vertex):
        self.vertex = vertex
        self.parent = None
        self.rank = 0

    def __str__(self):
        node = self
        path = [str(node.vertex)]
        while node.parent:
            node = node.parent
            path.append(str(node.vertex))
        return '>'.join(path)


class Forest(object):
    def __init__(self, vertices):
        self.nodes = {
            vertex: Node(vertex)
            for vertex in vertices
        }

    def make_set(self, vertex):
        self.nodes[vertex] = Node(vertex)

    def find_set(self, vertex):
        node = self.nodes[vertex]
        while node.parent:
            node = node.parent
        return node.vertex

    def union(self, first, second):
        first = self.find_set(first)
        second = self.find_set(second)
        if first != second:
            first = self.nodes[first]
            second = self.nodes[second]
            if first.rank > second.rank:
                second.parent = first
                return first
            else:
                first.parent = second
                if first.rank == second.rank:
                    second.rank += 1
                return second

    def __str__(self):
        return ', '.join([
            '{}({})'.format(vertex, self.find_set(vertex))
            for vertex in self.nodes
            ])
