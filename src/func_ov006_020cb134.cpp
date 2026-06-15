//cpp
extern "C" {
extern int data_ov006_02140548[];
int ApproachLinear(int *a, int b, int c);
void AddVec3(void *dst, void *a, void *b);
void func_ov006_020cb134(char *o) {
  ApproachLinear((int*)(o+0x38), data_ov006_02140548[0], *(int*)(o+0x40));
  AddVec3(o+0x1c, o+0x34, o+0x1c);
}
}
