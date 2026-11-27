// ChatGPT GPT-6.2, under hayalows; 2026-11-27.
// Independent compact exact scan for OEIS A135508.
// g++ -O3 -std=c++17 a135508_scan_v2.cpp -o scan && ./scan 100000000
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;
int main(int argc,char**argv){
 const uint32_t N=argc>1?stoul(argv[1]):50000000;
 if(N<500||N>1000000000u)return 2;
 vector<uint16_t> spf(N+3,0); vector<uint8_t> stock(N+3,0);
 for(uint32_t p=2;uint64_t(p)*p<=N+2;++p) if(!spf[p])
  for(uint64_t j=uint64_t(p)*p;j<=N+2;j+=p) if(!spf[j])spf[j]=p;
 auto prime=[&](uint32_t n){return n>=2&&!spf[n];};
 auto factor=[&](uint32_t n)->uint32_t{return spf[n]?spf[n]:n;};
 uint64_t eligible=0, failures=0, composite=0, twin=0, twin_active=0, ones=0, direct=0;
 uint32_t first_composite=0,first_failure=0,first_twin_active=0;
 cpp_int x=1;
 for(uint32_t n=2;n<=N;++n){
  uint32_t r=n,c=1;
  while(r>1){uint32_t p=factor(r);unsigned e=0;do{r/=p;++e;}while(r%p==0);for(unsigned k=stock[p];k<e;++k)c*=p;}
  if(n<=500){uint32_t rem=(x%n).convert_to<uint32_t>(); uint32_t a=n,b=rem;while(b){uint32_t t=a%b;a=b;b=t;}if(c!=n/a){cerr<<"direct mismatch "<<n<<'\n';return 1;}x*=c+2;++direct;}
  if(c==1)++ones;else if(!prime(c)){++composite;if(!first_composite)first_composite=n;}
  if(prime(n)){if(n>=4&&prime(n-2)){++twin;if(c==n){++twin_active;if(!first_twin_active)first_twin_active=n;}}else{++eligible;if(c!=n){++failures;if(!first_failure)first_failure=n;}}}
  r=c+2;while(r>1){uint32_t p=factor(r);if(stock[p]<32)++stock[p];r/=p;}
  if(n==10000000||n==N)cout<<"N="<<n<<" direct="<<direct<<" eligible="<<eligible<<" failures="<<failures<<" first_failure="<<first_failure<<" composite="<<composite<<" first_composite="<<first_composite<<" twin_upper="<<twin<<" twin_active="<<twin_active<<" first_twin_active="<<first_twin_active<<" ones="<<ones<<endl;
 }
}
