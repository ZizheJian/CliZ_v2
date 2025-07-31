CXX=g++
CXXFLAGS=-O3 -Wno-unused-result -lfftw3f -lzstd

.PHONY: all clean zstd fftw cliz_compress cliz_decompress cliz_validate

all: zstd fftw cliz_compress cliz_decompress cliz_validate

ZSTD_LIB_DIR=$(abspath zstd/lib)

zstd:
	make -j16 -C zstd

FFTW_DIR=$(abspath fftw-3.3.10)
FFTW_INSTALL_DIR=$(FFTW_DIR)/install
FFTW_LIB_DIR=$(FFTW_INSTALL_DIR)/lib
FFTW_LIB=$(FFTW_LIB_DIR)/libfftw3f.a
FFTW_INCLUDE_DIR=$(FFTW_INSTALL_DIR)/include

$(FFTW_LIB):
	cd $(FFTW_DIR) && ./configure --prefix=$(FFTW_INSTALL_DIR) --enable-float && make -j16 && make install

fftw: $(FFTW_LIB)

cliz_compress: cliz_compress.cpp change_err_bound/* choose_method/* compress/* DC/* debug/* fitting/* huffman_decode/* huffman_encode/* huffman_tree/* init/* io/* transform/* zstd/* globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_compress
	$(CXX) $< -o $@ $(CXXFLAGS) -I ${FFTW_INCLUDE_DIR} -L ${FFTW_LIB_DIR} -lfftw3f -I ${ZSTD_LIB_DIR} -L ${ZSTD_LIB_DIR} -lzstd

cliz_decompress: cliz_decompress.cpp change_err_bound/* choose_method/* DC/* debug/* decompress/* fitting/* huffman_decode/* huffman_tree/* init/* io/* transform/* zstd/* globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_decompress
	$(CXX) $< -o $@ $(CXXFLAGS) -I ${FFTW_INCLUDE_DIR} -L ${FFTW_LIB_DIR} -lfftw3f -I ${ZSTD_LIB_DIR} -L ${ZSTD_LIB_DIR} -lzstd

cliz_validate: cliz_validate.cpp change_err_bound/* choose_method/* validate/* debug/* init/* io/* globalvar.hpp hyper_iterator.cpp makefile
	rm -f cliz_validate
	$(CXX) $< -o $@ $(CXXFLAGS) -I ${FFTW_INCLUDE_DIR} -L ${FFTW_LIB_DIR} -lfftw3f -I ${ZSTD_LIB_DIR} -L ${ZSTD_LIB_DIR} -lzstd

clean: 
	rm -rf result
	mkdir result
	rm -f cliz_compress cliz_decompress cliz_validate