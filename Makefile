SRCDIR=./src/
BINDIR=./bin/

CC=g++
COPT=-O3
OPENMP=-fopenmp
WARN=-Wall

.PHONY: EULER
EULER: $(SRCDIR)FHN_sim_EULER.cpp	## Compile the simulation source file that uses Euler method
	$(CC) $(WARN) $(COPT) $(OPENMP) -o $(BINDIR)FHN_sim_EULER.exe $(SRCDIR)FHN_sim_EULER.cpp

.PHONY: RK_SECOND_ORD
RK_SECOND_ORD: $(SRCDIR)FHN_sim_RK2.cpp	## Compile the simulation source file that uses 2nd order Runge Kutta method
	$(CC) $(WARN) $(COPT) $(OPENMP) -o $(BINDIR)FHN_sim_RK2.exe $(SRCDIR)FHN_sim_RK2.cpp

.PHONY: RK_FORTH_ORD
RK_FORTH_ORD: $(SRCDIR)FHN_sim_RK4.cpp	## Compile the simulation source file that uses 4th order Runge Kutta method
	$(CC) $(WARN) $(COPT) $(OPENMP) -o $(BINDIR)FHN_sim_RK4.exe $(SRCDIR)FHN_sim_RK4.cpp

.PHONY: clean
clean:	## Clean bin directory
	rm -rf $(BINDIR)*

.PHONY: list
list:	## List all make targets
	@$(MAKE) -pRrn : -f $(MAKEFILE_LIST) 2>/dev/null | awk -v RS= -F: '/^# File/,/^# Finished Make Database/ {if ($$1 !~ "^[#.]") {print $$1}}' | egrep -v -e '^[^[:alnum:]]' -e '^$@$$' | sort

.PHONY: help
.DEFAULT_GOAL := help
help:
	@grep -h -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | awk 'BEGIN {FS = ":.*?## "}; {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}'

