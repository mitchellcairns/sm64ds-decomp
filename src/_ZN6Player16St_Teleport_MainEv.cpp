//cpp
typedef int s32;
typedef short s16;
typedef unsigned int u32;
typedef unsigned short u16;
typedef unsigned char u8;

typedef struct Obj { s16 x, y, z; u16 param; } Obj;
typedef struct Vector3 { int x, y, z; } Vector3;

extern "C" {
extern Obj* GetTeleportDestObj(int i);
extern void func_02035860(char* o, void* src);
extern void func_0200d1e4(char* self);
extern void _ZN5Sound13PlayCharVoiceEjjRK7Vector3(u32 a, u32 b, char* v);
extern void _ZN5Sound9PlayBank0EjRK7Vector3(u32 a, char* v);
extern void func_02020388(int handle);
extern void _ZN13RaycastGroundC1Ev(char* rc);
extern void _ZN13RaycastGround12SetObjAndPosERK7Vector3P5Actor(char* rc, Vector3* v, char* actor);
extern int _ZN13RaycastGround10DetectClsnEv(char* rc);
extern void _ZN13RaycastGroundD1Ev(char* rc);
extern void _ZN6Player11ChangeStateERNS_5StateE(char* c, void* s);
extern u32 func_02012790(u32 a);
extern void _ZN3G2x18SetBlendBrightnessEPVtts(volatile u16* p, u16 a, s16 b);
extern void func_ov002_020bedd4(char* c);

extern char* data_0209f318;
extern int data_0209f32c;
extern u8 data_0209f284;
extern int data_ov002_0211067c[];
extern int data_ov002_0211013c[];
}

extern "C" int _ZN6Player16St_Teleport_MainEv(char* c)
{
    switch (*(u8*)(c + 0x6e3)) {
    case 0:
        if (*(u8*)(c + 0x6f5) > 1) {
            (*(u8*)(((int)c + 0x6f5) & 0xFFFFFFFFFFFFFFFF))--;
            break;
        }
        (*(u8*)(((int)c + 0x6e5) & 0xFFFFFFFFFFFFFFFF))++;
        if (*(u8*)(c + 0x6e5) >= 0x10) {
            Obj* obj = GetTeleportDestObj((u8)(*(u8*)(c + 0x6e8) - 1));
            int tx = obj->x << 12;
            int tz = obj->z << 12;
            int ty = obj->y << 12;
            *(int*)(c + 0x5c) = tx;
            *(int*)(c + 0x60) = ty;
            *(int*)(c + 0x64) = tz;
            *(u8*)(c + 0xcc) = obj->param & 0xf;
            *(s16*)(c + 0x8e) = ((obj->param >> 4) & 0xf) << 12;
            *(s16*)(c + 0x94) = *(s16*)(c + 0x8e);
            *(int*)(c + 0x644) = 0x80000000;
            *(int*)(c + 0x64c) = 0x80000000;
            func_02035860(c + 0x380, c + 0x5c);
            *(u8*)(c + 0x6f5) = 0;
            func_0200d1e4(data_0209f318);
            _ZN5Sound13PlayCharVoiceEjjRK7Vector3(*(u8*)(c + 0x6d9), 0x19, c + 0x74);
            _ZN5Sound9PlayBank0EjRK7Vector3(0x19, c + 0x74);
            *(u8*)(c + 0x6e3) = 1;
        }
        break;
    case 1:
        if (*(u8*)(c + 0x6e5) != 0) {
            if (*(u8*)(c + 0x6e5) >= 0x10) {
                if (data_0209f32c > *(int*)(c + 0x60) + 0x64000)
                    *(u8*)(c + 0x706) = 1;
            }
            (*(u8*)(((int)c + 0x6e5) & 0xFFFFFFFFFFFFFFFF))--;
            break;
        }
        (*(u8*)(((int)c + 0x6f5) & 0xFFFFFFFFFFFFFFFF))++;
        func_02020388(*(u8*)(c + 0x6d8));
        if (*(u8*)(c + 0x6f5) >= 0x1f) {
            int hit = 0;
            *(u8*)(c + 0x6f5) = 0x1f;
            if (data_0209f32c >= *(int*)(c + 0x60) + 0x64000) {
                Vector3 v;
                char rc[0x50];
                _ZN13RaycastGroundC1Ev(rc);
                {
                    int vz = *(int*)(c + 0x64);
                    int vy = data_0209f32c + 0x64000;
                    int vx = *(int*)(c + 0x5c);
                    v.x = vx;
                    v.y = vy;
                    v.z = vz;
                }
                _ZN13RaycastGround12SetObjAndPosERK7Vector3P5Actor(rc, &v, c);
                if (_ZN13RaycastGround10DetectClsnEv(rc))
                    hit = 1;
                _ZN13RaycastGroundD1Ev(rc);
            }
            if (hit)
                _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211067c);
            else
                _ZN6Player11ChangeStateERNS_5StateE(c, data_ov002_0211013c);
            data_0209f284 = 1;
            *(u16*)(c + 0x6c8) = 0x3c;
            func_02012790(0x24);
        }
        break;
    }
    _ZN3G2x18SetBlendBrightnessEPVtts((volatile u16*)0x4000050, 0x3f, *(u8*)(c + 0x6e5));
    func_ov002_020bedd4(c);
    return 1;
}
