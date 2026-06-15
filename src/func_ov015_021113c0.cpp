//cpp
extern "C" {
void _ZN6Player16IncMegaKillCountEv(void*);
void func_ov015_021113c0(char* c, void* arg){
  if(*(unsigned char*)(c+0x397) >= 2) return;
  _ZN6Player16IncMegaKillCountEv(arg);
  *(unsigned char*)(c+0x397)=2;
  *(short*)(c+0x300+0x94)=0x640;
}
}
