void zero(unsigned long int& uli, int nr){
  uli &= ~(0xFUL << 4*nr);
}
