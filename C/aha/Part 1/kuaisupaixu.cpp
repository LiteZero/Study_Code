#include<iostream>
using namespace std;
void quickswitch(int left,int right,int a[]){
        if(left>=right) return;
        int start=left;
        int final=right;
        while(left<=right){
        while(a[right]>a[start]){
            right--;
        }
        while(a[left]<=a[start] && left!=right){
            left++;
        }
        if(left!=right){swap(a[left],a[right]);}
        else{swap(a[start],a[left]);break;}
    }
        quickswitch(start,left-1,a);
        quickswitch(right+1,final,a);
}
int main(){
    int a[1000],n;
    cin>>n;
    for(int i=0;i<n;i++){cin>>a[i];}
    quickswitch(0,n-1,a);
    for(int i=0;i<n;i++){cout<<a[i]<<" ";}
}