typedef signed char s8;
typedef unsigned int u32;

extern int IsStarCollectedInLevel(s8 levelID, int starID);
extern void _ZN5Actor5SpawnEjjRK7Vector3PK10Vector3_16ii(u32 id, u32 param, void *pos, void *ang, int a, int b);
extern void _ZN9ActorBase18MarkForDestructionEv(void *self);
extern void *_ZN5Model8LoadFileER13SharedFilePtr(void *f);
extern void _ZN9ModelBase7SetFileEP8BMD_Fileii(void *self, void *f, int a, int b);
extern void _ZN15TextureSequence8LoadFileER13SharedFilePtr(void *f);
extern void _ZN15TextureSequence7PrepareER8BMD_FileR8BTP_File(void *bmd, void *btp);
extern void _ZN15TextureSequence7SetFileER8BTP_Filei5Fix12IiEj(void *self, void *btp, int a, int fix, u32 u);
extern int _ZN11ShadowModel12InitCylinderEv(void *self);
extern void _ZN25MovingCylinderClsnWithPos4InitEP5ActorRK7Vector35Fix12IiES6_jj(void *self, void *act, void *pos, int f1, int f2, u32 u1, u32 u2);
extern void _ZN13RaycastGroundC1Ev(void *self);
extern void _ZN13RaycastGround12SetObjAndPosERK7Vector3P5Actor(void *self, void *pos, void *act);
extern int _ZN13RaycastGround10DetectClsnEv(void *self);
extern void func_ov072_021208d8(void *thiz);
extern void _ZN13RaycastGroundD1Ev(void *self);

extern int data_ov072_02122c48[];
extern int data_ov072_02122c40[];
extern int data_ov072_02122c50[];
extern int data_ov072_02122c70[];

int func_ov072_02120a44(char *c)
{
    char rg[0x50];
    int v[3];
    void *m;

    if (IsStarCollectedInLevel(0xa, 5) == 0)
    {
        _ZN5Actor5SpawnEjjRK7Vector3PK10Vector3_16ii(0x111, 0, c + 0x5c, c + 0x8c, *(s8 *)(c + 0xcc), -1);
        _ZN9ActorBase18MarkForDestructionEv(c);
    }

    m = _ZN5Model8LoadFileER13SharedFilePtr(data_ov072_02122c48);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(c + 0xd4, m, 1, 1);
    m = _ZN5Model8LoadFileER13SharedFilePtr(data_ov072_02122c40);
    _ZN9ModelBase7SetFileEP8BMD_Fileii(c + 0x124, m, 1, 1);

    _ZN15TextureSequence8LoadFileER13SharedFilePtr(data_ov072_02122c50);
    _ZN15TextureSequence7PrepareER8BMD_FileR8BTP_File((void *)data_ov072_02122c48[1], (void *)data_ov072_02122c50[1]);
    _ZN15TextureSequence7SetFileER8BTP_Filei5Fix12IiEj(c + 0x174, (void *)data_ov072_02122c50[1], 0, 0x1000, 0);

    if (_ZN11ShadowModel12InitCylinderEv(c + 0x188) == 0)
        return 0;

    _ZN25MovingCylinderClsnWithPos4InitEP5ActorRK7Vector35Fix12IiES6_jj(c + 0x1b0, c, data_ov072_02122c70, 0xc3000, 0x17c000, 0x800004, 0);

    v[0] = *(int *)(c + 0x5c);
    v[1] = *(int *)(c + 0x60);
    v[2] = *(int *)(c + 0x64);
    v[1] += 0x14000;
    _ZN13RaycastGroundC1Ev(rg);
    _ZN13RaycastGround12SetObjAndPosERK7Vector3P5Actor(rg, v, 0);
    if (_ZN13RaycastGround10DetectClsnEv(rg))
        *(int *)(c + 0x60) = *(int *)(rg + 0x44);
    else
        *(int *)(c + 0x60) = v[1];
    (*(int *)(((int)c + 0x60) & 0xFFFFFFFFFFFFFFFF)) += 0xc3000;
    *(int *)(c + 0x9c) = 0;
    *(int *)(c + 0xa0) = 0;
    *(int *)(c + 0x80) = 0x1800;
    *(int *)(c + 0x84) = 0x1800;
    *(int *)(c + 0x88) = 0x1800;
    func_ov072_021208d8(c);
    _ZN13RaycastGroundD1Ev(rg);
    return 1;
}
