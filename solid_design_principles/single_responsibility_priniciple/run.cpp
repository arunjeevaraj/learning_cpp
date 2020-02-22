#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>


using namespace boost;
using namespace std;

struct journal
{
  string title;
  vector<string> entries;
  journal(const string title) : title(title) {}

  void add_entry(const string entry)
  {
    static int counter;
    entries.push_back(lexical_cast<string>(counter++) + ' ' + entry);
  }
};


struct file_manager
{
  static void save(const journal j_save, const string& file_name)
  {
    ofstream ofs(file_name);
    for (auto& e : j_save.entries) {
       ofs << e << endl;
    }
  }
};

int main()
{
  cout << "A class should have only one responsibility " << endl;
  cout << "Saving is seperated from the functionality " << endl;
  cout << "This removes the interdependency "<< endl;
  journal j1("my diary");
  j1.add_entry("this was a day when things happened !!");
  j1.add_entry("I cried today !!");
  file_manager fm;
  fm.save(j1, "my_diary.txt");
  cout << "saving of the journal is done." << endl;
  return 0;
}
