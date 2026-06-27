//cpp
struct BMD_File;
struct SharedFilePtr;

struct Model {
    static BMD_File *LoadFile(SharedFilePtr &);
};

struct ModelBase {
    void SetFile(BMD_File *, int, int);
};

extern int data_ov015_02114960;
extern "C" void func_ov015_02111214(char *t);

extern "C" int func_ov015_021112a0(char *c) {
    BMD_File *file = Model::LoadFile(*(SharedFilePtr *)&data_ov015_02114960);
    ((ModelBase *)(c + 0xd4))->SetFile(file, 1, -1);
    func_ov015_02111214(c);
    return 1;
}
