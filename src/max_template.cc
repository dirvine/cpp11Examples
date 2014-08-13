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

#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

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
 
TEST_CASE("Max templates", "[max]") {
  CHECK(6 == ::max(2, 5, 6));  
  CHECK(5 == ::max(2, 5));

  /*-----------------------------------------------------------------------------
   *  Cannot be deduced from template or arg deduction
   *-----------------------------------------------------------------------------*/
//  std::cout << "::max('a', 5, 6)" <<  ::max('a', 5, 6) << " \n"; // ERROR 
  /*-----------------------------------------------------------------------------
   *  Cannot be deduced from template or arg deduction
   *-----------------------------------------------------------------------------*/
  // std::cout << "::max(5, 6, 'a')" <<  ::max(5, 6, 'a') << " \n"; // ERROR 
  CHECK('b' == ::max('a', 'b'));
  CHECK('a' == ::max('a', 4));
  //CHECK(3.14 == ::max<double>(2, 3.14));
  //CHECK(3.14 == ::max(2, 3.14));
  //CHECK(3.14 == ::max(3.14, 2));
}

