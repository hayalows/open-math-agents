"""Verify the A045473 factor-degree pattern for every prime below 500."""
from collections import Counter
from math import isqrt


def trim(polynomial):
    while polynomial and polynomial[-1] == 0:
        polynomial.pop()
    return polynomial


def remainder(dividend, divisor, prime):
    result = trim(dividend.copy())
    inverse = pow(divisor[-1], -1, prime)
    while len(result) >= len(divisor):
        offset = len(result) - len(divisor)
        scale = result[-1] * inverse % prime
        for index, coefficient in enumerate(divisor):
            result[offset + index] = (result[offset + index] - scale * coefficient) % prime
        trim(result)
    return result


def multiply_mod(left, right, modulus, prime):
    product = [0] * (len(left) + len(right) - 1)
    for i, a in enumerate(left):
        for j, b in enumerate(right):
            product[i + j] = (product[i + j] + a * b) % prime
    return remainder(product, modulus, prime)


def power_mod(base, exponent, modulus, prime):
    result = [1]
    while exponent:
        if exponent % 2:
            result = multiply_mod(result, base, modulus, prime)
        base = multiply_mod(base, base, modulus, prime)
        exponent //= 2
    return result


def gcd_degree(left, right, prime):
    while right:
        left, right = right, remainder(left, right, prime)
    return len(left) - 1


expected = {1: (1,) * 6, 2: (3, 3), 3: (6,), 4: (3, 3), 5: (6,), 6: (2, 2, 2)}
tested = Counter()
for prime in range(2, 500):
    if any(prime % n == 0 for n in range(2, isqrt(prime) + 1)):
        continue
    tested[prime % 7] += 1
    polynomial = [c % prime for c in (7, 21, 35, 35, 21, 7, 1)]
    if prime == 7:
        assert polynomial == [0] * 6 + [1]
        continue

    derivative = [i * polynomial[i] % prime for i in range(1, len(polynomial))]
    assert gcd_degree(polynomial, trim(derivative), prime) == 0
    frobenius = [0, 1]
    counts = {}
    for degree in range(1, 7):
        frobenius = power_mod(frobenius, prime, polynomial, prime)
        difference = frobenius + [0] * max(0, 2 - len(frobenius))
        difference[1] = (difference[1] - 1) % prime
        common_degree = gcd_degree(polynomial, trim(difference), prime)
        lower_degree = sum(d * count for d, count in counts.items() if degree % d == 0)
        counts[degree], rest = divmod(common_degree - lower_degree, degree)
        assert rest == 0 and counts[degree] >= 0
    actual = tuple(d for d, count in counts.items() for _ in range(count))
    assert actual == expected[prime % 7], (prime, actual)

assert set(tested) == set(range(7))
print(f"Passed for all {sum(tested.values())} primes below 500, covering every residue modulo 7.")
for residue in range(7):
    print(f"Residue {residue}: {tested[residue]} primes; " +
          ("X^6 in characteristic 7" if residue == 0 else f"factor degrees {expected[residue]}"))

