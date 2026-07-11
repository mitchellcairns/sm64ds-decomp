extern unsigned char data_0209f2d8;
extern int func_02005e28(void *c);

void _ZN8CapEnemy12Unk_02005d94Ev(unsigned char *c)
{
    int b1;
    int b2;
    if (!(c[0x113] & 0x80)) return;
    b1 = (*(unsigned int *)(c + 0xb0) & 8) ? 1 : 0;
    if (b1 == 0) {
        volatile unsigned char *q = &data_0209f2d8;
        b2 = (q[0] == 1) ? 1 : 0;
        if (b2 == 0) return;
    }
    *(unsigned char *)(((int)c + 0x113) & 0xFFFFFFFFFFFFFFFFULL) &= 7;
    if (func_02005e28(c))
        *(unsigned char *)(((int)(c + 0x113)) & 0xFFFFFFFFFFFFFFFFULL) |= 0x80;
}
