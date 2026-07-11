//cpp
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;

extern "C" {
extern int _ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(u32 vol, int t);
extern int func_ov002_020c47f4(char* c);
extern int _ZN6Player6IsAnimEj(void* c, u32 a);
extern void func_0201fc88(s16 a);
extern void func_0201f32c(s16 a);
extern void func_0200d3f8(void* cam, u8 playerID, void* ptr);
extern void func_0200d7a4(void* cam, u8 playerID);
extern int func_ov100_02144fcc(void);
extern int _Z15ApproachLinear2Rsss(s16* v, s16 target, s16 step);
extern void func_0200d81c(void* cam, u8 playerID);
extern void _ZN6Player11ChangeStateERNS_5StateE(void* c, void* s);
extern void func_ov002_020bedd4(char* c);

extern int data_0209b454;
extern char* data_0209f318;
extern u8 data_0209d660;
extern int data_ov002_0211022c[];
extern int data_ov002_02110514[];
extern int data_ov002_0211013c[];
}

extern "C" int _ZN6Player12St_Talk_MainEv(char* self)
{
    if (*(u8*)(self + 0x722) != 0) {
        if (_ZN5Sound17ChangeMusicVolumeEj5Fix12IiE(0x7f, 0x7222) != 0)
            *(u8*)(self + 0x722) = 0;
    }

    if (*(u8*)(self + 0x70a) == 0) {
        char* p = *(char**)(self + 0x368);
        if (p != 0)
            *(u32*)(((int)p + 0xb0) & 0xFFFFFFFFFFFFFFFF) |= 0x800000;
        *(u32*)(((int)self + 0xb0) & 0xFFFFFFFFFFFFFFFF) |= 0x800000;
        data_0209b454 |= 0x800000;
        *(u8*)(self + 0x70a) = 1;
    }

    switch (*(u8*)(self + 0x6e3)) {
    case 0:
        if (*(u8*)(self + 0x6e5) != 0)
            func_ov002_020c47f4(self);
        break;
    case 1:
        if (!_ZN6Player6IsAnimEj(self, 0x64)) {
            if (!func_ov002_020c47f4(self))
                break;
        }
        *(u8*)(self + 0x6e3) = 2;
        if (*(u8*)(self + 0x6e5) == 0)
            func_0201fc88(*(int*)(self + 0x688));
        else
            func_0201f32c(*(int*)(self + 0x688));
        {
            char* cam = data_0209f318;
            switch ((*(u8*)(self + 0x70c) >> 2) & 3) {
            case 0:
                func_0200d3f8(cam, *(u8*)(self + 0x6d8), self + 0x744);
                break;
            case 1:
                func_0200d7a4(cam, *(u8*)(self + 0x6d8));
                break;
            }
        }
        break;
    case 2:
        if (data_0209d660 != 0)
            break;
        switch (*(u8*)(self + 0x70c) & 3) {
        case 0:
            *(u8*)(self + 0x6e3) = 4;
            break;
        case 1:
            *(u8*)(self + 0x6e3) = 3;
            break;
        case 2:
            *(u8*)(self + 0x6e3) = 8;
            break;
        }
        break;
    case 8:
        if (func_ov100_02144fcc() != 0)
            *(u8*)(self + 0x6e3) = 4;
        break;
    case 4:
    case 5:
        if (_Z15ApproachLinear2Rsss((s16*)(self + 0x762), 0, 0x200) != 0) {
            if (*(u8*)(self + 0x6e3) != 5)
                *(u8*)(self + 0x6e3) = 6;
            else
                *(u8*)(self + 0x6e3) = 7;
            *(u8*)(self + 0x6e5) = 0;
            *(s16*)(self + 0x94) = *(s16*)(self + 0x8e);
            char* cam = data_0209f318;
            func_0200d81c(cam, *(u8*)(self + 0x6d8));
            *(u32*)(((int)cam + 0x154) & 0xFFFFFFFFFFFFFFFF) &= ~8;
            *(u8*)(self + 0x742) = 4;
        }
        break;
    case 7:
        if (*(u16*)(self + 0x6a6) != 0)
            break;
    case 6:
        if ((*(u32*)(data_0209f318 + 0x154) & 0x8000) != 0)
            break;
        if (*(u8*)(self + 0x70b) != 0) {
            *(u8*)(self + 0x70a) = 0x13;
            _ZN6Player11ChangeStateERNS_5StateE(self, data_ov002_0211022c);
            *(u8*)(self + 0x6e3) = 0x13;
        } else if (_ZN6Player6IsAnimEj(self, 0x64)) {
            _ZN6Player11ChangeStateERNS_5StateE(self, data_ov002_02110514);
        } else {
            _ZN6Player11ChangeStateERNS_5StateE(self, data_ov002_0211013c);
        }
        break;
    }

    func_ov002_020bedd4(self);
    return 1;
}
