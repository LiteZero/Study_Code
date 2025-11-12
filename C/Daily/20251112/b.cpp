#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

// 函数：计算将字符串变成回文串至少需要删除的字符数
int minDeletionsToPalindrome(const std::string& s) {
    int n = s.length();
    // 创建一个 n x n 的 DP 表
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, 0));

    // 初始化：单个字符的最长回文子序列长度为 1
    for (int i = 0; i < n; ++i) {
        dp[i][i] = 1;
    }

    // l 是子串的长度，从 2 开始到 n
    for (int l = 2; l <= n; ++l) {
        // i 是子串的起始索引
        for (int i = 0; i <= n - l; ++i) {
            // j 是子串的结束索引
            int j = i + l - 1;

            if (s[i] == s[j]) {
                // 如果两端字符相等
                if (l == 2) {
                    dp[i][j] = 2;
                } else {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                }
            } else {
                // 如果两端字符不相等，取两种情况的最大值
                dp[i][j] = std::max(dp[i + 1][j], dp[i][j - 1]);
            }
        }
    }

    // 最长回文子序列的长度是 dp[0][n-1]
    // 至少需要删除的字符数 = 原字符串长度 - 最长回文子序列长度
    return n - dp[0][n - 1];
}

int main() {
    std::string s;
    std::cin >> s;
    int result = minDeletionsToPalindrome(s);
    std::cout << result;
    return 0;
}