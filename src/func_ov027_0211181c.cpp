//cpp
extern "C" {
extern int func_ov064_02116ec0(void*);
extern int _ZN5Actor9TrackStarEjj(void*, unsigned int, unsigned int);
extern int data_ov027_021138f4[];
int func_ov027_0211181c(char* c){
  *(int*)(c+0x330) = (int)data_ov027_021138f4;
  int r = func_ov064_02116ec0(c);
  *(unsigned char*)(c+0x3fa) = *(int*)(c+8) & 0xf;
  *(unsigned char*)(c+0x3fb) = _ZN5Actor9TrackStarEjj(c, *(unsigned char*)(c+0x3fa), 2);
  return r;
}
}
