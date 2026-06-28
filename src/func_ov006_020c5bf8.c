struct Vec3 { int x, y, z; };
extern void AddVec3(struct Vec3 *a, struct Vec3 *b, struct Vec3 *c);
extern void ApproachLinear(short *a, short b, short c);
extern void func_ov006_020c49d8(void *c);

void func_ov006_020c5bf8(char *c)
{
    int a8 = *(int*)(c + 0xa8);
    if (a8 < 0 && *(int*)(c + 0x9c) < *(int*)(c + 0x20) + *(int*)(c + 0x10)) {
        *(int*)(c + 0xa8) = -a8;
    } else if (a8 > 0 && *(int*)(c + 0x9c) > *(int*)(c + 0x20) + *(int*)(c + 0x14)) {
        *(int*)(c + 0xa8) = -a8;
    }
    int ac = *(int*)(c + 0xac);
    if (ac < 0 && *(int*)(c + 0xa0) < *(int*)(c + 0x24) + *(int*)(c + 0x18)) {
        *(int*)(c + 0xac) = -ac;
    } else if (ac > 0 && *(int*)(c + 0xa0) > *(int*)(c + 0x24) + *(int*)(c + 0x1c)) {
        *(int*)(c + 0xac) = -ac;
    }
    AddVec3((struct Vec3*)(c + 0x9c), (struct Vec3*)(c + 0xa8), (struct Vec3*)(c + 0x9c));
    if (*(int*)(c + 0xa8) > 0)
        ApproachLinear((short*)(c + 0xe6), 0x3000, 0x200);
    else
        ApproachLinear((short*)(c + 0xe6), -0x3000, 0x200);
    func_ov006_020c49d8(c);
}
