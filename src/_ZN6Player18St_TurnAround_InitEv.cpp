//cpp
extern "C" {
extern int _ZN6Player7SetAnimEji5Fix12IiEj(void*,unsigned int,int,int,unsigned int);
int _ZN6Player18St_TurnAround_InitEv(char* c){
  _ZN6Player7SetAnimEji5Fix12IiEj(c,0x46,0x40000000,0x1000,0);
  *(char*)(c+0x6e3)=0;
  return 1;
}
}
