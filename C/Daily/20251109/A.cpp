#include <iostream>
using namespace std;
int main()
{
  double yuanjia[6]={100,689,599,373,300,99};
  double xianjia[6]={49,199,299,188,255,1688};
  //0.49 0.28 0.49 0.504 0.85 17
  double zhe;
  int a=0;
  for(int i=0;i<6;i++){
    zhe=xianjia[i]/yuanjia[i];
    if(zhe<0.5){a++;}
  }
  cout<<a;
  return 0;
}