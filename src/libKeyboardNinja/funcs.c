#include "funcs.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <locale.h>

#ifdef _WIN32
#include <windows.h>
#define BG_RED 0xC0
#define BG_GREEN 0xA0
#define FG_GRAY 0x08
#define FG_DEF 0x07
#else
#include <unistd.h>
#define FG_DEF 0
#define BG_RED 41
#define FG_GRAY 30
#define BG_GREEN 42
#endif

// Функция для удаления лишних символов 
void trim(char *str) {
    // Удаление с правого края
    int len = strlen(str);
    while (len > 0 && isspace(str[len-1])) {
        str[len-1] = '\0';
        len--;
    }
    
    // Удаление с левого края
    char *start = str;
    while (*start && isspace(*start)) {
        start++;
    }
    memmove(str, start, strlen(start) + 1);
}

// Меняем цвет текста
void set_text_color(int color) {
#ifdef _WIN32
    // для ОС Windows используется библиотека Windows.h,
    // получаем дескриптор стандартного вывода и устанавливаем цвет текста
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    // для *nix систем используется escape-последовательность ANSI,
    // которая устанавливает цвет текста
    printf("\033[1;%dm", color);
#endif
}

// Функция для вывода оригинального текста
void print_text(const char* text) {
    printf("\nType the following text: %s\n", text);

    set_text_color(FG_GRAY);
    printf("%s", text);
    set_text_color(FG_DEF);
}

// Функция для считывания текста из файла
void read_file(const char* filename, char* buffer, size_t buffer_size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fgets(buffer, buffer_size, file);
    trim(buffer);
    fclose(file);
}

// Функция для получения ввода пользователя
void read_user_input(char* buffer, size_t buffer_size) {
    printf("\n");
    fgets(buffer, buffer_size, stdin);

    trim(buffer);
}

// Выводим сравнение двух строк, а также считаем и возвращаем кол-во ошибок
int print_comparison(const char* original_text, const char* user_input) {
    printf("\nResult text:\n");
    int errors = 0;
    int i;

    int user_len = strlen(user_input);

    for (i = 0; original_text[i] != '\0'; i++) {
        if (i >= user_len)
        {
            set_text_color(FG_GRAY);
            errors++;
            putchar(original_text[i]);
            set_text_color(FG_DEF);
            continue;
        }

        if (original_text[i] != user_input[i]) {
            set_text_color(BG_RED);
            errors++;
        }
        if (original_text[i] == user_input[i]) {
            set_text_color(BG_GREEN);
        }

        putchar(user_input[i]);
        set_text_color(FG_DEF);
    }

    return errors;
}

// Выводим всю информацию
void print_results(int errors, int total_chars, double elapsed_time) {
    double error_percentage = (double) errors / total_chars * 100;
    printf("\n\nErrors: %d\n", errors);
    printf("Accuracy percentage: %.2f%%\n", 100.0-error_percentage);
    printf("Elapsed time: %.2f seconds\n\n", elapsed_time);
}

