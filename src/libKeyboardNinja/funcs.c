#include "funcs.h"
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

// Меняем цвет текста
void set_text_color(int color)
{
#ifdef _WIN32
    // для ОС Windows используется библиотека Windows.h,
    // получаем дескриптор стандартного вывода и устанавливаем цвет текста
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(
            hConsole,
            color | (BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_BLUE));
#else
    // для *nix систем используется escape-последовательность ANSI,
    // которая устанавливает цвет текста
    printf("\033[1;%dm", color);
#endif
}

// Функция для вывода оригинального текста
void print_text(const char* text)
{
    printf("\nType the following text: %s\n", text);

    set_text_color(37);
    printf("%s", text);
    set_text_color(0);
}

// Функция для считывания текста из файла
void read_file(const char* filename, char* buffer, size_t buffer_size)
{
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        exit(1);
    }
    fgets(buffer, buffer_size, file);
    fclose(file);
}

// Функция для получения ввода пользователя
void read_user_input(char* buffer, size_t buffer_size)
{
    printf("\n");
    fgets(buffer, buffer_size, stdin);

    // Убираем символ \n в конце
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[len - 1] = '\0';
    }
}

// Выводим сравнение двух строк, а также считаем и возвращаем кол-во ошибок
int print_comparison(const char* original_text, const char* user_input)
{
    printf("\nResult text:\n");
    int errors = 0;
    int i;

    int user_len = strlen(user_input);

    for (i = 0; original_text[i] != '\0'; i++) {
        if (i >= user_len) {
            set_text_color(FG_GRAY);
            errors++;
            putchar(original_text[i]);
            set_text_color(0);
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
        set_text_color(0);
    }

    return errors;
}

// Выводим всю информацию
void print_results(int errors, int total_chars, double elapsed_time)
{
    double error_percentage = (double)errors / total_chars * 100;
    printf("\n\nErrors: %d\n", errors);
    printf("Error percentage: %.2f%%\n", error_percentage);
    printf("Elapsed time: %.2f seconds\n\n", elapsed_time);
}
