extern void func_ov001_020ab110();
void func_ov002_020b8394(char* c){
  if(*(unsigned char*)(c+0x400)==0xff) return;
  func_ov001_020ab110(c+0x3d0);
}
