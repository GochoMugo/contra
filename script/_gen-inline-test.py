#!/usr/bin/env python

import re
import sys

func_raw = sys.argv[1]
test_raw = sys.argv[2]
src_file = sys.argv[3]
line_no = sys.argv[4]

args = None
out = None
ret_val = None
line_id = re.sub("[^\w\d]", "_", src_file)

func = re.sub('\(.*', '', func_raw);
test = re.match("^\s*\*\s*(.+)\s*\=\>\s*(.+)\s*\#\>\s*(.+)\s*$", test_raw)

if test:
    args = test.group(1).strip()
    out = test.group(2).strip()
    ret_val = test.group(3).strip()

if test is None:
    test = re.match("^\s*\*\s*(.+)\s*\=\>\s*(.+)\s*$", test_raw)
    if test:
        args = test.group(1).strip()
        out = test.group(2).strip()
        ret_val = 0

if test is None:
    test = re.match("^\s*\*\s*(.+)\s*\#\>\s*(.+)\s*$", test_raw)
    if test:
        args = test.group(1).strip()
        out = "NULL";
        ret_val = test.group(2).strip()

if args is None or out is None or ret_val is None:
    print "FAIL!"
    sys.exit(1)

print ""
print "void tests_contra_inline_%s_L%s(void **state) {" % (line_id, line_no)
print "\tchar *out = NULL;"
print "\tassert_int_equal(%s(&out, %s), %s);" % (func, args, ret_val)
if out != "NULL":
    print "\tassert_string_equal(out, %s);" % out
print "\tfree(out);"
print "}"
