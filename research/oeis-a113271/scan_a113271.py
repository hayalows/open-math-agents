"""Find and verify proper divisors of OEIS A113271 without constructing large terms."""
import argparse
import csv
import math
from pathlib import Path


def primes_up_to(limit):
    sieve = bytearray(b"\1") * (limit + 1)
    sieve[:2] = b"\0\0"
    for divisor in range(2, math.isqrt(limit) + 1):
        if sieve[divisor]:
            start = divisor * divisor
            sieve[start::divisor] = bytes((limit - start) // divisor + 1)
    return [p for p in range(3, limit + 1) if sieve[p]]


def residue(exponents, prime):
    return sum(pow(2, exponent % (prime - 1), prime) for exponent in exponents) % prime


def verify_divisor(n, divisor):
    # Independent evaluation of the original, unreduced base/exponent formula.
    original_residue = sum(pow(pow(2, i, divisor), 1 << (n - i), divisor)
                           for i in range(n + 1)) % divisor
    # The i=1 summand alone is 2**(2**(n-1)).
    strict_lower_bound = (1 << (n - 1)) >= divisor.bit_length()
    return strict_lower_bound and original_residue == 0


def scan(stop, prime_limit, output):
    if [sum(1 << (i * (1 << (n - i))) for i in range(n + 1))
        for n in range(6)] != [1, 3, 9, 41, 593, 135457]:
        raise ValueError("The exponents disagree with OEIS")
    primes = primes_up_to(prime_limit)
    covered = 0
    unsieved = []
    with output.open("w", encoding="utf-8", newline="") as handle:
        writer = csv.writer(handle)
        writer.writerow(("index", "proper_divisor"))
        for n in range(5, stop + 1):
            exponents = [i << (n - i) for i in range(n + 1)]
            divisor = next((p for p in primes if residue(exponents, p) == 0), None)
            if divisor is None:
                unsieved.append(n)
                print(f"No divisor at index {n} among primes through {prime_limit}", flush=True)
                continue
            if not verify_divisor(n, divisor):
                raise ValueError(f"Independent witness check failed at index {n}")
            writer.writerow((n, divisor))
            covered += 1
    first = unsieved[0] if unsieved else stop + 1
    print(f"Verified {covered} divisors for indices 5..{stop}; continuous coverage 5..{first - 1}.")
    print(f"Unsieved indices: {unsieved}")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("stop", type=int)
    parser.add_argument("prime_limit", type=int)
    parser.add_argument("output", type=Path)
    options = parser.parse_args()
    if options.stop < 5 or options.prime_limit < 3:
        parser.error("Require stop >= 5 and prime_limit >= 3")
    scan(options.stop, options.prime_limit, options.output)

