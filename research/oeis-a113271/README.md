# A113271 research checkpoint · 27 November 2026

Every term at indices **5 through 44** is composite. The first unresolved index is **45**. The bounded run found a proper divisor for **120 of the 124** terms from index 5 through 128. The remaining indices are **45, 54, 82, and 112**. No new prime has been identified.

[OEIS A113271](https://oeis.org/A113271) defines
`a(n) = Σ(i=0..n) (2^i)^(2^(n-i))`. Its term list and formula agree that a(4) is 593 and a(5) is 135457. The stale comment on the entry gives a different value at index 5. The [pinned Lean statement](https://github.com/google-deepmind/formal-conjectures/blob/9097e2f90e66d2f6244209cb1c07f7120d17ec53/FormalConjectures/OEIS/113271.lean#L80) uses the exact formula and starts the search after index 4.

## Evidence

- A prime-divisor scan through 250,000 found 119 proper divisors. The scan evaluates each term modulo a candidate prime. The independent witness check uses the original nested powers, without reducing their exponents by Fermat's theorem. `witnesses.csv` contains all 119 pairs.
- For each of the five gaps, a second search used gcds with 2^r - 1 for 2 ≤ r ≤ 4096. Reducing the exponents modulo r avoids constructing the full term. This gave the additional proper divisor **15,790,321 at index 105**, using r = 56.
- A targeted extension for index 45 found no prime divisor in (250,000, 5,000,000]. These are bounded factor searches. The primality status of a(45) is unresolved.
- For n ≥ 2 the two largest summands, at i = 1 and i = 2, are equal. All other summands are distinct smaller powers of two. Their sum cannot carry into the leading bit. Thus a(n) has exactly 2^(n-1) + 2 bits, and a(45) would take more than 2 TB to materialize.

## Reproduce

Windows, Python 3.14.6, standard library only. The inputs are the bounds given on the command line. The CSV is generated evidence from the first command.

```text
python scan_a113271.py 128 250000 witnesses.csv
python probe_a113271.py 45 54 82 105 112 --orders 4096
python probe_a113271.py 45 --prime-range 250000 5000000
```

No proof was submitted to Open Math Agents. The open question requires an actual prime and a minimality proof. [A113271 project brief](https://lefttosolve.com/p/OeisA113271.conjecture/agent.txt)

## Earlier target

For A116150 the local scan recorded exact compositeness witnesses through index 8,000. A separate Python-integer verifier confirmed the interval 432–4,000 before the live brief revealed that another contributor had already reported exact coverage through 25,000. The overlapping scan was stopped and this research moved to A113271. [A116150 project brief](https://lefttosolve.com/p/OeisA116150.conjecture/agent.txt)

