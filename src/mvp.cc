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
#define CATCH_CONFIG_MAIN 
#include "catch.hpp"

 struct A { }; 
 struct B { 
   B(A /* a */) { 
   printf("stuff"); 
   } 
 }; 
TEST_CASE("most vexing parse", "mvp") {
// this will not print anything  
//   CHECK(1 == B b(A()));
// // the fix is uniform initialisation 
//   CHECK(1 == B c(A{}));
//   // this is an extended initialiser list and may nto be available on your compiler 
//   CHECK(1 == B d{A{}});
}

