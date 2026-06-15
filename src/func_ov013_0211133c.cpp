//cpp
extern "C" {
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void*);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void*, void*, int, int);
extern void data_ov054_02111238(void*);
extern int __sinit_ov045_02112280[];
int func_ov013_0211133c(char *c){
  void *f = _ZN5Model8LoadFileER13SharedFilePtr((void*)__sinit_ov045_02112280);
  _ZN9ModelBase7SetFileEP8BMD_Fileii(c+0xd4, f, 1, -1);
  data_ov054_02111238(c);
  *(short*)(c+0x124)=0x100;
  return 1;
}
}
