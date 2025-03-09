#ifndef LOW_PRINT_H
#define LOW_PRINT_H
#include "low_mem.h"
#define VIDEO_MEMORY (char*)0xb8000
int video_offset=0;
#define VIDEO_IN *(VIDEO_MEMORY+video_offset)
char *DISPLAY_HISTORY=(char*)0x100000;
#define DISPLAY_HISTORY_LENGTH 80*2*1000
int display_history_offset=0;
void clearCurrentLine()//Broken
{
    memfill(VIDEO_MEMORY+video_offset-video_offset%160,160,0);
}
/*Puts a character to the GPU in text mode. If \n then adds a new line
@param t character to print
*/
void putc(char t)
{
    bochs_debug(t);
    if(t=='\n')
    {
        video_offset=((video_offset/2)/80+1)*160;
        if(video_offset>=80*25*2)video_offset=0;
        clearCurrentLine();
        return;
    }
    VIDEO_IN=t;
    *(VIDEO_MEMORY+video_offset+1)=(char)0x0f;
    video_offset+=2;
    if(video_offset>=80*25*2)
    {
        video_offset=0;
        //clearCurrentLine();
    }
}
/*Puts a character to the GPU in text mode. If \n then adds a new line
@param t character to print
@param style style byte | 0x80 blink| 0x40 bg red| 0x20 bg green| 0x10 bg blue| 0x08 bright| 0x04 red| 0x02 green| 0x01 blue|
*/
void putcStyled(char t, char style)
{
    VIDEO_IN=t;
    *(VIDEO_MEMORY+video_offset+1)=(char)style;
    video_offset+=2;
    if(video_offset>=80*25*2)video_offset=0;
}
/*Prints a string to text mode GPU
@param string string to be printed
*/
void basic_print(const char*string)
{
    for(;*string!=0;string++)putc(*string);
}
/*Prints a block of chars
@param data block of data to be printed
@param n number of bytes
*/
void print_data(const char* data, unsigned n)
{
    while(n--)putc(*(data++));
}
/*Prints a byte in hex form
@param t byte to be printed
*/
void print_hex(const unsigned char t)
{
    char *hex="0123456789ABCDEF"; 
    putc(hex[(((unsigned char)t)&0b11110000)>>4]);
    putc(hex[((unsigned char)t)&0b1111]);
}
/*Moves the text output a line up
*/
void scrollScreen()
{
    for(unsigned i=80;i<80*25;i++)
        *((short*)VIDEO_MEMORY+i-80)=*((short*)VIDEO_MEMORY+i);
    if(video_offset>=160)video_offset-=160;
}
//Clears the text output
void clearScreen()
{
    memfill(VIDEO_MEMORY,80*25*2,0);
}
/*Moves the caret by an offset
@param collumn the horizontal offset
@param line the vertical offset
*/
void moveCaret(int collumn, int line)
{
    video_offset+=collumn*2+line*160;
    if(video_offset<0)video_offset=0;
}
/*Moves the caret to a position
@param collumn the horizontal position
@param line the vertical position
*/
void setCaret(unsigned char collumn, unsigned char line)
{
    video_offset=collumn*2+line*160;
    if(video_offset>=2*80*25)video_offset=2*80*25-2;
}
//Clears text output and moves the caret to start
void resetScreen()
{
    clearScreen();
    setCaret(0,0);
}
/*Prints a number
@param a number to be printed
*/
void print_number(int a)
{
    char sign=(a>=0)?'+':'-';
    a=(a>=0)?a:-a;
    char t[11]={};
    for(unsigned i=0;i<11;i++)
    {
        t[i]='0'+a%10;
        a/=10;
        if(a==0)
        {
            break;
        }
    }
    putc(sign);
    for(unsigned i=0;i<11;i++)
    {
        if(t[10-i]!=0)putc(t[10-i]);
    }
}
/*Copies a string from one location to another
@param dst the destination for the string
@param src source string
*/
void strcpy(char*dst, const char *src)//to be tested
{while (*dst++=*src++);}
/*Compares two strings
@param s string 1
@param t string 2
@return 0 if same, first difference if different
*/
int strcmp(const char* s,const char *t)//to be tested
{
    int i;
    for(i=0; s[i]==t[i];i++)
    {
        if(s[i]=='\0')
        {
            return 0;
        }
    }
    return s[i]-t[i];
}
int printf(char* t,...)
{
    
}
#endif