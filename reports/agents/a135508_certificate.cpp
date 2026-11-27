// ChatGPT GPT-6.2 / hayalows. Finite first-counterexample certificate.
// Build: g++ -O3 -std=c++17 a135508_certificate.cpp -o cert
// ./cert 1000000000000 [witnesses.csv]
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <chrono>
#include <algorithm>
using namespace std; using u64=uint64_t; using u128=__uint128_t;
u64 powmod(u64 a,u64 d,u64 n){u64 v=1;while(d){if(d&1)v=u128(v)*a%n;a=u128(a)*a%n;d>>=1;}return v;}
// Deterministic for all uint64 inputs: seven standard Miller-Rabin bases.
bool prime(u64 n){if(n<2)return false;for(u64 p:{2,3,5,7,11,13,17,19,23,29,31,37}){if(n%p==0)return n==p;}u64 d=n-1;int s=0;while(!(d&1)){d>>=1;++s;}for(u64 a:{2ULL,325ULL,9375ULL,28178ULL,450775ULL,9780504ULL,1795265022ULL}){if(a%n==0)continue;u64 x=powmod(a%n,d,n);if(x==1||x==n-1)continue;bool ok=false;for(int j=1;j<s;++j){x=u128(x)*x%n;if(x==n-1){ok=true;break;}}if(!ok)return false;}return true;}
int main(int argc,char**argv){u64 B=argc>1?stoull(argv[1]):1000000000000ULL;if(B<25||B>10000000000000000ULL)return 2;u64 R=sqrtl(B);while((R+1)*(R+1)<=B)++R;while(R*R>B)--R;vector<bool> composite(R+1);for(u64 p=2;p*p<=R;++p)if(!composite[p])for(u64 j=p*p;j<=R;j+=p)composite[j]=true;ofstream csv;if(argc>2){csv.open(argv[2]);if(!csv)return 3;csv<<"p,k,q,deadline\n";}u64 pc=0,wc=0,tries=0,maxq=0,maxm=0,maxp=0,failures=0;auto start=chrono::steady_clock::now();for(u64 p=5;p<=R;p+=2)if(!composite[p]){++pc;u64 m=p%3==1?1:5;u64 deadline=p*p;for(u64 k=1;;++k){bool found=false;while(u128(m)*p-2<deadline){u64 q=m*p-2,used=m;m+=6;++tries;if(q>5&&prime(q)){// q=2 mod 3 and q-2>3, so q-2 composite.
 if(q%3!=2||(q+2)%p){cerr<<"internal error";return 4;}++wc;if(q>maxq)maxq=q;if(used>maxm){maxm=used;maxp=p;}if(csv)csv<<p<<','<<k<<','<<q<<','<<deadline<<'\n';found=true;break;}}
 if(!found){cerr<<"FAIL p="<<p<<" k="<<k<<" deadline="<<deadline<<endl;++failures;break;}if(deadline>B/p)break;deadline*=p;}}
 cout<<"B="<<B<<" root="<<R<<" primes_ge_5="<<pc<<" witnesses="<<wc<<" trials="<<tries<<" max_q="<<maxq<<" max_multiplier="<<maxm<<" multiplier_at_p="<<maxp<<" failures="<<failures<<" seconds="<<chrono::duration<double>(chrono::steady_clock::now()-start).count()<<endl;return failures?1:0;}
