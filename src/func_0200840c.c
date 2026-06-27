struct Camera;

extern short ReadUnalignedShort(unsigned char *p);
extern short ApproachLinear2(short *ref, short a, short b);

int func_0200840c(struct Camera *cam, const char *data) {
    short v1 = ReadUnalignedShort((unsigned char *)data);
    short v2 = ReadUnalignedShort((unsigned char *)data + 2);
    ApproachLinear2((short *)((char *)cam + 0x17a), v1, v2);
    return 1;
}
