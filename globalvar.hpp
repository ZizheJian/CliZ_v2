#ifndef __GLOBALVAR_H__
#define __GLOBALVAR_H__

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#include "math.h"
#include "functional"
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <iterator>
#include <random>
#include <limits>
#include <chrono>
#include <sstream>
#include <fftw3.h>

using namespace std;

namespace cliz
{
	#define FILE_NAME_LENGTH 1000
	#define FUNC_NAME_LENGTH 100
	#define TEMP_STRING_LENGTH 1000
	#define SAMPLING_RATE 1e-6
	#define TEST_ALL false
	#define FFT_SAMPLE_NUM 10
	#define FAST_SAMPLING false

	const char *supported_data_type[]={"i32","f32","f64"};
	const char *supported_dimension_type[]={"h","lat","lng","t","pert"};
	const char *supported_err_type[]={"ABS","REL","LOCAL"};
	random_device rd;
	mt19937_64 gen(rd());
	struct simple_hash{
		size_t operator()(const int &key) const
		{
			return key;
		}
	};

	template<typename T>
	class task_c;
	template<typename T>
	class huffman_tree_c;
	class node_c;
	class timer_c;

	class timer_c
	{
		public:
			vector<double> history;
			int state=0;

			double start_time=0;
			double end_time=0;

			void start();
			void pause();
			void reset();
			void write();
	};

	class hyper_iterator_c
	{
		public:
			int n=0;
			long long *mx=NULL;
			long long *weight=NULL;
			int *dim_seq=NULL;//从当前维度编号到相关迭代器维度编号的映射
			int dim_fission_l=0;//维度分解时得到的维度中变化最慢的一个，同时也表示被分解的维度
			int dim_fission_r=0;//维度分解时得到的维度中变化最快的一个+1

			hyper_iterator_c(int n);
			void print();
			void write(FILE *cfg_file);
			void delete_iterator();
	};

	class node_c
	{
		public:
			int self=0,father=0,lson=0,rson=0;
			int root=0;//仅在解压缩时，叶节点的root会被计算
			short lmost=0;//以自身为根的子树的最左侧叶节点编号
			short rmost=0;//以自身为根的子树的最右侧叶节点编号
			long long count=0;//以自身为根的子树的所有叶节点对应的quant_bin出现次数之和
			long long code=0;//哈夫曼码
			int length=0;//哈夫曼码长度
	};

	struct node_compare
	{
		bool operator()(const node_c *a,const node_c *b)
		{
			return a->count<b->count;
		}
	};

	template<typename T>
	class huffman_tree_c
	{
		public:
			multiset<node_c*,node_compare> unarranged_nodes;//目前还需要连成一个树的节点集合
			unordered_map<int,node_c,simple_hash> nodes;//前65536个node对应65536个quant_bin，后面的留给多个quant_bin组成的树的根节点。在压缩和解压时，前65536个一定相同，但后面的不一定相同

			void generate_tree();
			void generate_code(task_c<T> *task);
			void rebuild(task_c<T> *task);
			void traversal(int id,task_c<T> *task);
			//void append_cache(unsigned short x);
	};

	template<typename T>
	class predictor_c
	{
		public:
			function<T(int,long long)> f=function<T(int,long long)>();//和数据采集范围，mask有关
			char *name=NULL;
	};

	template<typename T>
	class task_c
	{
		public:
			char *in_file_path=NULL;
			FILE *in_file=NULL;
			char *out_file_path=NULL;
			FILE *out_file=NULL;
			unsigned char *bitstream=NULL;
			long long bitstream_length=0;
			long long best_bitstream_length=numeric_limits<long long>::max();
			long long bitstream_index=0;
			char *cfg_file_mode=NULL;
			char *cfg_file_path=NULL;
			FILE *cfg_file=NULL;
			char *map_file_mode=NULL;
			char *map_file_path=NULL;
			FILE *map_file=NULL;
			unsigned char *map_bitstream=NULL;
			char *mask_file_path=NULL;
			FILE *mask_file=NULL;
			char *src_file_path=NULL;
			FILE *src_file=NULL;
			char *dec_file_path=NULL;
			FILE *dec_file=NULL;
			char *data_name=NULL;
			int dimension_num=0;
			long long *dimension=NULL;
			char **dimension_type=NULL;
			long long data_num=0;
			char *data_type=NULL;
			char *err_type=NULL;
			double raw_err_bound=0;
			double err_bound=0;
			double err_bound_reciprocal=numeric_limits<double>::max();
			bool debug=false;

