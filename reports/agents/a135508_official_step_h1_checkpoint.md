# A135508: certificate for existing official finite step

ChatGPT GPT-6.2 for hayalows, 2026-11-27. The project now has an accepted reduction authored by @Hennyrick, with finite step [OeisA135508.conjecture.R1.H2.R1.H1](https://lefttosolve.com/p/OeisA135508.conjecture.R1.H2.R1.H1), worth 14 points per live brief at 17:31 UTC.

Exact H1: for every prime q between 5 and 1,000,000 inclusive there exists prime r > 5 with r < q², r mod 3 = 2 and q dividing r+2.

Our existing certificate generator and trial-division verifier directly cover this H1. Re-ran both at B=10^12:
```
./cert 1000000000000 witnesses_1t.csv
./verify 1000000000000 witnesses_1t.csv
B=1000000000000 root=1000000 primes_ge_5=78496 witnesses=80008 trials=381316 max_q=243937433 max_multiplier=277 multiplier_at_p=379123 failures=0 seconds=0.199305
VERIFIED B=1000000000000 primes=78496 witnesses=80008 max_q=243937433 seconds=0.180378
```
First witness (k=1) for each modulus gives precisely the official H1 condition. All 78,496 required moduli covered. Largest first witness 243,937,433; largest multiplier 277. CSV SHA256: 8ee7e906819059dc48dd5ce78c9f3da4c3e843d82e3ade09712384dfb7acc6b1.

Source programs: a135508_certificate.cpp and a135508_verify.cpp in this directory. The verifier independently sieves every required modulus and checks primality by trial division and all exact bounds. This is a complete finite mathematical certificate in ordinary arithmetic, not a Lean kernel proof. To formalize, construct small bounded batches with an explicit witness function/table, use an exact certified modular primality test or factor-based kernel computation, and prove completeness across batches; avoid a massive single naive existential enumeration.

Lease attempts at 17:30:55 and 17:31:12 returned HTTP 500; the public brief itself worked. No upstream proof PR and no points claimed. Do not open a duplicate or claim acceptance; obtain a valid lease and validate the exact Lean target first.
