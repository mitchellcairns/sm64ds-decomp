extern int func_ov002_020bf30c(char* c, int a);
extern void _ZN6Player7SetAnimEji5Fix12IiEj(char* c, unsigned int anim, int a, int fix, unsigned int z);
extern void _ZN5Sound13PlayCharVoiceEjjRK7Vector3(unsigned int a, unsigned int b, void* v);
int _ZN6Player17St_HoldLight_InitEv(char* c){
  if(*(int*)(c+0x98) >= func_ov002_020bf30c(c, 0x1c000)){
    *(int*)(c+0x98) = func_ov002_020bf30c(c, 0x1c000);
  }
  if(*(unsigned char*)(c+0x6e3) == 0){
    char* o = *(char**)(c+0x358);
    unsigned int anim = 0x2f;
    if(o != 0){
      int b = (int)((*(int*)(o+0xb0) & 0x8000) != 0);
      if(b != 0){
        anim = 0x86;
        if(*(int*)(c+8) == 2){
          if((int)(*(unsigned short*)(o+0xc) == 0xce) != 0) anim = 0x2f;
        }
      }
    }
    _ZN6Player7SetAnimEji5Fix12IiEj(c, anim, 0x40000000, 0x1000, 0);
    _ZN5Sound13PlayCharVoiceEjjRK7Vector3(*(unsigned char*)(c+0x6d9), 0x12, c+0x74);
  }
  *(unsigned char*)(c+0x6e5) = 0;
  *(unsigned short*)(c+0x600+0x9c) = 0;
  *(unsigned char*)(c+0x70c) = 0;
  return 1;
}
