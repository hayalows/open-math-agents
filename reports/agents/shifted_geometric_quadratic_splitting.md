# Uniform proof of shifted geometric-polynomial quadratic splitting

Agent: ChatGPT GPT-6.2 for hayalows, 2026-11-27.
Status: complete ordinary mathematical argument, awaiting independent review; not a Lean-checked proof. No claim of novelty: this is an application of established finite-field theory.

## Theorem

For every odd integer m>1 and prime p, let P_m(X)=sum_{j=0}^{m-1}(X+1)^j over F_p. Then P_m is a product of (m-1)/2 distinct monic irreducible quadratics if and only if p=-1 modulo m.

## Proof

The substitution T=X+1 is invertible and preserves monicity, degree, distinctness, and irreducibility. It suffices to treat S_m(T)=1+T+...+T^(m-1), satisfying (T-1)S_m(T)=T^m-1.

If p divides m, S_m(1)=m=0 in F_p. Thus T-1 is a linear factor and the asserted splitting is impossible. Also p cannot be -1 modulo m in this case.

Suppose p does not divide m. T^m-1 has simple roots because its derivative mT^(m-1) does not vanish at a root. The roots of S_m are exactly the nonidentity m-th roots of unity. Over F_p an element has minimal polynomial of degree two iff it belongs to F_(p^2) but not F_p. Finite field multiplicative groups are cyclic of orders p^2-1 and p-1, respectively.

If all irreducible factors have degree two, all m-th roots of unity lie in F_(p^2), giving m | p^2-1. No nonidentity m-th root lies in F_p, giving gcd(m,p-1)=1. Since m divides (p-1)(p+1) and is coprime to p-1, m divides p+1.

Conversely, suppose m divides p+1. Then m divides p^2-1, and gcd(m,p-1) divides gcd(p+1,p-1), which divides 2. Since m is odd, gcd(m,p-1)=1. Therefore all m-th roots are in F_(p^2) and only the identity is in F_p. Each of the m-1 nonidentity roots has minimal polynomial of degree two; separability gives (m-1)/2 distinct monic irreducible quadratics. Substitution T=X+1 gives the claimed result. QED.

## Applications to actual OEIS comments

- A045473 (m=7): p=6 mod 7, three irreducible quadratics. Federico Provvedi, 31 March 2018. https://oeis.org/A045473 . This proves the exact target of PR #7582, which does not require distinctness; distinctness follows automatically for p!=7, while p=7 yields a linear factor.
- A061242 (m=9): p=8 mod 9, four irreducible quadratics. Federico Provvedi, 27 June 2018. https://oeis.org/A061242 . Applies only to the polynomial-factorization comment, not the separate decimal-rotation conjecture.
- A030433 (m=5): p=4 mod 5, two distinct irreducible quadratics. https://oeis.org/A030433 . The entry already records the equivalent unshifted factorization in a 2022 comment; do not count this as a new open problem solved.

This is a shorter alternate proof of A045473 than the existing Frobenius-orbit argument in research/oeis-a045473/README.md, and covers composite odd exponents such as nine without additional factor-degree calculations.

## Independent numerical sanity check

Python/SymPy factorization of the unshifted S_m for m in (3,5,7,9,11,15,21,27,35) and all 46 primes below 200: 414 cases, 63 quadratic-only squarefree splits, 0 disagreements with p % m == m-1. This is a sanity check, not the proof. Reproduction:

```python
from sympy import symbols, Poly, primerange
x = symbols('x')
for m in (3,5,7,9,11,15,21,27,35):
    for p in primerange(2,200):
        factors = Poly(sum(x**i for i in range(m)), x, modulus=p).factor_list()[1]
        assert all(f.degree()==2 and e==1 for f,e in factors) == (p%m==m-1)
```

## Submission status and references

The underlying cyclotomic factorization theorem is classical, e.g. https://aimspress.com/article/doi/10.3934/math.20241141 (Lemma 2.1). A045473 is currently an open statement-formalization PR, not yet an accepted proof target. No second upstream proof PR is opened before statement approval. The existing Lean draft remains unverified. Please independently review the general argument and check the project's exact target and proof rules. A061242 is a potential separate formalization task only after confirming availability and obtaining the proper assignment.
