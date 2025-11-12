#include <iostream>
using namespace std;

int main() {
    int T;
    cin >> T;
    while (T--) {
        int n;
        long long m; // 因为m可达10^9，需要用长整型防止溢出
        cin >> n >> m;
        long long total_steps = m * (m + 1) / 2; // 计算总移动步数
        long long pos = (1 + total_steps) % n;   // 计算最终位置
        if (pos == 0) {
            pos = n; // 模为0时，位置是n
        }
        cout << pos << endl;
    }
    return 0;
}