#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>
#include <tuple>
#include <sstream>
#include <memory>

using namespace std;

struct Html_e {
  std::string name, text;
  std::vector<Html_e> child_elements;
  int intend_size = 2;
  Html_e()
  {

  }
  Html_e(string name, string text, int intend_size = 2) :
  name(name), text(text), intend_size(intend_size)
  {

  }

  std::string str(int intend = 0)
  {
    ostringstream oss;
    std::string i_s(intend_size*intend, ' ');
    oss << i_s << "<" << name << ">" << endl;
    if (text.size() > 0) {
      oss << string(intend_size*(intend + 1), ' ') << text << endl;
    }
    for (auto e : child_elements) {
      oss << e.str((intend + 1));
    }
    oss << i_s << "</" << name << ">" << endl;
    return oss.str();
  }

};

// instead of using a constructor of html_e we are using htlm_builder to build things up.

struct Html_builder {
  Html_e root;

  Html_builder(string root_name)
  {
    root.name = root_name;
  }

  void add_child(string name, string text)
  {
    Html_e he(name, text);
    root.child_elements.emplace_back(he);
  }

  std::string str(int intend = 0)
  {
    return root.str();
  }

};

// how to make changes in low level immune to the high level module.
int main()
{
  cout << "The reason why we need to create builder, the art of building step by step"
    << endl;
    Html_builder ul{"ul"};
    ul.add_child("li", "baby");
    ul.add_child("li", "babies");
    std::cout << ul.str() << '\n';
  return 0;
}
