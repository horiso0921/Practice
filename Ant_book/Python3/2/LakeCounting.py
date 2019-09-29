"""POJ No.2386"""


def dfs(n,m,N,M,CHECK):
    X = [-1, -1, -1, 0, 0, 1, 1, 1]
    Y = [-1, 0, 1, -1, 1, -1, 0, 1]
    if(0 <= n and n < N and 0 <= m and m < M):
        if(CHECK[n][m] and feald[n][m] == "W"):
            CHECK[n][m] = 0
            for i in range(8):
                dfs(n+Y[i], m+X[i], N, M, CHECK)

N, M = map(int, input().split())
feald = [input() for i in range(N)]
CHECK = [[1 for i in range(M)]for j in range(N)]
NONE = []
ans = 0

for n in range(N):
    for m in range(M):
        if(CHECK[n][m] and feald[n][m] == "W"):
            dfs(n,m,N,M,CHECK)
            ans += 1

"""解答"""
def dfs(n,m,N,M):
    X = [-1, -1, -1, 0, 0, 1, 1, 1]
    Y = [-1, 0, 1, -1, 1, -1, 0, 1]
    if(0 <= n and n < N and 0 <= m and m < M):
        if(feald[n][m] == "W"):
            feald[n][m] = '.'
            for i in range(8):
                dfs(n+Y[i], m+X[i], N, M)

N, M = map(int, input().split())
feald = [list(input()) for i in range(N)]
NONE = []
ans = 0

for n in range(N):
    for m in range(M):
        if(feald[n][m] == "W"):
            dfs(n,m,N,M)
            ans += 1

print(ans)