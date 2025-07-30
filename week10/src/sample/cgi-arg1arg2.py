#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# cgi-arg1arg2-python.cgi -- CGI プログラムに対する引数 arg1 と arg2 を表示するプログラム
# ~yas/syspro/www/cgi-arg1arg2-python.cgi

import warnings
warnings.filterwarnings("ignore", category=DeprecationWarning)

import cgi
import bleach

def main():
    print_header()
    print_content()
    exit(0)

def print_header():
    print("Content-Type: text/html")
    print("")

def print_content():
    print("<HTML><HEAD></HEAD><BODY><PRE>",flush=True)
    qh = cgi.FieldStorage(keep_blank_values=True)
    arg1 = qh.getfirst("arg1","")
    arg2 = qh.getfirst("arg2","")
    print(f"arg1: [{e(arg1)}]")
    print(f"arg2: [{e(arg2)}]")
    print("</PRE></BODY></HTML>\n")

def e(s):
    if s is None:
       return "(null)"
    else:
       return bleach.clean(s, tags=[])

main()
