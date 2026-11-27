"""Check selected A113271 terms against factors of 2^r - 1 or a prime interval."""
import argparse
from math import gcd

from scan_a113271 import primes_up_to, residue, verify_divisor


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("indices", type=int, nargs="+")
    parser.add_argument("--orders", type=int, default=0)
    parser.add_argument("--prime-range", type=int, nargs=2, metavar=("AFTER", "THROUGH"))
    options = parser.parse_args()
    if min(options.indices) < 5:
        parser.error("indices must be at least 5")
    primes = []
    if options.prime_range:
        lower, upper = options.prime_range
        if not 2 <= lower < upper:
            parser.error("Require 2 <= AFTER < THROUGH")
        primes = [p for p in primes_up_to(upper) if p > lower]
    for n in options.indices:
        exponents = [i << (n - i) for i in range(n + 1)]
        if options.orders:
            for order in range(2, options.orders + 1):
                modulus = (1 << order) - 1
                representative = sum(1 << (exponent % order) for exponent in exponents)
                divisor = gcd(representative, modulus)
                if 1 < divisor and verify_divisor(n, divisor):
                    print(f"Index {n}: proper divisor {divisor} from order {order}", flush=True)
                    break
            else:
                print(f"Index {n}: no proper divisor found at orders through {options.orders}", flush=True)
        if primes:
            divisor = next((p for p in primes if residue(exponents, p) == 0
                            and verify_divisor(n, p)), None)
            print(f"Index {n}: proper divisor in ({lower}, {upper}] = {divisor}", flush=True)


if __name__ == "__main__":
    main()

