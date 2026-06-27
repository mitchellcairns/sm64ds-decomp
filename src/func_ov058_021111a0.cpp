//cpp
struct Actor {
    ~Actor();
};

extern int data_ov058_02111a70;
extern int _ZN25MovingCylinderClsnWithPosD1Ev;
extern "C" int func_0207328c(char *, int, int, int);

extern "C" int func_ov058_021111a0(char *c) {
    *(int *)c = (int)&data_ov058_02111a70;
    func_0207328c(c + 0xd4, 5, 0x40, (int)&_ZN25MovingCylinderClsnWithPosD1Ev);
    ((Actor *)c)->~Actor();
    return (int)c;
}
