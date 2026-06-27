//cpp
class Animation {
public:
void Advance();
};

extern "C" int func_ov009_02111c4c(char *r0) {
*(int *)(r0 + 0x32c) = 0x1000;
((Animation *)(r0 + 0x320))->Advance();
return 1;
}
