//cpp
struct Vec3 { int x,y,z; };
extern "C" void Vec3_Sub(struct Vec3* out, struct Vec3* a, struct Vec3* b);
extern "C" int DotVec3(struct Vec3* a, struct Vec3* b);

struct Obj {
  virtual struct Vec3* GetA();
  virtual struct Vec3* GetB();
};

extern "C" void func_ov006_020ce8a0(char* self, struct Obj* o, int* outR5, int* outR4){
  struct Vec3 a, b, sa, sb;
  struct Vec3* p;
  int t;
  p=o->GetA();
  a.x=p->x; a.y=p->y; a.z=p->z;
  p=o->GetB();
  b.x=p->x; b.y=p->y; b.z=p->z;
  Vec3_Sub(&sa,&a,(struct Vec3*)(self+8));
  Vec3_Sub(&sb,&b,(struct Vec3*)(self+0x14));
  sa.y += 0xc000;
  t=DotVec3((struct Vec3*)(self+0x38),&sa);
  outR5[0]=DotVec3((struct Vec3*)(self+0x44),&sa);
  outR5[1]=t;
  t=DotVec3((struct Vec3*)(self+0x50),&sb);
  outR4[0]=DotVec3((struct Vec3*)(self+0x5c),&sb);
  outR4[1]=t;
}
