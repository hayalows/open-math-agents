"""Find an arithmetic progression on which a(n) in OEIS A113271 has a fixed divisor."""
import argparse
from math import gcd, lcm


def term_mod(n, modulus):
    return sum(pow(2, i * (1 << (n - i)), modulus)
               for i in range(n + 1)) % modulus


def order_of_two(modulus):
    if modulus == 1:
        return 1
    value, order = 2 % modulus, 1
    while value != 1:
        value = 2 * value % modulus
        order += 1
    return order


def progression(n, modulus, period_of_two):
    if n < 1 or modulus <= 1 or modulus % 2 == 0:
        raise ValueError("Require positive n and an odd modulus greater than one")
    if period_of_two <= 0 or pow(2, period_of_two, modulus) != 1:
        raise ValueError("The proposed period of two is invalid")
    odd_part = period_of_two
    exponent = 0
    while odd_part % 2 == 0:
        odd_part //= 2
        exponent += 1
    if n + 1 < exponent:
        raise ValueError("The start precedes the range of the affine congruence")

    block = lcm(period_of_two, order_of_two(odd_part))
    a0 = term_mod(n, modulus)
    increment = (term_mod(n + block, modulus) - a0) % modulus
    common = gcd(increment, modulus)
    if a0 % common:
        return None
    period = modulus // common
    first_k = 0 if period == 1 else (-a0 // common * pow(increment // common, -1, period)) % period
    return n + first_k * block, block * period, block, increment


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("start", type=int)
    parser.add_argument("modulus", type=int)
    parser.add_argument("order_multiple", type=int)
    args = parser.parse_args()
    result = progression(args.start, args.modulus, args.order_multiple)
    if result is None:
        print("The affine residue progression never reaches zero.")
    else:
        first, stride, block, increment = result
        print(f"Divisibility for indices n = {first} + k*{stride}, k >= 0.")
        print(f"Residue increases by {increment} modulo {args.modulus} every {block} indices.")
