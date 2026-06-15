//cpp
extern "C" {
extern int func_0207328c(void*, int, int, void*);
extern int _ZN11ShadowModelD1Ev(void*);
extern int _ZN5ModelD1Ev(void*);
extern int _ZN9ModelAnimD1Ev(void*);
extern int _ZN5ActorD1Ev(void*);
extern void *data_ov055_02111ae0;
extern int _ZN15TextureSequenceD1Ev();
int func_ov055_021111a0(char *c){
  *(void**)c = (void*)&data_ov055_02111ae0;
  func_0207328c((char*)c+0x1b0, 2, 0x14, (void*)&_ZN15TextureSequenceD1Ev);
  _ZN11ShadowModelD1Ev((char*)c+0x188);
  _ZN5ModelD1Ev((char*)c+0x138);
  _ZN9ModelAnimD1Ev((char*)c+0xd4);
  _ZN5ActorD1Ev(c);
  return (int)c;
}
}
