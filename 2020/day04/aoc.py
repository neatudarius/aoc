import math
import re
import sys


class Task:
    def read(self, file='in'):
        with open(file, 'r') as f:
            lines = f.readlines()
        if lines[-1] != '\n':
            lines.append('\n')

        passwords = []
        while len(lines) > 0:
            while len(lines) > 0 and lines[0] == '\n':
                lines = lines[1:]

            password = ""
            while lines[0] != '\n':
                password = '{} {} '.format(password, lines[0].strip())
                lines = lines[1:]
            lines = lines[1:]  # remove blank line

            passwords.append(password)

        return passwords

    def match(self, password, regex):
        return re.search(regex, password) is not None

    def compute(self, ps):
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

        cnt1 = cnt2 = 0
        for p in ps:
            flag1 = flag2 = True
            for r in rs:
                if not self.match(p, r[0:3]):
                    flag1 = flag2 = False
                elif not self.match(p, '{}\s\s*'.format(r)):
                    flag2 = False

            cnt1 += int(flag1)
            cnt2 += int(flag2)

        return (cnt1, cnt2)

    def print(self, result):
        print(result)

    def solve(self):
        ps = self.read()
        self.print(self.compute(ps))


Task().solve()
