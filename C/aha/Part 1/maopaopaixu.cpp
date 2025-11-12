// 将12 35 99 18 76这5个数进行从大到小的排序。
#include<iostream>
#include<vector>//vector是更智能的数组模型
using namespace std;
struct students{//自定义一个数据类型
    string name;
    int score;
};
int main(){
    int n;
    cin>>n;
    vector <students> student(n);//定义以n变量为数组成员数的students数组student
    for(int i=0;i<n;i++)
    {
        cin>>student[i].name;
        cin>>student[i].score;
    }
    for(int i=n-1;i>=0;i--){//为什么是<n-1? 当第一次比较进行到j[n-2](第n-1位)和j[n-1](第n位)后，j[n-1](第n位)不能和不存在的j[n](第n+1位)比较
        for(int j=0;j<i;j++){
            if(student[j].score<student[j+1].score){//如果说前一个数字小于后一个数字时进行交换
            int temp;temp=student[j].score;student[j].score=student[j+1].score;student[j+1].score=temp;
            string tempn;tempn=student[j].name;student[j].name=student[j+1].name;student[j+1].name=tempn;
        }
        }
    }
    for(int i=0;i<n;i++)
    {
        cout<<student[i].name<<" "<<student[i].score<<endl;
    }
}