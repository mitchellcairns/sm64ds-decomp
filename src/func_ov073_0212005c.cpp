//cpp
struct Animation { int Finished(); };
extern int data_ov073_02123360[];
extern "C" int func_ov073_0212157c(void* c, void* p);
extern "C" int func_ov073_0212005c(char* c){
  if(((Animation*)(c+0x35c))->Finished()){
    *(unsigned char*)(c+0x4c5)=0xff;
    func_ov073_0212157c(c, data_ov073_02123360);
  }
  return 1;
}
