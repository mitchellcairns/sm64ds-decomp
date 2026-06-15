extern int func_ov004_020afdd0(int a,int b,int c,int d,int e);
extern int data_ov006_0213c2e4[];
void _ZN6Player16St_WallJump_InitEv(char*c){
  if(*(unsigned char*)(c+0x4ee5)==0) return;
  int x=*(int*)(c+0x4eb0);
  int y=*(int*)(c+0x4eb4);
  func_ov004_020afdd0((int)data_ov006_0213c2e4,(x>>12)-0x20,(y>>12)-8,-1,0);
}
