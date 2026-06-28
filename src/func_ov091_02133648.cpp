//cpp
extern "C" {
extern void _ZN5Sound9PlayBank3EjRK7Vector3(unsigned int id, void* v);
extern void func_ov091_021334b8(void* c, int f);
void func_ov091_02133648(char* c, void* arg){
  if(arg==0) return;
  if(*(unsigned char*)(c+0x31e)==0) return;
  if(*(unsigned char*)(c+0x31f)) return;
  _ZN5Sound9PlayBank3EjRK7Vector3(0x62, c+0x74);
  int f = 0;
  if(*(int*)((char*)arg+8)==2) goto set;
  if(*(unsigned char*)((char*)arg+0x703)==0) goto done;
set:
  f=1;
done:
  func_ov091_021334b8(c, f);
}
}
