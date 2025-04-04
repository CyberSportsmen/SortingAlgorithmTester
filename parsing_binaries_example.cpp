#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

enum SortingMethods
{
  STL,
  RADIX10,
  RADIX2TO16,
  MERGE,
  SHELL,
  QUICK
};

char *sortingMethodToString[] = {"STL", "RADIX10", "RADIX2TO16", "MERGE", "SHELL", "QUICK"};

template <class T> class Tester
{
  vector<T> v;

public:
  Tester() = default;

  explicit Tester(vector<T> v_clone)
  {
    v = v_clone;
  }
  void Push_back(T val)
  {
    v.push_back(val);
  }
  bool isSorted()
  {
    for (int i = 1; i < v.size(); i++)
      if (v[i] < v[i - 1])
        return false;
    return true;
  }
  void Sort(const SortingMethods m)
  {
    switch (m)
    {
    case STL:
      std::sort(v.begin(), v.end());
      break;
    case RADIX10:
      std::sort(v.begin(), v.end());
      break;
    case RADIX2TO16:
      std::sort(v.begin(), v.end());
      break;
    case MERGE:
      std::sort(v.begin(), v.end());
      break;
    case SHELL:
      std::sort(v.begin(), v.end());
      break;
    case QUICK:
      std::sort(v.begin(), v.end());
      break;
    }
  }
};

void Testcase(Tester<long long> t)
{
  for (int i = STL; i <= QUICK; i++)
  {
    const auto m = static_cast<SortingMethods>(i);
    t.Sort(m);
    if (t.isSorted())
      cout << sortingMethodToString[i] << " was sorted successfully!\n";
    else
      cout << sortingMethodToString[i] << " was NOT sorted correctly!\n";
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
    t.Push_back(num);
  Testcase(t);
  file.close();
  return 0;
}
