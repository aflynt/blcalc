#include "bl.H"


  //1   2    3  4  5
  //prog NWT N SR OUT

int main(int argc, char * argv[])
{
  BL b;
  if (argc < 4){
    show_usage(argv[0]);
    return 1;
  }
  else
    b.read_cmdLine(argc, argv);

  b.blcalc();

  b.print_bl();


  return 0;
}
