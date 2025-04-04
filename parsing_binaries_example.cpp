#include <iostream>
#include <fstream>
#include <string>

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
  while (file.read(reinterpret_cast<char *>(&num), sizeof(long long)))
  {
    std::cout << num << ' '; // Print each number like a normal text file
  }

  file.close();
  return 0;
}
