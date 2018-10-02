a, b = [int(x) for x in input().split()]
if b == 1:
    if a % 2 == 1:
        print("0")
    else:
        print(a // 2)
else:
    if a % 4 == 2:
        print(1 + 2 * (a // 4))
    else:
        print("0")