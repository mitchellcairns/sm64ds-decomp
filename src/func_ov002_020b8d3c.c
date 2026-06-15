void func_ov002_020b8d3c(char* r0, char* r1){
  if(r1==0) return;
  *(short*)(r0+0x94)=*(short*)(r1+0x8e);
  if(*(int*)(r1+8)==2) *(int*)(r0+0x98)=0x8000;
  else *(int*)(r0+0x98)=0x4000;
}
