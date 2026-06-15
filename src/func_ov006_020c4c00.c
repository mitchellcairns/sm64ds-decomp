struct Mtx { int w[12]; };
extern struct Mtx data_020a0e68;
extern void Matrix4x3_FromTranslation(struct Mtx* m, int x, int y, int z);
extern void Matrix4x3_ApplyInPlaceToRotationY(struct Mtx* m, short angY);
void func_ov006_020c4c00(char* c) {
    Matrix4x3_FromTranslation(&data_020a0e68, *(int*)(c+0x9c), *(int*)(c+0xa0), *(int*)(c+0xa4));
    Matrix4x3_ApplyInPlaceToRotationY(&data_020a0e68, *(short*)(c+0xe6));
    *(struct Mtx*)(c+0x54) = data_020a0e68;
}
