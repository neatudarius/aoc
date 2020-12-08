import math
import sys
import copy


class Task:
    def read(self, file='in'):
        return [(line.strip().split(' ')[0], int(line.strip().split(' ')[1])) for line in open(file).read().strip().split('\n')]

    def compute(self, instructions):
        def execute(instruction, pc, acc):
            (i, offset) = instruction
            if i == 'nop':
                return pc + 1, acc
            elif i == 'acc':
                return pc + 1, acc + offset
            elif i == 'jmp':
                return pc + offset, acc
            else:
                assert(False)

        def run_code(instructions):
            visited = [False] * len(instructions)
            acc = 0
            pc = 0
            while pc < len(instructions) and not visited[pc]:
                visited[pc] = True
                pc, acc = execute(instructions[pc], pc, acc)

            return (pc, acc)

        _, acc1 = run_code(instructions)

        for i in range(len(instructions)):
            new_instructions = copy.deepcopy(instructions)

            (instr, acc) = instructions[i]
            not_instr = 'nop' if instr == 'jmp' else 'jmp'
            if instr in ['nop', 'jmp']:
                new_instructions[i] = (not_instr, acc1)
            else:
                continue

            pc, acc2_tmp = run_code(new_instructions)
            if pc == len(instructions):
                acc2 = acc2_tmp

        return (acc1, acc2)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        v = self.read()
        self.print(self.compute(v))


Task().solve()
