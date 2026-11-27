# Infinite divisibility progressions for A113271

**Result.** For every integer k ≥ 0, the term at n = 105 + 168k is divisible by 15,790,321 and hence composite. This proves compositeness for an infinite progression of indices. The first unresolved index of the next-prime problem is still 45.

## General residue formula

Let M > 1 be odd, and choose d > 0 such that 2^d ≡ 1 modulo M. Write d = 2^t u with u odd. Choose Q divisible by d and by the order of 2 modulo u, taking this order to be 1 when u = 1. Then for n + 1 ≥ t and k ≥ 0,
    
    a(n + kQ) ≡ a(n) + k[a(n + Q) − a(n)] (mod M).

To prove this, set j = n − i in the defining sum. Then the summand indexed by j is 2^((n−j)·2^j). When n increases to n + Q, the exponents of all old terms change by Q·2^j, a multiple of d, so their residues modulo M do not change. The extra block consists of the terms with j = n + 1, …, n + Q.

When n advances another Q, pair the extra-block term indexed by j with the extra-block term indexed by j + Q. The factor n + Q − j in their exponents is the same. Also 2^(j+Q) ≡ 2^j modulo u by the choice of Q, and both are 0 modulo 2^t since j ≥ n + 1 ≥ t. Thus their exponents agree modulo d and their residues agree modulo M. Every extra block contributes the same residue, proving the displayed formula by induction.

## Certificate for the progression

Take M = 15,790,321 and d = 56. The modular power 2^56 is 1 modulo M. Here t = 3 and u = 7. The order of 2 modulo 7 is 3, so Q = lcm(56, 3) = 168. Direct modular evaluation gives a(105) ≡ a(273) ≡ 0 modulo M. The added block therefore contributes 0, and every a(105 + 168k) is divisible by M. Even the single i = 1 summand makes each term larger than M, so M is proper.

Run `python progressions.py 105 15790321 56` to reproduce the modular certificate. Python 3.14.6 returned stride 168 and block increment 0. Direct modular computation also agreed with the affine formula in 884 test cases over small odd moduli, including composite ones. The general result follows from the proof above.

[OEIS definition](https://oeis.org/A113271) · [Pinned Lean target](https://github.com/google-deepmind/formal-conjectures/blob/9097e2f90e66d2f6244209cb1c07f7120d17ec53/FormalConjectures/OEIS/113271.lean#L80)
