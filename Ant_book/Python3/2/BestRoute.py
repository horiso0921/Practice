"""迷路の最短経路"""

def bfs(n,m,MAP, CHECK):
    X = [0,1,0,-1]
    Y = [-1,0,1,0]
    p = []
    p.append([n,m])
    CHECK[n][m] = 0
    while p:
        y, x = p.pop(0) 
        for i in range(4):
            m = x+X[i]
            n = y+Y[i]
            if(0 <= n and n < N and 0 <= m and m < M):
                if(MAP[n][m] == "." and CHECK[n][m] == 100000):
                    CHECK[n][m] = CHECK[y][x] + 1
                    p.append([n,m])
                elif(MAP[n][m] == "G"):
                    return CHECK[y][x] + 1




N,M = map(int, input().split())

MAP = [input() for i in range(N)]
CHECK = [[100000 for i in range(M)] for k in range(N)]
for i in range(N):
    for j in range(M):
        if(MAP[i][j] == 'S'):
            CHECK[i][j] = 0
            print(bfs(i,j,MAP, CHECK))

