-- Research draft. The full proof has not passed Lean or the project checker.
import Mathlib.RingTheory.Polynomial.Cyclotomic.Factorization
import Mathlib.Tactic.Ring
import Mathlib.Tactic.IntervalCases

/-!
# OEIS A045473: primes congruent to 6 modulo 7

Source: https://oeis.org/A045473 (OEIS Foundation, CC BY-SA 4.0).
Conjecture posed by Federico Provvedi, March 31, 2018.
Formalization by ChatGPT (GPT-6.2), on behalf of @hayalows.

Over the field with p elements, the polynomial obtained by dividing
(1 + X)^7 - 1 by X has three irreducible quadratic factors exactly
for primes p congruent to 6 modulo 7. Monic factors represent the
factorization without ambiguity from nonzero scalar units.
-/

namespace OMA.S_oeis_a045473

open Polynomial

/-- The polynomial quotient, expanded over ZMod p without rational-function division. -/
noncomputable def shiftedQuotient (p : ℕ) : Polynomial (ZMod p) :=
  X ^ 6 + C 7 * X ^ 5 + C 21 * X ^ 4 + C 35 * X ^ 3 +
    C 35 * X ^ 2 + C 21 * X + C 7


private def translate (p : ℕ) (a : ZMod p) :=
  Polynomial.algEquivAevalXAddC a

private lemma translate_monic {p : ℕ} [Fact p.Prime] (a : ZMod p)
    {f : Polynomial (ZMod p)} (hf : f.Monic) : (translate p a f).Monic := by
  change (f.comp (X + C a)).Monic
  exact hf.comp_X_add_C a

private lemma translate_degree {p : ℕ} [Fact p.Prime] (a : ZMod p)
    (f : Polynomial (ZMod p)) : (translate p a f).natDegree = f.natDegree := by
  change (f.comp (X + C a)).natDegree = f.natDegree
  rw [natDegree_comp, natDegree_X_add_C, mul_one]

private lemma translate_cyclotomic (p : ℕ) [Fact p.Prime] :
    translate p 1 (cyclotomic 7 (ZMod p)) = shiftedQuotient p := by
  letI : Fact (Nat.Prime 7) := ⟨by decide⟩
  rw [cyclotomic_prime]
  simp only [Finset.sum_range_succ, Finset.sum_range_zero, zero_add, translate,
    algEquivAevalXAddC_apply, aeval_add, aeval_pow, aeval_X, aeval_one, C_1, shiftedQuotient]
  ring

private lemma order_eq_two_iff (p : ℕ) (hp : p.Coprime 7) :
    orderOf (ZMod.unitOfCoprime p hp) = 2 ↔ p % 7 = 6 := by
  rw [orderOf_eq_prime_iff]
  have hext (a b : (ZMod 7)ˣ) : a = b ↔ (a : ZMod 7) = (b : ZMod 7) :=
    ⟨fun h => congrArg Units.val h, Units.ext⟩
  rw [hext, hext, Units.val_pow_eq_pow_val, Units.val_one, ZMod.coe_unitOfCoprime]
  rw [← ZMod.natCast_mod p 7]
  generalize hr : p % 7 = r
  have hlt : r < 7 := hr ▸ Nat.mod_lt p (by decide)
  interval_cases r <;> decide

private lemma split_monic {K : Type*} [Field K] {F : Polynomial K}
    (hF : F.Monic) (hdeg : 0 < F.natDegree) :
    ∃ f q : Polynomial K, f.Monic ∧ Irreducible f ∧ q.Monic ∧ F = f * q := by
  obtain ⟨f, hfm, hfi, q, hq⟩ :=
    exists_monic_irreducible_factor F (not_isUnit_of_natDegree_pos F hdeg)
  exact ⟨f, q, hfm, hfi, hfm.of_mul_monic_left (hq ▸ hF), hq⟩

