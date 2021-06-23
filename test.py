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
    if number_of_lines <= maximum_moves(num_of_nums):
        print("[\033[0;32m", end='')
    else:
        print("[\033[0;31m", end='')
        error_log(f"TOO MANY MOVES ({number_of_lines})\n"+nums);
    if len(nums) > 20:
        nums = "/" + str(num_of_nums) + " numbers/"
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
            "-261 -271 -117 -231 56 59 144 -283 260 272 49 171 -91 -189 62 -208 -266 -101 298 20 -239 -16 28 -103 93 -73 167 -259 -4 75 248 263 5 -275 -33 118 -45 -121 143 210 132 -60 -67 64 -164 135 29 -246 -50 84 35 -214 -85 -148 57 4 166 242 9 -145 -147 -22 160 -104 -267 -15 65 73 184 50 218 -150 180 -251 -107 -44 106 -235 154 141 63 234 -221 159 261 193 70 113 -210 276 -127 -293 179 -176 197 -270 -27 -232 262 240",
            "-136 281 16 106 236 -288 92 122 298 102 233 240 40 195 -84 116 7 72 290 -255 -283 -27 54 -107 -28 58 -137 161 118 260 -213 -295 224 -24 101 -173 141 291 267 -51 -219 -64 151 -162 246 36 235 219 222 143 95 46 -118 -292 -287 -3 -125 126 -109 57 239 183 75 -36 170 299 142 129 -73 93 18 199 223 11 -52 -112 -192 -263 -7 -291 -66 -166 20 -99 206 -102 -54 -76 -100 51 133 3 277 229 251 -11 -298 4 -196 104",
            "256 234 -191 -14 299 -45 -255 225 -152 221 -134 -177 2 90 16 165 -234 -199 -63 -21 249 226 93 286 -92 196 -194 -144 -183 243 180 -282 -257 -270 140 150 -290 115 227 -149 281 -256 147 -29 -277 114 -22 164 143 60 -115 15 -196 161 -141 137 151 70 -156 -78 -162 -100 230 -293 -121 -271 -46 237 -123 -59 -226 54 47 82 272 158 -57 -244 -223 8 168 274 105 215 241 46 218 -83 98 29 251 -103 112 118 -158 65 -36 149 -31 -112",
            "175 278 -218 143 218 52 141 2 -190 -258 191 111 121 284 130 -101 287 -81 64 -113 82 208 -80 -47 -199 -43 37 221 272 -133 -179 -198 -231 33 274 80 -282 214 190 276 -41 68 159 102 -154 9 150 187 146 -176 -112 180 77 -27 -279 -270 151 -216 -72 -254 -161 -293 115 87 212 207 69 -75 -69 202 186 84 -77 34 -144 -141 268 39 213 277 -132 296 -71 -32 107 -182 -131 206 -239 120 197 -180 210 216 -240 -30 129 -159 73 158",
            "-285 119 -15 -220 275 85 -193 -188 -118 -167 95 -151 -258 84 139 204 261 -149 263 -225 -195 43 -201 288 -159 -276 -196 152 184 -269 -207 182 -211 262 -158 -240 240 41 -37 -282 -51 -299 153 -116 234 -132 -112 -82 -38 -297 -92 54 167 -55 171 243 78 36 29 233 299 -224 -75 163 117 18 127 151 193 -97 249 297 -79 -123 -31 144 284 -135 266 -228 -160 231 -250 -260 59 128 35 215 -58 -275 -162 -280 -245 -5 -30 75 55 -177 -210 -1",
            "-140 -105 -48 -213 184 82 -198 -255 -133 145 -38 97 297 -251 -85 -195 7 213 -223 -157 47 -228 266 275 48 61 -202 -22 -152 -233 -154 -90 -54 -298 26 151 -253 299 89 123 60 172 226 -44 -170 -34 -200 159 87 148 23 -183 243 -275 -21 176 228 171 258 -122 19 -221 -252 -283 -110 -231 -59 -150 -177 -212 -111 -274 -292 -175 279 18 211 -63 -289 -182 -282 -50 -193 -88 -191 265 209 -272 -240 10 -178 291 198 -287 -33 296 71 -126 233 -276",
            "-238 -298 -7 103 -85 -165 163 -16 38 -2 -287 252 50 208 -145 -49 -272 272 -46 76 -188 -80 -215 -264 37 166 -200 -176 131 126 270 111 -195 281 45 -203 277 -174 226 -32 121 92 48 59 232 -106 -224 5 -96 -114 -35 212 87 186 116 -105 91 249 -115 271 -225 -33 -278 -87 -164 -180 -185 -222 8 80 84 -40 -190 -63 266 283 241 -89 -113 117 -124 -162 228 293 -237 259 -36 -192 279 130 -253 -233 254 -20 -240 267 -157 -111 282 -125",
            "6 -283 77 210 -272 -122 118 -246 101 -144 259 -277 -55 -227 -38 169 124 -276 89 214 120 186 266 -7 -131 -182 -226 -67 40 -118 239 -21 177 -145 155 275 -194 175 -166 -292 95 -95 203 243 134 -160 57 276 -92 -287 -248 99 253 36 -138 215 -46 -43 -250 192 -52 -29 68 113 -96 -115 274 142 -199 -86 147 126 78 262 138 -205 25 -271 -3 294 -105 -187 268 -158 -175 295 31 280 -59 -284 -142 -269 181 -26 -206 202 -213 299 61 -123",
            "-261 -271 -117 -231 56 59 144 -283 260 272 49 171 -91 -189 62 -208 -266 -101 298 20 -239 -16 28 -103 93 -73 167 -259 -4 75 248 263 5 -275 -33 118 -45 -121 143 210 132 -60 -67 64 -164 135 29 -246 -50 84 35 -214 -85 -148 57 4 166 242 9 -145 -147 -22 160 -104 -267 -15 65 73 184 50 218 -150 180 -251 -107 -44 106 -235 154 141 63 234 -221 159 261 193 70 113 -210 276 -127 -293 179 -176 197 -270 -27 -232 262 240",
            "197 -64 88 261 28 -82 125 122 286 -131 -232 -66 -35 213 -194 96 227 -9 287 -237 -176 -114 297 11 108 -96 85 -195 -124 110 -89 -95 -17 69 -259 254 -14 -23 37 -70 -47 204 -261 154 279 271 289 -284 45 -169 77 144 298 -167 274 -152 189 -42 -222 -280 153 -182 -67 99 -153 -245 -271 -149 158 -34 -221 138 -121 36 -88 247 -16 -263 -52 219 209 47 200 -24 116 148 170 -26 220 195 -228 294 276 -251 124 43 -57 229 293 2 262 -68 -111 252 -21 285 -218 93 -276 -110 -210 97 -258 -246 -200 -156 -93 284 -27 -267 -7 75 -44 -260 -282 246 3 265 268 103 -108 -216 41 -84 -252 65 257 -226 -171 90 -234 24 22 -296 18 133 -119 44 -300 -211 -208 245 -193 -43 29 -241 -54 1 -118 21 68 -87 186 -179 139 183 49 81 10 -227 299 243 -112 152 250 -91 -139 -140 70 23 58 14 270 -127 149 191 -164 -262 -116 238 -81 272 -238 -233 -293 -135 256 -104 -266 27 115 160 -236 205 119 255 162 117 131 50 -243 -25 -224 39 -39 288 -142 -230 -239 92 89 208 156 33 180 266 -83 -265 -100 147 35 -274 -173 -107 198 57 73 95 -50 181 -281 48 -183 66 194 -244 278 218 216 295 -5 206 -161 -199 -76 -19 -198 -53 -103 -130 -285 -55 185 107 -168 151 -80 13 190 -115 169 -165 -120 -178 5 263 -32 -126 78 -122 168 -190 -212 259 136 -137 -202 104 237 -98 -49 223 -256 6 275 228 179 38 -174 -132 132 155 -150 -223 -125 -20 202 127 -162 -61 178 -46 51 120 83 280 84 -206 -134 150 -105 203 199 -85 0 -37 -4 -63 -144 4 240 -29 -154 248 -145 277 137 -33 -191 -79 244 174 239 -72 173 -264 196 -219 175 -217 -255 188 146 249 -75 -242 -209 -225 114 20 12 182 111 -290 15 187 -283 -28 52 141 -207 -181 -235 64 -136 101 -205 34 9 292 -69 -157 -1 -123 -22 161 61 283 8 91 -248 -60 -298 126 -31 226 -270 -240 234 71 -30 -148 -18 253 17 264 207 -249 -147 -166 -128 32 -295 -163 273 282 -188 40 -36 -275 -186 142 -151 -101 -117 157 -247 163 -299 -129 -58 -288 -94 291 -77 -143 235 -197 -97 -138 -13 -189 79 54 82 76 214 296 -291 -289 233 -231 140 164 159 267 74 -92 -45 -268 46 26 42 112 -272 184 -214 7 134 86 224 -41 -286 -287 113 106 72 -40 -11 -78 269 -273 -279 225 -99 -177 222 -196 -250 53 -6 -73 193 -59 217 -185 -141 -155 63 56",
            "279 -61 -7 155 235 291 -201 -46 70 -170 -155 264 81 26 -231 -119 172 -295 182 249 227 -256 -80 74 -67 171 -18 -112 20 -148 -66 224 -242 91 -55 118 208 183 -95 170 254 -217 -246 201 57 -135 -74 240 6 127 -118 -166 -207 -62 261 122 157 256 -181 160 62 237 150 161 276 -84 -153 210 253 142 73 -250 -199 -264 -281 -273 -1 22 59 4 284 103 116 133 90 180 -200 -16 293 257 -40 -17 -226 -20 -75 187 -156 -147 -294 270",
            "12 1 201 -289 -77 -133 -256 -132 56 -128 -246 -247 175 -218 298 220 281 33 218 92 -81 -294 45 127 -270 -189 70 -255 75 87 137 -124 -205 215 32 167 -184 192 -3 -27 157 -69 -57 233 177 -215 22 -137 -171 -209 105 35 -161 156 153 178 -204 -267 -272 203 -44 132 -103 -283 -135 120 -177 -95 264 17 294 -141 104 -253 -20 -39 184 287 -36 254 232 -221 -163 74 113 -87 107 248 -54 28 193 221 -92 -70 57 116 -235 185 292 -295",
            "-48 -77 -94 80 -35 -36 -91 -41 -187 -74 75 26 73 -194 -32 94 148 -280 -136 -19 109 184 -5 276 202 -112 -128 -153 29 193 260 270 -143 -212 41 -23 -98 114 -22 -85 -64 -33 108 -262 -191 -11 -130 152 -7 -58 -28 -192 290 21 59 -96 -150 -13 58 19 -42 -88 35 68 156 171 -127 -27 144 194 167 -244 45 -293 -110 240 9 -148 -271 113 237 -265 117 54 165 61 153 223 -83 -12 220 222 -214 174 -209 -217 106 -151 188 -6",
            "-58 -153 123 -154 -226 144 -181 212 -255 -257 -112 233 -9 -143 -99 262 -7 179 -90 154 -186 -56 207 -115 -54 157 98 209 -111 119 257 276 -18 91 -178 49 -59 93 -67 -126 -288 245 222 274 196 -81 -20 6 268 244 211 43 202 -37 -260 238 113 174 203 -172 -85 -113 -31 -271 266 -195 -238 -98 -160 -173 -205 -23 208 -200 104 16 -285 -15 109 284 152 -82 65 -221 -75 277 278 285 156 -211 -76 -240 137 129 -138 38 169 279 -45 218",
            " ".join(random.sample([str(x) for x in range(-300, 300)], 100)),
#            " ".join(random.sample([str(x) for x in range(-300, 300)], 500)),
            ]
    error_cases = ["1 one 3", "1 3 1 2", "2 % 4", "1 0 -5 7 -0 8",
            "2147483648", "-2147483649",
            "1 2 2",
            "1 0 2 -0",
            ]
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
            " ".join(random.sample([str(x) for x in range(-300, 300)], random.randint(1, 500))),
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
