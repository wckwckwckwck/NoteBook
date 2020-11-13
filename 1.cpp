#include<iostream>
#include<math.h>
using namespace std;

int main(){
    float s1=0,s2=0;
    long long x;
    cin>>x;
    for(int i=1;i<=x;i++){
        s1+=sqrt(x);
        s2+=1/sqrt(x);

    }
    float res=s1*s2/pow(x,2);
    cout<<res<<endl;
}