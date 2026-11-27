"""Check published A362252 and A362253 prime-index pairs modulo p squared."""
import argparse
from itertools import zip_longest
from pathlib import Path


def table(path):
    for line in path.read_text(encoding="utf-8-sig").splitlines():
        row = line.strip()
        if row and not row.startswith("#"):
            yield tuple(map(int, row.split()))


def verify(primes_path, indices_path):
    checked = 0
    for expected, (prime_row, index_row) in enumerate(
        zip_longest(table(primes_path), table(indices_path)), 1
    ):
        if prime_row is None or index_row is None:
            raise ValueError("Table lengths differ")
        row, prime = prime_row
        index_row_number, index = index_row
        if row != expected or index_row_number != row or prime <= 1 or index < 1:
            raise ValueError(f"Invalid or misaligned input at row {expected}")
        modulus = prime * prime
        value = 5 % modulus
        for _ in range(1, index):
            value = ((value - 1) * value * value + 1) % modulus
        if value % prime:
            raise ValueError(f"Published pair does not divide at row {row}")
        if not value:
            raise SystemExit(f"SQUARE DIVISOR: row {row}, prime {prime}, index {index}")
        checked += 1
    print(f"Checked {checked} published pairs with no square divisor.")


if __name__ == "__main__":
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("primes", type=Path)
    parser.add_argument("indices", type=Path)
    options = parser.parse_args()
    verify(options.primes, options.indices)
