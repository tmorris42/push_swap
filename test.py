#! /usr/bin/python3

import subprocess

ERROR = -1
KO = 0
OK = 1

def check_nums(program_name, nums):
    out_bytes = subprocess.check_output(f"{program_name} {nums} | wc -l", shell=True)
    number_of_lines = int(out_bytes.decode("utf-8"))
    out_bytes = subprocess.check_output(f"{program_name} {nums} | ./checker {nums}", shell=True)
    out_str = out_bytes.decode("utf-8")
    print(f"({number_of_lines})\tTest [{nums}]", end="\t")
    if "Error\n" in out_str:
        #print("ERROR MESSAGES: ==========\n", out_str, "\n==========\n")
        return -1
    if "KO\n" in out_str:
        return 0
    if "OK\n" in out_str:
        return 1
    return -2

def check_OK(program_name, nums, expected=1):
    msg = ["ERROR", "KO", "OK"]
    res = check_nums(program_name, nums)
    if res == expected:
        print("\033[0;32m", end="")
    else:
        print("\033[0;31m", end="")
    print(f"{msg[res + 1]}\033[0;0m")
    return res == expected

if __name__ == '__main__':
    subprocess.call("make")

    test_cases = [
            "4 2 3",
            "4 3 1",
            "2 -1 5",
            "-9 9 5",
            "3 9 0",
            "3 2 1 0",
            "5 2 3 1 4",
            "4 2 5 3 1",
            "-5 10 8 -7 94 -800 33",
            "1 5 9 7 3 4 8 6 2",
            ]
    error_cases = ["1 one 3", "1 3 1 2", "2 % 4", "1 0 -5 7 -0 8",
            "2147483648", "-2147483649"]
    program_names = ["./push_swap", "./sort_5", "./rough_sort"]

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
