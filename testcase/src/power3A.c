int power3_A(int in) {
  int i, out_a;
  out_a = in; 
  for (i = 0; i < 2; i++) 
    out_a = out_a * in;
  return out_a;
}