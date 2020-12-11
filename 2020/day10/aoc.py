import math
import sys


class Task:
    def read(self, file='in'):
        return [int(p.strip()) for p in open(file).read().split('\n') if p != '']

    def compute(self, v):
        v.sort()
        v = [0] + v + [max(v) + 3]
        n = len(v)

        diff = [0] * n
        for i in range(0, n - 1):
            diff[v[i + 1] - v[i]] += 1
        cnt1 = diff[1] * diff[3]

        # dp[i] = # of seq using from first i elements and ending with value v[i]
        # dp[0] = 1
        # dp[i > 0] = sum(dp[j]) where j = 0:i-1 and v[i] - v[j] <= 3

        dp = [0] * n
        dp[0] = 1
        for i in range(1, n):
            dp[i] = sum([dp[j] for j in range(0, i)
                         if v[i] - v[j] <= 3])
        cnt2 = dp[n - 1]

        return (cnt1, cnt2)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
