//cpp
extern "C" {
extern int _ZN9Animation7AdvanceEv(void*);
int func_ov009_02111c4c(char* c){
  *(int*)(c+0x32c)=0x1000;
  _ZN9Animation7AdvanceEv(c+0x320);
  return 1;
}
}
