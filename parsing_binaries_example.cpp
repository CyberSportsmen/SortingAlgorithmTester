#include <iostream>
#include <fstream>
#include <string>

enum SortingMethods
{
  STL,
  RADIX10,
  RADIX2TO16,
  MERGE,
  SHELL,
  QUICK
};

class<T> Tester
{
  vector<T> v;

public:
  Tester() = default;
  Tester(vector<T> v_clone)
  {
    v = v_clone;
  }
  Push_back(T val)
  {
    v.push_back(val);
  }
  Sort(method m)
  {
    switch (m)
    {
    case STL:
      sort(v);
      break;
    case RADIX10:
      sort(v);
      break;
    case RADIX2TO16:
      sort(v);
      break;
    case MERGE:
      sort(v);
      break;
    case SHELL:
      sort(v);
      break;
    case QUICK:
      sort(v);
      break;
    }
  }
};

void Testcase(Tester t)
{
  for (auto method : SortingMethods)
  {
    // here we can place the chronometer logic
    t.Sort(method);
  }
}

int main(int argc, char *argv[])
{
  std::string filename;
  try
  {
    if (argc > 1)
      filename = argv[1];
    else
      throw std::out_of_range("naspa");
  }
  catch (std::out_of_range)
  {
    std::cerr << "No argument found!\n";
    return 0;
  }
  std::ifstream file(filename, std::ios::binary);
  if (!file)
  {
    std::cerr << "Error opening file for reading!\n";
    return 1;
  }
  long long num;
  Tester<long long> t;
  while (file.read(reinterpret_cast<char *>(&num), sizeof(long long)))
    t.push_back(num);
  Testcase(t);
  file.close();
  return 0;
}
