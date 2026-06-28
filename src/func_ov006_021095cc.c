extern void func_ov006_02107b14(void);
extern void func_ov006_020c0e8c(int *t);
extern void func_ov006_021092a0(int *o);
extern void func_ov006_02108524(char *c);
extern void func_ov004_020b66d4(void);
extern int *func_020beb68;
extern void *data_ov006_021428c8;
extern int func_020bc7d4;

void func_ov006_021095cc(char *this)
{
    int i;
    int *e;
    int n;

    func_ov006_02107b14();
    func_ov006_020c0e8c((int *)(this + 0x4f38));

    *(short *)(this + 0x53f2) = 0;
    *(short *)(this + 0x53e8) = 0xa;

    e = (int *)(this + 0x51a8);
    for (i = 0; i < 5; i++) {
        func_ov006_021092a0(e);
        e = (int *)((char *)e + 0x34);
    }

    *(int *)(this + 0x53f8) = 0;
    *(short *)(this + 0x53f6) = 0;
    n = 0;
    if (func_020beb68 != 0) n = func_020beb68[0xa8 / 4];
    if (n >= 5) n = 5;
    *(int *)(this + 0x53fc) = n;

    func_ov006_02108524(this + 0x530c);

    data_ov006_021428c8 = 0;
    *(short *)(this + 0x53e4) = 0;
    *(int *)(this + 0x53e0) = 0x100;
    *(short *)(this + 0x53ea) = 0;
    *(unsigned char *)(this + 0x53ec) = 0;
    *(unsigned char *)(this + 0x53ed) = 0;
    *(unsigned char *)(this + 0x53ee) = 0;
    *(unsigned char *)(this + 0x53ef) = 0;
    *(unsigned char *)(this + 0x53f0) = 0;
    *(short *)(this + 0x53e6) = 1;

    func_ov004_020b66d4();
    func_020bc7d4 = 1;
}
