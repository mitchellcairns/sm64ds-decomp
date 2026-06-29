typedef signed int s32;

extern int data_ov004_020bf9ec;
extern int data_ov004_020bfa18;
extern int data_020a0db0;
extern void **data_ov004_020bc828[];
extern int data_ov004_020bfa24;
extern int data_ov004_020bf9e8;
extern unsigned char data_ov004_020bfa34[];

extern s32 func_ov004_020ad674(void);
extern void func_ov004_020af68c(void *fn, s32 a, s32 b, s32 r3arg, s32 stack_arg);
extern void func_ov004_020b653c(int arg);
extern void func_ov004_020b52b8(void *c);

void func_ov004_020b6430(void) {
    int i;
    unsigned char *p;

    if (data_ov004_020bf9ec == 0 && data_ov004_020bfa18 != 0) {
        if (data_020a0db0 & 0x10) {
            func_ov004_020af68c(data_ov004_020bc828[func_ov004_020ad674()][0], 0x14, 0x30, -1, -1);
        } else {
            func_ov004_020af68c(data_ov004_020bc828[func_ov004_020ad674()][1], 0x14, 0x30, -1, -1);
        }
        func_ov004_020af68c(data_ov004_020bc828[func_ov004_020ad674()][2], 0x14, 0x30, -1, -1);
    }

    if (data_ov004_020bfa24 != 0) {
        func_ov004_020b653c(data_ov004_020bf9e8);
    }

    p = data_ov004_020bfa34;
    for (i = 0; i < 0x14; i++) {
        func_ov004_020b52b8(p);
        p += 0x24;
    }
}
