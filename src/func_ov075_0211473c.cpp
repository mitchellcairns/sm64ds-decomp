//cpp
typedef short s16;
struct Vector3 { int x,y,z; };
extern "C" s16 Vec3_HorzAngle(const Vector3* a, const Vector3* b);
int ApproachLinear(short&,short,short);
extern short data_ov075_0211b52c[];
extern "C" void func_ov075_0211473c(char* c){
  s16 a=Vec3_HorzAngle((Vector3*)(c+0x118),(Vector3*)(c+0x130));
  unsigned char idx=*(unsigned char*)(c+0x152);
  short lim=data_ov075_0211b52c[idx];
  if(ApproachLinear(*(short*)(c+0x150), a, lim)){
    *(int*)(c+0x110)=4;
    *(int*)(c+0x114)=0;
  }
}
