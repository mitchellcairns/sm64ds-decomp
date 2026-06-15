//cpp
extern "C" {
int _ZN5Actor13DistToCPlayerEv(void*);
int func_ov071_021202ec(void*, int);
int func_ov071_021201b4(void* c){
  if(*(unsigned short*)((char*)c+0x3a8)) return 1;
  if(_ZN5Actor13DistToCPlayerEv(c) < 0x5dc000) func_ov071_021202ec(c,1);
  return 1;
}
}
