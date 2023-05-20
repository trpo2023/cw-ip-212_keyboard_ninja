#pragma once
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

void trim(char* str);
void set_text_color(int color);
void print_text(const char* text);
void read_file(const char* filename, char* buffer, size_t buffer_size);
void read_user_input(char* buffer, size_t buffer_size);
int print_comparison(const char* original_text, const char* user_input);
void print_results(int errors, int total_chars, double elapsed_time);
