#ifndef SCANSET_2_H
#define SCANSET_2_H
#define KEY_F9 0x01
#define KEY_F5 0x03
#define KEY_F3 0x04
#define KEY_F1 0x05
#define KEY_F2 0x06
#define KEY_F12 0x07
#define KEY_F10 0x09
#define KEY_F8 0x0A
#define KEY_F6 0x0B
#define KEY_F4 0x0C
#define KEY_TAB 0x0D
#define KEY_BACK_TICK 0x0E
#define KEY_LEFT_ALT 0x11
#define KEY_LEFT_SHIFT 0x12
#define KEY_LEFT_CONTROL 0x14
#define KEY_Q 0x15
#define KEY_1 0x16
#define KEY_Z 0x1A
#define KEY_S 0x1B
#define KEY_A 0x1C
#define KEY_W 0x1D
#define KEY_2 0x1E
#define KEY_C 0x21
#define KEY_X 0x22
#define KEY_D 0x23
#define KEY_E 0x24
#define KEY_4 0x25
#define KEY_3 0x26
#define KEY_SPACE 0x29
#define KEY_V 0x2A
#define KEY_F 0x2B
#define KEY_T 0x2C
#define KEY_R 0x2D
#define KEY_5 0x2E
#define KEY_N 0x31
#define KEY_B 0x32
#define KEY_H 0x33
#define KEY_G 0x34
#define KEY_Y 0x35
#define KEY_6 0x36
#define KEY_M 0x3A
#define KEY_J 0x3B
#define KEY_U 0x3C
#define KEY_7 0x3D
#define KEY_8 0x3E
#define KEY_COMMA 0x41
#define KEY_K 0x42
#define KEY_I 0x43
#define KEY_O 0x44
#define KEY_0 0x45
#define KEY_9 0x46
#define KEY_DOT 0x49
#define KEY_SLASH 0x4A
#define KEY_L 0x4B
#define KEY_SEMICOLON 0x4C
#define KEY_P 0x4D
#define KEY_MINUS 0x4E
#define KEY_APOSTROPHE 0x52
#define KEY_LEFT_SQUARE_BRACKET 0x54
#define KEY_EQUALS 0x55
#define KEY_CAPSLOCK 0x58
#define KEY_RIGHT_SHIFT 0x59
#define KEY_ENTER 0x5A
#define KEY_RIGHT_SQUARE_BRACKET 0x5B
#define KEY_BACKSLASH 0x5D
#define KEY_BACKSPACE 0x66
#define KEY_KEYPAD_1 0x69
#define KEY_KEYPAD_4 0x6B
#define KEY_KEYPAD_7 0x6C
#define KEY_KEYPAD_0 0x70
#define KEY_KEYPAD_DOT 0x71
#define KEY_KEYPAD_2 0x72
#define KEY_KEYPAD_5 0x73
#define KEY_KEYPAD_6 0x74
#define KEY_KEYPAD_8 0x75
#define KEY_ESCAPE 0X76
#define KEY_NUMBERLOCK 0x77
#define KEY_F11 0x78
#define KEY_KEYPAD_PLUS 0x79
#define KEY_KEYPAD_3 0x7A
#define KEY_KEYPAD_MINUS 0x7A
#define KEY_KEYPAD_MULTIPLY 0x7C
#define KEY_KEYPAD_9 0x7d
#define KEY_SCROLLLOCK 0x7E
#define KEY_F7 0x83
//MORE KEYS TO BE DEFINED WITH E0
#define KEY_RELEASED 0xF0
/*Converts a scancode to char. Assumes scanset 2.
@return scanned character or 0 if the character is not found.
*/
char testCharacter(unsigned char t)
{
    switch(t)
    {
        case KEY_0:
        return '0';
        case KEY_1:
        return '1';
        case KEY_2:
        return '2';
        case KEY_3:
        return '3';
        case KEY_4:
        return '4';
        case KEY_5:
        return '5';
        case KEY_6:
        return '6';
        case KEY_7:
        return '7';
        case KEY_8:
        return '8';
        case KEY_9:
        return '9';
        case KEY_A:
        return 'A';
        case KEY_B:
        return 'B';
        case KEY_C:
        return 'C';
        case KEY_D:
        return 'D';
        case KEY_E:
        return 'E';
        case KEY_F:
        return 'F';
        case KEY_G:
        return 'G';
        case KEY_H:
        return 'H';
        case KEY_I:
        return 'I';
        case KEY_J:
        return 'J';
        case KEY_K:
        return 'K';
        case KEY_L:
        return 'L';
        case KEY_M:
        return 'M';
        case KEY_N:
        return 'N';
        case KEY_O:
        return 'O';
        case KEY_P:
        return 'P';
        case KEY_Q:
        return 'Q';
        case KEY_R:
        return 'R';
        case KEY_S:
        return 'S';
        case KEY_T:
        return 'T';
        case KEY_U:
        return 'U';
        case KEY_V:
        return 'V';
        case KEY_W:
        return 'W';
        case KEY_X:
        return 'X';
        case KEY_Y:
        return 'Y';
        case KEY_Z:
        return 'Z';
        case KEY_SPACE:
        return ' ';

        default:
        return 0;
    }
}
#endif