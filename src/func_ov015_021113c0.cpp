//cpp
struct Player {
    void IncMegaKillCount();
};

extern "C" void func_ov015_021113c0(char *c, void *arg) {
    unsigned char v = *(unsigned char *)(c + 0x397);
    if (v >= 2) return;
    ((Player *)arg)->IncMegaKillCount();
    *(unsigned char *)(c + 0x397) = 2;
    *(short *)(c + 0x300 + 0x94) = 0x640;
}
