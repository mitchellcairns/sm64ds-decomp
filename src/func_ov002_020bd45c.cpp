//cpp
struct Vector3{int x,y,z;};
extern "C" unsigned int ReadUnalignedInt(unsigned char *p);
namespace Sound{ void PlayBank0(unsigned int, const Vector3 &); }
extern "C" int func_ov002_020bd45c(unsigned char *c, unsigned char *p){
    unsigned int v=ReadUnalignedInt(p);
    Sound::PlayBank0(v, *(Vector3*)(c+0x74));
    return 1;
}
