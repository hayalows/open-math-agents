// ChatGPT independent Floyd orbit scan; extends the A231830 research branch.
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstdlib>
using U=uint64_t; using W=__uint128_t;
U f(U x,U p){return (((x*x)%p)*((x+p-1)%p)+1)%p;}
int main(int argc,char**argv){U N=argc>1?std::stoull(argv[1]):1000000;if(N<5||N>5000000)return 2;std::vector<bool> c(N+1);for(U p=2;p*p<=N;p++)if(!c[p])for(U j=p*p;j<=N;j+=p)c[j]=true;U total=0,hits=0,steps=0,maxi=0;for(U p=5;p<=N;p+=4)if(!c[p]){++total;U x=5%p,y=f(x,p),i=1;while(x&&x!=1&&x!=y){x=f(x,p);y=f(f(y,p),p);++i;++steps;}if(x!=0&&y==0){while(x&&x!=1){x=f(x,p);++i;}}
if(x==0){++hits;U m=p*p,z=5%m;for(U j=1;j<i;++j)z=(W((z+m-1)%m)*z%m*z+1)%m;if(z%p||!z){std::cout<<"FAIL "<<p<<' '<<i<<' '<<z<<'\n';return 1;}if(i>maxi)maxi=i;std::cout<<p<<','<<i<<','<<z<<'\n';}}
std::cerr<<"N="<<N<<" eligible="<<total<<" hits="<<hits<<" maxindex="<<maxi<<" steps="<<steps<<"\n";}
