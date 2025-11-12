#include <iostream>
using namespace std;

// 冒泡排序函数
void bubbleSort(int arr[], int n) {
    // 外层循环控制排序轮数
    for (int i = 0; i < n - 1; i++) {
        // 内层循环比较相邻元素并交换
        for (int j = 0; j < n - i - 1; j++) {
            // 如果前面的元素大于后面的元素，则交换它们
            if (arr[j] > arr[j + 1]) {
                // 交换两个元素
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

// 打印数组函数
void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

int main() {
    // 测试数组
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);
    
    cout << "原始数组: ";
    printArray(arr, n);
    
    // 调用冒泡排序
    bubbleSort(arr, n);
    
    cout << "排序后数组: ";
    printArray(arr, n);
    
    return 0;
}