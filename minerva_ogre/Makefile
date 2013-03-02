OUTPUTDIR = bin/
OBJSDIR = obj/
ARTKDIR = ARToolKit

# Default compilation value
mode = debug

#To build libs, please run a 'make libs' first!
all: credentials dirs
	cd source; $(MAKE) mode=$(mode)

libs: ARTK

credentials:
	@echo
	@echo '--------------------------------------'
	@echo ' ABBY Makefile'
	@echo ' Cesar Mora Castro - 2013'
	@echo ' Compiling $(mode) mode'
	@echo '--------------------------------------'
	@echo ' NOTE: To build the libraries, run "make libs" first!'
	@echo

dirs:
	mkdir -p $(OUTPUTDIR)
	mkdir -p $(OBJSDIR)

ARTK:
	cd lib/$(ARTKDIR); $(MAKE)

	
clean:
	cd source; $(MAKE) clean

allclean: clean
	cd lib/$(ARTKDIR); $(MAKE) clean
	rm -Rf bin	