theorem main : ∀ (p : ℕ) [Fact p.Prime],
    p % 7 = 6 ↔
      ∃ f g h : Polynomial (ZMod p),
        f.Monic ∧ g.Monic ∧ h.Monic ∧
        Irreducible f ∧ Irreducible g ∧ Irreducible h ∧
        f.natDegree = 2 ∧ g.natDegree = 2 ∧ h.natDegree = 2 ∧
        f * g * h = shiftedQuotient p := by
  intro p hp
  by_cases h7 : p = 7
  · subst p
    have hz : shiftedQuotient 7 = X ^ 6 := by
      have hseven : (7 : ZMod 7) = 0 := by decide
      have htwentyone : (21 : ZMod 7) = 0 := by decide
      have hthirtyfive : (35 : ZMod 7) = 0 := by decide
      simp [shiftedQuotient, hseven, htwentyone, hthirtyfive]
    constructor
    · intro h
      omega
    · rintro ⟨f, g, h, hfm, -, -, hfi, -, -, hfd, -, -, heq⟩
      have hdiv : f ∣ (X : Polynomial (ZMod 7)) ^ 6 :=
        ⟨g * h, by rw [← hz, ← heq, mul_assoc]⟩
      have hx := hfi.prime.dvd_of_dvd_pow hdiv
      have hle := natDegree_le_of_dvd hx (X_ne_zero : (X : Polynomial (ZMod 7)) ≠ 0)
      rw [natDegree_X, hfd] at hle
      omega
  have hpn : ¬p ∣ 7 := by
    intro hd
    rcases (Nat.dvd_prime (show Nat.Prime 7 by decide)).mp hd with h | h
    · exact hp.out.ne_one h
    · exact h7 h
  have hcop : p.Coprime 7 := hp.out.coprime_iff_not_dvd.mpr hpn
  let F := cyclotomic 7 (ZMod p)
  have hFm : F.Monic := cyclotomic.monic 7 (ZMod p)
  have hFd : F.natDegree = 6 := by
    rw [show F = cyclotomic 7 (ZMod p) from rfl, natDegree_cyclotomic]
    decide
  have factor_degree {f : Polynomial (ZMod p)} (hf : f ∣ F)
      (hirr : Irreducible f) :
      f.natDegree = orderOf (ZMod.unitOfCoprime p hcop) := by
    simpa using natDegree_of_dvd_cyclotomic_of_irreducible
      (f := 1) (p := p) (by simp) hcop hf hirr
  constructor
  · intro hr
    have horder := (order_eq_two_iff p hcop).mpr hr
    obtain ⟨f, q, hfm, hfi, hqm, heq⟩ := split_monic hFm (by omega)
    have hfd : f.natDegree = 2 := (factor_degree ⟨q, heq⟩ hfi).trans horder
    have hqd : q.natDegree = 4 := by
      rw [heq, hfm.natDegree_mul hqm, hfd] at hFd
      omega
    obtain ⟨g, h, hgm, hgi, hhm, hqh⟩ := split_monic hqm (by omega)
    have heq' : F = f * g * h := by rw [heq, hqh, mul_assoc]
    have hgd : g.natDegree = 2 :=
      (factor_degree ⟨f * h, by rw [heq']; ac_rfl⟩ hgi).trans horder
    have hhd : h.natDegree = 2 := by
      rw [hqh, hgm.natDegree_mul hhm, hgd] at hqd
      omega
    have hhi : Irreducible h :=
      ZMod.irreducible_of_dvd_cyclotomic_of_natDegree hpn
        ⟨f * g, by rw [heq', mul_comm]⟩ (hhd.trans horder.symm)
    let e := translate p 1
    refine ⟨e f, e g, e h, translate_monic 1 hfm, translate_monic 1 hgm,
      translate_monic 1 hhm, (MulEquiv.irreducible_iff e).2 hfi,
      (MulEquiv.irreducible_iff e).2 hgi, (MulEquiv.irreducible_iff e).2 hhi,
      (translate_degree 1 f).trans hfd, (translate_degree 1 g).trans hgd,
      (translate_degree 1 h).trans hhd, ?_⟩
    rw [← map_mul, ← map_mul, ← heq']
    exact translate_cyclotomic p
  · rintro ⟨f, g, h, -, -, -, hfi, -, -, hfd, -, -, heq⟩
    let e := translate p 1
    have he : e F = shiftedQuotient p := translate_cyclotomic p
    have hfdiv : f ∣ e F := ⟨g * h, by rw [he, ← heq, mul_assoc]⟩
    have hfdiv' : e.symm f ∣ F := by
      simpa using map_dvd e.symm hfdiv
    have hfirr' : Irreducible (e.symm f) := (MulEquiv.irreducible_iff e.symm).2 hfi
    have hfd' : (e.symm f).natDegree = f.natDegree := by
      simpa only [translate, algEquivAevalXAddC_symm, e] using translate_degree (-1 : ZMod p) f
    exact (order_eq_two_iff p hcop).mp
      ((factor_degree hfdiv' hfirr').symm.trans (hfd'.trans hfd))

end OMA.S_oeis_a045473

#print axioms OMA.S_oeis_a045473.main