			T *data=NULL;
			int *mask_data=NULL;
			int latid=-1,lngid=-1,hid=-1,tid=-1,pertid=-1;
			hyper_iterator_c *it1=NULL;
			hyper_iterator_c *best_it1=NULL;
			hyper_iterator_c *best_pert_it1=NULL;
			hyper_iterator_c *it2=NULL;
			hyper_iterator_c *pert_it2=NULL;
			long long test_num=0;
			long long *test_pos=NULL;
			bool best_map=false;
			unsigned char *map=NULL;
			long long pert=0;
			T *avg_data=NULL;
			double best_average_bytes=numeric_limits<double>::max();
			double best_avg_average_bytes=numeric_limits<double>::max();
			short *quant_bin=NULL;
			vector<huffman_tree_c<T>> huffman;
			vector<T> irregular_data;
			T *src_data=NULL;
			T *dec_data=NULL;

			////////////////IO Functions////////////////
			void read_cfg();
			void read_cfg_dimension_num(char *temp_string);
			void read_cfg_dimension(char *temp_string);
			void read_cfg_data_type(char *temp_string);
			void read_cfg_err_bound(char *temp_string);
			void read_cfg_best_compress_function(char *temp_string);
			void read_cfg_best_decompress_function(char *temp_string);
			void read_cfg_best_fitting_function(char *temp_string);
			void read_cfg_it1_max(char *temp_string);
			void read_cfg_seq_mapping(char *temp_string);
			void read_cfg_fission_mapping(char *temp_string);
			void write_cfg();
			template<typename T2>
			void align_cache();
			template<typename T2>
			void append_cache(T2 x);
			template<typename T2>
			void read_cache(T2 &x);
			template<typename T2>
			T2 read_cache();

			////////////////Some Other Functions////////////////
			void init_it();
			void print_detail();
			void identify_dimensions();
			void print_best_strategy();
			
			////////////////Error Bound Functions////////////////
			void change_err_bound();
			void change_err_bound_1D();
			void change_err_bound_2D();
			void change_err_bound_3D();
			void change_err_bound_4D();
			void change_err_bound_mask_1D();
			void change_err_bound_mask_2D();
			void change_err_bound_mask_3D();
			void change_err_bound_mask_4D();

			////////////////Testing Functions////////////////
			void choose_method();
			void test();
			void test_map();
			void test_pert();
			void test_map_pert();
			void test_all_dimension_sequence();
			void test_all_dimension_fission();		
			void test_all_fitting_function();	
			void test_i32();
			void test_mask();
			void test_pert_mask();
			void print_test_condition();
			void assign_test_pos_with_map(hyper_iterator_c *map_it);
			void calc_pert_mask(task_c<int> *mask_subtask);
			void calc_avg_data();
			void test_avg_data();
			void calc_diff_data();
			void calc_original_data();
			void test_diff_data();

			////////////////Compress Functions////////////////
			void call_compress_functions();
			void call_compress_functions_test();
			char *best_compress_function=NULL,*compress_function=NULL;
			void compress();
			void compress_test();
			//compress_framework_c compress_framework,best_compress_framework,best_avg_compress_framework;
			void compress_framework_i32();
			void compress_framework_mask(task_c<int> *mask_subtask);
			void compress_framework_mask_test(task_c<int> *mask_subtask);
			void compress_framework_map();
			void compress_framework_map_test();
			void compress_framework_map_mask(task_c<int> *mask_subtask);
			void compress_framework_map_mask_fast(task_c<int> *mask_subtask);
			void compress_framework_map_mask_test(task_c<int> *mask_subtask);
			void assign_irr_data();
			void assign_irr_data_mask(task_c<int> *mask_subtask);
			void write_map(int lngid,int latid);
			void write_map_mask(task_c<int> *mask_subtask,int lngid,int latid);

