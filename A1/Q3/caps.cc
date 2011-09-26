#import "q3filter.h"

Caps::Caps( Filter *f ) {
  this->f = f;
}  
void Caps::main() {
  for (;;) {
    // Skip past whitespace if there is any.
    for ( ; ch == ' ' || ch == '\t' || ch == '\n' ; ) {
      // Print whitespace.
      f->put(ch);
      suspend();
      if (ch == End_Filter) goto fini;
    }

    // Capitalize first letter of input.
    if (islower(ch)) {
      ch = toupper(ch);
    }
    f->put(ch);

    for (;;) {
      suspend();
      if (ch == End_Filter) goto fini;

      if (ch == '.' || ch == '!' || ch == '?') {
        // Print punctuation.
        f->put(ch);
        suspend();
        if (ch == End_Filter) goto fini;

        if (ch == ' ' || ch == '\t' || ch == '\n') {
          for ( ; ch == ' ' || ch == '\t' || ch == '\n' ; ) {
            // Print whitespace.
            f->put(ch);
            suspend();
            if (ch == End_Filter) goto fini;
          }

          // Capitalize first letter of sentence.
          if (islower(ch)) {
            ch = toupper(ch);
          }
        }

      }
      f->put(ch);
    }
  }
  fini: ;
    f->put(ch);
}
