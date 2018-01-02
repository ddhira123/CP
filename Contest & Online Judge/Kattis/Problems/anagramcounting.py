from sys import stdin

fact = [1]
for i in range(1, 101):
    fact.append(fact[i-1] * i)

for line in stdin:
    occ = {}

    for ch in line[:-1]:
        if ch in occ.keys():
            occ[ch] = occ[ch] + 1
        else:
            occ[ch] = 1

    ret = fact[len(line)-1]
    for ch in occ.keys():
        ret //= fact[occ[ch]]

    print(ret)