			////////////////Decompress Functions////////////////
			void call_decompress_functions();
			char *best_decompress_function=NULL;
			void decompress();
			void decompress_framework_i32();
			void decompress_framework_basic();
			void decompress_framework_mask(task_c<int> *mask_subtask);
			void decompress_framework_map();
			void decompress_framework_map_mask(task_c<int> *mask_subtask);
			//void match_decompress_functions(compress_framework_c &best_decompress_framework,predictor_c<T> &best_predictor);
			void read_map(int lngid,int latid);
			void read_map_mask(task_c<int> *mask_subtask,int lngid,int latid);

			////////////////Transpose Functions////////////////
			void transpose(T *data_backup);
			void transpose_1D(T *data_backup);
			void transpose_2D(T *data_backup);
			void transpose_3D(T *data_backup);
			void transpose_4D(T *data_backup);
			void anti_transpose(T *data_backup);
			void anti_transpose_1D(T *data_backup);
			void anti_transpose_2D(T *data_backup);
			void anti_transpose_3D(T *data_backup);
			void anti_transpose_4D(T *data_backup);

			////////////////DC Functions////////////////
			void call_DC_functions();
			void call_DC_functions_test();
			void DC_1D_linear();
			void DC_2D_linear();
			void DC_3D_linear();
			void DC_4D_linear();
			void DC_3D_cubic();
			void DC_linear_test();

			////////////////Fitting Functions////////////////
			char *best_fitting_function=NULL,*fitting_function=NULL;
			T cubic_fitting_ddpdd(long long i,long long stride);
			T cubic_fitting_dddpd(long long i,long long stride);
			T cubic_fitting_ddddp(long long i,long long stride);
			T quadratic_fitting_ddpd(long long i,long long stride);
			T quadratic_fitting_dddp(long long i,long long stride);
			T linear_fitting_dpd(long long i,long long stride);
			T linear_fitting_ddp(long long i,long long stride);
			T constant_fitting_dp(long long i,long long stride);

			////////////////Quantization Functions////////////////
			short quantize(long long i,T pred);
			T dequantize(long long i,T pred);

			////////////////Count Quant_Bin Functions////////////////
			void count_quant_bin();
			void count_quant_bin_test();
			void count_quant_bin_mask(task_c<int> *mask_subtask);
			void count_quant_bin_mask_test(task_c<int> *mask_subtask);
			void count_quant_bin_map(int lngid,int latid);
			void count_quant_bin_map_test(int lngid,int latid);
			void count_quant_bin_map_mask(task_c<int> *mask_subtask,int lngid,int latid);
			void count_quant_bin_map_mask_test(task_c<int> *mask_subtask,int lngid,int latid);
			
			/////////////////Encode Quant_Bin Functions////////////////
			void encode();
			void encode_test();
			void encode_quant_bin_mask(task_c<int> *mask_subtask);
			void encode_quant_bin_map(int lngid,int latid);
			void encode_quant_bin_map_mask(task_c<int> *mask_subtask,int lngid,int latid);
			void decode_quant_bin_mask(task_c<int> *mask_subtask);
			void decode_quant_bin_map(int lngid,int latid);
			void decode_quant_bin_map_mask(task_c<int> *mask_subtask,int lngid,int latid);
			
			////////////////Decode Quant_Bin Functions////////////////
			void decode();

			////////////////Validate Functions////////////////
			void call_validate_functions();
			void validate_ABS();
			
			void generate_map(hyper_iterator_c *map_it);
			void generate_map_test(hyper_iterator_c *map_it,int lngid,int latid);

			T linear_interp_predictor_mask(task_c<int> *mask_subtask,int direction,long long stride);
			T cubic_interp_predictor(int direction,long long stride);
			T cubic_interp_predictor_fast(int direction,long long stride);
			T cubic_interp_predictor_mask(task_c<int> *mask_subtask,int direction,long long stride);
			T cubic_interp_predictor_mask_fast(task_c<int> *mask_subtask,int direction,long long stride);

			void draw_quant_bin(int lngid,int latid);
			void draw_map(int lngid,int latid);
			void printdetail();
			void get_derivative(float *derivative);
			int find_dim_name(char **name_list,const char *name);
	};
}

#endif