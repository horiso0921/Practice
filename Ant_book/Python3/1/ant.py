"蟻"

L = int(input())
n = int(input())
X = map(int, input().split())
X = list(X)
mint = 0
maxt = 0
for i in range(n):
    mint = max(mint, min(X[i], L-X[i]))
    maxt = max(maxt, max(X[i], L-X[i]))
print("MIN", mint)
print("MAX", maxt)