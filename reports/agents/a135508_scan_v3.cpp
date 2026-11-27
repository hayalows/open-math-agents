// ChatGPT GPT-6.2 / hayalows, 2026-11-27. Exact bounded scan, not proof.
// g++ -O3 -std=c++17 a135508_scan_v3.cpp -o scan && ./scan 1000000000
#include <cstdint>
#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <chrono>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;
using boost::multiprecision::cpp_int;
int main(int argc,char**argv){
 uint64_t arg=argc>1?stoull(argv[1]):1000000000ULL;
 if(arg<500||arg>4294967293ULL)return 2;
 uint32_t N=arg; auto t0=chrono::steady_clock::now();
 vector<uint16_t> spf(size_t(N/2)+2); vector<uint8_t> stock(size_t(N/2)+2); uint8_t stock2=0;
 for(uint32_t p=3;uint64_t(p)*p<=uint64_t(N)+2;p+=2) if(!spf[p/2])
  for(uint64_t j=uint64_t(p)*p;j<=uint64_t(N)+2;j+=2ULL*p) if(!spf[j/2])spf[j/2]=p;
 cerr<<"sieve seconds="<<chrono::duration<double>(chrono::steady_clock::now()-t0).count()<<endl;
 auto prime=[&](uint32_t n){return n==2||(n>2&&(n&1)&&!spf[n/2]);};
 auto factor=[&](uint32_t n)->uint32_t{return !(n&1)?2:spf[n/2]?spf[n/2]:n;};
 auto val=[&](uint32_t p)->uint8_t&{return p==2?stock2:stock[p/2];};
 uint64_t eligible=0,failures=0,composite=0,twin=0,twin_active=0,ones=0,direct=0;uint32_t first_composite=0,first_failure=0,first_twin_active=0;
 cpp_int x=1;
 for(uint64_t nn=2;nn<=N;++nn){uint32_t n=nn;
  uint32_t r=n,c=1;
  while(r>1){uint32_t p=factor(r);unsigned e=0;do{r/=p;++e;}while(r%p==0);for(unsigned k=val(p);k<e;++k)c*=p;}
  if(n<=500){uint32_t rem=(x%n).convert_to<uint32_t>();if(c!=n/gcd(n,rem)){cerr<<"direct mismatch "<<n<<endl;return 1;}x*=c+2;++direct;}
  if(c==1)++ones;else if(!prime(c)){++composite;if(!first_composite)first_composite=n;}
  if(prime(n)){if(n>=4&&prime(n-2)){++twin;if(c==n){++twin_active;if(!first_twin_active)first_twin_active=n;}}else{++eligible;if(c!=n){++failures;if(!first_failure)first_failure=n;}}}
  r=c+2;while(r>1){uint32_t p=factor(r);auto &s=val(p);if(s<32)++s;r/=p;}
  if(n==10000000||n%100000000==0||n==N)cout<<"N="<<n<<" direct="<<direct<<" eligible="<<eligible<<" failures="<<failures<<" first_failure="<<first_failure<<" composite="<<composite<<" first_composite="<<first_composite<<" twin_upper="<<twin<<" twin_active="<<twin_active<<" first_twin_active="<<first_twin_active<<" ones="<<ones<<" seconds="<<chrono::duration<double>(chrono::steady_clock::now()-t0).count()<<endl;
 }
}
