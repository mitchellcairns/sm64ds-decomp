//cpp
extern "C" {
extern int data_ov058_02111a70[];
extern int data_020a0eac[];
extern int _ZN25MovingCylinderClsnWithPosD1Ev[];
void func_0207328c(void*, int, int, void*);
void _ZN5ActorD1Ev(void*);
void _ZN6Memory10DeallocateEPvP4Heap(void*, void*);
void* func_ov058_021111e0(char* c){
  *(int*)c = (int)data_ov058_02111a70;
  func_0207328c(c+0xd4, 5, 0x40, (void*)_ZN25MovingCylinderClsnWithPosD1Ev);
  _ZN5ActorD1Ev(c);
  _ZN6Memory10DeallocateEPvP4Heap(c, (void*)data_020a0eac[0]);
  return c;
}
}
