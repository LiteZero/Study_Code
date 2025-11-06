// 小蓝是一名计算机专业的学生，最近他学习了《操作系统》、《数据结构》 等课程，他设计了一种名为 “冷热数据队列” 的数据结构，来对数据页进行管理。 
// 冷热数据队列 q 可以看做由两个子队列组成：长度为 n1 的热数据队列 q1 和长度为 n2 的冷数据队列 q2 。当我们需要访问某个数据页 p 时：
// 1）若 p 不在队列 q 中（即既不在 q1 中，也不在 q2 中），则加载数据页 p ，并插入到 q2 的首部。 
// 2）若 p 已经在队列 q 中，则将 p 移动至 q1 首部。 
// 3）当 q1 或 q2 队列容量不足时，会将其尾部的数据页淘汰出去。 
// 4）当 q1 已满，但 q2 未满时，从 q1 中淘汰出的数据页会移动到 q2 首部。
#include<stdio.h>
int findthing(int a,int b[],int total){
    for(int i=0;i<total;i++)
    {
        if(a==b[i]){return 1;}
    }
    return 0;
}
int main(){
    int n1,n2,m,v[10000];
    scanf("%d%d",&n1,&n2);
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&v[i]);
    }
    // 下面的代码是根据m动态给出数组成员的代码
    int *RUT = (int*)malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        scanf("%d", RUT[i]);
    }
    // 到此结束
    int *q1 = (int*)malloc(sizeof(int) * n1);
    int *q2 = (int*)malloc(sizeof(int) * n2);
    for(int i=0;i<m;i++)
    {
        if(findthing(RUT[i],q1,n1)&&findthing(RUT[i],q2,n2)){}
        else{
            
        }
    }
}