import math
import sys


class Task:
    def read(self, file='in'):
        return [p.strip() for p in open(file).read().split('\n\n')]

    def compute(self, v):
        pass

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
