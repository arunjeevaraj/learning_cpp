

#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>


using namespace boost;
using namespace std;

// Document that has to be scanned. !
enum class relation {child, parent, spouse};

struct person {
  string name;
  person(string name): name(name) {};
};

// low data storage.
struct relations {
  vector<tuple<person, relation, person>> relations;
public:
  void add_parent_child(const person parent, const person child )
  {
    relations.push_back({parent, relation::parent, child});
    relations.push_back({child, relation::child, parent });
  }
};

// do research. high level
// Dependency inversion is about not making high level independent of the low level module.
// example where you break it.

struct research {
  research(relations& Relation_db)
  {
    auto& rel_elements = Relation_db.relations;
    for (auto&& [p1, relate, p2] : rel_elements) {
      if (relate == relation:: parent && p1.name == "john") {
          std::cout << p2.name << " is a child of john" << '\n';
      }
    }
  }
};


// how to make changes in low level immune to the high level module.
int main()
{
  cout << "The abstraction shouldn't depend" <<
    "on the details of the implementation." << endl;

    person parent("john");
    person child1((string)"james");
    person child2((string)"sara");
    relations relation_db;
    relation_db.add_parent_child(parent, child1);
    relation_db.add_parent_child(parent, child2);
    research res(relation_db);
  return 0;
}
