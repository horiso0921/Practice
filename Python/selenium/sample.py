from selenium import webdriver
from time import sleep
#ブラウザオープン
#Chromeを動かすドライバを読み込み
driver = webdriver.Chrome(r"C:\Users\crdjf\Desktop\Program\python\chromedriver.exe")
#URLを指定してWebページを開く
driver.get("https://google.co.jp")
# ID属性から検索用テキストボックスの要素を取得
text = driver.find_element_by_id("q")
# 文字列"selenium"をテキストボックスに入力
text.send_keys("selenium")
"""
# 検索用ボタンにはID属性がないのでname属性から取得し
btn = driver.find_element_by_name("btnK")
# 対象をクリック！
btn.click() 
"""