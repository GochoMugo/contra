#
# The MIT License (MIT)
# Copyright (c) 2016 GochoMugo <mugo@forfuture.co.ke>
# Copyright (c) 2016 Forfuture, LLC <we@forfuture.co.ke>
#

ROOT           = $(PWD)/..
PREFIX        ?= /usr/local
DEPS           = $(ROOT)/deps
SCRIPTS        = $(ROOT)/script
GEN_ITESTS     = $(SCRIPTS)/gen-inline-tests.sh
GEN_HEADERS    = $(DEPS)/cok/script/cmocka/gen-test-headers.sh
WHICH_HEADERS  = $(DEPS)/cok/script/cmocka/which-test-headers.sh
ECHO           = ROOT=$(ROOT) $(DEPS)/cok/script/echo-task.sh

CFLAGS        += -I$(ROOT)/deps/
CFLAGS        += --std=c99 -Wall -pedantic
LIBS           =
SRC            = $(ROOT)/src/**/*.c $(ROOT)/deps/**/*.c
OUT            = $(PWD)/src
LIB            = $(OUT)/libblackhole.a

CFLAGS_TEST    = `pkg-config --cflags cmocka`
LIBS_TEST      = `pkg-config --libs cmocka` -L$(OUT) -lblackhole $(LIBS)
TEST_DIR       = $(ROOT)/test
SRC_TEST       = $(TEST_DIR)/*.c
OUT_TEST       = $(PWD)/test
EXE_TEST       = $(PWD)/test-contra


.PHONY: clean install pc veryclean test


$(LIB): $(SRC)
	@mkdir -p $(OUT)
	@$(ECHO) CC $? ; cd $(OUT) && $(CC) -c $? $(CFLAGS)
	@$(ECHO) AR $(LIB) ; cd $(OUT) && $(AR) cr $(LIB) *.o

test:
	@$(ECHO) SCRIPT $(GEN_ITESTS)  ; $(GEN_ITESTS) $(ROOT)/src/**/*.c
	@make $(LIB) $(EXE_TEST)
	@$(ECHO) RUN $(EXE_TEST) ; TEST_DIR=$(TEST_DIR) \
		$(EXE_TEST)

$(EXE_TEST): $(SRC_TEST)
	@mkdir -p $(OUT_TEST)
	@$(ECHO) SCRIPT $(GEN_HEADERS) ; $(GEN_HEADERS) $(TEST_DIR)
	@$(ECHO) CC $? ; cd $(OUT_TEST) && $(CC) -c $? $(CFLAGS_TEST) -g
	@$(ECHO) CC $@ ; cd $(OUT_TEST) && $(CC) -o $@ *.o $(CFLAGS_TEST) $(LIBS_TEST)

clean:
	@$(RM) -r $(OUT) $(OUT_TEST) \
		`$(WHICH_HEADERS) $(TEST_DIR)` \
		$(TEST_DIR)/src_*

veryclean: clean
	@$(RM) $(EXE) $(EXE_TEST)
