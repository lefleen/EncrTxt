#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "Windows.h"
#include "classes.h"
#include "zlib.h"

using str = std::string;
using uc = unsigned char;

using pix_vec = std::vector<Pixel>;
using uc_vec = std::vector<unsigned char>;
using ul_vec = std::vector<unsigned long>;

class png 
{
protected:
	static unsigned long num_rows;
	static unsigned long num_pixels;
	static unsigned long num_columns;
	static ul_vec row_filter;
};

class work_with_files : public png
{
	static bool is_correct_file_format(const str& file_name, const str& file_format);
	static void change_format_path_file(str& path_to_file);
	static void open_file_dialog(str& path_to_file);
	static void get_path_to_png(str& path_to_png_file);
	static void input(str& text_from_file);
	static void output(const uc_vec& text);
	static void output(const str& text);
public:
	static void get(uc_vec &code_file);
};

class work_with_chunks : public png
{
	static bool is_true_chunk(int index, const uc_vec& code_file, const str& name_chunk);
	static int from_file_to_chunk(uc_vec& chunk, const uc_vec& code_file, int position_chunk_in_flle);
	static long get_length_chunk(int chunk_offset_size, const uc_vec& code_chunk);
	static uc_vec uncompress_chunk(const uc_vec& compress_chunk);
	static uc_vec search_chunk(const uc_vec& code_file, const str& name_chunk, bool& next_IDAT_is_exist, int& chunk);
	static bool get_IDAT(uc_vec& IDAT, const uc_vec& code_file);
public:
	static int get(uc_vec& IDAT, uc_vec& IHDR, const uc_vec& code_file);
};

class search_pixels : public png
{
private:
	static int extract_dimension_from_ihdr(unsigned long& dimension, const uc_vec& IHDR, const bool is_y);
public:
	static int get(const uc_vec& IDAT, const uc_vec& IHDR, pix_vec& pixels);
};

class change_format_pixels : public png
{
private:
	static void change_format_up_filter(pix_vec& pixels, size_t index_row);
	static void change_format_sub_filter(pix_vec& pixels, size_t num_current_pixel);
	static void change_format_average_filter(pix_vec& pixels, size_t num_current_pixel);
	static void change_format_paeth_filter(pix_vec& pixels, size_t index_row);
	static void get_average(const pix_vec& pixels, size_t current_pixel, uc& average_r, uc& average_g, uc& average_b);
	static uc get_paeth(const pix_vec& pixels, size_t current_pixel, uc code_color_pixel);
public:
	static void get(pix_vec& pixels);
};

class create_png : public png
{
	static void set_IHDR(uc_vec& code_file);
};