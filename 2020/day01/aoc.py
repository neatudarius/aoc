def read_vector(file='in'):
    with open(file, 'r') as f:
        v = [int(line) for line in f.readlines()]
    return v


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


v = read_vector()
print(solve2(v))
print(solve3(v))
