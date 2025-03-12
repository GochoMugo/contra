#include "index.h"

#define LONG_TEXT                                                              \
  "Lorem ipsum odor amet, consectetuer adipiscing elit. Etiam maximus fames "  \
  "felis quisque blandit tellus duis feugiat tristique dapibus accumsan "      \
  "accumsan inceptos mattis nostra vestibulum lobortis nascetur convallis "    \
  "convallis integer ultricies lacus a tempor scelerisque ante ipsum laoreet " \
  "a at pharetra natoque sollicitudin adipiscing a arcu erat montes ex "       \
  "lacinia dui imperdiet parturient potenti felis placerat dui a aptent leo, " \
  "morbi posuere molestie tristique et nostra egestas nisi facilisis "         \
  "interdum lectus vulputate lacinia condimentum integer rhoncus tortor nisl " \
  "porttitor montes sodales rutrum ridiculus vulputate magna molestie luctus " \
  "massa sodales molestie curae enim iaculis senectus bibendum parturient in " \
  "hendrerit condimentum pharetra felis cras luctus adipiscing litora "        \
  "condimentum et senectus duis dis fusce taciti facilisis habitasse "         \
  "hendrerit cras massa habitasse aenean proin volutpat orci cras varius "     \
  "hendrerit aptent auctor sagittis dui consectetur aliquam adipiscing "       \
  "pharetra quisque consectetur ultricies tempor dolor sapien rutrum nisi "    \
  "arcu rutrum orci ex nam class porttitor conubia nulla molestie volutpat "   \
  "proin euismod eleifend quisque habitant condimentum interdum ullamcorper "  \
  "potenti inceptos habitant accumsan justo dignissim etiam ante lacinia "     \
  "pellentesque tristique arcu suspendisse bibendum morbi conubia dapibus "    \
  "torquent sem tristique ultricies maximus felis varius quisque.\n"

static char *out = NULL;

void tests_contra_proc_exec(void **state) {
  assert_out(contra_proc_exec(&out, "true"), "");
  assert_out(contra_proc_exec(&out, "/bin/echo -n foo"), "foo");
  assert_out(contra_proc_exec(&out, "/bin/echo foo"), "foo\n");
  assert_out(contra_proc_exec(&out, "echo foo"), "foo\n");
  assert_out(contra_proc_exec(&out, "echo foo | cat"), "foo\n");

  assert_out(contra_proc_exec(&out, "cat ../test/data/long_text.txt"),
             LONG_TEXT);
  assert_true(sizeof(LONG_TEXT) > CONTRA_PROC_EXEC_BUFFER_SIZE);
  assert_int_equal(strlen(out), strlen(LONG_TEXT));

  assert_fail(contra_proc_exec(&out, "false"), CONTRA_ERR_PROC_EXEC);
  assert_fail(contra_proc_exec(&out, "/bin/unknown"), CONTRA_ERR_PROC_EXEC);
}

int main(void) {
  const struct CMUnitTest tests[] = {
      cmocka_unit_test(tests_contra_proc_exec),
  };
  return cmocka_run_group_tests(tests, NULL, NULL);
}
