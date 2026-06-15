//cpp
extern "C" {
extern int func_0207328c(void*, int, int, void*);
extern int _ZN5ActorD1Ev(void*);
extern void *data_ov058_02111a70;
extern int _ZN25MovingCylinderClsnWithPosD1Ev();
int func_ov058_021111a0(char *c){
  *(void**)c = (void*)&data_ov058_02111a70;
  func_0207328c((char*)c+0xd4, 5, 0x40, (void*)&_ZN25MovingCylinderClsnWithPosD1Ev);
  _ZN5ActorD1Ev(c);
  return (int)c;
}
}
