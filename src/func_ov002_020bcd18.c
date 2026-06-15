extern int func_ov002_020bf30c(void*, int);
int func_ov002_020bcd18(void *c){
    *(int*)((char*)c+0x98)=func_ov002_020bf30c(c, 0xa000);
    return 1;
}
