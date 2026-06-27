//cpp
class Sound {
public:
    static void UnsetPlayerVoiceGroup();
};

extern void CleanCommonModelDataArr(void);

extern "C" int func_ov003_020af86c(void) {
    CleanCommonModelDataArr();
    Sound::UnsetPlayerVoiceGroup();
    unsigned short *p = (unsigned short *)0x4000304;
    *p = *p | 0x8000;
    return 1;
}
