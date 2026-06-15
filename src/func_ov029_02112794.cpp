//cpp
struct Sub { virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4(); virtual void v5(int); };
extern "C" {
int func_ov029_02112794(char *c){
  if (*(unsigned char*)(c+0x3a3) != 0) {
    Sub *s = (Sub*)(c+0x320);
    s->v5(0);
  }
  return 1;
}
}
