extern int SetAnim(char* anim, void* file, int a, int b, unsigned int u);
struct S { int w[2]; };
extern struct S data_ov006_0213aec0;
void func_ov006_020c3adc(char *p) {
    SetAnim(p+0xd18, *(void**)(p+0xd90), 0, 0x800, 0);
    *(struct S *)(p + 0x0) = data_ov006_0213aec0;
}
