import math
import sys


class Task:
    def read(self, file='in'):
        return [int(p.strip()) for p in open(file).read().split('\n') if p != '']

    def compute(self, v):
        def task1(v, cnt):
            assert(len(v) > cnt)

            for i in range(cnt, len(v)):
                found = False
                for x in range(i - cnt - 1, i):
                    for y in range(x + 1, i):
                        if v[x] + v[y] == v[i]:
                            found = True
                if not found:
                    return v[i]
            assert(False)

        def task2(v, target):
            for i in range(0, len(v)):
                for j in range(i, len(v)):
                    if target == sum(v[i:j]):
                        return min(v[i:j]) + max(v[i:j])
            assert(False)

        cnt = 25
        return (task1(v, cnt), task2(v, task1(v, cnt)))

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
