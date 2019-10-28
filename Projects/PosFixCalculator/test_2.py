import os
import subprocess

with subprocess.Popen('gcc -Wall -ansi new_part2.c -o part2.exe'.split(" "), stdout=subprocess.PIPE, stderr=subprocess.PIPE) as compa:
    outm = compa.stdout.read()
    comp = outm.decode("utf-8")
    oute = compa.stderr.read()
    comp += oute.decode("utf-8")

def test_me(v, exp):
    with subprocess.Popen(["part2.exe"], stdout=subprocess.PIPE, stdin=subprocess.PIPE) as proc:
        proc.stdin.write(bytes(v + "\n", 'ascii'))
        proc.stdin.flush()
        out = proc.stdout.read().decode('ascii')
        if out[:-2] == exp:
            print("[PASS] " + v + " : " + out[:-2])
            return 1
        else:
            print("[FAIL] " + v + " : " + out[:-2] + " (expected: " + exp + ")")
            return 0


tests = [
    ["1 + 2 * 3", "1 2 3 * +"],
    ["(1 + 2) * 3", "1 2 + 3 *"],
    ["(3.14 * 2.5) + 7 - (0.25 / 1 + 42)", "3.14 2.5 * 7 + 0.25 1 / 42 + -"],
    ["1 ^ 3 * 5 + 4 / 2", "1 3 ^ 5 * 4 2 / +"],
    ["(4 * [7] + 3 / 5 ^ 2) * 4 + 1", "4 7 * 3 5 2 ^ / + 4 * 1 +"],
    ["7 + 3 / 5 ^ 2", "7 3 5 2 ^ / +"],
    ["7 + 3 / 5 ^ 2 + 3 * 2", "7 3 5 2 ^ / + 3 2 * +"]
]

if len(comp) > 0:
    print("Test interrupted by compilation problems/warnings:")
    print(comp)
else:
    t = 0
    p = 0
    for v in tests:
        t+=1
        if test_me(v[0], v[1]):
            p+=1
    print("Success rate: " + ("%.1f" % (100*(p/t))) +"%")