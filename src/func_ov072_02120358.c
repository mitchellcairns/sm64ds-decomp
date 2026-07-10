struct Vec3 { int x, y, z; };
extern short Vec3_HorzAngle(const void* a, const void* b);
extern int _Z14ApproachLinearRsss(short* p, short to, short step);
extern int _ZN6Player11ShowMessageER9ActorBasejPK7Vector3jj(void* self, void* actor, unsigned int msg, const void* pos, unsigned int a, unsigned int b);
extern int _ZN6Player12GetTalkStateEv(void* self);
extern void func_ov072_021205d4(void* c, int a);

int func_ov072_02120358(char* c)
{
    struct Vec3 v;
    unsigned char *st;
    switch (*(unsigned char*)(c + 0x334)) {
    case 0:
        if (_Z14ApproachLinearRsss((short*)(c + 0x8e),
                Vec3_HorzAngle(c + 0x5c, *(char**)(c + 0x32c) + 0x5c), 0x514)) {
            v.x = *(int*)(c + 0x5c);
            v.y = *(int*)(c + 0x60);
            v.z = *(int*)(c + 0x64);
            v.y = v.y + 0xfa000;
            if (_ZN6Player11ShowMessageER9ActorBasejPK7Vector3jj(*(void**)(c + 0x32c), c, 0xaf, &v, 0, 0)) {
                st = (unsigned char*)(((int)c + 0x334) & 0xFFFFFFFFFFFFFFFFLL);
                *st = *st + 1;
            }
        }
        break;
    case 1:
        if (_ZN6Player12GetTalkStateEv(*(void**)(c + 0x32c)) == -1) {
            func_ov072_021205d4(c, 0);
        }
        break;
    }
    return 1;
}
