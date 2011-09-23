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
  //vector<string> parameters;
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
  void main() { 
    cout << "I'm READER" << endl;
    f->put(ch);
  };
  public:
    Reader( Filter *f, istream *i ) {
      this->f = f;
    };
};

_Coroutine Writer : public Filter {
  Filter* f;
  void main() {
    cout << "I'm WRITER" << endl;
    f->put(ch);
  };
  public:
    Writer( ostream *o ) {
      this->f = f;
    };
};

_Coroutine Hex : public Filter {
  Filter* f;
  void main() {
    cout << "I'm HEX" << endl;
    f->put(ch);
  };
  public:
    Hex( Filter *f ) {
      this->f = f;
    };
};

_Coroutine Caps : public Filter {
  Filter* f;
  void main() {
    cout << "I'm CAPS" << endl;
    f->put(ch);
  };
  public:
    Caps( Filter *f ) {
      this->f = f;
    };
};

_Coroutine Whitespace : public Filter {
  Filter* f;
  void main() {
    cout << "I'm WHITESPACE" << endl;
    f->put(ch);
  };
  public:
    Whitespace( Filter *f ) {
      this->f = f;
    };
};

_Coroutine Tee : public Filter {
  Filter* f;
  void main() {
    cout << "I'm TEE" << endl;
    f->put(ch);
  };
  public:
    Tee( Filter *f, int base_width ) {
      this->f = f;
    };
};

_Coroutine Extra : public Filter {
  Filter* f;
  void main() {
    cout << "I'm EXTRA" << endl;
    f->put(ch);
  };
  public:
    Extra( Filter *f ) {
      this->f = f;
    };
};

#endif
