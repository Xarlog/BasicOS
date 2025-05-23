#include "console.h"
#include "../driver/buzzer.h"
int __main(void)
{
    clearScreen();
    basic_print("Greetings from kernel!\n");
    initKeyboard();
    resetScreen();
    basic_print("Basic OS V-0.05a\n");
    console();
}
