import bisect

n = int(input())
m = int(input())
a = list(map(int, input().split()))

a.sort()
kl = []

for i in range(n):
    for j in range(n):
        kl.append(a[i]*a[j])
kl.sort()
for i in range(n):
    for j in range(n):
        X = m-a[i]-a[j]
        k = 0
        l = n*n
        while (l-k >= 1):
            n = (k+l)//2
            print(n,l,k,kl[n])
            if(kl[n] == X): 
                print("YES")
                quit()
            elif (kl[n] < X):
                k = n+1
            else:
                print("A")
                l = n
print("NO")
