all:
	mkdir -p bin
	(cd lib/SRC;    make -f Makefile)
#	(cd util;       make -f Makefile)
#	(cd examples;   make -f Makefile)

clean:
	rm -Rf bin
	(cd lib/SRC;    make -f Makefile clean)
#	(cd util;       make -f Makefile clean)
#	(cd examples;   make -f Makefile clean)

install:
	echo "FIX ME, ASK SERGIO!"
	(cp -R ./include/AR /usr/local/include)
	(cp ./lib/*.a /usr/local/lib)
	ldconfig

uninstall:
	echo "FIX ME, ASK SERGIO!"
	(rm -Rf /usr/local/include/AR)
	(rm  /usr/local/lib/libAR*)
	ldconfig

#allclean:
#	(cd lib/SRC;    make -f Makefile allclean)
#	(cd util;       make -f Makefile allclean)
#	(cd examples;   make -f Makefile allclean)
#	rm -f Makefile
#	rm -f include/AR/config.h
