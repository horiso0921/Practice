
x = open('sample_auth_log1.txt','r')

from collections import Counter

y = x.read()

print("admin:" +str(y.count('user admin '))+"test:" +str(y.count(' user test '))+"user:" +str(y.count('user user ')))
