//cpp
struct Vector3 { int x, y, z; };

struct Model {
    void Render(Vector3 const *);
};

extern "C" int func_ov085_02129854(char *c) {
    ((Model *)(c + 0x108))->Render(0);
    return 1;
}
