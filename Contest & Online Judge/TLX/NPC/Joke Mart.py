
p ,q ,r ,o = map(int, input().split())
sumAll = p + q + r + o
sisa = sumAll % 4
sisa *= 25
sumAll //= 4
ssisa = str(sisa)
if len(ssisa) == 1 :
	ssisa = ssisa + "0"
print ("Rp " + str(sumAll) + "," + ssisa)
