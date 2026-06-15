//cpp
extern "C" {
extern int _ZN13SharedFilePtr7ReleaseEv(void*);
extern void UnloadBlueCoinModel(void*);
extern int data_ov020_02114aa0[];
extern int data_ov020_02114ab8[];
int func_ov020_02112290(char* c){
  _ZN13SharedFilePtr7ReleaseEv(data_ov020_02114aa0);
  _ZN13SharedFilePtr7ReleaseEv(data_ov020_02114ab8);
  UnloadBlueCoinModel(c);
  return 1;
}
}
