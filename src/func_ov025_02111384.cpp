//cpp
extern "C" {
void _ZN13SharedFilePtr7ReleaseEv(void* self);
int _ZN16MeshColliderBase9IsEnabledEv(void* self);
void _ZN16MeshColliderBase7DisableEv(void* self);
extern int data_ov025_02113a68[];
extern int data_ov036_02113a60[];
int func_ov025_02111384(char* c) {
  _ZN13SharedFilePtr7ReleaseEv(data_ov025_02113a68);
  _ZN13SharedFilePtr7ReleaseEv(data_ov036_02113a60);
  if (_ZN16MeshColliderBase9IsEnabledEv(c+0x124))
    _ZN16MeshColliderBase7DisableEv(c+0x124);
  return 1;
}
}
