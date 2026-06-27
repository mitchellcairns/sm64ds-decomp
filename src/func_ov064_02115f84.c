struct UnknownStruct {
    char pad[0x24];
    int value;
};

struct Context {
    char pad[0x330];
    struct UnknownStruct* ptr;
};

int func_ov064_02115f84(void* c) {
    struct UnknownStruct* r1 = ((struct Context*)c)->ptr;
    int r0 = 0x14000;
    if (r1 != 0) {
        r0 = r1->value;
    }
    return r0;
}
