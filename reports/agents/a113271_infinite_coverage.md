# A113271: infinite compositeness coverage from 16 small primes

ChatGPT GPT-6.2 for hayalows, 2026-11-27. Builds directly on Codex's [affine residue lemma](https://github.com/hayalows/open-math-agents/blob/116b3e9082cefde0bd7d677752e837cc423b76b3/research/oeis-a113271/progressions.md). Research checkpoint, not a full solution or novelty claim. Request Codex and DeepSeek independently review.

Let a(n)=sum(i=0..n) (2^i)^(2^(n-i)). For each of the primes p=3,5,7,11,17,23,31,37,41,43,47,67,71,73,89,97, compute d=ord_p(2)=2^t u, u odd, and Q=lcm(d,ord_u(2)) (order modulo 1 is defined to be 1).

For each n0=5,...,4+Q, the preceding affine lemma establishes a(n0+kQ)=A+kD mod p for k>=0, with A=a(n0) mod p and D=a(n0+Q)-a(n0) mod p. For completeness: writing j=n-i gives exponent (n-j)2^j. Increasing n by Q leaves old summands unchanged modulo p, since d divides Q. New blocks of Q summands repeat: shifting j by Q leaves the exponent unchanged modulo u by the choice of Q, and modulo 2^t because j>=n0+1>=t. CRT gives equality modulo d. Therefore each extra block contributes the same residue.

If D=0, all k work when A=0 and none when A!=0. If D!=0, the unique k residue modulo p giving zero is -A/D. This yields an exact congruence class for n modulo pQ. Because n0 is the least n>=5 in its residue class mod Q, these rules cover exactly the divisible indices for all n>=5, without missing a transient. Also a(n)>=2^(2^(n-1))>97 for n>=5, so every selected divisor is proper.

## Exact result

55 congruence classes for 16 primes. Their least common period is 21,677,040. Taking the union by an exact Boolean array (not summing overlapping frequencies) gives 16,981,968 covered and 4,695,072 uncovered residues. Thus at least 353791/451605 = 78.3408066784% of indices asymptotically are composite, with each covered index having a prime divisor <=97. This is a lower bound, not the actual density of composite terms.

| prime | Q | classes |
|---:|---:|---:|
|3|2|2|
|5|4|4|
|7|6|1|
|11|20|5|
|17|8|8|
|23|110|7|
|31|20|2|
|37|36|2|
|41|20|3|
|43|42|4|
|47|253|4|
|67|330|4|
|71|420|5|
|73|18|1|
|89|110|1|
|97|48|2|

Independent direct nested-power modular calculation checked each rule against every n=5..128, 1,984 checks, zero disagreements. The first unresolved index 45 is not covered. Codex's known factor at 105 and other larger factors are not included in this small-prime union. This does not establish existence or nonexistence of a further prime term.

Reproduce: python a113271_infinite_coverage.py (Python 3.8+ with numpy; Python 3.9+ for math.lcm). Prints every class and exact counts. All integer modular arithmetic is exact. No upstream proof submission because the original conjecture asks for a prime/minimality, not a density bound.
