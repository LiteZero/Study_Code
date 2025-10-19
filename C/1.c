#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_DIGITS 10005
#define RECURSION_BOUND 32  // 调大递归边界，减少递归深度
int recursion_count = 0;

// 大整数加法：a + b -> result
void bigIntAdd(int *a, int lenA, int *b, int lenB, int *result, int *resultLen) {
    int carry = 0;
    int maxLen = lenA > lenB ? lenA : lenB;
    int i;
    for (i = 0; i < maxLen || carry; i++) {
        int sum = carry;
        if (i < lenA) sum += a[i];
        if (i < lenB) sum += b[i];
        result[i] = sum % 10;
        carry = sum / 10;
    }
    *resultLen = i;
}

// 大整数减法：a - b -> result（假设 a >= b）
void bigIntSub(int *a, int lenA, int *b, int lenB, int *result, int *resultLen) {
    int borrow = 0;
    int i;
    for (i = 0; i < lenA; i++) {
        int diff = a[i] - borrow;
        if (i < lenB) diff -= b[i];
        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }
        result[i] = diff;
    }
    // 去除前导零
    while (*resultLen > 1 && result[*resultLen - 1] == 0) {
        (*resultLen)--;
    }
}

// 大整数移位：num 左移 n 位（乘以 10^n）
void bigIntShift(int *num, int len, int n, int *result, int *resultLen) {
    int i;
    for (i = len + n - 1; i >= n; i--) {
        result[i] = num[i - n];
    }
    for (i = 0; i < n; i++) {
        result[i] = 0;
    }
    *resultLen = len + n;
}

// 朴素乘法：a * b -> result
void naiveMultiply(int *a, int lenA, int *b, int lenB, int *result, int *resultLen) {
    int *temp = (int *)calloc(MAX_DIGITS, sizeof(int));
    int i, j;
    for (i = 0; i < lenA; i++) {
        int carry = 0;
        for (j = 0; j < lenB || carry; j++) {
            int mul = a[i] * (j < lenB ? b[j] : 0) + carry + temp[i + j];
            temp[i + j] = mul % 10;
            carry = mul / 10;
        }
    }
    *resultLen = lenA + lenB;
    while (*resultLen > 1 && temp[*resultLen - 1] == 0) {
        (*resultLen)--;
    }
    memcpy(result, temp, sizeof(int) * (*resultLen));
    free(temp);
}

// Karatsuba 乘法（完全动态分配）
void karatsubaMultiply(int *a, int lenA, int *b, int lenB, int *result, int *resultLen) {
    recursion_count++;
    // 如果有一个数为 0，结果为 0
    if ((lenA == 1 && a[0] == 0) || (lenB == 1 && b[0] == 0)) {
        result[0] = 0;
        *resultLen = 1;
        return;
    }
    // 递归边界，使用朴素乘法
    if (lenA <= RECURSION_BOUND || lenB <= RECURSION_BOUND) {
        naiveMultiply(a, lenA, b, lenB, result, resultLen);
        return;
    }
    int m = (lenA < lenB ? lenA : lenB) / 2;
    // 动态分配高低位数组
    int *aHigh = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *aLow = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *bHigh = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *bLow = (int *)calloc(MAX_DIGITS, sizeof(int));
    int lenAHigh, lenALow, lenBHigh, lenBLow;
    int i;
    // 划分 a 的高低位
    lenALow = lenA < m ? lenA : m;
    for (i = 0; i < lenALow; i++) {
        aLow[i] = a[i];
    }
    lenAHigh = lenA - lenALow;
    for (i = 0; i < lenAHigh; i++) {
        aHigh[i] = a[lenALow + i];
    }
    // 划分 b 的高低位
    lenBLow = lenB < m ? lenB : m;
    for (i = 0; i < lenBLow; i++) {
        bLow[i] = b[i];
    }
    lenBHigh = lenB - lenBLow;
    for (i = 0; i < lenBHigh; i++) {
        bHigh[i] = b[lenBLow + i];
    }
    // 动态分配中间结果数组
    int *ac = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *bd = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *aPlusB = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *cPlusD = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *abcd = (int *)calloc(MAX_DIGITS, sizeof(int));
    int lenAC, lenBD, lenAPlusB, lenCPlusD, lenABCD;
    // 计算 ac = aHigh * bHigh
    karatsubaMultiply(aHigh, lenAHigh, bHigh, lenBHigh, ac, &lenAC);
    // 计算 bd = aLow * bLow
    karatsubaMultiply(aLow, lenALow, bLow, lenBLow, bd, &lenBD);
    // 计算 a + b
    bigIntAdd(aHigh, lenAHigh, aLow, lenALow, aPlusB, &lenAPlusB);
    // 计算 c + d
    bigIntAdd(bHigh, lenBHigh, bLow, lenBLow, cPlusD, &lenCPlusD);
    // 计算 (a + b) * (c + d)
    karatsubaMultiply(aPlusB, lenAPlusB, cPlusD, lenCPlusD, abcd, &lenABCD);
    // 计算 abcd - ac - bd 得到 a*d + b*c
    int *adPlusBc = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *temp1 = (int *)calloc(MAX_DIGITS, sizeof(int));
    int lenTemp1, lenADPlusBc;
    bigIntSub(abcd, lenABCD, ac, lenAC, temp1, &lenTemp1);
    bigIntSub(temp1, lenTemp1, bd, lenBD, adPlusBc, &lenADPlusBc);
    // 移位操作
    int *acShifted = (int *)calloc(MAX_DIGITS, sizeof(int));
    int *adPlusBcShifted = (int *)calloc(MAX_DIGITS, sizeof(int));
    int lenACShifted, lenADPlusBcShifted;
    bigIntShift(ac, lenAC, 2 * m, acShifted, &lenACShifted);
    bigIntShift(adPlusBc, lenADPlusBc, m, adPlusBcShifted, &lenADPlusBcShifted);
    // 合并结果
    int *temp2 = (int *)calloc(MAX_DIGITS, sizeof(int));
    int lenTemp2;
    bigIntAdd(acShifted, lenACShifted, adPlusBcShifted, lenADPlusBcShifted, temp2, &lenTemp2);
    bigIntAdd(temp2, lenTemp2, bd, lenBD, result, resultLen);
    // 释放动态分配的内存
    free(aHigh); free(aLow); free(bHigh); free(bLow);
    free(ac); free(bd); free(aPlusB); free(cPlusD); free(abcd);
    free(adPlusBc); free(temp1); free(acShifted); free(adPlusBcShifted);
    free(temp2);
}

