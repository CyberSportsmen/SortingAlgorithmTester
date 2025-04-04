#include <iostream>
#include <fstream>

int main()
{
  std::ifstream file("generated_files/random/random_100_interval_-1000000_1000000.bin", std::ios::binary);
  if (!file)
  {
    std::cerr << "Error opening file for reading!\n";
    return 1;
  }

  long long num;
  while (file.read(reinterpret_cast<char *>(&num), sizeof(long long)))
  {
    std::cout << num << '\n'; // Print each number like a normal text file
  }

  file.close();
  return 0;
}
