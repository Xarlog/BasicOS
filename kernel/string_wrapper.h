#ifndef STRING_WARPPER_H
#define STRING_WARPPER_H
struct _string_w
{
    char * begining;
    char * end;
};
typedef struct _string_w string_w;
string_w convertToWrapper(char*str)
{
    string_w res;
    res.begining=str;
    while(*str)str++;
    res.end=str;
    return res;
}
unsigned char compareStr_w(string_w a, string_w b)
{
    if(a.end-a.begining!=b.end-b.begining)return a.end-a.begining - (b.end-b.begining);
    while(a.begining<a.end)
    {
        if(*a.begining!=*b.begining) return *a.begining-*b.begining;
        a.begining++;
        b.begining++;
    }
    return 0;
} 
/*Finds the index of a character in a string
@param str string to be searched
@param c character to be found
@return index at which the character was found, last index if not found
*/
int findCharacter(const char * str, char c)
{
    const char* t=str;
    while(*t!=c&& *t!=0)t++;
    if(*t==c)return t-str;
    return t-str;
}
#endif