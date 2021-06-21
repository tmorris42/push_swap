#! /usr/bin/python3

import subprocess
import random
import itertools
from datetime import datetime

ERROR = -1
KO = 0
OK = 1
TIMEOUT = 2
UNKNOWN = 3

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
    return 3

def check_OK(program_name, nums, expected=1):
    msg = ["ERROR", "KO", "OK", "TIMEOUT", "UNKNOWN"]
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
            "-238 -298 -7 103 -85 -165 163 -16 38 -2 -287 252 50 208 -145 -49 -272 272 -46 76 -188 -80 -215 -264 37 166 -200 -176 131 126 270 111 -195 281 45 -203 277 -174 226 -32 121 92 48 59 232 -106 -224 5 -96 -114 -35 212 87 186 116 -105 91 249 -115 271 -225 -33 -278 -87 -164 -180 -185 -222 8 80 84 -40 -190 -63 266 283 241 -89 -113 117 -124 -162 228 293 -237 259 -36 -192 279 130 -253 -233 254 -20 -240 267 -157 -111 282 -125",
            "6 -283 77 210 -272 -122 118 -246 101 -144 259 -277 -55 -227 -38 169 124 -276 89 214 120 186 266 -7 -131 -182 -226 -67 40 -118 239 -21 177 -145 155 275 -194 175 -166 -292 95 -95 203 243 134 -160 57 276 -92 -287 -248 99 253 36 -138 215 -46 -43 -250 192 -52 -29 68 113 -96 -115 274 142 -199 -86 147 126 78 262 138 -205 25 -271 -3 294 -105 -187 268 -158 -175 295 31 280 -59 -284 -142 -269 181 -26 -206 202 -213 299 61 -123",
            "-261 -271 -117 -231 56 59 144 -283 260 272 49 171 -91 -189 62 -208 -266 -101 298 20 -239 -16 28 -103 93 -73 167 -259 -4 75 248 263 5 -275 -33 118 -45 -121 143 210 132 -60 -67 64 -164 135 29 -246 -50 84 35 -214 -85 -148 57 4 166 242 9 -145 -147 -22 160 -104 -267 -15 65 73 184 50 218 -150 180 -251 -107 -44 106 -235 154 141 63 234 -221 159 261 193 70 113 -210 276 -127 -293 179 -176 197 -270 -27 -232 262 240",
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
