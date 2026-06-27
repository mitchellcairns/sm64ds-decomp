//cpp
class Platform {
public:
void UpdateClsnPosAndRot();
};

extern "C" int func_ov002_020bac18();

extern "C" int func_ov014_02111268(Platform *r5) {
int r4 = func_ov002_020bac18();
r5->UpdateClsnPosAndRot();
return r4;
}
