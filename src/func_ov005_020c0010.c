extern char data_ov005_020c24dc[];
int func_ov005_020c0010(int a, int i){
  unsigned int* p=(unsigned int*)(data_ov005_020c24dc + i*0x34);
  return (*p >> 8) & 0xff;
}
