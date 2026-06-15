//cpp
extern "C" {
void CleanCommonModelDataArr(void);
void _ZN5Sound21UnsetPlayerVoiceGroupEv(void);
}
extern "C" int func_ov003_020af86c(void){
    CleanCommonModelDataArr();
    _ZN5Sound21UnsetPlayerVoiceGroupEv();
    *(volatile unsigned short*)0x4000304 |= 0x8000;
    return 1;
}
