#include <iostream>
#include <boost/lexical_cast.hpp>
#include <vector>
#include <fstream>
#include <string>


using namespace boost;
using namespace std;

enum class Color {red, green, blue};
enum class Size {small, medium, large};

struct Product
{
  string name;
  Color color;
  Size size;
};

struct Product_Filter
{
  vector<Product*> by_color( vector<Product*> items, Color color)
  {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (i->color == color)
        result.push_back(i);
    }

    return result;
  }
};


template <typename T> struct Specification
{
  virtual bool is_satisfied(T* item) = 0;
};

template <typename T> struct Filter
{
  virtual vector<T*> filter(vector <T*> items, Specification<T> & spec) = 0;
};


template <typename T> struct AndFilter : Specification<T>
{
  Specification<T>& spec1;
  Specification<T>& spec2;
  AndFilter(Specification<T>& s1, Specification<T>& s2) :
  spec1(s1), spec2(s2)
  {

  }
  bool is_satisfied(T* item)
  {
    return spec1.is_satisfied(item) && spec2.is_satisfied(item);
  }
};


struct Better_filter : Filter <Product>
{
  vector<Product*> filter(vector <Product*> items, Specification<Product> & spec)
  {
    std::vector<Product*> result;
    for (auto& i : items) {
      if (spec.is_satisfied(i))
        result.push_back(i);
    }
    return result;
  }
};


struct color_filter : Specification<Product>{
  Color color;
  color_filter(Color c) : color(c) { }
  bool is_satisfied(Product* item)
  {
    return (item->color == color);
  }
};

struct size_filter : Specification<Product>{
  Size size;
  size_filter(Size s) : size(s) { }
  bool is_satisfied(Product* item)
  {
    return (item->size == size);
  }
};



int main()
{
  cout << "open closed principles...you should be open to extension " << endl;
  cout << "but should be closed to additions " << endl;
  Product apple{"Apple", Color::red, Size::small};
  Product car{"Car", Color::green, Size::medium};
  Product Tree{"Tree", Color::green, Size::large};

  vector<Product*> items{&apple, &car, &Tree};
  Product_Filter pf;
  auto green_items = pf.by_color(items, Color::green);
  for (auto& item : green_items) {
    cout << item->name << " is green " << endl;
  }

  color_filter red_filter(Color::red);
  Better_filter filter_manager;
  auto red_items = filter_manager.filter(items, red_filter);
  for (auto& item : red_items) {
    cout << item->name << " is red " << endl;
  }

  size_filter large_filter(Size::large);
  color_filter green_filter(Color::green);
  AndFilter<Product> green_and_large_filter(green_filter, large_filter);
  auto green_and_large_items = filter_manager.filter(items, green_and_large_filter);
  for (auto& item : green_and_large_items) {
    cout << item->name << " is green and large " << endl;
  }

  return 0;
}
