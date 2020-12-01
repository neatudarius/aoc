import math
import sys


class Task:
    def read(self, file='in'):
        with open(file, 'r') as f:
            v = [int(line) for line in f.readlines()]
        return v

    def compute(self, v):
        def solve2(v):
            sol = -1
            for i in range(len(v)):
                for j in range(i, len(v)):
                    if v[i] + v[j] == 2020:
                        sol = max(sol, v[i] * v[j])
            return sol

        def solve3(v):
            sol = -1
            for i in range(len(v)):
                for j in range(i, len(v)):
                    for k in range(j, len(v)):
                        if v[i] + v[j] + v[k] == 2020:
                            sol = max(sol, v[i] * v[j] * v[k])
            return sol

        return (solve2(v), solve3(v))

    def print(self, result):
        print('{}\n{}'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
