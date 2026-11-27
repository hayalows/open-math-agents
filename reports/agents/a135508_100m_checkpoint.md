# OEIS A135508: exact scan to 100,000,000

**Agent:** ChatGPT GPT-6.2, acting for hayalows. **Date:** 2026-11-27.
**Status:** finite computational evidence only; no formal proof, no claim of mathematical novelty and no upstream proof submission.

Extends the earlier ChatGPT scan (65fa87ee5c48279532d550009df67c742f841433), without replacing the original. Codex and DeepSeek may independently reproduce and review this checkpoint.

## Results

The recurrence is x_1=1, x_n=x_(n-1)*(2+c_n), c_n=n/gcd(n,x_(n-1)), for n>=2. OEIS A135508 is shifted relative to this recurrence index. We check the conjecture that c_n is 1 or prime, and the related prime-index assertion that c_p=p when p is prime and p-2 is not prime.

| Inclusive recurrence bound | Eligible primes | Failures | Composite increments | Upper twin primes tested | Upper twin primes with c_p=p |
|---:|---:|---:|---:|---:|---:|
| 10,000,000 | 605,599 | 0 | 0 | 58,980 | 1 (p=7) |
| 50,000,000 | 2,762,033 | 0 | 0 | 239,101 | 1 (p=7) |
| 100,000,000 | 5,321,143 | 0 | 0 | 440,312 | 1 (p=7) |

At the largest bound there were 82,964,768 increments equal to 1, among 99,999,999 total recurrence updates.

## Reproduction

Requires a C++17 compiler and Boost headers (multiprecision).
```sh
g++ -O3 -std=c++17 a135508_scan_v2.cpp -o scan
./scan 50000000
./scan 100000000
```
Observed output for the latter run:
```
N=10000000 direct=499 eligible=605599 failures=0 first_failure=0 composite=0 first_composite=0 twin_upper=58980 twin_active=1 first_twin_active=7 ones=8129309
N=100000000 direct=499 eligible=5321143 failures=0 first_failure=0 composite=0 first_composite=0 twin_upper=440312 twin_active=1 first_twin_active=7 ones=82964768
```
Linux container, elapsed 7.84 seconds, peak RSS 294528 KiB (environment-specific). The direct independent big-integer calculation agrees at n=2..500. A zero first_failure/first_composite is a sentinel, not an actual index.

## Why the storage is exact

A sieve records the smallest prime factor only for composite integers, with zero denoting primes for integers >=2. The largest possible smallest factor of a composite at N+2 is sqrt(N+2); it fits in uint16_t for the allowed N<=1,000,000,000. The stock for p is min(32, v_p(x_(n-1))). Every exponent in n is <32 in this range, so truncation cannot change min(v_p(n),v_p(x_(n-1))). Factoring c_n+2 updates that capped stock exactly. Thus neither primality nor recurrence steps are probabilistic. The use of c_n+2<=N+2 prevents out-of-bounds accesses.

## Mathematical relationship (known direction; not claimed novel)

For any prime p>=5, p divides x_(p-1) iff c_(p-2)=p-2. Indeed each factor c_k+2 of x_(p-1) lies between 3 and p+1; a multiple of p must equal p. Thus c_k=p-2 divides k, and k<=p-1 forces k=p-2. The converse is immediate. Since c_p=p/gcd(p,x_(p-1)), if p-2 is composite and c_p=1, a composite increment already occurred at p-2. Therefore a failure of the prime-index assertion implies a failure of the broader 1-or-prime conjecture, and checking the broader conjecture on the prefix certifies the prime-index assertion on that prefix. This does not prove either assertion globally. See Cloitre, Primes in LCM recurrences (arXiv:2510.18891v3, 21 April 2026), section 6, for related established results and open questions.

## Next action

Independent review of the scan and its relation to the exact OEIS conjecture; prioritize structural arguments for composite increments rather than interpreting a larger finite scan as a proof. No existing statement PR has been changed; all work is on the fork's shared research branch.
