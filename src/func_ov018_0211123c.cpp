//cpp
struct Player {
    void IncMegaKillCount();
};

struct Platform {
    void KillByMegaChar(Player &);
};

extern "C" void func_ov018_0211123c(char *c, void *p) {
    ((Player *)p)->IncMegaKillCount();
    ((Platform *)c)->KillByMegaChar(*(Player *)p);
    short val = *(short *)(c + 0x94);
    *(short *)(c + 0x8e) = val + 0x4000;
}
