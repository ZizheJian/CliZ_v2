all: cliz_compress

cliz_compress: change_err_bound/* debug/* init/* io/* \
	cliz_compress.cpp hyper_iterator.cpp globalvar.hpp makefile
	rm -f cliz_compress
	g++ cliz_compress.cpp -o cliz_compress -O3 -Wno-unused-result -lfftw3f

clean: 
	rm -rf result
	mkdir result
	rm -f cliz_compress