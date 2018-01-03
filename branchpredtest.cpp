//g++ -std=c++11 branchpredtest.cpp -o branchpredtest

#include <iostream>
#include <random>
#include <chrono>
#include <algorithm>


uint32_t count(const std::vector<uint32_t>& vec, uint32_t cut)
{
  uint32_t r=0;
  for (const auto& a: vec) {
    if (a>cut) r+=1;
  }
  return r;
}


void measure(const std::vector<uint32_t>& vec, uint32_t cut)
{
  auto start = std::chrono::steady_clock::now();
  auto r = count(vec, cut);
  auto end = std::chrono::steady_clock::now();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start).count();

  std::cout << " result = " << r << " duration = " << duration << " ns" <<std::endl;
}


int main(int argc, char** argv)
{
  if (argc != 2) {
    std::cout << "Usage: " << argv[0] << " size " << std::endl;
    return 0;
  }
  const uint32_t size = atoi(argv[1]);

  const uint32_t mmin = 0, mmax = 10000, mcut = 5000;

  
  std::random_device rd;  
  std::mt19937 generator(rd()); 
  std::uniform_int_distribution<uint32_t> distribution(mmin, mmax);
							  

  std::vector<uint32_t> vec(size);
  std::generate(vec.begin(), vec.end(), [&](){return distribution(generator);});
  

  std::cout << "Unsorted add:";
  measure(vec, mcut);
  std::cout << "Unsorted add:";
  measure(vec, mcut);
  
  std::sort(vec.begin(), vec.end());
  
  std::cout << "Sorted add  :";
  measure(vec, mcut);
  std::cout << "Sorted add  :";
  measure(vec, mcut);



}
