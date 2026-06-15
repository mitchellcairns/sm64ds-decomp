//cpp
typedef int Fix12i;
typedef struct { Fix12i z,y,x; } Vector3;
extern "C" {
void _ZNK7PathPtr7GetNodeER7Vector3j(void*, Vector3&, unsigned int);
Fix12i Vec3_HorzDist(const Vector3* a, const Vector3* b);
int func_ov019_0211127c(char* c, Vector3* arg, unsigned int j){
  Vector3 v;
  _ZNK7PathPtr7GetNodeER7Vector3j(c+0x364, v, j);
  return Vec3_HorzDist(&v, arg) <= 0x320000;
}
}
