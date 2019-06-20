#include <iostream> //std::cout
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>

using std::vector;

void show_usage(std::string name);

class BL{
  public:

    BL(); //default constructor
    int read_cmdLine(int argc, char * argv[]);

    void blcalc();

    void print_bl();

  private:
    double NWT;
    double N;
    double SR;
    double OUT;
    int    mc;  // good cell size
    vector<double> tcell;
    vector<double> plthk;
};


