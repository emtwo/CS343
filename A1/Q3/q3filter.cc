#include "q3filter.h"

void uMain::main() {
 
  // Associates filters with their parameters.
  vector<FilterObj*> filterObjs;

  // A list of all filters.
  vector<Filter*> filters;

  istream *infile = &cin;
  ostream *outfile = &cout;	

  // Save a list of filters & empty out argv
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      FilterObj* f = new FilterObj();
      f->type = argv[i];
      argv[i] = "empty";
      if (!strcmp(f->type, "-T")) {
        f->param = argv[i+1];
        argv[i+1] = "empty";
        i++;
      }

      filterObjs.push_back(f);
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
 
  // Initialize filters and store in vector.
  Filter *f = new Writer(outfile);
  filters.push_back(f);

  for (int i = filterObjs.size()-1; i >= 0; i--) {
    if (!strcmp(filterObjs[i]->type, "-h")) { 
      Hex* h = new Hex(f);
      filters.push_back(h);
      f = h;
    }
    else if (!strcmp(filterObjs[i]->type, "-s")) {
      Caps* c = new Caps(f);
      filters.push_back(c);
      f = c;
    }
    else if (!strcmp(filterObjs[i]->type, "-w")) {
      Whitespace* w = new Whitespace(f);
      filters.push_back(w);
      f = w;
    }
    else if (!strcmp(filterObjs[i]->type, "-T")) {
      int basewidth = atoi(filterObjs[i]->param);
      Tee* t = new Tee(f, basewidth);
      filters.push_back(t);
      f = t;
    }
    else if (!strcmp(filterObjs[i]->type, "-e")) {
      Extra* e = new Extra(f);
      filters.push_back(e);
      f = e;
    }
  }
  Reader* r = new Reader(f, infile);
  filters.push_back(r);

  // Cleanup.
  if ( infile != &cin ) delete infile;
  if ( outfile != &cout ) delete outfile;

  for (int i = filters.size()-1; i >= 0; i--) {
    delete filters[i];
  }
  for (int i = filterObjs.size()-1; i >= 0; i--) {
    delete filterObjs[i];
  }
  filters.clear();
}
