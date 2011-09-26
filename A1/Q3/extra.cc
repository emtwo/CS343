/**
 * The Extra filter translates text into Morse Code. Morse code is a
 * character representation in which a combination of underscores and dots are used to
 * signify every letter. The letter mappings can be found at the
 * following website: http://en.wikipedia.org/wiki/File:International_Morse_Code.svg
 * 
 * To make the morse translation more readable. The string ' * ' is
 * placed at the beginning and end of the file as well as between every letter.
 * Spaces between words are replaced with the '\n' characher such that
 * each word is on a new line. At the beginning and end of a line
 * that is not the beginning or end of the file, there is no ' * ' string.
 *
 * Characters that are not between 0-9 and not a letter of the alphabet
 * are printed and displayed as they are.
 * 
 * Author: Marina Samuel
 */

#include "q3filter.h"

/**
 * The first 26 strings in this array represent the letters a through z
 * they are applicable for both capital and lowercase letters.
 * The next 10 strings represent the numbers 0 through 9.
 */
const string Extra::morse[36] = 
                     {"._", "_...", "_._.", "_..", ".", ".._.", "__.", "....", "..", ".___", "_._",
                      "._..", "__", "_.", "___", ".__.", "__._", "._.", "...", "_", ".._", "..._",
                      ".__", "_.._", "_.__", "__..", "_____", ".____", "..___", "...__",
                      "...._", ".....", "_....", "__...", "___..", "____."};


Extra::Extra( Filter *f ) {
  this->f = f;
}

void Extra::main() {
  char ch1;

  // Print ' * ' string at start of file.
  f->put(' ');
  f->put('*');
  f->put(' ');
  for (;;) {
    // Read in a second character to be stored.
    ch1 = ch;
    suspend();
    if (ch1 == End_Filter) break;
    string charcode = "";

    // Convert characters to morse code appropriately.
    if (ch1 >= 'a' && ch1 <= 'z') {
      charcode = morse[(int)ch1 - 97];
    } else if (ch1 >= 'A' && ch1 <= 'Z') {
      charcode =  morse[(int)ch1 - 65];
    } else if (ch1 >= '0' && ch1 <= '9') {
      charcode =  morse[(int)ch1 - 22];
    } else if (ch1 == ' ') {
      charcode = "\n";
    }

    // Print the converted morse strings
    for (int i = 0; i < charcode.length(); i++) {
      f->put(charcode[i]);
    }
    
    // If we're going to be starting a new line, skip printing ' * '
    if (ch == ' ') continue;

    // Print all non-alphanumeric characters as they are.
    if (charcode == "") {
      f->put(ch1);
    }
    // If we're not starting a new line print ' * '
    if (charcode != "\n" && ch1 != '\n') {
      f->put(' ');
      f->put('*');
      f->put(' ');
    }
  }
}
