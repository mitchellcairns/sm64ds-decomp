//cpp
extern "C" {
int _ZN6Player6IsAnimEj(void*, unsigned int);
int _ZN6Player14IsFrontSlidingEv(void* c){
  return _ZN6Player6IsAnimEj(c, 0x43) || _ZN6Player6IsAnimEj(c, 0x40);
}
}
