struct Mtx { int w[12]; };
extern struct Mtx data_020a0e68;
extern void Matrix4x3_FromTranslation(struct Mtx* m, int x, int y, int z);
void func_ov006_020c2290(char* c) {
    Matrix4x3_FromTranslation(&data_020a0e68, *(int*)(c+0x180), *(int*)(c+0x184), *(int*)(c+0x188));
    *(struct Mtx*)(c+0x24) = data_020a0e68;
}
