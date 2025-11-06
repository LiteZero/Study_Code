// 在一条一维的直线上，存在着 n 台显示器和 n 个电源插座。老师给小蓝布置了个任务：
// 负责将每台显示器通过电源线与一个插座相连接（每个插座最多只能给一台显示器供电）；
// 同时，老师希望所消耗的电源线的长度尽可能的少， 请你帮小蓝计算下电源线的最小消耗长度为多少？ 
// 为了便于计算，你只需要考虑直线距离即可。
#include <stdio.h>
#include <stdlib.h>

// 比较函数，用于qsort排序long long类型的数组,使用贪心算法
int compare(const void *a, const void *b) {
    long long num1 = *(const long long *)a;
    long long num2 = *(const long long *)b;
    if (num1 < num2) return -1;
    else if (num1 > num2) return 1;
    else return 0;
}

int main() {
    long long int n;
    scanf("%lld", &n);
    long long int display[50000];
    long long int socket[50000];
    for (int i = 0; i < n; i++) {
        scanf("%lld", &display[i]);
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &socket[i]);
    }
    qsort(display, n, sizeof(long long), compare);
// void qsort(void *base, size_t nmemb, size_t size, int (*compar)(const void *, const void *));
// qsort是C语言标准库当中的快速排序函数，参数如下：
// 1.void *base：排序数组的地址
// 2.size_t nmemb：数组中有效元素的总个数
// 3.size_t size：单个数组成员的所占空间
// 4.int (*compar)(const void *, const void *)：比较使用的函数指针
// qsort会把每个成员都放入到比较函数当中进行比对，返回-1则第一个指针所指向的数应该在第二个指针所指向的数之前，返回1则是在之后，返回0就相等，不影响结果
    qsort(socket, n, sizeof(long long), compare);
    long long int total_length = 0;
    for (int i = 0; i < n; i++) {
        long long int diff = display[i] - socket[i];
        if (diff < 0) {
            diff = -diff;
        }
        total_length += diff;
    }
    printf("%lld\n", total_length);
    return 0;
}