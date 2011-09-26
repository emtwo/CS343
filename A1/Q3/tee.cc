#include "q3filter.h"
#include <math.h>

Tee::Tee( Filter *f, int base_width ) {
  this->f = f;
  this->basewidth = base_width;
}

void Tee::main() {
  cout << "I'm TEE" << endl;

  if (basewidth % 2 == 0) {
    basewidth++;
  }
  int numspaces, numrows;
  numspaces = numrows = floor(basewidth / 2);

  int g, b, c;
  for (;;) {
    for (g = 0; g < numrows + 2; g++) {
      if (numspaces == -1) numspaces = numrows;

      for (b = 0; b < numspaces; b++) {
        f->put(' ');
      }

      for (c = 0; c < (basewidth - numspaces * 2); c++) {
        if (ch == End_Filter) goto fini;
        if (ch == '\n' || ch == '\t') ch = ' ';
        f->put(ch);
        suspend();
      }

      if (ch == End_Filter) goto fini;
      f->put('\n');
      numspaces--;
    }
  }
  fini: ;
    f->put(ch);
}
