//cpp
extern "C" {
int data_ov004_020bad10(void*, void*);
void _ZN16MeshColliderBase6EnableEP5Actor(void*, void*);
extern int data_ov014_021145c4[];
int func_ov014_02111294(char* c){
  int r = data_ov004_020bad10(c, (void*)data_ov014_021145c4);
  _ZN16MeshColliderBase6EnableEP5Actor(c+0x124, c);
  return r;
}
}
