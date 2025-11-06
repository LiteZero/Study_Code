#include <stdio.h>
#include <stdlib.h>

// 队列结构体定义
typedef struct {
    int *data;   // 存储队列元素
    int size;    // 当前元素数量
    int capacity;// 队列容量
} Queue;

// 初始化队列
Queue* initQueue(int capacity) {
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->data = (int*)malloc(sizeof(int) * capacity);
    q->size = 0;
    q->capacity = capacity;
    return q;
}

// 查找元素在队列中的索引（不存在返回-1）
int findIndex(Queue *q, int v) {
    for (int i = 0; i < q->size; i++) {
        if (q->data[i] == v) {
            return i;
        }
    }
    return -1;
}

// 从队列中移除指定索引的元素
void removeAtIndex(Queue *q, int idx) {
    if (idx < 0 || idx >= q->size) return;
    // 元素前移覆盖
    for (int i = idx; i < q->size - 1; i++) {
        q->data[i] = q->data[i + 1];
    }
    q->size--;
}

// 向队列首部插入元素
void insertFront(Queue *q, int v) {
    // 元素后移腾出首位
    for (int i = q->size; i > 0; i--) {
        q->data[i] = q->data[i - 1];
    }
    q->data[0] = v;
    q->size++;
}

// 移除队列尾部元素并返回其值（空队列返回-1）
int removeTail(Queue *q) {
    if (q->size == 0) return -1;
    int val = q->data[q->size - 1];
    q->size--;
    return val;
}

int main() {
    int n1, n2, m;
    // 读取输入参数
    scanf("%d %d", &n1, &n2);
    scanf("%d", &m);
    int *vs = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d", &vs[i]);
    }

    // 初始化热队列q1和冷队列q2
    Queue *q1 = initQueue(n1);
    Queue *q2 = initQueue(n2);

    // 处理每个访问元素
    for (int i = 0; i < m; i++) {
        int v = vs[i];
        int idx1 = findIndex(q1, v);
        int idx2 = findIndex(q2, v);
        int in_q1 = (idx1 != -1);
        int in_q2 = (idx2 != -1);

        if (!in_q1 && !in_q2) {
            // 不在任何队列，插入q2首部
            insertFront(q2, v);
            // 若超过容量，淘汰尾部
            if (q2->size > q2->capacity) {
                removeTail(q2);
            }
        } else {
            if (in_q1) {
                // 在q1中，移到首部
                removeAtIndex(q1, idx1);
                insertFront(q1, v);
                // 检查容量，超则淘汰尾部并尝试移到q2
                if (q1->size > q1->capacity) {
                    int removed = removeTail(q1);
                    if (q2->size < q2->capacity) {
                        insertFront(q2, removed);
                    }
                }
            } else {
                // 在q2中，移到q1首部
                removeAtIndex(q2, idx2);
                insertFront(q1, v);
                // 检查容量，超则淘汰尾部并尝试移到q2
                if (q1->size > q1->capacity) {
                    int removed = removeTail(q1);
                    if (q2->size < q2->capacity) {
                        insertFront(q2, removed);
                    }
                }
            }
        }
    }

    // 输出q1元素
    for (int i = 0; i < q1->size; i++) {
        if (i > 0) printf(" ");
        printf("%d", q1->data[i]);
    }
    printf("\n");

    // 输出q2元素
    for (int i = 0; i < q2->size; i++) {
        if (i > 0) printf(" ");
        printf("%d", q2->data[i]);
    }
    printf("\n");

    // 释放内存
    free(vs);
    free(q1->data);
    free(q1);
    free(q2->data);
    free(q2);
    return 0;
}