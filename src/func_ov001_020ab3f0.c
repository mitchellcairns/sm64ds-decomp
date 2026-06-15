void func_ov001_020ab3f0(void* c){
  if(*(unsigned char*)((char*)c+0x10)) *(unsigned char*)((char*)c+0x10)=0;
  else *(unsigned char*)((char*)c+0x10)=1;
  *(unsigned char*)((char*)c+0x11)=0;
  *(int*)((char*)c+0xc)=*(int*)((char*)c+0x18);
}
