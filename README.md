aoc-impl-comparison
===================

`Advent of Code implement comparison`. This repo aims to expose the
complexity diff when trying to implement the same solution for
distinct programming languages.

The `aoc-2020` was chosen for this challenge. I won't solve the
entire edition, but just the initial days, instead...

As programming languages, `Python` and `C` was chosen since they're
the most _level-gap_[^level-gap] languages I know.

## Requirements

To run and build this program, you'll need:
- git
- gcc[^gcc]
- python interpreter

You can also use the `Makefile` and `wincbuild.bat` provided to
fast-(build|run) the program.

## Usage

- clone + change directory
```sh
git clone https://github.com/nasccped/aoc-impl-comparison
cd aoc-impl-comparison
```

### C code

- compile

```sh
mkdir -p out
gcc -o out/main.exe $(find c -type f -name *.c)
```

- run

```sh
out/main # for normal run
out/main test # for test run
```

> [!WARNING]
>
> At WindowsOS, you'll may need to use a `./` _(dot)_ before the executable
> path.

### Python code

- run

```sh
# for normal run
./out/main
# for test run
# ./out/main test
```

### Using the Makefile

You can use the Makefile to handle sources and bins.
```sh
make # this will print a help panel
```

> [!IMPORTANT]
>
> `make cbuild` recipe doesn't works well in Windows. Use
> `./wincbuild.bat` instead.

[^level-gap]: **level-gap:** the level distance (`high-level` |
  `low-level`) between languages
[^gcc]: **GCC** (GNU Compiler Collection) is a collection of
  compilers that transforms human-readable source code into
  machine-readable executable code.