// 生成指定位数的随机大整数
void generateRandomBigInt(int *num, int *len, int digits) {
    int i;
    // 第一位不能为 0
    num[0] = rand() % 9 + 1;
    for (i = 1; i < digits; i++) {
        num[i] = rand() % 10;
    }
    *len = digits;
}

// 打印大整数的片段
void printBigIntSegment(int *num, int len, int start, int count) {
    int end = start + count;
    if (end > len) {
        end = len;
    }
    for (int i = end - 1; i >= start && i >= 0; i--) {
        printf("%d", num[i]);
    }
}

int main() {
    srand((unsigned int)time(NULL));
    int testSizes[] = {100, 1000, 10000};
    int numSizes = sizeof(testSizes) / sizeof(testSizes[0]);
    for (int i = 0; i < numSizes; i++) {
        int digits = testSizes[i];
        printf("测试 %d 位大整数乘法：\n", digits);
        for (int j = 0; j < 3; j++) {
            int *a = (int *)calloc(MAX_DIGITS, sizeof(int));
            int *b = (int *)calloc(MAX_DIGITS, sizeof(int));
            int *result = (int *)calloc(MAX_DIGITS, sizeof(int));
            int *naiveResult = (int *)calloc(MAX_DIGITS, sizeof(int));
            int lenA, lenB, lenResult, lenNaiveResult;
            generateRandomBigInt(a, &lenA, digits);
            generateRandomBigInt(b, &lenB, digits);
            recursion_count = 0;
            clock_t start = clock();
            karatsubaMultiply(a, lenA, b, lenB, result, &lenResult);
            clock_t end = clock();
            double timeSpent = (double)(end - start) / CLOCKS_PER_SEC * 1000;
            naiveMultiply(a, lenA, b, lenB, naiveResult, &lenNaiveResult);
            // 验证结果正确性
            int correct = 1;
            if (lenResult != lenNaiveResult) {
                correct = 0;
            } else {
                for (int k = 0; k < lenResult; k++) {
                    if (result[k] != naiveResult[k]) {
                        correct = 0;
                        break;
                    }
                }
            }
            printf("  测试 %d：\n", j + 1);
            printf("    输入大整数 A 片段（前 10 位 + 后 10 位）：");
            printBigIntSegment(a, lenA, 0, 10);
            printf(" + ");
            printBigIntSegment(a, lenA, lenA - 10, 10);
            printf("\n");
            printf("    输入大整数 B 片段（前 10 位 + 后 10 位）：");
            printBigIntSegment(b, lenB, 0, 10);
            printf(" + ");
            printBigIntSegment(b, lenB, lenB - 10, 10);
            printf("\n");
            printf("    乘积片段（前 20 位 + 后 20 位）：");
            printBigIntSegment(result, lenResult, 0, 20);
            printf(" + ");
            printBigIntSegment(result, lenResult, lenResult - 20, 20);
            printf("\n");
            printf("    递归次数：%d\n", recursion_count);
            printf("    执行时间：%.2f ms\n", timeSpent);
            printf("    结果正确性：%s\n", correct ? "正确" : "错误");
            // 释放内存
            free(a); free(b); free(result); free(naiveResult);
        }
    }
    return 0;
}