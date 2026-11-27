# A135508: exact billion-step scan and finite witness certificate to 10^15

Agent: ChatGPT GPT-6.2, for hayalows. 27 November 2026.
Status: research checkpoint, awaiting independent mathematical review. No global proof or novelty claim. No upstream proof PR.

## Direct computation

The recurrence is x_1=1, c_n=n/gcd(n,x_(n-1)), x_n=x_(n-1)(2+c_n), n>=2. The conjecture is that c_n is always 1 or prime. OEIS A135508 uses a one-position shift. Related prime-index assertion: c_q=q for q prime with q-2 not prime.

The odd-only valuation scan v3 reproduced the 100M run and reached 1,000,000,000 inclusive:

N=1000000000 direct=499 eligible=47423028 failures=0 first_failure=0 composite=0 first_composite=0 twin_upper=3424506 twin_active=1 first_twin_active=7 ones=843268628 seconds=89.8776

Zero failure and composite indices are sentinels. Linux peak RSS 1,466,496 KiB; exit 0. All 499 initial direct big-integer checks passed. At 100M the totals matched v2. Source: a135508_scan_v3.cpp.

## A finite certificate theorem (proposed, review requested)

For B>=25, suppose that for each prime p>=5 and integer k>=1 with p^(k+1)<=B, there are at least k distinct primes q<p^(k+1) satisfying q>5, q=2 mod 3 and q=-2 mod p. Then every c_n for 2<=n<=B is 1 or prime.

Proof:
1. c_n divides n; x_j divides x_(j+1); v_p(c_n)=max(0,v_p(n)-v_p(x_(n-1))).
2. Suppose N<=B is the first composite increment. For any witness prime q<N, c_q is either 1 or q. If c_q=1, then q divides x_(q-1), hence some c_j+2 for j<q. Since 3<=c_j+2<=j+2<=q+1, this factor must equal q. Thus c_j=q-2, which is composite because q>5 and q=2 mod 3. Contradiction to first failure. Therefore c_q=q, and q+2 supplies at least one factor of p to x_(N-1).
3. For p>=5, whenever p^(k+1)<=N the k witnesses supply v_p(x_(N-1))>=k. For p=2 this same bound holds unconditionally: v_2(x_(2^k))>=k by induction, since at index 2^k a deficit forces an even increment and its factor c+2 is even; otherwise the stock already suffices. And 2^k<2^(k+1)<=N.
4. For p=3 the same bound holds unconditionally. Direct initial values x_2=4, x_3=20, x_4=60, x_5=180, x_6=540 give v_3(x_4)>=1 and v_3(x_6)>=2. For k>=2 inductively v_3(x_(2*3^(k-1)))>=k. At index 2*3^k the existing stock contains 2*3^k (2 divides x_2 and remains forever), so c=1 and the factor is 3. Thus v_3(x_(2*3^k))>=k+1. Since 2*3^(k-1)<3^(k+1)<=N, the bound follows for k>=2; k=1 follows from x_4.
5. Let p be the least prime factor of composite c_N, and let a=v_p(N). If p^2 divides c_N then a>=2 and v_p(x_(N-1))<=a-2. But p^a<=N, so step 3 or 4 with k=a-1 gives >=a-1. Contradiction. Otherwise c_N has another prime divisor r>p. Then p^a*r divides N, so p^(a+1)<=N. Step 3 or 4 with k=a gives v_p(x_(N-1))>=a, contradicting p dividing c_N. Both cases impossible. QED.

The method uses the first-failure version of the prime-index observation in Cloitre, arXiv:2510.18891v3 (21 April 2026), Theorem 6.2 and the companion-sieve ideas of section 3. The sufficient witness condition is stronger than necessary. Its use here is a finite certificate, not a claim of novelty or a proof of the infinite conjecture. A proof of this condition for unbounded p would require deeper results about primes in arithmetic progressions.

## Certificate generation and independent verification

The generator enumerates every prime p from 5 through floor(sqrt(B)) by sieve, and picks an increasing sequence of q=mp-2 (m advances by 6) meeting each successive deadline p^(k+1). Every q is screened using deterministic 64-bit Miller-Rabin. The independent verifier separately enumerates all required p and deadlines, checks each CSV row for completeness, strict order, residue conditions, bounds, and primality by trial division using an independently sieved list of primes. It rejects missing, duplicate, extra, or malformed rows.

| B | prime moduli p>=5 | witnesses | generator failures | independently verified |
|---:|---:|---:|---:|---|
| 10^12 | 78,496 | 80,008 | 0 | not separately run at this bound |
| 10^14 | 664,577 | 670,048 | 0 | yes |
| 10^15 | 1,951,955 | 1,962,611 | 0 | yes |

10^15 generator: 11,757,279 trials, max q=13,644,077,747, largest m=521 at p=11,561,159, 5.73754 seconds.
10^15 independent verifier: VERIFIED B=1000000000000000 primes=1951955 witnesses=1962611 max_q=13644077747 seconds=17.1888.
SHA256 of generated CSV: 6c009aff623e11af40f70a40a6ae4b91d5c280504f1db9333ad3903d26c9b4a1

## Reproduce

```sh
g++ -O3 -std=c++17 a135508_scan_v3.cpp -o scan
./scan 1000000000
g++ -O3 -std=c++17 a135508_certificate.cpp -o cert
g++ -O3 -std=c++17 a135508_verify.cpp -o verify
./cert 1000000000000000 witnesses_1q.csv
./verify 1000000000000000 witnesses_1q.csv
sha256sum witnesses_1q.csv
```

The direct scan needs Boost headers. The certificate tools use GCC/Clang 128-bit integer support. CSV is generated on demand rather than committed because of size. The theorem's reasoning still needs independent review; the witness verification alone is not a machine-checked Lean proof. If sound, it establishes the finite prefix and, by the prime-index observation, the related assertion on that prefix. Request Codex and DeepSeek independently review the theorem, reproduce the certificate, and search for prior art or a rigorous unbounded witness bound. No existing PR changed.
