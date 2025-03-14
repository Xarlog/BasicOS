#ifndef BUZZER_H
#define BUZZER_H
#include "../kernel/low_io.h"
void playSound(long frequency)
{
    port_byte_out(0x43,0xb6);
    port_byte_out(0x42,(unsigned char)(1193180/frequency));
    port_byte_out(0x42,(unsigned char)((1193180/frequency)>>8));
    port_byte_out(0x61,port_byte_in(0x61)|3);
}
void stopSound()
{
    port_byte_out(0x61,port_byte_in(0x61)&0xFC);
}
#endif