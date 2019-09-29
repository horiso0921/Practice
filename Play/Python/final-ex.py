
#アクセスを試みてきたIPアドレスとその出現回数の算出および表示
file = open("sample_auth_log2.txt","r")

import re

ipaddress = {}

for line in file:
	patt1 = r"(\d+\.\d+\.\d+\.\d+)"
	a = re.search(patt1,line)
	b = a.group()

	ipaddress.setdefault(b,0)
	ipaddress[b] += 1
print("-アクセスを試みてきたIPアドレスとその出現数-")

for i in ipaddress:
	print(i,":",ipaddress[i],"回")


#アクセスを試みてきたユーザー名とその出現数の算出と表示
file = open("sample_auth_log2.txt","r")

username = {}

for line in file:
	patt2 = r"(Invalid user )(\S+)"
	a = re.search(patt2,line)
	b = a.group(2)

	username.setdefault(b,0)
	username[b] += 1
print("-アクセスを試みてきたユーザー名とその出現数-")                

for i in username:
	print(i,":",username[i],"回")


#各日におけるアクセス数の合計の算出および表示
file = open("sample_auth_log2.txt","r")

per_date = {}

for line in file:
	patt3 = r"\D+\s\d+"
	a = re.search(patt3,line)
	b = a.group()
	
	per_date.setdefault(b,0)
	per_date[b] += 1
print("-各日におけるアクセス数の合計-")

for i in per_date:
	print(i,":",per_date[i],"回")


#毎時におけるアクセス数の合計の算出および表示
file = open("sample_auth_log2.txt","r")

per_hour = {}

for line in file:
	patt4 = r"(\d{2})(:\d{2}:\d{2})"
	a = re.search(patt4,line)
	b = a.group(1)
	
	per_hour.setdefault(b,0)
	per_hour[b] += 1
print("-毎時におけるアクセス数の合計-")

for i in sorted(per_hour):
        print(i,"時　:",per_hour[i],"回")

