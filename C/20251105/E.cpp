// 我们将含有不少于 6 个 6 的数视为一个好数。例如 666666, 162636465666 是好数，12366666 不是好数。 
// 给定 n 个正整数 ai，你可以把这些数分成若干组拼起来，每组内的数可以 按任意顺序拼，但一组最多只能有 3 个数。求最多可以得到多少个好数。
#include<iostream>
#include<vector>
using namespace std;
// 提取数字n的各位，逆序存入b（如123 -> 3,2,1）
void add(int n, vector<int>& b) {  
    if (n == 0) { // 特殊处理n=0的情况（避免0被跳过）
        b.push_back(0);
        return;
    }
    int t;
    while (n != 0) {
        t = n % 10;
        b.push_back(t);
        n = n / 10;
    }
}
int main() {
    int n, c;
    cin >> n;
    vector<int> b;         // 存储所有提取的数字位（逆序）
    vector<int> groups;    // 存储每组拼接后的结果
    for (int i = 0; i < n; i++) {
        cin >> c;
        // 步骤1：记录当前组的起始索引（处理前b的长度）
        int start = b.size();
        // 步骤2：提取当前数字c的各位，存入b
        add(c, b);
        // 步骤3：记录当前组的结束索引（处理后b的长度，不含）
        int end = b.size();
        // 步骤4：拼接当前组的数字（反转逆序，恢复原数字）
        int result = 0;
        // 遍历组内元素：从end-1到start（因为存储的是逆序，需反向拼接）
        for (int j = end - 1; j >= start; j--) {
            result = result * 10 + b[j]; // 核心拼接逻辑：如3,2,1 -> 1*100 + 2*10 + 3 = 123
        }
        re
    }
    return 0;
}