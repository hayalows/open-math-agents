// Independent certificate verifier using the first seven prime bases.
// For n < 341550071728321, strong pseudoprime tests to 2,3,5,7,11,13,17 are deterministic.
#include <cstdint>
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <string>
#include <chrono>
using U=uint64_t; using W=__uint128_t;
constexpr U cutoff=341550071728321ULL;
U power(U b,U e,U m){U x=1;for(;e;e>>=1,b=W(b)*b%m)if(e&1)x=W(x)*b%m;return x;}
bool prime(U n){if(n<2||n>=cutoff)return false;for(U a:{2,3,5,7,11,13,17})if(n%a==0)return n==a;U d=n-1;int s=0;while(!(d&1)){d>>=1;++s;}for(U a:{2,3,5,7,11,13,17}){U x=power(a,d,n);if(x==1||x==n-1)continue;bool pass=false;for(int j=1;j<s;j++){x=W(x)*x%n;if(x==n-1){pass=true;break;}if(x==1)return false;}if(!pass)return false;}return true;}
int main(int argc,char**argv){if(argc!=3)return 2;U B=std::stoull(argv[1]);if(B<25||B>10000000000000000ULL)return 2;U R=sqrtl(B);while((R+1)*(R+1)<=B)++R;while(R*R>B)--R;std::vector<bool> composite(R+1);for(U p=2;p*p<=R;p++)if(!composite[p])for(U j=p*p;j<=R;j+=p)composite[j]=true;std::ifstream f(argv[2]);std::string line;if(!std::getline(f,line)||line!="p,k,q,deadline")return 3;U rows=0,pc=0,mx=0;auto t=std::chrono::steady_clock::now();for(U p=5;p<=R;p+=2)if(!composite[p]){++pc;U deadline=p*p,last=0;for(U k=1;;k++){U a,b,q,d;char c1,c2,c3;if(!(f>>a>>c1>>b>>c2>>q>>c3>>d)||c1!=','||c2!=','||c3!=','||a!=p||b!=k||d!=deadline||q<=5||q<=last||q>=deadline||q%3!=2||(q+2)%p||!prime(q)){std::cerr<<"FAIL p="<<p<<" k="<<k<<'\n';return 4;}last=q;++rows;if(q>mx)mx=q;if(deadline>B/p)break;deadline*=p;}}if(f>>line)return 5;std::cout<<"VERIFIED B="<<B<<" primes="<<pc<<" witnesses="<<rows<<" max_q="<<mx<<" seconds="<<std::chrono::duration<double>(std::chrono::steady_clock::now()-t).count()<<'\n';}
