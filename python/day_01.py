from testing import assert_eq, run_test

"""Solves for day 01"""

SAMPLE_CODE = """1721
979
366
299
675
1456
"""

def part1(input: str) -> int:
    vals = [int(l) for l in input.split("\n") if l]
    v_set = set()
    for v in vals:
        if 2020 - v in v_set:
            return v * (2020 - v)
        v_set.add(v)
    return 0

def part2(input: str) -> int:
    vals = [int(l) for l in input.split("\n") if l]
    v_set = set()
    for v in vals:
        for a in v_set:
            for b in v_set:
                if a == b:
                    continue
                elif a + b == 2020 - v:
                    return a * b * v
        v_set.add(v)
    return 0

def test1() -> bool:
    return assert_eq(part1(SAMPLE_CODE), 514579)

def test2() -> bool:
    return assert_eq(part2(SAMPLE_CODE), 241861950)

def tests():
    run_test(test1, __name__)
    run_test(test2, __name__)
