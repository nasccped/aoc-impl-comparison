from testing import assert_eq, run_test

"""Solves for day 2"""
SAMPLE_CODE = """
1-3 a: abcde
1-3 b: cdefg
2-9 c: ccccccccc
"""

def part1(input: str) -> int:
    lines = [l for l in input.split("\n") if l]
    accum = 0
    for l in lines:
        nums, char, row = l.split(" ")
        min, max = (int(n) for n in nums.split("-"))
        char = char[0]
        if row.count(char) in range(min, max + 1):
            accum += 1
    return accum

def part2(input: str) -> int:
    lines = [l for l in input.split("\n") if l]
    accum = 0
    for l in lines:
        nums, char, row = l.split(" ")
        min, max = (int(n) for n in nums.split("-"))
        char = char[0]
        if (char == row[min - 1]) ^ (char == row[max - 1]):
            accum += 1
    return accum

def test1():
    return assert_eq(part1(SAMPLE_CODE), 2)

def test2():
    return assert_eq(part2(SAMPLE_CODE), 1)

def tests():
    run_test(test1, __name__)
    run_test(test2, __name__)
