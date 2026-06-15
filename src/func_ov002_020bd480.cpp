//cpp
struct Vector3{int x,y,z;};
extern "C" unsigned int ReadUnalignedInt(unsigned char *p);
namespace Sound{ void PlayCharVoice(unsigned int, unsigned int, const Vector3 &); }
extern "C" int func_ov002_020bd480(unsigned char *c, unsigned char *p){
    unsigned int v=ReadUnalignedInt(p);
    Sound::PlayCharVoice(c[0x6d9], v, *(Vector3*)(c+0x74));
    return 1;
}
