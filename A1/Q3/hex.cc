#include "q3filter.h"

Hex::Hex(Filter *f) {
  this->f = f;
}

string Hex::makehex(char character) {
  int value = static_cast<int>(character);
  char chOut[10];
  sprintf( chOut, "%02x", value );
  return std::string(chOut);
}

void Hex::main() {
  cout << "I'm HEX" << endl;
  int g, b;
  for (;;) {
    for (g = 0; g < 8; g++) {
      for (b = 0; b < 2; b++) {
        if (ch == End_Filter) goto fini;
        
        string str = makehex(ch);
        f->put(str[0]);
        f->put(str[1]);
        suspend();
      }
      if (ch == End_Filter) goto fini;
      f->put(' ');
      if (g % 2 != 0) {
        f->put(' ');
        f->put(' ');
      }
    }
    f->put('\n');
  }
  fini: ;
    f->put(ch);
}
