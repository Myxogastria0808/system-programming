#!/usr/bin/env python3
# -*- coding: utf-8 -*-
import sys
import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)
import cgi

DATA_FILENAME = "file-counter-value.data"

def main() -> None:
    print_header()
    print_content()

def print_header() -> None:
    print("Content-Type: text/html\n", flush=True)
    return None

def print_content() -> None:
    counter: int = 0
    print("<HTML><HEAD></HEAD><BODY><PRE>",flush=True)
    qh: cgi.FieldStorage = cgi.FieldStorage(keep_blank_values=True)
    op: str | None = qh.getfirst("op",None)
    val: str | None = qh.getfirst("val", None)
    if op == "inc":
        counter = counter_load()
        counter += 1
        counter_save(counter)
        print(f"{counter}", flush=True)
    elif op == "set":
        if val is not None and is_int(val):
            counter = int(val, 10)
            counter_save(counter)
            print(f"{counter}", flush=True)
        else:
            print("Error: Invalid value for 'set' operation.", flush=True)
    else:
        print("Error: Invalid operation.", flush=True)
    print("</PRE></BODY></HTML>\n", flush=True)
    return None

def is_int(s: str) -> bool:
    try:
        int(s, 10)
    except ValueError:
        return False
    return True

def counter_load() -> int:
    counter: int = 0
    try:
        with open(DATA_FILENAME, "rb") as f:
            counter_bytes: bytes = f.read(4)
            counter = int.from_bytes(counter_bytes, byteorder=sys.byteorder)
    except FileNotFoundError:
        pass
    return counter

def counter_save(counter: int) -> None:
    counter_bytes: bytes = counter.to_bytes(4, byteorder=sys.byteorder)
    with open(DATA_FILENAME, "wb") as f:
        f.write(counter_bytes)
    return None

if __name__ == "__main__":
    main()
