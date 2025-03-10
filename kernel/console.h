#ifndef CONSOLE_H
#define CONSOLE_H
#include "ps2.h"
#include "scanset_2.h"
#include "string_wrapper.h"
#define CONSOLE_BUFFER 100
//A simple function to print a blinking caret symbol
void putCaretSymbol()
{
    putcStyled('_',0x8f);moveCaret(-1,0);
}
/*A function to read a command from input
@param buffer the c-string intended as the command buffer
@return the typed command bound within the string_w structure
*/
string_w readCommand(char*buffer)
{
    *buffer='\0';
    string_w res;
    res.begining=buffer;
    int pos=0;
    unsigned char key=0;
    while(key!=KEY_ENTER&&pos<CONSOLE_BUFFER)
    {
        if(ps2_read_status().out_buffer!=0)
        {
            key=getScanCode();
            if(key==KEY_RELEASED){while((ps2_read_status().out_buffer)==0);key=getScanCode();key=0;continue;}
            if(key==KEY_BACKSPACE&&pos>0)
            {
                buffer[pos-1]=buffer[pos];
                buffer[pos]='\0';
                putc('\0');
                moveCaret(-2,0);
                putCaretSymbol();
                pos--;
            }
            buffer[pos]=testCharacter(key);
            if(buffer[pos])putc(buffer[pos]);putCaretSymbol();
            pos+=(buffer[pos]!=0);
        }
    }
    res.end=buffer+findCharacter(buffer,' ');
    return res;
}
//A simple console subsystem
void console()
{
    char buffer[CONSOLE_BUFFER];
    basic_print("\n>");putCaretSymbol();
    while(1)
    {
        string_w cmd={.begining=buffer,.end=buffer};
        cmd=readCommand(buffer);
        putc('\0'); putc('\n');
        if(compareStr_w(cmd,convertToWrapper("ECHO"))==0)
        {
            basic_print(cmd.end+1);
        }
        else if(strcmp(buffer,"CLEAR")==0)
        {
            resetScreen();
        }
        else if(strcmp(buffer,"HELP")==0)
        {
            basic_print("\nCLEAR - clears screen\nECHO <text> - prints following text\nHELP - prints help\nQUIT - poweroffs the device\nRESTART - restarts the system\n");
        }
        else if(strcmp(buffer,"QUIT")==0)port_word_out(0xB004,0x2000);//Bochs specific.
        else if(strcmp(buffer,"RESTART")==0)ps2_send_commmand(0xFE);
        else basic_print("\nUnknown command! Type HELP for commands.");
        basic_print("\n>");putCaretSymbol();
        continue;
    }
}
#endif