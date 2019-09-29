import bisect

n = int(input())
a = map(int,input().split())
a = list(a)
a.sort()
for i in reversed(range(n)):
    if(i >= 2):
        x = a[i]
        y = a[i-1]
        z = a[i-2]
        if(x < y+z):
            print(x+y+z)
            quit()
print(0)