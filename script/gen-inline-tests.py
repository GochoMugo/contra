#!/usr/bin/env python


import os
import sys
import lib


def main():
    ret_code = 0
    root_dir = os.getenv("ROOT_DIR")
    if root_dir is None:
        print("Error: Missing environment variable ROOT_DIR")
        return 1

    src_filenames = sys.argv[1:]
    for src_filename in src_filenames:
        src_filename = os.path.realpath(src_filename)
        dest_filename = src_filename.replace(root_dir, "").strip(os.sep)
        dest_filename = dest_filename.replace(os.sep, "_")
        try:
            process_file(src_filename, dest_filename)
        except:
            return 2
    return 0


def process_file(src_filename, dest_filename):
    file_id, _ = os.path.splitext(dest_filename)
    src_filecontent = []
    with open(src_filename, "r") as src_file:
        src_file_content = src_file.readlines()
    with open(dest_filename, "w") as dest_file:
        dest_file.write(
                "/* Automatically generated by script/gen-inline-tests.py */\n"
                "#include <test-headers/main.h>\n"
                "\n"
                "int tests_contra_%s_setup_each(void **state) { return 0; }\n"
                "int tests_contra_%s_teardown_each(void **state) { return 0; }\n"
                % (file_id, file_id))
        cache = []
        parser_on = False
        for line_index in range(len(src_file_content)):
            line = src_file_content[line_index]
            if line.find("#tests") != -1:
                parser_on = True
            elif line.find("#endtests") != -1:
                parser_on = False
            elif line.find("contra_") != -1:
                func_raw = line.strip()
                add_tests(dest_filename, dest_file, func_raw, cache)
                cache = []
            else:
                if parser_on:
                    cache.append((line_index, line))


def add_tests(dest_filename, dest_file, func_raw, cache):
    for test_index in range(len(cache)):
        (line_index, test_raw) = cache[test_index]
        line_num = line_index + 1
        try:
            output = lib.test_parser.parse(dest_filename, dest_file, func_raw, test_raw, line_num)
        except Exception as e:
            print("failed to generate inline test:")
            print("  file:     %s" % dest_file.name)
            print("  line no.: %s" % line_num)
            print("  function: %s" % func_raw)
            print("  test:     %s" % test_raw)
            print(e)
            raise e
        dest_file.write(output)


# invoking the 'main' function, if the script is being run
if __name__ == "__main__":
    sys.exit(main())
