
void toggle_port(void)
{

  P2OUT ^= 0xFF;

}

void shift_port(void)
{
  int shift_right;
  shift_right = 1;
  while(1){
    P2OUT = shift_right ? P2OUT >> 1 : P2OUT << 1;
    if (P2OUT & 0x01){ //if LSB == 1
      shift_right = 0;
    }else{
      if (P2OUT & 0x80) //if MSB == 1
        shift_right = 1;
    }
  }
}