def gcd( x, y ):
    if y == 0:
        return x
    else:
        return gcd(y,x % y)
g = int(input("please"))
i = int(input("please"))

print(gcd( g, i ))