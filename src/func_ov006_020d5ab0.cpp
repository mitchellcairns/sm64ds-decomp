//cpp
extern "C" { void func_ov004_020afa20(void*, int, int, int, int); }
extern "C" void* data_ov006_02134f30;
extern "C" void func_ov006_020d5ab0(char* c){
  if(*(unsigned char*)(c+0x6000+0x2fa)==0) return;
  func_ov004_020afa20(data_ov006_02134f30, 0x80, 0xc0, -1, 1);
}
