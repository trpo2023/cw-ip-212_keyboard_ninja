#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifdef _WIN32
#include <windows.h>
#define BG_RED 64
#define BG_GREEN 32
#define FG_GRAY 2
#else
#include <unistd.h>
#define BG_RED 41
#define FG_GRAY 30
#define BG_GREEN 42
#endif

void set_text_color(int color);
void print_text(const char* text);
void read_file(const char* filename, char* buffer, size_t buffer_size);
void read_user_input(char* buffer, size_t buffer_size);
int print_comparison(const char* original_text, const char* user_input);
void print_results(int errors, int total_chars, double elapsed_time);
