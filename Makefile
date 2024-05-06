help:
	@echo
	@echo "  clean                Clean build"
	@echo "  deps                 Install dependencies"
	@echo "  help                 Show this help info"
	@echo

clean:
	rm -rf build deps
		
deps:
	git submodule init
	git submodule update

.PHONY: clean deps help
