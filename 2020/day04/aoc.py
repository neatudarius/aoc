import math
import re
import sys


class Task:
    def read(self, file='in'):
        return [p.replace('\n', ' ') + ' ' for p in open(file).read().split('\n\n')]

    def compute(self, ps):
        def match(password, regex):
            return re.search(regex, password) is not None

        rs = [
            r"byr:((19[2-9][0-9])|(200[0-2]))",
            r"iyr:(20(1[0-9])|(2020))",
            r"eyr:(20(2[0-9])|(2030))",
            r"hgt:((((1[5-8][0-9])|(19[0-3]))cm)|(((59)|(6[0-9])|(7[0-6]))in))",
            r"hcl:#[0-9a-f]{6}",
            r"ecl:((amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth))",
            r"pid:[0-9]{9}",
            # "cid:" # optional
        ]

        cnt_exist = sum(
            map(lambda p: all(map(lambda r: match(p, r[0:3]), rs)),
                ps))

        cnt_valid = sum(
            map(lambda p: all(map(lambda r: match(p, '{}([ ]|$)'.format(r)), rs)),
                ps))

        return (cnt_exist, cnt_valid)

    def print(self, result):
        print('{}\n{}\n'.format(result[0], result[1]))

    def solve(self):
        ps = self.read()
        self.print(self.compute(ps))


Task().solve()
