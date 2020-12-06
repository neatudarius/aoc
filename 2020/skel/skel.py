import math
import sys


class Task:
    def read(self, file='in'):
        with open(file, 'r') as f:
            v = [int(line) for line in f.readlines()]
        return v

    def compute(self, v):
        pass

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
