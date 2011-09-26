#include "q3filter.h"

Whitespace::Whitespace( Filter *f ) {
  this->f = f;
}
  
void Whitespace::main() {
  cout << "I'm WHITESPACE" << endl;
  char ch1;

  ch1 = ch;
  for (;;) {
    if (ch1 == End_Filter) goto fini;
    if (ch1 == '\n') f->put(ch1);
    if(ch1 == ' ' || ch1 == '\t' || ch1 == '\n') {
      suspend();
      ch1 = ch;
      continue;
    } else {
      f->put(ch1);
      suspend();
      if (ch == '\t') ch = ' ';
    }

    for (;;) {
      ch1 = ch;
      suspend();
      if (ch == '\t') ch = ' ';
      if (ch1 == ' ' && ch == ' ') {
        continue;
      } 
      else if (ch1 == ' ' && ch == '\n') {
        f->put(ch);
        break;
      } else if (ch1 == '\n') {
        f->put(ch1);
        ch1 = ch;
        break;
      } else {
        f->put(ch1);
      }
    }
  }
  fini: ;
    f->put(ch);
}
