// g++ operatoroverloading.cpp -o operatoroverloading
#include <iostream>
#include <cassert>
#include <cmath>

template <class T, unsigned int N>
class MyVec {
public:
  MyVec(std::initializer_list<T> c)
  {
    if (c.size() != N) throw std::invalid_argument("aaa");
    std::copy(c.begin(), c.end(), data);
  }
  MyVec(){;}
  ~MyVec(){}

  T get(unsigned int i) const
  {
    return data[i];
  }
  void set(unsigned int i, T x)
  {
    data[i] = x;
  }
  
  friend std::ostream& operator<<(std::ostream& os, const MyVec& v)
  {
    for (unsigned int i=0;i<N;i++) {
      os << v.get(i);
      if (i!=N-1) os << " ";
    }
    return os;
  }
  
  MyVec<T,N> operator+(const MyVec<T,N>& v) const
  {
    MyVec<T,N> result;
    for (unsigned int i=0;i<N;i++) result.set(i, data[i]+v.get(i));
    
    return result;
  }

  T operator*(const MyVec<T,N>& v) const
  {
    T result = 0;
    for (unsigned int i=0;i<N;i++) result += data[i]*v.get(i);
    return result;
  }

  double norm() const
  {
    double res=0.;
    for (unsigned int i=0;i<N;i++) res += data[i]*data[i];
    return sqrt(res);
  }
  
private:
  T data[N] = {0};
};


class MyVec3 : MyVec<double, 3>
{
public:

  MyVec3(std::initializer_list<double> c) : MyVec<double, 3>(c)
  {
  }
  
  double angle(const MyVec3& v) const
  {
    return acos(((*this)*v)/v.norm()/this->norm());
  }
};
  

typedef MyVec<int, 3> iVec3;

int main(int argc, char** argv)
{

  try {
    MyVec<double, 3> a({1., 2.});
  } catch(int n) {
    std::cerr << "blu" << std::endl;
  } catch (std::exception& e){
    std::cout << "hello" << std::endl;
  }
  
  //  MyVec<int, 3> vint({1, 4, 9});
  iVec3 vint({1, 4, 9});
  std::cout << vint << std::endl;

  MyVec<double, 3> v1({1, 2, 3});
  MyVec<double, 3> v2({3, 4, 6});
  
  auto v3 = v1 + v2;
  std::cout << v1 * v3 << std::endl;

  std::cout << vint + vint << std::endl;
  std::cout << vint * vint << std::endl;

  
  MyVec3 u1({1., 0., 0.});
  MyVec3 u2({0., 1., 0.});
  std::cout << "angle = " << u1.angle(u2) << std::endl;
  
  return 0;
}
