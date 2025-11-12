#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <tuple>
#include <algorithm>

// 定义结果常量
enum Result { LOSE, DRAW, WIN };

// 允许取球的集合
std::vector<int> allowed_takes;

// 记忆化存储，键是一个包含(剩余球数, 当前玩家, 先手奇偶, 后手奇偶)的元组
std::map<std::tuple<int, int, int, int>, Result> memo;

// 将对方的结果转换为当前玩家的结果
Result invert_result(Result res) {
    if (res == WIN) return LOSE;
    if (res == LOSE) return WIN;
    return DRAW; // DRAW的反转还是DRAW
}

// 递归函数，计算当前状态下的最优结果
Result dfs(int remaining, int current_player, int a_odd, int b_odd) {
    // 检查是否已经计算过该状态
    auto key = std::make_tuple(remaining, current_player, a_odd, b_odd);
    if (memo.find(key) != memo.end()) {
        return memo[key];
    }

    // 检查当前玩家是否有球可取
    bool can_take = false;
    for (int k : allowed_takes) {
        if (k <= remaining) {
            can_take = true;
            break;
        }
    }

    if (!can_take) {
        // 游戏结束，判断胜负
        if (current_player == 0) { // 先手回合结束
            if (a_odd == 1 && b_odd == 0) return memo[key] = WIN;
            if (a_odd == 0 && b_odd == 1) return memo[key] = LOSE;
            return memo[key] = DRAW;
        } else { // 后手回合结束
            if (b_odd == 1 && a_odd == 0) return memo[key] = WIN;
            if (b_odd == 0 && a_odd == 1) return memo[key] = LOSE;
            return memo[key] = DRAW;
        }
    }

    // 当前玩家尝试所有可能的取球方式
    Result best_result = LOSE; // 初始化为最差结果
    for (int k : allowed_takes) {
        if (k > remaining) continue;

        int new_remaining = remaining - k;
        int next_player = 1 - current_player;
        int new_a = a_odd;
        int new_b = b_odd;

        if (current_player == 0) {
            new_a = (a_odd + k) % 2;
        } else {
            new_b = (b_odd + k) % 2;
        }

        // 递归计算对手在新状态下的结果
        Result opponent_result = dfs(new_remaining, next_player, new_a, new_b);
        // 转换为当前玩家的结果
        Result current_result = invert_result(opponent_result);

        // 更新当前玩家的最优结果
        if (current_result > best_result) {
            best_result = current_result;
            // 如果已经找到必胜策略，可以提前退出循环
            if (best_result == WIN) {
                break;
            }
        }
    }

    return memo[key] = best_result;
}

int main() {
    int N;

    std::set<int> take_set; // 使用set自动去重
    int num;
    while (std::cin >> num) {
        if (num > 0) {
            take_set.insert(num);
        }
        // 检查是否为最后一个输入（按下回车）
        if (std::cin.peek() == '\n') {
            break;
        }
    }
    allowed_takes.assign(take_set.begin(), take_set.end());
    if (allowed_takes.empty()) {
        return 0;
    }
    
    Result initial_result = dfs(N, 0, 0, 0);

    if (initial_result == WIN) {
        std::cout << "先手一定能赢" << std::endl;
    } else {
        std::cout << "先手不一定能赢" << std::endl;
    }

    return 0;
}