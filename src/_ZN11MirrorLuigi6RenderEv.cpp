//cpp
struct Mtx { int m[12]; };
struct Sub {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void m5(int);
};

extern "C" {

extern int data_ov055_02111b6c;
extern int data_ov055_02111b64;
extern unsigned char data_0209f250;
extern char* data_0209f394[];
extern char data_020a0e68;

char* func_ov002_020e496c(char* c);
void func_0203c178(void* m, int a, int b, int c);
void MulMat3x3Mat3x3(void* d, void* a, void* b);
void _ZN5Model6RenderEPK7Vector3(void* m, void* v);
void _ZN15TextureSequence6UpdateER15ModelComponents(void* ts, void* mc);

}

extern "C" int _ZN11MirrorLuigi6RenderEv(char* self)
{
    char* player;
    char* r8res;
    char* comp;
    char* q;
    char* p_f0;
    unsigned int i;
    Mtx* dst;
    Mtx* src;

    if (data_ov055_02111b6c == 0) return 1;

    player = data_0209f394[data_0209f250];
    r8res = func_ov002_020e496c(player);

    q = (char*)(int)(((long long)(int)(self + 0xdc)) & 0xFFFFFFFFFFFFFFFFLL);
    comp = *(char**)q;
    dst = *(Mtx**)(q + 0xc);
    src = *(Mtx**)(r8res + 0x14);
    for (i = 0; i < *(unsigned int*)(comp + 4); i++) {
        *(Mtx*)(int)(((long long)(int)dst) & 0xFFFFFFFFFFFFFFFFLL) = *src;
        src++;
        dst++;
    }

    p_f0 = self + 0xf0;
    *(Mtx*)p_f0 = *(Mtx*)(r8res + 0x1c);
    *(int*)(p_f0 + 0x24) = -*(int*)(p_f0 + 0x24);
    func_0203c178(&data_020a0e68, -0x1000, 0x1000, 0x1000);
    MulMat3x3Mat3x3(p_f0, &data_020a0e68, p_f0);
    *(Mtx*)(self + 0x154) = *(Mtx*)p_f0;

    if (data_ov055_02111b64 & 0x20000) return 1;

    _ZN5Model6RenderEPK7Vector3((void*)(self + 0xd4), 0);
    *(Mtx*)(*(char**)(self + 0x14c)) = *(Mtx*)(*(char**)(self + 0xe8) + 0x2d0);
    _ZN15TextureSequence6UpdateER15ModelComponents((void*)(self + 0x1b0), (void*)(self + 0xdc));
    *(int*)(self + 0x1b8) = (int)(*(unsigned char*)(player + 0x6fb)) << 12;
    _ZN15TextureSequence6UpdateER15ModelComponents((void*)(self + 0x1c4), (void*)(self + 0x140));
    *(int*)(self + 0x1cc) = (int)(*(unsigned char*)(player + 0x6fb)) << 12;
    ((Sub*)(self + 0x138))->m5(0);
    return 1;
}
