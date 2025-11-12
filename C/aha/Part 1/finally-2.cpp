#include<iostream>
#include<algorithm>
using namespace std;
int main(){
int n,ntp,a[1000];
cin>>n;
ntp=n;
for(int i=0;i<n;i++){cin>>a[i];}
sort(a,a+n);
for(int i=1;i<=n;i++){
    if(a[i]==a[i-1]){ntp--;}
}
cout<<ntp<<endl;
for(int i=1;i<=n;i++){
    if(a[i]!=a[i-1]){cout<<a[i-1]<<" ";}
}
}