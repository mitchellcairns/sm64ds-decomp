//cpp
extern "C" {
extern void _ZN5Actor18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(void*,void*,void*,int,int,int,unsigned int);
struct M4x3 { int w[12]; };
void func_ov015_021123c8(char* c){
  *(struct M4x3*)(c+0x348) = *(struct M4x3*)(c+0xf0);
  *(int*)(c+0x36c) = (*(int*)(c+0x5c) - *(int*)(c+0x384)) >> 3;
  *(int*)(c+0x370) = *(int*)(c+0x378) >> 3;
  *(int*)(c+0x374) = (*(int*)(c+0x64) - *(int*)(c+0x388)) >> 3;
  _ZN5Actor18DropShadowScaleXYZER11ShadowModelR9Matrix4x35Fix12IiES5_S5_j(
    c, c+0x320, c+0x348, 0x190000, 0x28000, 0x258000, 0xf);
}
}
