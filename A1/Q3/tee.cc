#include "q3filter.h"
#include <math.h>

Tee::Tee( Filter *f, int base_width ) {
  this->f = f;
  this->basewidth = base_width;
}

void Tee::main() {
  // Only have odd basewidth.
  if (basewidth % 2 == 0) {
    basewidth++;
  }

  /**
   * numspaces is the number of prefixed spaces
   * in a given line.
   */
  int numspaces, numrows;
  numspaces = floor(basewidth / 2);
  numrows = numspaces + 2;

  int g, b, c;
  for (;;) {
    for (g = 0; g < numrows; g++) {
      if (numspaces == -1) numspaces = numrows;

      // Print all the prefixed spaces.
      for (b = 0; b < numspaces; b++) {
        f->put(' ');
      }

      // Print all the characters after the spaces.
      for (c = 0; c < (basewidth - numspaces * 2); c++) {
        if (ch == End_Filter) goto fini;
        if (ch == '\n' || ch == '\t') ch = ' ';
        f->put(ch);
        suspend();
      }

      // Print a newline & decrement the prefixed spaces.
      if (ch == End_Filter) goto fini;
      f->put('\n');
      numspaces--;
    }
  }
  // Pass along the EOF character.
  fini: ;
    f->put(ch);
}
