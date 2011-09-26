#include "q3filter.h"

Hex::Hex(Filter *f) {
  this->f = f;
}

/**
 * Returns a hex string given a character
 */
string Hex::makehex(char character) {
  int value = static_cast<int>(character);
  char chOut[10];
  sprintf( chOut, "%02x", value );
  return std::string(chOut);
}

void Hex::main() {
  int g, b;
  for (;;) {
    // Loop through 8 character inputs
    for (g = 0; g < 8; g++) {
      // Loop through 2 characters at a time
      // to form groups.
      for (b = 0; b < 2; b++) {
        if (ch == End_Filter) goto fini;
        
        string str = makehex(ch);
        f->put(str[0]);
        f->put(str[1]);
        suspend();
      }
      if (ch == End_Filter) goto fini;
      // Print a space after every 4 hex characters.
      f->put(' ');
      // Print 2 additional spaces between every other 
      // 4 hex characters.
      if (g % 2 != 0) {
        f->put(' ');
        f->put(' ');
      }
    }
    // Print a newline after 16 input characters.
    f->put('\n');
  }
  // Pass down the final EOF characher.
  fini: ;
    f->put(ch);
}
