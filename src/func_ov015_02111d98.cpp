//cpp
extern "C" {
void _ZN5Actor22UpdatePosWithOnlySpeedEP12CylinderClsn(void*,void*);
void func_ov015_02111fb8(void*,int);
void func_ov015_02111d98(char *c){
  _ZN5Actor22UpdatePosWithOnlySpeedEP12CylinderClsn(c, 0);
  int v = *(int*)(c+0x320);
  if(*(int*)(c+0x5c) >= v){
    *(int*)(c+0x5c) = v;
    func_ov015_02111fb8(c, 5);
  }
}
}
