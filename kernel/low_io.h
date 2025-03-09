#ifndef LOW_IO_H
#define LOW_IO_H
/*Low level function to read a byte from port
@param port port for data to be read from
@return the byte read from port
*/
unsigned char port_byte_in ( const unsigned short port ) {
// A handy C wrapper function that reads a byte from the specified port
// "= a " ( result ) means : put AL register in variable RESULT when finished
// " d " ( port ) means : load EDX with port
    unsigned char result ;
    asm( "in %%dx , %%al " : "= a" ( result ) : "d" ( port ));
    return result ;
}
/*Low level function to write data to port
@param port port to write data to
@param data to be written
*/
void port_byte_out ( const unsigned short port , const unsigned char data ) {
// " a " ( data ) means : load EAX with data
// " d " ( port ) means : load EDX with port
    asm( "out %%al , %%dx " : : "a" ( data ) , "d" ( port ));
}
/*Low level function to read a byte from port
@param port port for data to be read from
@return the byte read from port
*/
unsigned short port_word_in ( const unsigned short port ) {
    unsigned short result ;
    __asm__(" in %%dx , %%ax " : "= a" ( result ) : "d" ( port ));
    return result ;
}
/*Low level function to write data to port
@param port port to write data to
@param data to be written
*/
void port_word_out ( const unsigned short port , const unsigned short data ) {
    __asm__(" out %%ax , %%dx " : : "a" ( data ) , "d" ( port ));
}
/*Low level function to check if the data read from a port is equal to the one provided
@param port port to read from
@param data data to be compared
@return 1 if equal, 0 if not
*/
unsigned char port_byte_test(const unsigned short port, const unsigned char data)
{
    return port_byte_in(port)==data;
}
/*A debug function using the Bochs 0xE9 hack to log data
@param d data to be logged
*/
void bochs_debug(const unsigned d)
{
    port_byte_out(0xE9,d);
}
#endif