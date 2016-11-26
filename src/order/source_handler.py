import ast


class CountingVisitor(ast.NodeVisitor):
    def __init__(self):
        self.counts = {}

    def generic_visit(self, node):
        token = node.__class__.__name__
        self.counts[token] = self.counts.get(token, 0) + 1
        super(CountingVisitor, self).generic_visit(node)


def check_source(source):
    try:
        ast.parse(source)
    except SyntaxError:
        return False
    return True


def count_tokens(source):
    root = ast.parse(source)

    counter = CountingVisitor()
    counter.visit(root)

    return counter.counts
