//cpp
extern "C" {
int _ZN6Player6IsAnimEj(void*, unsigned int);
int _ZN6Player17LostGrabbedObjectEv(void* c){
  return _ZN6Player6IsAnimEj(c, 0x18) || _ZN6Player6IsAnimEj(c, 0x8b);
}
}
