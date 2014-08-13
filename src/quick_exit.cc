// /*
//  * =====================================================================================
//  *
//  *       Filename:  quick_exit.cc
//  *
//  *    Description:  iquick exit example
//  *
//  *        Version:  1.0
//  *        Created:  29/07/12 13:13:05
//  *       Revision:  none
//  *       Compiler:  gcc
//  *
//  *         Author:  David Irvine (MaidSafe), david.irvine@maidsafe.net
//  *   Organization:  
//  *
//  * =====================================================================================
//  */
// #include <iostream>
// #include <cstdlib>
// 
// struct C {
//     C() { std::cout << "Making a C\n"; }
//     ~C() { std::cout << "Destroying a C\n";}
// };
// 
// C c;
// 
// void foo() {
//     std::cout << "Exiting!\n";
// }
// 
// int main() {
//     at_quick_exit(foo);
//     // std::atexit(foo);
//     //This would destroy c
//     //exit(0);
//     //This does not
//     quick_exit(0);
// }
