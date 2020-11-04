#include <iostream>
#include "gain.hpp"
using namespace std;


int main(int argc, char const *argv[]) {
  if (argc != 2) {
    cout << "usage: " << argv[0] << " number of Stützstellen" << endl;
    return -1;
  }

  stringstream ss;
  ss << argv[1];
  int anz;
  ss >> anz;

  bool tests = true;
  if (tests) {
    test();
  }

  float Gain = gain_moncar(anz);
  cout << Gain << endl;
  cout << volume << endl;
  return 0;
}
