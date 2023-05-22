#include "ctest.h"
#include <libKeyboardNinja/funcs.h>

CTEST(TextsComparison, error_count)
{
    char text[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    char input[100]
            = "beware of love. beware of love. it is more dangerous than "
              "brandy, bronchitis, or pleurisy";
    int expected = 4;
    ASSERT_EQUAL(expected, print_comparison(text, input));
    char input2[100]
            = "Beware of love. Beware of love. It is more dangerous than "
              "brandy, bronchitis, or pleurisy!";
    expected = 0;
    ASSERT_EQUAL(expected, print_comparison(text, input2));
}
