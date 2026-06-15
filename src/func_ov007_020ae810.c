void func_ov007_020ae810(char* c){
  *(int*)(c+8) = *(short*)(*(int*)(c+0x24)+2) << 0xc;
  *(int*)(c+0xc) = *(short*)(*(int*)(c+0x24)+4) << 0xc;
}
