#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h>
#include "Windows.h"
#include "classes.h"
#include "zlib.h"

typedef std::string str;
typedef std::vector<Pixel> pix_vec;
typedef std::vector<unsigned char> uc_vec;

void main();

#ifndef  USER_INTERFACE_H
#define  USER_INTERFACE_H
class user_interface 
{
	bool is_coorect_input(const char value, const char min_val_arg, const char max_val_arg);
	char func_choose_source();
	char func_choose_mode();
public:
	void input_from_console(str& text_from_console);
	void do_you_want_continue(int& choose);
	void input_menu(char &current_mode, char &current_source);
};
#endif

#ifndef  WORK_WITH_FILES_H
#define  WORK_WITH_FILES_H
class work_with_files 
{
	bool is_correct_file_format(const str& file_name, const str& file_format);
	void change_format_path_file(str& path_to_file);
	void open_file_dialog(str& path_to_file);
	void get_path_to_png(str& path_to_png_file);
public:
	void png_read(uc_vec &code_file);
	void input(str& text_from_file);
	void output(const uc_vec& text);
	void output(const str& text);
};
#endif

#ifndef  WORK_WITH_CHUNKS_H
#define  WORK_WITH_CHUNKS_H

class work_with_chunks
{
	bool is_true_chunk(int index, const uc_vec& code_file, const str& name_chunk);
	int from_file_to_chunk(uc_vec& chunk, const uc_vec& code_file, int position_chunk_in_flle);
	long get_length_chunk(int chunk_offset_size, const uc_vec& code_chunk);
	uc_vec uncompress_chunk(const uc_vec& compress_chunk);
	uc_vec search_chunk(const uc_vec& code_file, const str& name_chunk);
public:
	int get(uc_vec& IDAT, uc_vec& IHDR, const uc_vec& code_file);
};
#endif

#ifndef  CRYPTOGRATHY_H
#define  CRYPTOGRATHY_H
class cryptograthy 
{
	void show_plain_text(const str& plain_text);
	void show_key(const uc_vec& key);
public:
	int encryption_text(const str& text, const pix_vec& pixels, uc_vec& key);
	int decryption_text(const str& text, const pix_vec& pixels, str& plain_text);
};
#endif

#ifndef  SEARCH_PIXELS_H
#define  SEARCH_PIXELS_H
class search_pixels 
{
private:
	int extract_dimension_from_ihdr(unsigned long& dimension, const uc_vec& IHDR, const bool is_y);
    bool is_null_pixel(const uc_vec& IDAT, const int index);
public:
	int get_pixels(const uc_vec& IDAT, const uc_vec& IHDR, pix_vec& pixels);
};
#endif

#ifndef CHANGE_FORMAT_PIXELS_H
#define CHANGE_FORMAT_PIXELS_H
class change_format_pixels 
{
private:
	bool is_end_of_row(Pixel& pixel);
	bool is_null_pixel(const Pixel& pixel);
	void new_sum_pixels(const pix_vec& pixels, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b, const int index);
	int get_num_last_element_column(const pix_vec& pixels, int& num_last_el_column, int index);
	void change_format_row_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_pixel, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b);
	void change_format_column_pixels(pix_vec& new_pixels, const pix_vec& pixels, int& num_last_el_row, const int index, unsigned char& sum_r, unsigned char& sum_g, unsigned char& sum_b);
public:
	// ОТЛАДОЧНАЯ ФУНКЦИЯ
	void show(const pix_vec& pixels);	
	//
	void change_format_all_pixels(pix_vec& pixels);
};
#endif
