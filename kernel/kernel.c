#include "low_io.h"
#include "low_print.h"
#include "ps2.h"
#include "scanset_2.h"
#include "console.h"
int __main(void)
{
    clearScreen();
    basic_print("Greetings from kernel!\n");

    initKeyboard();
    resetScreen();
    basic_print("Basic OS V-0.05a\n");
    console();
}
