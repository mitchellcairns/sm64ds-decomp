struct S{ int w[12]; };
extern struct S data_ov006_0213c85c;
void func_ov006_020e7b0c(char* c){
  *(struct S*)(c+0x28)=data_ov006_0213c85c;
}
