import math
import sys
import copy


class Task:
    def read(self, file='in'):
        return [list(p.strip()) for p in open(file).read().split('\n') if p != '']

    def compute(self, a):
        def next(n, m, a, neigbours, cnt_L, cnt_Hash):
            new_a = copy.deepcopy(a)
            for i in range(1, n + 1):
                for j in range(1, m + 1):
                    if a[i][j] == '.':
                        continue
                    elif a[i][j] == 'L':
                        cnt = sum(
                            [a[x][y] == '#' for (x, y) in neigbours(i, j, a)])
                        # print('L', i, j, cnt)
                        if cnt_L(cnt):
                            new_a[i][j] = '#'
                        assert(a[i][j] == 'L')

                    elif a[i][j] == '#':
                        cnt = sum(
                            [a[x][y] == '#' for (x, y) in neigbours(i, j, a)])
                        # print('#', i, j, cnt)
                        if cnt_Hash(cnt):
                            new_a[i][j] = 'L'
                        assert(a[i][j] == '#')
                    else:
                        assert(False)
            return new_a

        def pprint(n, m, a):
            print(n, m)
            for row in a:
                print(''.join(row))

        def conway(n, m, a, neigbours, cnt_L, cnt_Hash):
            generation = 1
            while True:
                pprint(n, m, a)
                new_a = next(n, m, a, neigbours, cnt_L, cnt_Hash)
                if new_a == a:
                    break
                generation += 1
                a = new_a

            return generation, new_a

        def neigbours1(i, j, a):
            return [(i + di, j + dj) for di in [-1, 0, 1]
                    for dj in [-1, 0, 1] if dj != 0 or di != 0]

        def cnt_L1(cnt):
            return cnt == 0

        def cnt_Hash1(cnt):
            return cnt >= 4

        def neigbours2(i, j, a):
            n = len(a) - 2
            m = len(a[0]) - 2

            neigbours = []
            for (di, dj) in [(di, dj)for di in [-1, 0, 1]
                             for dj in [-1, 0, 1] if di != 0 or dj != 0]:
                x, y = i + di, j + dj
                while True:
                    if x < 1 or x > n or y < 1 or y > m:
                        break

                    if a[x][y] != '.':
                        assert((x, y) != (i, j))
                        neigbours.append((x, y))
                        break
                    x, y = x + di, y + dj

            return neigbours

        def cnt_L2(cnt):
            return cnt == 0

        def cnt_Hash2(cnt):
            return cnt >= 5

        n = len(a)
        m = len(a[0])
        a = [['.'] + row + ['.'] for row in a]
        a = [['.'] * (m + 2)] + a + [['.'] * (m + 2)]

        print('task1:')
        _, a1 = conway(n, m, a, neigbours1, cnt_L1, cnt_Hash1)
        pprint(n,  m, a1)
        cnt1 = sum([1 if a1[i][j] == '#' else 0 for i in range(1, n + 1)
                    for j in range(1, m + 1)])

        print('task2:')
        _, a2 = conway(n, m, a, neigbours2, cnt_L2, cnt_Hash2)
        pprint(n,  m, a2)
        cnt2 = sum([1 if a2[i][j] == '#' else 0 for i in range(1, n + 1)
                    for j in range(1, m + 1)])

        return (cnt1, cnt2)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
