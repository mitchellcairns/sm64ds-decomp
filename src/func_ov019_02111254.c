int func_ov019_02111254(int unused, int r1) {
  int v = r1 * 0x54cc + 0x4a800;
  if (v > 0x65000) v = 0x65000;
  if (v < 0x30000) v = 0x30000;
  return v;
}
