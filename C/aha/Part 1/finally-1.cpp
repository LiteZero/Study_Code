#include<iostream>
using namespace std;
int main(){
    int n,a,b[1000],total=0;
    cin>>n;
    for(int i=0;i<1000;i++){b[i]=0;}
    for(int i=0;i<n;i++){
        cin>>a;
        b[a]=1;
    }
    for(int i=0;i<1000;i++){
        if(b[i]==1){total++;}
    }
    cout<<total<<endl;
    for(int i=0;i<1000;i++){
        if(b[i]==1){cout<<i<<" ";}
    }
}
