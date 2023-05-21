#include <libKeyboardNinja/funcs.h>
#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#ifdef _WIN32
#include <windows.h>
#define BG_RED 0xC0
#define BG_GREEN 0xA0
#define FG_GRAY 0x08
#define FG_DEF 0x07
#else
#include <unistd.h>
#define BG_RED 41
#define FG_GRAY 30
#define BG_GREEN 42
#endif

int main()
{
    setlocale(LC_ALL, "");

    printf("\t\t —— TYPING TRAINER —— \n\n");

    char filename[100] = "test.txt";
    int choice = 0;
    scanf("%d", &choice);
    getchar();
    genName(filename, choice);
    char text[1000];
    char user_input[2000];
    struct timeval start, end;

    read_file(filename, text, sizeof(text)); // Читаем текст из файла
    print_text(text); // Выводим текст на экран

    gettimeofday(&start, NULL); // Начинаем отсчет времени
    read_user_input(
            user_input,
            sizeof(user_input)); // Читаем введенный пользователем текст
    gettimeofday(&end, NULL); // Заканчиваем отсчет времени

    double elapsed = end.tv_sec - start.tv_sec
            + (end.tv_usec - start.tv_usec)
                    / 1000000.0; // Вычисляем прошедшее время в секундах

    int errors = print_comparison(
            text, user_input); // Сравниваем введенный текст с оригинальным и
                               // считаем количество ошибок
    print_results(
            errors,
            strlen(text),
            elapsed); // Выводим результаты: количество ошибок, процент ошибок и
                      // время набора

    return 0;
}
