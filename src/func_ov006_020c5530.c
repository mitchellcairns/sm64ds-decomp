struct Vec3 { int x, y, z; };
extern void AddVec3(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c);
extern void ApproachLinear(short *a, short b, short c);
extern void func_ov006_020c49d8(void *c);

void func_ov006_020c5530(char *c)
{
    int a8 = *(int*)(c + 0xa8);
    if (a8 < 0 && *(int*)(c + 0x9c) < -0x68000) {
        *(int*)(c + 0xac) = -a8;
        *(int*)(c + 0xa8) = 0;
    } else if (a8 > 0 && *(int*)(c + 0x9c) > 0x68000) {
        *(int*)(c + 0xac) = -a8;
        *(int*)(c + 0xa8) = 0;
    }
    int ac = *(int*)(c + 0xac);
    if (ac < 0 && *(int*)(c + 0xa0) < 0x20000) {
        *(int*)(c + 0xa8) = ac;
        *(int*)(c + 0xac) = 0;
    } else if (ac > 0 && *(int*)(c + 0xa0) > 0xc0000) {
        *(int*)(c + 0xa8) = ac;
        *(int*)(c + 0xac) = 0;
    }
    AddVec3((struct Vec3*)(c + 0x9c), (struct Vec3*)(c + 0xa8), (struct Vec3*)(c + 0x9c));
    if (*(int*)(c + 0xa8) > 0)
        ApproachLinear((short*)(c + 0xe6), 0x3000, 0x200);
    else
        ApproachLinear((short*)(c + 0xe6), -0x3000, 0x200);
    func_ov006_020c49d8(c);
}
