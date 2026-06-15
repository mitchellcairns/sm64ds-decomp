extern short Vec3_HorzAngle(const void* a, const void* b);
extern int func_ov002_020ae968(void*, void*);
int func_ov002_020ae844(void* c, void* a){
  *(short*)((char*)c+0x94)=Vec3_HorzAngle((char*)a+0x5c,(char*)c+0x5c);
  return func_ov002_020ae968(c,a);
}
