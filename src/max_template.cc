/*
 * =====================================================================================
 *
 *       Filename:  max_template.cc
 *
 *    Description:  simple template example
 *
 *        Version:  1.0
 *        Created:  25/07/12 19:56:01
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Irvine (MaidSafe), david.irvine@maidsafe.net
 *   Organization:  
 *
 * =====================================================================================
 */
/*-----------------------------------------------------------------------------
 *  OK not a c++11 thing this is template tests
 *-----------------------------------------------------------------------------*/

#include <iostream>

/*-----------------------------------------------------------------------------
 *  max of two int's
 *-----------------------------------------------------------------------------*/
inline int const& max(int const& a, int const& b) {
  return a < b ? b : a;
}

/*-----------------------------------------------------------------------------
 *  max of two values (that have < operator)
 *-----------------------------------------------------------------------------*/
template <typename T>
inline T const& max(T const& a, T const& b) {
  return a < b ? b : a;
}

/*-----------------------------------------------------------------------------
 *  max of 3 values (that have < operator)
 *-----------------------------------------------------------------------------*/
template <typename T>
inline T const& max(T const& a, T const& b, T const& c) {
  return ::max(::max(a, b), c);
}
 
int main() {
  std::cout << "::max(2, 5, 6) " <<  ::max(2, 5, 6) << " template for 3 args \n";  
  std::cout << "::max(2, 5) " <<  ::max(2, 5) << " nontemplate for 2 ints \n";  

  /*-----------------------------------------------------------------------------
   *  Cannot be deduced from template or arg deduction
   *-----------------------------------------------------------------------------*/
//  std::cout << "::max('a', 5, 6)" <<  ::max('a', 5, 6) << " \n"; // ERROR 
  /*-----------------------------------------------------------------------------
   *  Cannot be deduced from template or arg deduction
   *-----------------------------------------------------------------------------*/
  // std::cout << "::max(5, 6, 'a')" <<  ::max(5, 6, 'a') << " \n"; // ERROR 
  std::cout << "::max('a' , 'b') " <<  ::max('a', 'b') << "max<char> arg deduction \n";  
  std::cout << "::max('a' , 4) " <<  ::max('a', 4) << " nontemplate for 2 ints \n";  
  std::cout << "::max<double>(2, 3.14) " <<  ::max<double>(2, 3.14) << " no arg deduction \n";  
  std::cout << "::max(2, 3.14) " <<  ::max(2, 3.14) << " nontemplate 2 ints \n";  
  std::cout << "::max(3.14, 2) " <<  ::max(3.14, 2) << " nontemplate 2 ints \n";  
  return 0;
}

