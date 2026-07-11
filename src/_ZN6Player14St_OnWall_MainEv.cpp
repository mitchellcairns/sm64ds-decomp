//cpp
typedef int s32;
typedef short s16;
typedef long long s64;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;
typedef s32 Fix12;

extern "C" {
extern void func_ov002_020c0364(char* c, u32 a);
extern void func_ov002_020cabe0(char* c);
extern int func_ov002_020c5244();
extern int func_ov002_020d36d8(char* c, int a);
extern void _ZN6Player11ChangeStateERNS_5StateE(void* c, void* s);
extern int _ZN4cstd5atan2E5Fix12IiES1_(Fix12 a, int b);
extern int AngleDiff(int a, int b);
extern void _ZN6Player14St_OnWall_InitEv(char* c);
extern void _Z14ApproachLinearRsss(s16* v, s16 t, s16 s);
extern int func_ov002_020bf224(char* c, int a, int b);
extern void func_ov002_020eee3c(char* a, char* b);
extern void _ZN6Player7SetAnimEji5Fix12IiEj(void* c, u32 anim, int a, Fix12 b, u32 d);
extern int func_ov002_020d4d88(char* c, int a, int b);
extern void func_ov002_020bedd4(char* c);

extern u8 data_020a0e40;
extern s16 data_0209f4a0[];
extern int data_ov002_0211013c[];
}

extern "C" int _ZN6Player14St_OnWall_MainEv(char* c)
{
    u16 f = *(u16*)(c + 0x6ce);
    u16 b0 = f & 1;
    if (b0 != 0) {
        func_ov002_020c0364(c, 3);
        return 1;
    }
    u16 b1 = f & 4;
    if (b1 != 0) {
        func_ov002_020cabe0(c);
        return 1;
    }
    if (func_ov002_020c5244() != 0)
        return 1;
    if (func_ov002_020d36d8(c, 0) != 0) {
        *(s16*)(c + 0x94) = *(s16*)(c + 0x8e);
        return 1;
    }
    if ((*(u8*)(c + 0x6e9) & 2) == 0) {
        _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211013c);
        return 1;
    }
    if (*(u8*)(c + 0x6e3) == 2) {
        if (*(s16*)((char*)data_0209f4a0 + data_020a0e40 * 0x18) == 0) {
            _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211013c);
            return 1;
        }
        int a = _ZN4cstd5atan2E5Fix12IiES1_(*(int*)(c + 0x560), *(int*)(c + 0x568)) + 0x8000;
        int d = AngleDiff((s16)a, *(s16*)(c + 0x6d2));
        if (d >= 0x4000) {
            _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211013c);
            return 1;
        }
        if (d >= 0x1555) {
            *(u8*)(c + 0x6e3) = 0;
            if ((s16)a == (s16)(*(s16*)(c + 0x6d2) + d))
                *(u8*)(c + 0x6e3) = 1;
            _ZN6Player14St_OnWall_InitEv(c);
            return 1;
        }
        _Z14ApproachLinearRsss((s16*)(c + 0x8e), (s16)a, 0x800);
        *(s16*)(c + 0x94) = a;
        *(int*)(c + 0x98) = func_ov002_020bf224(c, 0xa000, 0x2000);
        func_ov002_020eee3c(c + 0x380, c);
    } else {
        if (*(s16*)((char*)data_0209f4a0 + data_020a0e40 * 0x18) != 0) {
            int ang = _ZN4cstd5atan2E5Fix12IiES1_(*(int*)(c + 0x560), *(int*)(c + 0x568));
            int d = AngleDiff((s16)(ang + 0x8000), *(s16*)(c + 0x6d2));
            if (d >= 0x4000) {
                _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211013c);
                return 1;
            }
            if (d < 0x1555) {
                *(u8*)(c + 0x6e3) = 2;
                _ZN6Player14St_OnWall_InitEv(c);
                return 1;
            }
            int a2 = ang + 0x8000;
            _Z14ApproachLinearRsss((s16*)(c + 0x8e), (s16)a2, 0x800);
            u32 anim;
            if ((s16)a2 == (s16)(*(s16*)(c + 0x6d2) + d)) {
                *(s16*)(c + 0x94) = ang + 0x4000;
                anim = 0x5d;
            } else {
                *(s16*)(c + 0x94) = ang - 0x4000;
                anim = 0x5c;
            }
            Fix12 spd = (Fix12)(((s64)*(int*)(c + 0x98) * 0x600 + 0x800) >> 12);
            if (spd < 0x400)
                spd = 0x400;
            _ZN6Player7SetAnimEji5Fix12IiEj(c, anim, 0, spd, 0);
            func_ov002_020d4d88(c, func_ov002_020bf224(c, 0x6000, 0x1000), 0x1000);
        } else {
            *(int*)(c + 0x98) = 0;
            _ZN6Player7SetAnimEji5Fix12IiEj(c, 0x5e, 0, 0x1000, 0);
        }
    }
    func_ov002_020bedd4(c);
    return 1;
}
