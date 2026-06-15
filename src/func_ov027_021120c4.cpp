//cpp
extern "C" {
extern int func_0207328c(void*, int, int, void*);
extern void _ZN5ActorD1Ev(void*);
extern int data_ov036_02113b50[];
extern int data_ov056_02112158[];
int func_ov027_021120c4(char* c){
  *(int**)c = data_ov036_02113b50;
  func_0207328c(c+0xd4, 0x32, 0x60, data_ov056_02112158);
  _ZN5ActorD1Ev(c);
  return (int)c;
}
}
