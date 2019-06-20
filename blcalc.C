#include "bl.H"

using std::cout;
using std::endl;
using std::setw;
using std::setprecision;

void show_usage(std::string name)
{
  std::cerr << "Usage: " << name << " <option(s)>\n"
            << "Options:\n"
            << "\t-h,--help    \tShow this help message\n"
            << "\tNWT N SR     \tspecify near wall thickness, n-layers, stretch-ratio\n"
            << "\tNWT N SR OUT \talso specify outer cell thickness\n";
}

BL::BL()
{
  NWT = 0.0;
  N   = 0.0;
  SR  = 0.0;
  OUT = 0.0;
  mc  = 0;
}

int BL::read_cmdLine(int argc, char * argv[])
{
  std::vector <std::string> input;
  //std::cout << "reading cmdLine\n";
  for(int i = 1; i < argc; ++i)
  {
    std::string arg = argv[i];
    if((arg == "-h") || (arg == "--help")){
      show_usage(argv[0]);
      return 0;
    }
    else
      input.push_back(argv[i]);
  }

  //std::cout << "N-inputs: "
  //          << input.size()
  //          << std::endl;

  // check for negative input
  for(auto val : input)
    if(std::stod(val) < 0){
      cout << "value " << val << " is negative!\n";
      return 1;
    }

  if(input.size() >= 3){
    NWT = std::stod(input[0]); cout << "NWT: "<< NWT << endl;
    N   = std::stod(input[1]); cout << "N  : "<< N   << endl;
    SR  = std::stod(input[2]); cout << "SR : "<< SR  << endl;
  }
  if(input.size() == 4){
    OUT = std::stod(input[3]); cout << "OUT: "<< OUT << endl;
  }

  return 0;
}

void BL::blcalc()
{

  double tc = NWT;
  double pc = tc;
  double target = OUT / 2.0;

  for(int i = 0; i < N; i++)
  {
    tcell.push_back(tc);
    plthk.push_back(pc);

    if(tc < target)
      mc = i;

    //cout << " i= " << i+1;
    //cout << " t= " << tc ;
    //cout << " p= " << pc ;
    //cout << endl;

    tc *= SR;
    pc += tc;
  }

  //cout << "target = " << target << endl;
  //cout << "mc     = " << mc << endl;
}

void BL::print_bl()
{
  char cx = '#';
  cout << cx << " i"
       << "    "
       << "Tcell"
       << "    "
       << "PLT"
       << endl;
  cout << "---------------------\n";
  for(int i = 0; i < tcell.size(); i++)
  {
    char cc = ' ';
    if (i == mc) cc = cx;
    cout <<  cc  << setw(2) << i+1
         <<  ' ' << std::fixed
                 << setprecision(3)
                 << setw(8)
                 << tcell[i]
         <<  ' ' << setw(8) << plthk[i]
         << endl;
  }

  //  //tcell *= SR;
  //  //plt += tcell;
  //}
}

/*
  //for(int i = 0; i < N; i++)
  //{
  //  cout <<         setw(2) << i+1
  //       <<  ' ' << std::fixed
  //               << setprecision(3)
  //               << setw(8)
  //               << tcell
  //       <<  ' ' << setw(8) << plt
  //       << endl;

  //  //tcell *= SR;
  //  //plt += tcell;
  //}
*/
