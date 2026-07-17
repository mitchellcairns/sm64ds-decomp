typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;

void func_ov063_02118914(char* c)
{
    int z = 0;
    int scale;

    *(u8*)(c + 0x5cc) = 7;
    *(u8*)(c + 0x5c8) = z;
    *(u8*)(c + 0x5c9) = *(u8*)(c + 0x5c8);
    *(int*)(c + 0x584) = 0x1000;
    *(u8*)(c + 0x5ca) = 3;

    scale = *(int*)(c + 0x584);
    *(int*)(c + 0x80) = scale;
    *(int*)(c + 0x84) = scale;
    *(int*)(c + 0x88) = scale;

    *(int*)(c + 0x188) = *(int*)(c + 0x590) * *(int*)(c + 0x584);
    *(int*)(c + 0x18c) = *(int*)(c + 0x594) * *(int*)(c + 0x584);

    *(u16*)(((int)c + 0x5d4) & 0xFFFFFFFFFFFFFFFFLL) |= 8;
    *(int*)(((int)c + 0x19c) & 0xFFFFFFFFFFFFFFFFLL) |= 1;
    *(u16*)(((int)c + 0x5d4) & 0xFFFFFFFFFFFFFFFFLL) |= 0x100;
    *(int*)(c + 0x5c) = -*(int*)(c + 0x51c);
    *(s16*)(((int)c + 0x8e) & 0xFFFFFFFFFFFFFFFFLL) += 0x8000;
    *(s16*)(((int)c + 0x94) & 0xFFFFFFFFFFFFFFFFLL) += 0x8000;
    *(u8*)(c + 0x5ce) = z;
    *(int*)(((int)c + 0xb0) & 0xFFFFFFFFFFFFFFFFLL) &= ~2;
}
