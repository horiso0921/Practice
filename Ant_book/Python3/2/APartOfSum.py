"""部分和"""

n = int(input())
a = list(map(int, input().split()))
k = int(input())
SUM = 0
def dfs(i,n,k,a, SUM):
    SUM += a[i]
    if(SUM == k):
        return True
    for j in range(i, n):
        if(dfs(j,n,k,a,SUM)):return True

for i in range(n):
    if(dfs(i,n,k,a,SUM)):
        print("YES")
        quit()
print("NO")

"""解答"""
def dfs(i,sum):
    if i == n :return sum == k

    if dfs(i + 1, sum):return True

    if dfs(i + 1, sum + a[i]): return True

    return False

if dfs(0,0): print("YES")
else:print("NO")