#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>


using namespace boost;
using namespace std;

struct rectangle {
protected:
  int height;
  int weight;
public:
  rectangle (int h, int w) : height(h), weight(w) {  }

  int area()
  {
    return height * weight ;
  }
};




int main()
{
  cout << "A derived class should be able  " << endl;
  cout << "to substituted with the base class " << endl;
  cout << "So that it wouldnt affect any other APIs "
      << "relying on the functionality of the base class "<< endl;

  return 0;
}
