#include "q3filter.h"

Whitespace::Whitespace( Filter *f ) {
  this->f = f;
}
  
void Whitespace::main() {
  // ch1 is used along with ch to store the
  // next two characters to be processed.
  char ch1;

  ch1 = ch;
  for (;;) {
    // PART 1: Processing the start of a line.

    if (ch1 == End_Filter) goto fini;
    // Print a newline if it exists.
    if (ch1 == '\n') f->put(ch1);
    // Ignore whitespace & get the next character.
    if(ch1 == ' ' || ch1 == '\t' || ch1 == '\n') {
      suspend();
      ch1 = ch;
      continue;
    // Print the first non-whitespace character in a line
    } else {
      f->put(ch1);
      suspend();
      if (ch == '\t') ch = ' ';
    }

    // PART 2: Processing the rest of a line.
    for (;;) {
      ch1 = ch;
      suspend();
      // Change a tab to a space.
      if (ch == '\t') ch = ' ';
      // If there are two spaces in a row, ignore one.
      if (ch1 == ' ' && ch == ' ') {
        continue;
      }
      // If there's a space and a newline, ignore the space,
      // and print the newline.
      else if (ch1 == ' ' && ch == '\n') {
        f->put(ch);
        break;
      // If the current character is a newline, print it
      // and move on to the next one.
      } else if (ch1 == '\n') {
        f->put(ch1);
        ch1 = ch;
        break;
      // Print all other non-whitespace characters.
      } else {
        f->put(ch1);
      }
    }
  }
  // Pass the EOF character along.
  fini: ;
    f->put(ch);
}
