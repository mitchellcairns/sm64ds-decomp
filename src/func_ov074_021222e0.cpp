//cpp
struct Vec3 { int x, y, z; };
struct M48 { int w[12]; };
extern "C" {
extern void Vec3_Asr(Vec3* d, Vec3* s, int sh);
extern void Matrix4x3_FromTranslation(void* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToTranslation(void* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationZXYExt(void* m, int x, int y, int z);
extern void _ZN15MaterialChanger6UpdateER15ModelComponents(void*, void*);
extern M48 data_020a0e68;
}

struct Obj210 {
    virtual void v0();
    virtual void v1();
    virtual void v2();
    virtual void v3();
    virtual void v4();
    virtual void v5(int a);
};

extern "C" int func_ov074_021222e0(char* c)
{
    Vec3 v;
    Vec3_Asr(&v, (Vec3*)(c + 0x5c), 3);
    Matrix4x3_FromTranslation(&data_020a0e68, v.x, v.y, v.z);
    Matrix4x3_ApplyInPlaceToTranslation(&data_020a0e68, 0, 0x6400, 0);
    Matrix4x3_ApplyInPlaceToRotationZXYExt(&data_020a0e68, *(short*)(c + 0x8c), *(short*)(c + 0x8e), *(short*)(c + 0x90));
    Matrix4x3_ApplyInPlaceToTranslation(&data_020a0e68, 0, -0x6400, 0);
    *(M48*)(c + 0x22c) = data_020a0e68;

    if (*(unsigned char*)(c + 0x60a) == 0) return 1;

    ((Obj210*)(c + 0x210))->v5(0);
    _ZN15MaterialChanger6UpdateER15ModelComponents(c + 0x3d0, c + 0x218);
    return 1;
}
