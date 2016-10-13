from os import path


class ProgramMeta(object):
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

    def __init__(self, filepath, token_counts):
        self.pid = self.generate_pid()
        self.filepath = filepath
        self.counts = token_counts

        self.register(self)

    @property
    def name(self):
        return path.splitext(path.basename(self.filepath))[0]

    def __repr__(self):
        return self.name
        return "<ProgramMeta #{}>  {}".format(self.pid, self.name)

    def __contains__(self, other):
        return (
            set(other.counts.keys()) <= set(self.counts.keys()) and
            all([
                other.counts[key] <= self.counts[key]
                for key in other.counts.keys()
                ])
            )
