module

public section

/-- A residue modulo seven squares to one without itself being one exactly when it is six. -/
theorem orderTwoModuloSeven (p : Nat) :
    (p * p % 7 = 1 ∧ p % 7 ≠ 1) ↔ p % 7 = 6 := by
  rw [Nat.mul_mod p p 7]
  have hlt : p % 7 < 7 := Nat.mod_lt _ (by decide)
  generalize p % 7 = r at *
  have cases : r = 0 ∨ r = 1 ∨ r = 2 ∨ r = 3 ∨ r = 4 ∨ r = 5 ∨ r = 6 := by omega
  rcases cases with rfl | rfl | rfl | rfl | rfl | rfl | rfl <;> decide

#print axioms orderTwoModuloSeven
