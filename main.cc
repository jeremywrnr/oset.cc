/*
 * Jeremy Warner for assn 5, CSC 254, F2015
 * Provides code for generic ordered sets.
 * main() tests this ordered set class.
 * */


#include <iostream>
#include <string>
#include "oset.h"
using std::cout;
using std::cerr;
using std::endl;
using std::flush;
using std::string;


// OSET Tester
int testno = 0;
template<class T>
void test(T expected[], oset<T>& OS) {
    int e = 0; // expected iterator for checking with primitive arrays
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i) {
        if (expected[e] != *i) {
            cerr << "FAILURE, expected (" << expected[e] << "), but got ("
                << *i << "). Exiting." << endl;
            exit(1); // ERR AND DIE
        } e++; // check next
    }
    testno++;
    cout << "GOOD: passed test number " << testno << endl;
}


// OSET Printer
template<class T>
void print(oset<T>& OS) {
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i)
        cout << *i << " ";
    cout << endl;
}


// Comparator definitions for testing
typedef int (*IntComparator)(int, int);
int primeComp(int a, int b) { return 1; }
int sizeComp(int a, int b) { return 1; }

typedef int (*FloatComparator)(float, float);
int decimalComp(float a, float b) { return 1; }
int sizeComp(float a, float b) { return 1; }

typedef int (*StringComparator)(string, string);
int lengthComp(string a, string b) { return 1; }
int alphaComp(string a, string b) { return 1; }


// testing code for the oset class (ordered set)
int main() {
    // create an empty set, then add 4 and 3
    // make sure it orders elements added in
    oset <int> A; A += 4; A += 3;
    int ta[]= {3, 4}; test(ta, A);

    // create an empty set, then add 4 and 5
    oset <int> B; B += 4; B += 5;
    int tb[]= {4, 5}; test(tb, B);

    // Program compiled and tested successfully!
    cout << "PASS: compiles and runs test successfully." << endl;
}





















/*
// EXTRA SCOTT TESTING
cout << S[3] << " ";            // should print 1 (true) : 3 is in S
S += 3;                         // should be a no-op
cout << S[5] << endl;           // should print 0 (false) : 5 not in S
(S += 5) += 7;
print(S);                       // should print 3 5 7
oset <int> T(3);                // singleton
print(T);                       // should print 3
oset <int> U(S);                // copy of S
oset <int> V(S);                // copy of S
oset <int> W;
W = S;  print(W);               // 3 5 7
S -= 4;                         // should be a no-op
S -= 3;
U -= 5;
V -= 7;
print(S);                       // 5 7
print(U);                       // 3 7
print(V);                       // 3 5
oset <int> A;
((A += 5) += 3) += 4; print(A); // 3 4 5
oset <int> B;
((B += 6) += 5) += 7; print(B); // 5 6 7
oset <int> AuB(A);
AuB += B;  print(AuB);          // 3 4 5 6 7
oset <int> AmB(A);
AmB -= B;  print(AmB);          // 3 4
oset <int> AiB(A);
AiB *= B;  print(AiB);          // 5
*/
