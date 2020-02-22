

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>


using namespace boost;
using namespace std;

// Document that has to be scanned. !
struct Document {
  /* data */
};

// interface for scanning printing etc.

struct Interface_machine {
  virtual void print(Document d) = 0;
  virtual void scan(Document d) = 0;
  virtual void fax(Document d) = 0;
};

//implementation

struct I_Machine_API : Interface_machine {
   void print(Document d)
   {
     // what if the client machine doesnt have this function.
   }
   void scan(Document d)
   {

   }
   void fax(Document d)
   {

   }
};

// A BETTER approach would be to have
struct print_interface {
  virtual void print(Document d) = 0;
};

struct scan_interface {
  virtual void scan(Document d) = 0;
};

struct fax_interface {
  virtual void fax(Document d) = 0;
};

// so to create an abstract interface that has print and scan
struct print_scan_interface:scan_interface, print_interface {};

struct print_scan_machine : print_scan_interface
{
  print_interface& printer;
  scan_interface& scanner;
public:
    print_scan_machine (print_interface& p, scan_interface& s):
      printer(p), scanner(s)
      {

      }

    void print(Document d)
    {
        printer.print(d);
    }

    void scan(Document d)
    {
        scanner.scan(d);
    }
};

int main()
{
  cout << "A interface should be decluttered and splitted up";

  return 0;
}
