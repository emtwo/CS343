#include "q3filter.h"

const string Extra::morse[36] = 
                     {"._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._",
                      "._..", "__", "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._",
                      ".__", "_.._", "_.__", "__..", "_____", ".____", "..___", "...__",
                      "...._", ".....", "_....", "__...", "___..", "____."};


Extra::Extra( Filter *f ) {
  this->f = f;
}

void Extra::main() {
  cout << "I'm EXTRA" << endl;

  char ch1;

  f->put(' ');
  f->put('*');
  f->put(' ');
  for (;;) {
    ch1 = ch;
    suspend();
    if (ch1 == End_Filter) break;
    string charcode = "";

    if (ch1 >= 'a' && ch1 <= 'z') {
      charcode = morse[(int)ch1 - 97];
    } else if (ch1 >= 'A' && ch1 <= 'Z') {
      charcode =  morse[(int)ch1 - 65];
    } else if (ch1 >= '0' && ch1 <= '9') {
      charcode =  morse[(int)ch1 - 22];
    } else if (ch1 == ' ') {
      charcode = "\n";
    }

    for (int i = 0; i < charcode.length(); i++) {
      cout << charcode[i];
    }
    if (ch == ' ') continue;
    if (charcode == "") {
      cout << ch1;
    }
    if (charcode != "\n" && ch1 != '\n') {
      cout << ' ';
      cout << '*';
      cout << ' ';
    }
  }
}
