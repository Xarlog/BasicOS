#include "low_io.h"
#include "low_print.h"
#include "ps2.h"
#include "scanset_2.h"
#include "console.h"
int __main(void)
{
    clearScreen();
    basic_print("Greetings from kernel!\n");
    putcStyled('>',0x8f);

    initKeyboard();
    resetScreen();
    basic_print("Basic OS V-0.05a\n");
    console();

    while(1)
    {    
        if((ps2_read_status().out_buffer)!=0){
            //print_hex(port_byte_in(0x60)); putc(' ');
            unsigned char t=port_byte_in(0x60);
            if(t==KEY_RELEASED){while((ps2_read_status().out_buffer)==0);t=port_byte_in(0x60);continue;}
            putc(testCharacter(t));
        }
    }
}
