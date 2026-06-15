//cpp
extern "C" {
extern void* _ZN5Model8LoadFileER13SharedFilePtr(void*);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void*, void*, int, int);
extern void func_ov044_02111214(char*);
extern int data_ov015_02114960[];
int func_ov015_021112a0(char *c){
  void *f = _ZN5Model8LoadFileER13SharedFilePtr((void*)data_ov015_02114960);
  _ZN9ModelBase7SetFileEP8BMD_Fileii(c+0xd4, f, 1, -1);
  func_ov044_02111214(c);
  return 1;
}
}
