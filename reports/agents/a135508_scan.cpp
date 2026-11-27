// Exact valuation scan for OEIS A135508, no probabilistic primality.
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdint>
using namespace std;
int main(){
 const int N=10000000; vector<int>spf(N+3),v(N+3);
 for(int i=2;i<=N+2;++i) if(!spf[i]){
  spf[i]=i;
  if((int64_t)i*i<=N+2)
   for(int64_t j=(int64_t)i*i;j<=N+2;j+=i) if(!spf[j]) spf[j]=i;
 }
 long long checked=0;int first_comp=0;
 for(int n=2;n<=N;n++){
  int a=n,g=1;
  while(a>1){
   int p=spf[a],e=0;do{a/=p;++e;}while(a%p==0);
   for(int k=0;k<min(e,v[p]);k++)g*=p;
  }
  int m=n/g+2;
  if(n>=2&&spf[n]==n&&(n<4||spf[n-2]!=n-2)){
   ++checked;
   if(g!=1){cout<<"COUNTEREXAMPLE p="<<n<<" gcd="<<g<<endl;return 0;}
  }
  if(n/g>1&&spf[n/g]!=n/g&&!first_comp){
   first_comp=n;cout<<"first composite a="<<n/g<<" step="<<n<<endl;
  }
  while(m>1){int p=spf[m];++v[p];m/=p;}
 }
 cout<<"checked "<<checked<<" prime cases through "<<N<<" first composite a step="<<first_comp<<endl;
}
