from typing import List, Tuple
from functools import reduce
from testing import assert_eq, run_test

"""Solves for day 03"""

SAMPLE_CODE = """
..##.......
#...#...#..
.#....#..#.
..#.#...#.#
.#...##..#.
..#.##.....
.#.#.#....#
.#........#
#.##...#...
#...##....#
.#..#...#.#
"""

def common_traversal(grid: list[str],
                     xy_begin: tuple[int, int],
                     xy_increment: tuple[int, int]) -> int:
    accum = 0
    x, y = xy_begin
    x_incr, y_incr = xy_increment
    while True:
        if y >= len(grid):
            return accum
        if grid[y][x] == "#":
            accum += 1
        x = (x + x_incr) % len(grid[y])
        y += y_incr
    return accum

def part1(input: str) -> int:
    grid = [l for l in input.split("\n") if l]
    return common_traversal(grid, (3, 1), (3, 1))

def part2(input: str) -> int:
    grid = [l for l in input.split("\n") if l]
    xys = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
    accum = []
    for xy in xys:
        accum.append(common_traversal(grid, xy, xy))
    return reduce(lambda x, y: x * y, accum)

def test1() -> bool:
    return assert_eq(part1(SAMPLE_CODE), 7)

def test2() -> bool:
    return assert_eq(part2(SAMPLE_CODE), 336)

def tests():
    run_test(test1, __name__)
    run_test(test2, __name__)
