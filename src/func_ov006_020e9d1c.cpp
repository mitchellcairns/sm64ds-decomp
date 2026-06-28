//cpp
extern "C" void func_ov006_020e81a4(char *c);
extern "C" void func_ov006_020e8e10(char *c);
extern "C" void func_ov006_020e8b18(char *c);
extern "C" void func_ov006_020e8354(char *c);
extern "C" void func_ov006_020c0134(char *c);
extern "C" void func_ov006_020e7b44(char *c);

struct ModelComponents;
struct TextureTransformer { void Update(ModelComponents &m); };

struct Obj { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void vcall(int); };

extern "C" int func_ov006_020e9d1c(char *c)
{
    func_ov006_020e81a4(c);
    func_ov006_020e8e10(c);
    func_ov006_020e8b18(c);
    func_ov006_020e8354(c);
    *(int *)(c + 0x4700) = 0;
    *(int *)(c + 0x4704) = 0xd0000;
    *(int *)(c + 0x4708) = 0x40000;
    *(int *)(c + 0x470c) = 0xffed3000;
    *(int *)(c + 0x4710) = 0xe0000;
    *(int *)(c + 0x4714) = 0x40000;
    *(short *)(c + 0x4718) = 0xc00;
    func_ov006_020c0134(c + 0x4660);
    ((TextureTransformer *)(c + 0x51f4))->Update(*(ModelComponents *)(c + 0x4f40));
    ((Obj *)(c + 0x4f38))->vcall(0);
    func_ov006_020e7b44(c + 0x4fd8);
    ((Obj *)(c + 0x4f88))->vcall(0);
    return 1;
}
