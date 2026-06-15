//cpp
extern "C" {
extern void _ZN6Player16IncMegaKillCountEv(void*);
extern void _ZN8Platform14KillByMegaCharER6Player(void*, void*);
void func_ov018_0211123c(char *c, void *p){
  _ZN6Player16IncMegaKillCountEv(p);
  _ZN8Platform14KillByMegaCharER6Player(c, p);
  *(short*)(c+0x8e) = *(short*)(c+0x94) + 0x4000;
}
}
