//cpp
struct ShadowModel { ~ShadowModel(); };
struct Model { ~Model(); };
struct ModelAnim { ~ModelAnim(); };
struct Actor { ~Actor(); };

extern int data_ov055_02111ae0;
extern int _ZN15TextureSequenceD1Ev;
extern "C" int func_0207328c(char *, int, int, int);

extern "C" int func_ov055_021111a0(char *c) {
    *(int *)c = (int)&data_ov055_02111ae0;
    func_0207328c(c + 0x1b0, 2, 0x14, (int)&_ZN15TextureSequenceD1Ev);
    ((ShadowModel *)(c + 0x188))->~ShadowModel();
    ((Model *)(c + 0x138))->~Model();
    ((ModelAnim *)(c + 0xd4))->~ModelAnim();
    ((Actor *)c)->~Actor();
    return (int)c;
}
