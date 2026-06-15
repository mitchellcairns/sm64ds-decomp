//cpp
extern "C" {
int _ZN13SharedFilePtr7ReleaseEv(void*);
extern int data_ov051_021116b0[];
int func_ov013_02111478(char* c){
  unsigned char i=*(unsigned char*)(c+0x124);
  _ZN13SharedFilePtr7ReleaseEv((void*)data_ov051_021116b0[i]);
  return 1;
}
}
