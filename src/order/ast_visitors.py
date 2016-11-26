from ast import NodeVisitor


class CountingVisitor(NodeVisitor):
    def __init__(self):
        self.counts = {}

    def generic_visit(self, node):
        token = node.__class__.__name__
        self.counts[token] = self.counts.get(token, 0) + 1
        super(CountingVisitor, self).generic_visit(node)
