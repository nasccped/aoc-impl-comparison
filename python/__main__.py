import sys
import day_01
import day_02

# loading input as variables
for i in range(1, 3):
    with open(f"inputs/day-0{i}.txt", "r") as f:
        # you can access it later by using the variable literal:
        # i01 => input for day 1
        # i02 => input for day 2
        # ...
        # i0<n> => input for day <n>
        globals()[f"i0{i}"] = f.read()

def main():
    print("The solves are located on its respective python module")
    print("you can call it this function bellow")
    # the line bellow will print the result of day 1 (part 2).
    # works for other solves too
    print(day_01.part2(i01))

def tests():
    day_01.tests()
    day_02.tests()

if __name__ == "__main__":
    if (argc := len(sys.argv)) > 2:
        print(f"No action for this amount of args ({argc})")
        print("Aborting")
        exit(1)
    elif argc < 2:
        main()
    elif (arg := sys.argv[1]) == "test":
        tests()
    else:
        print(f"Non valid arg: {arg}")
        exit(1)
