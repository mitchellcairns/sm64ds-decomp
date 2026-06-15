//cpp
extern "C" {
extern int _ZN6Player7IsStateERNS_5StateE(void* c, void* st);
extern int data_ov002_02110094[];
int _ZN6Player12GetHurtStateEv(char* c){
  if(_ZN6Player7IsStateERNS_5StateE(c, data_ov002_02110094))
    return *(unsigned char*)(c+0x6e3) & 7;
  return -1;
}
}
