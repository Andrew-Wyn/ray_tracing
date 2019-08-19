
.PHONY: all

all: warn


compile:
	@echo "========== Compiling source ..."
	g++ main.cc -o raytracing.out
	@echo "========== DONE!"

run:
	./raytracing.out

warn:
	@echo "========== Warning ...\nDO: make compile, make run"
