n, s = [int(x) for x in input().split()]
arr = []

for i in range(n):
    nama, val = input().split()
    val = int(val)
    arr.append([nama, val])

# print(arr)
arr = sorted(arr, key=lambda x:x[1])
# print(arr)

ans = []
for x in reversed(arr):
    if (s >= x[1]):
        ans.append(x[0])
        s -= x[1]

if s == 0:
    print(len(ans))
    for x in ans:
        print(x)
else:
    print("0")