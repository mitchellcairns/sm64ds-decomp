// NONMATCHING: base materialization / addressing (div=7). Logic verified correct vs ROM; not
// byte-matchable from C at mwccarm 1.2/sp2p3 (see notes/matching-style.md).
// Counts as decompiled, not matched.
struct Struct_ov080_02124fec {
    char pad[176];
    int field_B0;
    char pad2[696];
    int field_370;
};

int func_ov080_02124fec(struct Struct_ov080_02124fec *arg0, int dummy1, int dummy2) {
    int r3 = 1;
    arg0->field_370 = r3;
    
    int *r2 = (int *)((char *)arg0 + 0xB0);
    int r1 = *r2;
    
    int r0 = r3;
    r1 &= ~3;
    *r2 = r1;
    
    return r0;
}
