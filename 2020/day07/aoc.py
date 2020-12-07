import math
import sys


class Task:
    def read(self, file='in'):
        return [line.strip() for line in open(file).read().strip().split('\n')]

    def build_graph(self, input):
        is_dep = {}
        has_dep = {}

        for line in input:
            base_color = line.split('bags contain')[0].strip()

            deps = line.split('contain')[1].strip(' .')
            if deps == 'no other bags':
                continue

            for dep in deps.split(','):
                count = int(dep.strip().split(' ')[0])
                dep_color = ' '.join(dep.strip().split(' ')[1:3])

                has_dep.setdefault(base_color, []).append((count, dep_color))
                is_dep.setdefault(dep_color, []).append((count, base_color))

        return (is_dep, has_dep)

    def compute(self, input):
        def dfs(node, is_dep, visited):
            if node in visited:
                return 0
            visited[node] = True

            return 1 + sum(map(lambda cx: dfs(cx[1], is_dep, visited), is_dep.get(node, [])))

        def dfs_transpose(node, has_dep, visited, cache):
            if node in visited:
                return cache[node]
            visited[node] = True

            cache[node] = sum(map(lambda cx: cx[0] + cx[0] * dfs_transpose(cx[1],
                                                                           has_dep, visited, cache), has_dep.get(node, [])))
            return cache[node]

        start = 'shiny gold'
        is_dep, has_dep = self.build_graph(input)

        cnt_nodes = dfs(start, is_dep, {}) - 1  # don't count start
        cnt_deps = dfs_transpose(start, has_dep, {}, {})

        return (cnt_nodes, cnt_deps)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        input = self.read()
        self.print(self.compute(input))


Task().solve()
