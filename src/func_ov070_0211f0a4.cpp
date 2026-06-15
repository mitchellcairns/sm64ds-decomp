//cpp
extern "C" {
int _ZN5Actor13SmallPoofDustEv(void*);
int _ZN5Actor10SpawnCoinsERK7Vector3j5Fix12IiEs(void*, void*, unsigned, int, short);
int _ZN5Actor24KillAndTrackInDeathTableEv(void*);
int func_ov070_0211f0a4(void* c){
  int v[3];
  _ZN5Actor13SmallPoofDustEv(c);
  v[0]=*(int*)((char*)c+0x5c);
  v[1]=*(int*)((char*)c+0x60);
  v[2]=*(int*)((char*)c+0x64);
  _ZN5Actor10SpawnCoinsERK7Vector3j5Fix12IiEs(c, v, *(unsigned char*)((char*)c+0x10a)+1, 0xa000, 0);
  return _ZN5Actor24KillAndTrackInDeathTableEv(c);
}
}
