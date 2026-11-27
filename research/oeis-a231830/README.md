# A231830 squarefreeness research checkpoint

The conjecture that every term is squarefree remains open. The computations below completed on 27 November 2026.

- **Every prime at most 1,000,000, every index.** An exhaustive orbit scan checked 39,175 primes congruent to 1 modulo 4. There were 136 primes that divided a term. All 136 had nonzero residues modulo their squares.
- **Every pair in the two published OEIS b-files.** An exact JavaScript BigInt computation aligned all 8,503 rows by row number, checked each published divisibility claim, and found no square divisor. The largest prime checked in those tables was 9,997,763,389 and the largest term index was 237,516. This second result covers the listed pairs. It does not assert completeness for all primes up to the largest listed prime.

## Why the bounded orbit check covers all indices

For n ≥ 1, a(n) = 1 + 4*P(n−1)^2, with P(n−1) the product of the preceding positive-index terms. This follows by induction from the defining recurrence a(n+1) = (a(n)−1)*a(n)^2 + 1. Thus each divisor prime is 1 modulo 4, because −1 is a square modulo that prime. Modulo any prime the recurrence is deterministic. A repeated state before reaching 0 rules out any later 0. If a term is 0 modulo p, the next term is 1 modulo p² and every subsequent term stays 1 modulo p². It therefore suffices to test the first index divisible by p. The search finds this index with a cycle check and evaluates the product recurrence modulo p² independently.

## Reproduce

The scripts use Python's standard library. The first command generates the recorded witness table. The second expects the two linked OEIS data files.

```text
python scan.py 1000000 witnesses.csv
python verify_published.py b362252.txt b362253.txt
```

Sources: [A231830](https://oeis.org/A231830), [prime table b362252](https://oeis.org/A362252/b362252.txt), [index table b362253](https://oeis.org/A362253/b362253.txt), and the [project brief](https://lefttosolve.com/p/OeisA231830.conjecture/agent.txt).
