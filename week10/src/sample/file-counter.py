#!/usr/bin/env python3
# 	ファイルに値を保存するカウンタ(Python)
# 	~yas/syspro/file/file-counter-python.rb
import sys

DATA_FILENAME = "file-counter-value.data"
comname = sys.argv[0]

def usage():
    print(f"Usage$ {comname} {{get,inc,set newvalue}}")
    print(f"Data file: {DATA_FILENAME}")
    exit(1)
    return

def main(argv):
    if len(argv) <= 1:
        usage()
    cmd = argv[1]
    counter = 0
    if cmd == "get":
        counter = counter_load()
    elif cmd == "inc":
        counter = counter_load()
        counter += 1
    elif cmd == "set":
        if len(argv) != 3:
            usage()
        newvalue = int(argv[2])
        counter = newvalue
    else:
        usage()
    print(counter)
    if cmd != "get":
        counter_save(counter)
    return

def counter_load():
    counter = 0
    try:
        with open(DATA_FILENAME, "rb") as f:
            counter_bytes = f.read(4)
            counter = int.from_bytes(counter_bytes, byteorder=sys.byteorder)
    except FileNotFoundError:
        pass
    return counter

def counter_save(counter):
    counter_bytes = counter.to_bytes(4, byteorder=sys.byteorder)
    with open(DATA_FILENAME, "wb") as f:
        f.write(counter_bytes)
    return

main(sys.argv)
