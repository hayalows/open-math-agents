# A135508: extension to 10^16 and unconditional exclusion of small-prime composite increments

Agent: ChatGPT GPT-6.2 for hayalows, 27 November 2026.
Research only; independent mathematical and Lean review remain pending. No upstream submission.

## Reproduced finite certificate

The sufficient condition and first-counterexample argument are given in a135508_1q_checkpoint.md. This run extends the bound tenfold, without pretending to visit every recurrence index.

Generator (existing a135508_certificate.cpp):
```
B=10000000000000000 root=100000000 primes_ge_5=5761453 witnesses=5782383 trials=36995313 max_q=59871068051 max_multiplier=607 multiplier_at_p=98634379 failures=0 seconds=17.5184
```
SHA256 of witnesses_10q.csv: d0cb869c4fc4ea7208e9babac092209d6e65c897acc9ee12bcca535710b8b6ef

The original independent trial-division verifier timed out at 120 seconds at this bound; no completed trial-division verification is claimed for 10^16. A separately implemented verifier (a135508_verify_fast.cpp) checks full row coverage, increasing distinct witnesses, deadlines, both residue requirements, and primality using the first seven prime bases. The generator uses a different deterministic 64-bit Miller-Rabin base set. The verifier rejects any q>=341550071728321, the established first-seven-base deterministic threshold (Jaeschke 1993, https://doi.org/10.2307/2153262; https://mathworld.wolfram.com/Rabin-MillerStrongPseudoprimeTest.html). The largest actual witness is 59871068051, well below this threshold.

```
VERIFIED B=10000000000000000 primes=5761453 witnesses=5782383 max_q=59871068051 seconds=12.9564
```

Reproduce:
```sh
g++ -O3 -std=c++17 a135508_certificate.cpp -o cert
g++ -O3 -std=c++17 a135508_verify_fast.cpp -o verify_fast
./cert 10000000000000000 witnesses_10q.csv
./verify_fast 10000000000000000 witnesses_10q.csv
sha256sum witnesses_10q.csv
```
The large CSV is generated on demand; it is not committed.

## Unconditional structural refinement (proof proposed, novelty not claimed)

Let x_1=1, c_n=n/gcd(n,x_(n-1)), x_n=x_(n-1)(c_n+2). Then c_n divides n, x_n is divisible by x_(n-1), and v_p(c_n)=max(0,v_p(n)-v_p(x_(n-1))).

**Exact 2-adic behavior.** For every integer j>=1, c_(2^(2j-1))=2 and all other c_n are odd. Indeed c_2=2 and v_2(x_2)=2. Suppose v_2(x_(2^(2j-1)))=2j. For every n strictly between 2^(2j-1) and 2^(2j+1), v_2(n)<=2j. Thus c_n is odd, the multiplying factor c_n+2 is odd, and the stock stays at 2j throughout that interval. At n=2^(2j+1), the denominator has valuation 2j and n is a pure power of 2. Hence c_n=2, the multiplier is 4, and the stock becomes 2j+2. Induction proves the assertion, without any conjectural hypothesis.

**Exact exclusion of multiples of 3.** c_3=3, and no other c_n is divisible by 3. Direct values x_2=4,x_3=20,x_4=60,x_5=180,x_6=540 imply v_3(x_4)>=1 and v_3(x_6)>=2. For every a>=2, v_3(x_(2*3^(a-1)))>=a by induction: at index 2*3^a, the earlier stock has at least a powers of 3 and at least one factor of 2, so c=1 and multiplication by 3 supplies the next power. For any n with v_3(n)=a>=2, n>=3^a>2*3^(a-1), hence v_3(x_(n-1))>=a. For a=1 and n!=3, n>=6, so x_4 already provides the necessary factor. Thus the claim holds.

**Consequence:** every possible composite increment, at any index, has all prime factors >=5. This is an unconditional restriction, not merely a finite computational finding. It also clarifies the earlier certificate argument for p=2,3.

The remaining obstruction is to show enough suitable prime witnesses for every p>=5 at the required deadlines, or find a different way of obtaining p-adic stock. The finite certificate cannot resolve this unbounded distribution problem. A proof of the global conjecture has not been obtained. Review request: independently check the exact small-prime lemmas and the first-counterexample certificate before making any novelty claim. 
