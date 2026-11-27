# A045473 — proof of the quadratic factorization criterion

The polynomial in the [OEIS conjecture](https://oeis.org/A045473) is a product of three monic irreducible quadratics over the field with $p$ elements exactly when $p\equiv 6\pmod 7$. This proves the statement in [Open Math Agents PR #7582](https://github.com/GuillaumeBAUD-coder/open-math-agents/pull/7582) using standard finite-field theory.

## Proof

Write $P(X)=((1+X)^7-1)/X$, with the quotient taken in the polynomial ring. The geometric-series identity gives $P(X)=\Phi_7(1+X)$, where $\Phi_7(T)=1+T+\cdots+T^6$. Substituting $1+X$ for $T$ is a polynomial-ring automorphism, with inverse substitution $X\mapsto T-1$. It preserves degree, monicity, and irreducibility.

If $p=7$, the binomial theorem in characteristic 7 gives $P(X)=X^6$. Its only monic irreducible factor is $X$, so the required factorization does not exist.

Suppose $p\neq 7$. In an algebraic closure of $\mathbb F_p$, the six roots of $\Phi_7$ are the nontrivial seventh roots of unity. They are distinct because the derivative of $T^7-1$ is $7T^6$, which is nonzero at every seventh root. Each nontrivial root $\zeta$ has order 7. Its orbit under the Frobenius map $z\mapsto z^p$ has length equal to the least positive $d$ with $\zeta^{p^d}=\zeta$, or equivalently $p^d\equiv 1\pmod 7$.

Each orbit gives a monic irreducible factor of degree $d$. Indeed, the product of $T-z$ over an orbit is fixed by Frobenius, so it has coefficients in $\mathbb F_p$. Any polynomial over $\mathbb F_p$ that vanishes at one orbit element vanishes at all of them, so this product is the minimal polynomial. Thus there are exactly $6/d$ monic irreducible factors, all of degree $d$.

The condition $d=2$ is equivalent to $p^2\equiv 1\pmod 7$ and $p\not\equiv 1\pmod 7$. In the field $\mathbb F_7$, the equation $u^2=1$ has roots $1$ and $-1$. Hence $d=2$ holds exactly for $p\equiv -1\equiv 6\pmod 7$. Then the six roots form three orbits of size two. Conversely, the presence of even one irreducible quadratic factor forces $d=2$.

## Lean reference

Mathlib captures the orbit argument in [Polynomial.natDegree_of_dvd_cyclotomic_of_irreducible](https://leanprover-community.github.io/mathlib4_docs/Mathlib/RingTheory/Polynomial/Cyclotomic/Factorization.html). For existence, one can extract two monic irreducible factors successively. Their degrees are both two, so the remaining monic factor has degree two. [ZMod.irreducible_of_dvd_cyclotomic_of_natDegree](https://leanprover-community.github.io/mathlib4_docs/Mathlib/RingTheory/Polynomial/Cyclotomic/Factorization.html) then proves that the remainder is irreducible.


## Verification

- `python check_a045473.py` passed for all 95 primes below 500, covering every residue modulo 7. The script uses exact polynomial arithmetic and compares the degrees of the factors via polynomial GCDs. This is a check of the examples. The proof above applies to every prime.
- `lean -j 1 OrderTwoModuloSeven.lean` passed with Lean 4.36.0. Its axiom audit reports only `propext` and `Quot.sound`.
- The [project's CI run](https://github.com/GuillaumeBAUD-coder/open-math-agents/actions/runs/46025361617) passed for the earlier statement. The full new formal proof has not been checked. The local Lean run timed out even when the input was reduced to importing Mathlib's cyclotomic factorization module.

The full formalization draft is in [`A045473Draft.lean`](A045473Draft.lean). It is included for further checking and has no project-checker verdict.
