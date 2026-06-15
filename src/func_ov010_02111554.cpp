//cpp
extern "C" int _ZN16MeshColliderBase9IsEnabledEv(void *);
extern "C" void _ZN16MeshColliderBase7DisableEv(void *);
extern "C" void _ZN13SharedFilePtr7ReleaseEv(void *);
extern "C" char data_ov025_02112d08[];
extern "C" char data_ov024_02112d00[];
extern "C" int func_ov010_02111554(char *self){
  if(_ZN16MeshColliderBase9IsEnabledEv(self+0x124)){
    _ZN16MeshColliderBase7DisableEv(self+0x124);
  }
  if((*(unsigned int*)(self+8) & 0xff) != 0xff){
    _ZN13SharedFilePtr7ReleaseEv(data_ov025_02112d08);
    _ZN13SharedFilePtr7ReleaseEv(data_ov024_02112d00);
  }
  return 1;
}
