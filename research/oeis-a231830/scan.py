"""Search all indices of A231830 for square divisors from a bounded prime range."""
import argparse
import csv
import math


def primes_up_to(limit):
    sieve = bytearray(b"\1") * (limit + 1)
    sieve[:2] = b"\0\0"
    for p in range(2, math.isqrt(limit) + 1):
        if sieve[p]:
            sieve[p*p::p] = bytes((limit - p*p) // p + 1)
    return (p for p in range(2, limit + 1) if sieve[p])


def first_divisible_index(p):
    # Brent's cycle test compares one orbit state per step.
    state = anchor = 5 % p
    index = 1
    window = 1
    traversed = 0
    while True:
        if state == 0:
            return index
        if state == 1 or (traversed and state == anchor):
            return None
        if traversed == window:
            anchor = state
            window *= 2
            traversed = 0
        state = ((state - 1) * state * state + 1) % p
        index += 1
        traversed += 1


def square_residue(p, index):
    # In a(n) = 1 + 4*P(n-1)^2, P(n)=P(n-1)*a(n).
    modulus = p * p
    cumulative = 1
    for _ in range(1, index):
        cumulative = cumulative * (1 + 4 * cumulative * cumulative) % modulus
    return (1 + 4 * cumulative * cumulative) % modulus


def scan(limit, csv_path):
    tested = hits = 0
    with open(csv_path, "w", newline="", encoding="utf-8") as out:
        writer = csv.writer(out)
        writer.writerow(("prime", "first_index", "residue_mod_prime_squared"))
        for p in primes_up_to(limit):
            if p % 4 != 1:
                continue
            tested += 1
            index = first_divisible_index(p)
            if index is None:
                continue
            hits += 1
            residue = square_residue(p, index)
            if residue % p:
                raise ValueError(f"Independent recurrence disagrees at p={p}, n={index}")
            writer.writerow((p, index, residue))
            if residue == 0:
                print(f"COUNTEREXAMPLE p={p} index={index} square={p*p} tested={tested}")
                return
    print(f"No square divisor from primes <= {limit}; checked {tested} eligible primes, "
          f"{hits} primes dividing a term once.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("limit", type=int)
    parser.add_argument("csv")
    args = parser.parse_args()
    if args.limit < 5:
        parser.error("limit must be at least 5")
    scan(args.limit, args.csv)
