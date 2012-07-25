/*
 * =====================================================================================
 *
 *       Filename:  mvp.cc
 *
 *    Description:  the most vexing parse
 *
 *        Version:  1.0
 *        Created:  25/07/12 19:19:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  David Irvine (MaidSafe), david.irvine@maidsafe.net
 *   Organization:  
 *
 * =====================================================================================
 */
#include <iostream>

 struct A { }; 
 struct B { 
   B(A a) { 
   std::cout << "B ctor\n"; 
   } 
 }; 
int main() {
// this will not print anything  
  B b(A());
// the fix is uniform initialisation 
  B c(A{});
  // this is an extended initialiser list and may nto be available on your compiler 
//  B d{A{}};
  return 0;
}

