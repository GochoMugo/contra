import re
import subprocess
import sys


def parse(func_raw, test_raw, line_num, test_num):
    # 'func_raw' would be in the form: 'contra_funcname(int **out)'
    # we are removing the argument list so as to remain with the function
    # name
    func_name = re.sub('\(.*', '', func_raw)
    # we need to get the type of the 1st parameter of the function.
    # For example, 'contra_funcname(int **out)' would produce 'int'
    out_type = re.search("\((\w+)", func_raw).group(1)

    # this will hold the arguments i.e. in LHS
    args = None

    # this will hold the out value i.e. assigned to 1st pointer-to-pointer
    # arg
    out = None

    # this will hold the return value i.e. returned from the function
    ret = None

    # this will hold the output to write to the destination file
    output = None

    # the test definition may be in the format:
    # '  * "arg1", "arg2"    =>    "out"    #>    "ret"'
    test = re.match("^\s*\*\s*(.+)\s*\=\>\s*(.+)\s*\#\>\s*(.+)\s*$", test_raw)
    if test:
        args = test.group(1).strip()
        out = test.group(2).strip()
        ret = test.group(3).strip()

    # the test definition may be in the format:
    # '  * "arg1", "arg2"    =>    "out"'
    if test is None:
        test = re.match("^\s*\*\s*(.+)\s*\=\>\s*(.+)\s*$", test_raw)
        if test:
            args = test.group(1).strip()
            out = test.group(2).strip()
            ret = 0

    # the test definition may be in the format:
    # '  * "arg1", "arg2"    #>    "ret"'
    if test is None:
        test = re.match("^\s*\*\s*(.+)\s*\#\>\s*(.+)\s*$", test_raw)
        if test:
            args = test.group(1).strip()
            out = "NULL"
            ret = test.group(2).strip()

    # if we could not parse the input, fail
    if args is None or out is None or ret is None:
        raise Exception("could not parse test definition")

    # define the function name and arguments list, etc.
    output = ("\nvoid tests_contra_inline_L%s_%s(void **state) {\n" % (line_num, test_num))

    # if the type of the out value is an 'int', declare an 'int' variable
    # otherwise, declare a pointer of type 'type'
    if out_type == "int":
        output += "\tint out = -1;\n"
    else:
        output += ("\t%s *out = NULL;\n" % out_type)

    # invoking the function and asserting here
    output += ("\tassert_int_equal(%s(&out, %s), %s);\n" % (func_name, args, ret))

    # asserting the return value
    if out_type == "int": output += ("\tassert_int_equal(out, %s);\n" % out)
    elif out_type == "char": output += ("\tassert_string_equal(out, %s);\n" % eval(out))

    # if the out type was an integer, we need not do anythin
    # however, if it was a pointer, we need to free it
    if out_type == "int": pass
    else: output += "\tfree(out);\n"

    # closing the function/output
    output += "}\n"

    return output


# This performs evaluations using a bash terminal
def eval(string):
    return "\"%s\"" % subprocess.check_output("echo %s" % string, shell=True, executable='/bin/bash').strip()
