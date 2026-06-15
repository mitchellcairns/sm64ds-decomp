//cpp
extern "C" void _ZN13SharedFilePtr7ReleaseEv(void*);
extern void* data_ov031_02111424[];
extern "C" int func_ov031_02111254(char *c){
  _ZN13SharedFilePtr7ReleaseEv(data_ov031_02111424[*(unsigned char*)(c+0x124)]);
  return 1;
}
