#ifndef PS2_H
#define PS2_H
#include "low_print.h"
#include "low_io.h"
#define NOP asm("nop\nnop\nnop\n");
struct ps2_status
{
    unsigned char out_buffer:1;
    unsigned char in_buffer:1;
    unsigned char sys_flag:1;
    unsigned char command_bit:1;
    unsigned char b4:1;
    unsigned char b5:1;
    unsigned char timeout:1;
    unsigned char parity_err:1; 
};
union ps2_type_transform
{
    struct ps2_status b;
    unsigned char a;
};
#define PS2_DATA 0x60
#define PS2_COMMAND 0x64
#define PS2_STATUS 0x64
//Waits until data can be written to PS2
void keyboardAwait()
{
    asm("nop\nnop\nnop\n");
    basic_print("    Out-wait start"); //putc(' '); print_hex(port_byte_in(0x64));
    while(port_byte_in(PS2_STATUS)&0b00000010==2)asm("nop\nnop\nnop\n");;
    basic_print("    Out-wait end\n");
}
/*Waits until data can be read from PS2
@return 0 if successfull, 1 if timed out
*/
int keyboardAwaitIn()
{
    unsigned n=0;
    asm("nop\nnop\nnop\n");
    basic_print("    In-wait start"); putc(' '); //print_hex(port_byte_in(0x64));
    while((port_byte_in(PS2_STATUS)&0b00000001)==0&&n<1000)n++;
    if(n==1000)
    {
        basic_print("    Timeout\n");
        return 1;
    }
    basic_print("    In-wait end\n");
    return 0;
}
/*Sends a command to the PS2 controller
@param command command to be sent
*/
void ps2_send_commmand(const unsigned char command)
{
    keyboardAwait();
    port_byte_out(PS2_COMMAND,command);
}
/*Sends a command and additional data to the PS2 controller
@param command command to be sent
@param data additional data for the command
*/
void ps2_send_compound_command(const unsigned char command, const unsigned char data)
{
    keyboardAwait();
    port_byte_out(PS2_COMMAND,command);
    keyboardAwait();
    port_byte_out(PS2_DATA,data);
}
/*Sends data to the PS2 controller
@param data data byte to be sent
*/
void ps2_send_data(const unsigned char data)
{
    keyboardAwait();
    port_byte_out(PS2_DATA,data);
}
/*Reads data from the PS2 controller
@return read byte, 0 if timed out
*/
unsigned char ps2_read_data()
{
    if(keyboardAwaitIn())
    {basic_print("PS2 read timeout!\n");return 0;}//timeout
    return port_byte_in(PS2_DATA);
}
/*Returns the status byte of the PS2 controller as a structure
@return PS2 controller status
*/
struct ps2_status ps2_read_status()
{
    return ((union ps2_type_transform)port_byte_in(PS2_STATUS)).b;
    //return port_byte_in(PS2_STATUS);
};
/*Performs a self-test on the PS2 keyboard
@return 0 if success, 1 if fail
*/
int ps2_keyboard_self_test()
{
    unsigned char ret;
    do
    {
        ps2_send_data(0xFF);
        NOP
        NOP
        NOP
        NOP
    }while((ret=ps2_read_data())==0xFE);
    if(ret!=0xFA)
    {
        basic_print("Failed to send ACK! Code sent:");
        print_hex(ret);
        return 1;
    }
    ret=ps2_read_data();
    if(ret!=0xAA)
    {
        basic_print("Self-test success code not sent! Code sent:");
        print_hex(ret);
        return 1;
    }

    return 0;
}
//Initializes the PS2 controller. Only call once.
void initPS2()
{
    basic_print("1. Disabling PS/2-1\n");
    ps2_send_commmand(0xAD);
    resetScreen();

    basic_print("2. Disabling PS/2-2\n");
    ps2_send_commmand(0xA7);//Disable PS/2-2
    resetScreen();

    basic_print("3. Writing config\n");//Write controller configuration byte
    ps2_send_compound_command(0x60,0b00010101);
    resetScreen();

    basic_print("4. Checking PS/2 controller\n");
    ps2_send_commmand(0xAA);//PS/2 check
    if(ps2_read_data()!=0x55)putc('1');//FAIL
    resetScreen();

    basic_print("5. Checking PS/2-1\n");
    ps2_send_commmand(0xAB);//PS/2-1 check
    if(ps2_read_data()!=0x00)putc('2');//FAIL
    resetScreen();

    basic_print("6. Enabling PS/2-1\n");
    ps2_send_commmand(0xAE);//Enable PS/2-1
    resetScreen();

    //basic_print("7. Reseting\n");
    //ps2_send_commmand(0xFF);//Reset?
    //resetScreen();

    basic_print("8. Writing config\n");
    ps2_send_compound_command(0x60,0b00010101);//Write controller configuration byte
    resetScreen();
}
//Initializes the PS2 keyboard. Only call once.
void initKeyboard()
{
    initPS2();
    basic_print("9. KBD init done\n");
    resetScreen();
    asm("nop\nnop\nnop\n");

    basic_print("Keyboard echo test:\n");
    ps2_send_data(0xEE);
    print_hex(ps2_read_data());

    print_hex(port_byte_in(PS2_STATUS));
    putc('\n');
    clearScreen();
    basic_print("10. Keyboard self-test\n");
    if (ps2_keyboard_self_test())
        basic_print("Keyboard error\n");
    // resetScreen();

    print_hex(port_byte_in(PS2_STATUS));
    putc('\n');
    basic_print("11. Enabling scanning\n");
    ps2_send_data(0xF4);
    if (ps2_read_data() != 0xFA)
        basic_print("Keyboard Error\n");
    basic_print("12. Scanning enabled\n");

    /*Scan set test - result is 02
    ps2_send_data(0xF0);
    print_hex(ps2_read_data());
    ps2_send_data(0x0);
    print_hex(ps2_read_data());*/
}
#endif