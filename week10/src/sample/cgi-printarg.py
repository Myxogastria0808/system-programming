#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# cgi-printarg-python.cgi -- CGI プログラムに対する引数を表示するプログラム
# ~yas/syspro/www/cgi-printarg-python.cgi

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
    print("<HTML><HEAD></HEAD><BODY><PRE>")
    qh = cgi.FieldStorage(keep_blank_values=True)
    i = 0
    for name in qh:
        val = qh[name].value
        print(f"qv[{i}]: {e(name)}={e(val)}")
        i = i + 1
    print("</PRE></BODY></HTML>")

def e(s):
    if s is None:
       return "(null)"
    else:
       return bleach.clean(s, tags=[])

main()
