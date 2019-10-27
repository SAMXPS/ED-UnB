import os
import subprocess

with subprocess.Popen('gcc -Wall -ansi part1.c -o part1.exe'.split(" "), stdout=subprocess.PIPE) as compa:
    out = compa.stdout.read()
    comp = out.decode("utf-8")

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
        else:
            print("[FAIL] " + v + ":" + out[:-2] + "-> (expected: " + exp + ")")


if len(comp) > 0:
    print("Test interrupted by compilation problems/warnings:")
    print(comp)
else:
    for v in valid:
        test_me(v, "VALIDA")
    for v in invalid:
        test_me(v, "INVALIDA")