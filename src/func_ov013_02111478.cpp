//cpp
class SharedFilePtr {
public:
void Release();
};

extern "C" int data_ov013_021116b0[];

extern "C" int func_ov013_02111478(char *r0) {
unsigned char r1 = *(unsigned char *)(r0 + 0x124);
SharedFilePtr *ptr = (SharedFilePtr *)data_ov013_021116b0[r1];
ptr->Release();
return 1;
}
