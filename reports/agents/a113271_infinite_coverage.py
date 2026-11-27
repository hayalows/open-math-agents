# ChatGPT GPT-6.2 / hayalows, 2026-11-27. Extends Codex's affine residue lemma.
from math import lcm, isqrt
from fractions import Fraction
import numpy as np
PRIMES=(3,5,7,11,17,23,31,37,41,43,47,67,71,73,89,97)
START=5
def order2(m):
    assert m%2 and m>0
    if m==1: return 1
    a,k=2%m,1
    while a!=1: a,k=2*a%m,k+1
    return k
def residue(n,p,d):
    return sum(pow(2,((n-j)*pow(2,j,d))%d,p) for j in range(n+1))%p
def original(n,p):
    return sum(pow(pow(2,i,p),1<<(n-i),p) for i in range(n+1))%p
def classes(p):
    assert p>2 and all(p%j for j in range(2,isqrt(p)+1))
    d=order2(p); u=d; t=0
    while u%2==0: u//=2; t+=1
    Q=lcm(d,order2(u)); assert START+1>=t
    rules=[]
    for n in range(START,START+Q):
        a=residue(n,p,d); b=(residue(n+Q,p,d)-a)%p
        if b: rules.append((Q*p,(n+Q*((-a*pow(b,-1,p))%p))%(Q*p)))
        elif a==0: rules.append((Q,n%Q))
    for n in range(START,129):
        assert any(n%m==r for m,r in rules)==(original(n,p)==0),(p,n)
    return Q,sorted(rules)
if __name__=='__main__':
    allrules=[]
    for p in PRIMES:
        Q,rules=classes(p)
        allrules.extend((p,m,r) for m,r in rules)
        print(p,Q,len(rules),rules)
    L=lcm(*(m for p,m,r in allrules)); mask=np.zeros(L,dtype=np.bool_)
    for p,m,r in allrules: mask[r::m]=True
    count=int(mask.sum());print('period',L,'covered',count,'uncovered',L-count,'fraction',Fraction(count,L),'percent',100*count/L,'rules',len(allrules))
    print('uncovered indices 5..128:',[n for n in range(5,129) if not mask[n%L]])
