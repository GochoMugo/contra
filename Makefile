help:
	@echo
	@echo "  clean                Clean build"
	@echo "  deps                 Install dependencies"
	@echo "  doc                  Generate documentation"
	@echo "  help                 Show this help info"
	@echo

clean:
	rm -rf build deps doc/html doc/man
	git checkout deps

deps:
	git submodule init
	git submodule update

doc:
	doxygen

.PHONY: clean deps doc help
