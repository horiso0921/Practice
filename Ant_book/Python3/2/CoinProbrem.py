"""硬貨の問題"""

C = list(map(int, input().split()))
V = [1,5,10,50,100,500]
A = int(input())
i = 5
ANS = 0
while i != -1:
    if(A-V[i] >= 0 and C[i] > 0):
        A -= V[i]
        C[i] -= 1
        ANS += 1 
    else:
        i -= 1
print(ANS)

"""解答"""
C = list(map(int, input().split()))
V = [1,5,10,50,100,500]
A = int(input())
ANS = 0
for i in range(5):
    t = min(A/V[i], C[i])
    A -= t*V[i]
    ANS += t
print(ANS)