/*
 * Jeremy Warner for Assignment 5, CSC 254, F2015
 * oset.h provides code for generic ordered sets.
 * main() tests this ordered set class.
 *
 * Since the lists are sorted, we can create O(N) solutions to intersection,
 * union, and difference operations between sets that are sorted the same way.
 *
 * If no comparator is given upon the oset's creation it uses the default '<',
 * to order elements in increasing order. Otherwise, the user can provide a
 * comparator function to sort the lists. An example of this is given is shown
 * below in the test code.
 * */


#include <iostream>
#include <string>
#include "oset.h"
using std::string;
using std::cout;
using std::cerr;
using std::endl;


// OSET Assert
int testno = 0;
void pass() {
    cout << "GOOD: passed test number " << ++testno << endl;}
    template<class T>
    void assert(T exp, T act) {
        if (exp != act) { // something strange is going on
            cerr << "FAILURE: failed test number " << ++testno << endl;
            cerr << "Expected (" << exp << "), got (" << act << ")" << endl;
            exit(1); // ERR AND DIE
        }
    }


// OSET Tester
template<class T>
void test(T expected[], oset<T>& OS) {
    int e = 0; // expected iterator for checking with primitive arrays
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i) {
        assert(expected[e], *i);
        e++; // check next
    } // tests have passed!
    pass();
}


// OSET Printer
template<class T>
void print(oset<T>& OS) {
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i)
        cout << *i << " ";
    cout << endl;
}


// Comparator definitions for testing
typedef int (*DoubleComparator)(double, double);
int sizeComp(double a, double b) { return a>=b? 1:0;}

typedef int (*StringComparator)(string, string);
int lengthComp(string a, string b) { return 1; }


// testing code for the oset class (ordered set)
int main() {
    // 1 | create an empty set, then add 4 and 3
    // + making sure it orders elements added in
    oset <int> A; A += 4; A += 3;
    int ta[]= {3, 4}; test(ta, A);

    // 2 | Create an empty set, then add 4 and 5
    oset <int> B; B += 4; B += 5;
    int tb[]= {4, 5}; test(tb, B);

    // 3 | Intersect the two sets A and B -> A = {4}
    A *= B; int taib[]= {4}; test(taib, A);

    // 4 | Difference the two sets A and B -> B = {5}
    B -= A; int tbda[]= {5}; test(tbda, B);

    // 5 | Union the two sets A and B -> B = {4, 5}
    B += A; int tbua[]= {4, 5}; test(tbua, B);

    // 6 | Inclusion - check set B{4,5} contains...
    assert(false, B[3]); assert(false, B[10]);
    assert(true, B[4]); assert(true, B[5]);
    pass(); // need to call manually

    // 7 | Copying constructor.
    A = B; test(tbua, A);

    // 8 | Create a double set, then add 4 and 3
    oset <double> C; (C += 4) += 3;
    double tc[]= {3, 4}; test(tc, C);

    // 9 | Make set w/ 6, then add 5 and 4
    // + testing removing fake elements
    oset <double> D(6); (D += 5) += 4;
    double td[]= {4, 5, 6}; test(td, D);
    D -= 10; D -= 20; D -= 30; D -= 40;

    // Program compiled and tested successfully!
    cout << "PASS: compiles and runs test successfully." << endl;
}

