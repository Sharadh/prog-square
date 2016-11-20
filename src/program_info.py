from os import path


class ProgramInfo(object):
    COUNT = 0
    PROGRAMS = {}

    @classmethod
    def generate_pid(cls):
        cls.COUNT += 1
        return cls.COUNT

    @classmethod
    def register(cls, program):
        cls.PROGRAMS[program.pid] = program

    @classmethod
    def ids(cls):
        return cls.PROGRAMS.keys()

    def __init__(self, filepath, token_counts, meta):
        self.pid = self.generate_pid()
        self.filepath = filepath
        self.counts = token_counts
        self.meta = meta

        self.register(self)

    @property
    def name(self):
        return path.splitext(path.basename(self.filepath))[0]

    def __str__(self):
        return self.name

    def __repr__(self):
        return "<ProgramInfo {}>".format(self.name)

    def __contains__(self, other):
        return (
            set(other.counts.keys()) <= set(self.counts.keys()) and
            all([
                other.counts[key] <= self.counts[key]
                for key in other.counts.keys()
                ])
            )

    def __eq__(self, other):
        return (self in other) and (other in self)

    def __ne__(self, other):
        return not self.__eq__(other)


class ProgramInfoGroup(ProgramInfo):
    """Think of this as a CompositeProgramInfo,
    not as a container or iterator. Simplifies
    dealing with single/merged programs.
    Ref: https://en.wikipedia.org/wiki/Composite_pattern
    """
    def __init__(self, programs):
        self.pid = self.generate_pid()
        self.programs = set(programs) or set([])
        self.delegate = (len(programs) and programs[0]) or None

        self.register(self)

    def add(self, program):
        self.programs.add(program)
        if not self.delegate:
            self.delegate = program

    def remove(self, program):
        self.programs.add(program)

    @property
    def name(self):
        return '[{}]'.format(
            ','.join([program.name for program in self.programs])
            )

    @property
    def filepath(self):
        return ';'.join([program.filepath for program in self.programs])

    @property
    def counts(self):
        return self.delegate.counts

    def __str__(self):
        return self.name

    def __repr__(self):
        return "<ProgramInfoGroup {}+{}>".format(
            self.delegate.name, len(self.programs) - 1)
