#include "q3filter.h"

void uMain::main() {
  vector<FilterObj*> filters;
  istream *infile = &cin;
  ostream *outfile = &cout;	

  cout << argc << endl;
  // Save a list of filters & empty out argv
  for (int i = 1; i < argc; i++) {
    //cout << argv[i] << endl;
    if (argv[i][0] == '-') {
      FilterObj* f = new FilterObj();
      f->type = argv[i];
      argv[i] = "empty";
      if (!strcmp(f->type, "-T")) {
        cout << "got here" << endl;
        f->param = argv[i+1];
        argv[i+1] = "empty";
        i++;
      }

      filters.push_back(f);
    }
  }
 
  // Save the input and output files, if any
  for (int i = 1; i < argc; i++) { 
    if (strcmp(argv[i], "empty")){
      if (infile == &cin) {
        infile = new ifstream(argv[i]);
      }
      else if (outfile == &cout) {
        outfile = new ofstream(argv[i]);
      }
    }
  }
  
  cout << "INPUT: " << *infile << endl;
  cout << "OUTPUT: " << *outfile << endl;

  Filter *f = new Writer(outfile);

  for (int i = filters.size()-1; i >= 0; i--) {
    cout << filters[i]->type << endl;
    if (!strcmp(filters[i]->type, "-h")) { 
      Hex* h = new Hex(f);
      f = h;
    }
    else if (!strcmp(filters[i]->type, "-s")) {
      Caps* c = new Caps(f);
      f = c;
    }
    else if (!strcmp(filters[i]->type, "-w")) {
      Whitespace* w = new Whitespace(f);
      f = w;
    }
    else if (!strcmp(filters[i]->type, "-T")) {
      int basewidth = atoi(filters[i]->param);
      Tee* t = new Tee(f, basewidth);
      f = t;
    }
    else if (!strcmp(filters[i]->type, "-e")) {
      Extra* e = new Extra(f);
      f = e;
    }
  }
  Reader* r = new Reader(f, infile);

  r->put('a');
}
