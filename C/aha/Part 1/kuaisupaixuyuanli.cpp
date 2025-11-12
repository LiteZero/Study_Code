#include<iostream>
using namespace std;
int main(){
    int a[10]={6,1,2,7,9,3,4,5,10,8};
    int left=0,right=9;
    for(int i=0;i<10;i++){cout<<a[i]<<" ";}
    cout<<endl;
    while(left<=right){
        while(a[right]>a[0]){
            right--;
        }
        while(a[left]<=a[0] && left!=right){
            left++;
        }
        if(left!=right){swap(a[left],a[right]);}
        else{swap(a[0],a[left]);break;}
    }
    for(int i=0;i<10;i++){cout<<a[i]<<" ";}
}