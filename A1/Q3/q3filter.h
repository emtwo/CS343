#ifndef __X_H
#define __X_H

#include <uC++.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
using namespace std;
#include <cstdlib>

class FilterObj {
  public:
    char* type;
    char* param;
};

_Coroutine Filter {
  protected:
    static const unsigned char End_Filter = '\377';
    unsigned char ch;
  public:
    void put( unsigned char c ) {
        ch = c;
        resume();
    }
};

_Coroutine Reader : public Filter {
  Filter* f;
  istream *i;
  void main() {
    try {
      for (;;) {
        ch = i->get();
        f->put(ch);
      }
    } catch (ios_base::failure) {
      f->put(End_Filter);
    }
  };
  public:
    Reader( Filter *f, istream *i ) {
      i->exceptions(ios_base::eofbit);
      this->f = f;
      this->i = i;
      resume();
    };
};

_Coroutine Writer : public Filter {
  ostream *o;
  void main() {
    for (;;) {
      if (ch == End_Filter) break;
      *o << ch;
      suspend();
    }
    
  };
  public:
    Writer( ostream *o ) {
      this->o = o;
    };
};

_Coroutine Hex : public Filter {
  Filter* f;
  void main();
  string makehex(char character);
  public:
    Hex( Filter *f );
};

_Coroutine Caps : public Filter {
  Filter* f;
  void main();
  public:
    Caps( Filter *f );
};

_Coroutine Whitespace : public Filter {
  Filter* f;
  void main();
  public:
    Whitespace( Filter *f );
};

_Coroutine Tee : public Filter {
  Filter* f;
  int basewidth;
  void main();
  public:
    Tee( Filter *f, int base_width );
};

_Coroutine Extra : public Filter {
  Filter* f;

  static const string morse[36];

  void main();
  public:
    Extra( Filter *f );
};

#endif
