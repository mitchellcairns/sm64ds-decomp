//cpp
extern "C" {
struct BCA_File; struct SharedPtr{void*a;BCA_File*f;};
extern struct SharedPtr data_ov081_02128db8;
int _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(void*,BCA_File*,int,int,unsigned);
int func_ov081_02124d14(char*c){
  _ZN9ModelAnim7SetAnimEP8BCA_Filei5Fix12IiEj(c+0x30c, data_ov081_02128db8.f, 0x40000000, 0x1000, 0);
  return 1;
}
}
