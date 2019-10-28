import os
import subprocess

with subprocess.Popen('gcc -Wall -ansi part1.c -o part1.exe'.split(" "), stdout=subprocess.PIPE, stderr=subprocess.PIPE) as compa:
    outm = compa.stdout.read()
    comp = outm.decode("utf-8")
    oute = compa.stderr.read()
    comp += oute.decode("utf-8")

valid = [
    "1 + 2 * 3",
    "[(1 + 2) * 3]",
    "(1 + 2) ^ (3)",
    "{2 ^ [3 - (4 / 8)]}",
    "1.5 + 3.14 * (7)"
]

invalid = [
    "(1 + 2) * 3)",
    ")1 + 2( * (3)",
    "2 2",
    "1 + (2 * 3("
]

def test_me(v, exp):
    with subprocess.Popen(["part1.exe"], stdout=subprocess.PIPE, stdin=subprocess.PIPE) as proc:
        proc.stdin.write(bytes(v + "\n", 'ascii'))
        proc.stdin.flush()
        out = proc.stdout.read().decode('ascii')
        if out[:-2] == exp:
            print("[PASS] " + v + ": " + out[:-2])
            return 1
        else:
            print("[FAIL] " + v + ":" + out[:-2] + "-> (expected: " + exp + ")")
            return 0


if len(comp) > 0:
    print("Test interrupted by compilation problems/warnings:")
    print(comp)
else:
    t = 0
    p = 0
    for v in valid:
        t+=1
        if test_me(v, "VALIDA"):
            p+=1
    for v in invalid:
        t+=1
        if test_me(v, "INVALIDA"):
            p+=1
    print("Success rate: " + ("%.1f" % (100*(p/t))) +"%")