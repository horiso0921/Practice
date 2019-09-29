//三角形

#include <cstdio>
#include <algorithm>
#include <iostream>
#include <string>

#define MAX_N 100

using namespace std;

//入力
int n, a[MAX_N] = {2, 3, 4, 5, 10};

void solve() {
    int ans = 0; //答え

    //某を重複して選ばないようi < j < k となるようにしている
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            for (int k = j+1; k < n; k++) {
                int len = a[i] + a[j] + a[k];           //周長 
                int ma = max(a[i], max(a[j], a[k]));    //最も長い棒の長さ
                int rest = len - ma;

                if (ma < rest) { 
                    //三角形が作れるので答えを更新できれば更新
                    ans = max(ans, len);
                }
            }
        }
    }
    printf("%d\n", ans);
}
int main() {
    n = 5;
    solve();
    return 0;
}
