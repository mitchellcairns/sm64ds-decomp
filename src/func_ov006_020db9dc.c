typedef short s16;
typedef unsigned short u16;

extern void func_ov006_020c1604(char *c, int unused, short a2, int a3);
extern void func_ov006_020da974(int v);
extern void func_ov006_020da00c(char *p);
extern void func_ov004_020b66d4(void);
extern int func_020bc7d4;
extern int data_ov006_0214176c;
extern int data_ov006_02141768;
extern int data_ov006_02141770;
extern int data_ov006_0213bc44;

void func_ov006_020db9dc(char *c)
{
    int i;
    char *p1, *p2;

    *(s16 *)(c + 0x538c) = 0;
    *(s16 *)(c + 0x538e) = 6;
    *(s16 *)(c + 0x5390) = 6;
    *(s16 *)(c + 0x5392) = 6;
    *(s16 *)(c + 0x5394) = 6;
    func_ov006_020c1604(c + 0x4f38, 4, 5, (int)(c + 0x538c));

    *(s16 *)(c + 0x511e) = 1;
    *(s16 *)(c + 0x4f52) = 2;
    func_ov006_020da974(5);

    p1 = c + 0x51a8;
    p2 = c + 0x5298;
    for (i = 0; i < 5; i++) {
        func_ov006_020da00c(p1);
        func_ov006_020da00c(p2);
        p1 += 0x30;
        p2 += 0x30;
    }

    func_ov004_020b66d4();

    func_020bc7d4 = 1;
    data_ov006_0214176c = 0;
    data_ov006_02141768 = 0;
    data_ov006_02141770 = 0;
    *(char *)(c + 0x539a) = 0;
    data_ov006_0213bc44 = 1;
    *(s16 *)(c + 0x5388) = 1;
}
