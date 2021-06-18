#! /usr/bin/python3

import subprocess
import random
import itertools
from datetime import datetime

ERROR = -1
KO = 0
OK = 1
TIMEOUT = 2

LOGFILE = "logs/" +  datetime.now().strftime("%Y-%m-%d-%H-%M-%S") + ".log"

def error_log(nums):
    with open(LOGFILE, "a") as out:
        out.write(nums);
        out.write("\n\n");

def maximum_moves(number_of_numbers):
    maximum = 0
    reqs = (
            (3, (3,)),
            (5, (12,)),
            (100, (700, 900, 1100, 1300, 1500)),
            (500, (5500, 7000, 8500, 10000, 11500))
            )
    for cutoff in reqs:
        if number_of_numbers <= cutoff[0]:
            maximum = cutoff[1][0]
            return maximum

def check_nums(program_name, nums):
    try:
        out_bytes = subprocess.run(f"{program_name} {nums} | wc -l", shell=True, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL, timeout=5)
        number_of_lines = int(out_bytes.stdout.decode("utf-8"))
        out_bytes = subprocess.run(f"{program_name} {nums} | ./checker {nums}", shell=True, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, timeout=5)
        out_str = out_bytes.stdout.decode("utf-8")
        num_of_nums = len(nums.split())
    except subprocess.TimeoutExpired:
        return TIMEOUT
    if len(nums) > 20:
        nums = "/" + str(num_of_nums) + " numbers/"
    if number_of_lines <= maximum_moves(num_of_nums):
        print("[\033[0;32m", end='')
    else:
        print("[\033[0;31m", end='')
    print(f"({number_of_lines})\033[0;0m] {nums} [", end="")
    if "Error\n" in out_str:
        #print("ERROR MESSAGES: ==========\n", out_str, "\n==========\n")
        return ERROR
    if "KO\n" in out_str:
        return KO
    if "OK\n" in out_str:
        return OK
    return -2

def check_OK(program_name, nums, expected=1):
    msg = ["ERROR", "KO", "OK", "TIMEOUT"]
    res = check_nums(program_name, nums)
    if res == expected:
        print("\033[0;32m", end="")
    else:
        print("\033[0;31m", end="")
        error_log(nums)
    print(f"{msg[res + 1]}\033[0;0m]", end="\n")
    return res == expected

if __name__ == '__main__':
    subprocess.call("make")

    test_cases = []
    test_cases = [str(x).replace(',', '').replace('(', '').replace(')', '') for x in itertools.permutations(range(0, 3), 3)]
    test_cases += [
            "4 2 3",
            "4 3 1",
            "2 -1 5",
            "-9 9 5",
            "3 9 0",
            "3 2 1 0",
            "5 2 3 1 4",
            "4 2 5 3 1",
            "4 7 3 8 2 5 1",
            "-5 10 8 -7 94 -800 33",
            "1 5 9 7 3 4 8 6 2",
            "1 76 4 6 38 9 18 -4 -36 100 -72 0 -41 3 17",
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
#            " ".join(random.sample([str(x) for x in range(-300, 300)], 500)),
            ]
    error_cases = ["1 one 3", "1 3 1 2", "2 % 4", "1 0 -5 7 -0 8",
            "2147483648", "-2147483649"]
    test_cases += [
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
            " ".join(random.sample([str(x) for x in range(-300, 300)], 500)),
        ]
#    error_cases = []

    program_names = [
            "./push_swap",
           # "./four_hold_sort_mod", 
            ]
            #"./hold_sort_mod",]# "./best_so_far", ]#"./sort_5", "./rough_sort"]

    for program_name in program_names:
        total = 0
        success = 0
        print(f"Checking {program_name}")
        for case in test_cases:
            total += 1
            success += check_OK(program_name, case, OK)
        for case in error_cases:
            total += 1
            success += check_OK(program_name, case, ERROR)
        print(f"Tests Passed: {success}/{total}\n\n")
