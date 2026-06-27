//cpp
struct Vector3 { int x, y, z; };

struct CommonModel {
    void Render(Vector3 const *);
};

extern "C" int func_ov036_0211169c(char *c) {
    ((CommonModel *)(c + 0xd4))->Render(0);
    return 1;
}
