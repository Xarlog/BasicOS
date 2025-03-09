#ifndef LOW_MEM_H
#define LOW_MEM_H
void memcpy(void * src,void  *dst,unsigned n)
{
    while(n--) *(char*)(dst)++=*(char*)(src++);
}

void memfill(void * start,unsigned n,char init)
{
    while(n--) *((char*)start++)=init;
}
#endif