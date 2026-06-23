typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef unsigned int u32;

struct State;
extern int _ZN6Player7IsStateERNS_5StateE(void* thiz, struct State* s);
extern void _ZN6Player11ChangeStateERNS_5StateE(void* thiz, struct State* s);

extern struct State data_ov002_0211010c;
extern struct State data_ov002_02110124;
extern struct State data_ov002_0211022c;

int _ZN6Player17SetNoControlStateEhih(char* thiz, int a, int b, u8 c)
{
    u8 flag;

    if (_ZN6Player7IsStateERNS_5StateE(thiz, &data_ov002_0211010c) ||
        _ZN6Player7IsStateERNS_5StateE(thiz, &data_ov002_02110124)) return 0;

    flag = 0;
    if (a <= 3) {
        if (*(u8*)(thiz + 0x709) != 0) return 0;
        flag = c;
    } else {
        if (*(u8*)(thiz + 0x709) != 0) {
            if (c == 0) return 0;
        }
    }

    *(u8*)(thiz + 0x70a) = a;
    *(int*)(thiz + 0x688) = b;
    _ZN6Player11ChangeStateERNS_5StateE(thiz, &data_ov002_0211022c);
    *(u8*)(thiz + 0x6e6) = flag;
    return 1;
}
