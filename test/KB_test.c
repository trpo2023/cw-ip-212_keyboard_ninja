#include "ctest.h"
#include <libKeyboardNinja/funcs.h>

CTEST(error_counter, correct_input)
{
    char text[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    char input[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    int expected = 0;
    ASSERT_EQUAL(expected, print_comparison(text, input));
}

CTEST(error_counter, wrong_input)
{
    char text[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    char input[100]
            = "beware of love. beware of love. it is more dangerous than "
              "brandy, bronchitis, or pleurisy";
    int expected = 4;
    ASSERT_EQUAL(expected, print_comparison(text, input));
}

CTEST(error_counter, empty_input)
{
    char text[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    char input[100] = "";
    int expected = 90;
    ASSERT_EQUAL(expected, print_comparison(text, input));
}

