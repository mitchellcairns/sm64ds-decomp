struct S{char pad[0x24]; int v;};
int func_ov064_02115f84(void* c){
  struct S* p=*(struct S**)((char*)c+0x330);
  int r=0x14000;
  if(p) r=p->v;
  return r;
}
