#! /usr/bin/python3

import subprocess

ERROR = -1
KO = 0
OK = 1

def check_nums(nums):
    out_bytes = subprocess.check_output(f"./push_swap {nums} | wc -l", shell=True)
    number_of_lines = int(out_bytes.decode("utf-8"))
    out_bytes = subprocess.check_output(f"./push_swap {nums} | ./checker {nums}", shell=True)
    out_str = out_bytes.decode("utf-8")
    print(f"Testing {nums}\t\tOperations Needed: {number_of_lines}", end=": ")
    if "Error\n" in out_str:
        return -1
    if "KO\n" in out_str:
        return 0
    if "OK\n" in out_str:
        return 1
    return -2

def check_error(nums):
    if check_nums(nums) == -1:
        return 1
    return 0

def check_KO(nums):
    if check_nums(nums) == 0:
        return 1
    return 0

def check_OK(nums, expected=1):
    msg = ["ERROR", "KO", "OK"]
    res = check_nums(nums)
    if res == expected:
        print("\033[0;32m", end="")
    else:
        print("\033[0;31m", end="")
    print(f"{msg[res + 1]}\033[0;0m")
    return res == expected

if __name__ == '__main__':
    subprocess.call("make")
    total = 0
    success = 0

    test_cases = ["4 2 3", "3 2 1 0", "-5 10 8 -7 94 -800 33"]
    error_cases = ["1 one 3", "1 3 1 2", "2 % 4", "1 0 -5 7 -0 8",
            "2147483648", "-2147483649"]
    ko_cases = []
    for case in test_cases:
        total += 1
        success += check_OK(case, OK)
    for case in error_cases:
        total += 1
        success += check_OK(case, ERROR)
    for case in ko_cases:
        total += 1
        success += check_OK(case, KO)

    print(f"Tests Passed: {success}/{total}")
