// Independent verifier: no Miller-Rabin; trial division by independently sieved primes.
#include <cstdint>
#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>
#include <string>
#include <chrono>
using namespace std; using U=uint64_t;
int main(int argc,char**argv){if(argc!=3)return 2;U B=stoull(argv[1]);if(B<25||B>10000000000000000ULL)return 2;U R=sqrtl(B);while((R+1)*(R+1)<=B)++R;while(R*R>B)--R;vector<bool> is(R+1,true);is[0]=is[1]=false;for(U p=2;p*p<=R;++p)if(is[p])for(U j=p*p;j<=R;j+=p)is[j]=false;vector<uint32_t> small;for(U p=2;p<=R;++p)if(is[p])small.push_back(p);ifstream f(argv[2]);string head;if(!getline(f,head)||head!="p,k,q,deadline")return 3;U count=0,pc=0,maxq=0;auto t=chrono::steady_clock::now();for(U p=5;p<=R;++p)if(is[p]){++pc;U lim=p*p,prev=0;for(U k=1;;++k){U a,b,q,d;char x,y,z;if(!(f>>a>>x>>b>>y>>q>>z>>d)||x!=','||y!=','||z!=','||a!=p||b!=k||d!=lim||q<=5||q>=lim||q<=prev||q%3!=2||(q+2)%p){cerr<<"bad row p="<<p<<" k="<<k<<endl;return 4;}if(q>R*R)return 5;for(uint32_t r:small){if(U(r)*r>q)break;if(q%r==0){cerr<<"composite q="<<q<<endl;return 6;}}prev=q;++count;if(q>maxq)maxq=q;if(lim>B/p)break;lim*=p;}}string rest;if(f>>rest)return 7;cout<<"VERIFIED B="<<B<<" primes="<<pc<<" witnesses="<<count<<" max_q="<<maxq<<" seconds="<<chrono::duration<double>(chrono::steady_clock::now()-t).count()<<endl;}
