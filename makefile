all: cliz_compress cliz_decompress cliz_validate

cliz_compress: change_err_bound/* choose_method/* compress/* DC/* debug/* fitting/* huffman_encode/* huffman_tree/* init/* zstd/* io/* \
	cliz_compress.cpp globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_compress cliz_decompress cliz_validate
	g++ cliz_compress.cpp -o cliz_compress -O3 -Wno-unused-result -lfftw3f -lzstd

cliz_decompress: change_err_bound/* choose_method/* DC/* debug/* decompress/* fitting/* huffman_encode/* huffman_tree/* init/* zstd/* io/* \
	cliz_decompress.cpp globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_decompress cliz_validate
	g++ cliz_decompress.cpp -o cliz_decompress -O3 -Wno-unused-result -lfftw3f -lzstd

cliz_validate: change_err_bound/* validate/* debug/* init/* io/* \
	cliz_validate.cpp globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_validate
	g++ cliz_validate.cpp -o cliz_validate -O3 -Wno-unused-result -lfftw3f -lzstd

clean: 
	rm -rf result
	mkdir result
	rm -f cliz_compress cliz_decompress cliz_validate