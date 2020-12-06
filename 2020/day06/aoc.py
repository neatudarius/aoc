import math
import sys


class Task:
    def read(self, file='in'):
        return [p.strip() for p in open(file).read().split('\n\n')]

    def compute(self, v):
        cnt_any = sum([len(set(x.replace('\n', ''))) for x in v])
        cnt_all = sum([len(set.intersection(*[set(y)
                                              for y in x.split('\n')])) for x in v])
        return (cnt_any, cnt_all)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
