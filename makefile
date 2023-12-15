all: cliz_compress

cliz_compress: change_err_bound/* choose_method/* compress/* DC/* debug/* init/* io/* \
	call_compress_functions.cpp cliz_compress.cpp globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_compress
	g++ cliz_compress.cpp -o cliz_compress -O3 -Wno-unused-result -lfftw3f

clean: 
	rm -rf result
	mkdir result
	rm -f cliz_compress