/*
 * Jeremy Warner for assn 5, CSC 254, F2015
 * Provides code for generic ordered sets.
 * main() tests this ordered set class.
 * */


#include <iostream>
#include <string>
#include "oset.h"
using std::cout;
using std::endl;
using std::flush;
using std::string;


//void print(oset& OS) {
//for (oset::iter i = OS.begin(); i != OS.end(); ++i)
//cout << *i << " ";
//cout << endl;
//}


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

    oset <int, int> S;                 // create an empty set
    cout << "PASS: compiled successfully!" << endl;














    /*
       S += 3;     // now should contain 3

       cout << S[3] << " ";            // should print 1 (true) : 3 is in S
       S += 3;                         // should be a no-op
       cout << S[5] << endl;           // should print 0 (false) : 5 not in S

       (S += 5) += 7;
       print(S);                       // should print 3 5 7

       oset T(3);                      // singleton
       print(T);                       // should print 3

       oset U(S);                      // copy of S
       oset V(S);                      // copy of S

       oset W;  W = S;  print(W);      // 3 5 7

       S -= 4;                         // should be a no-op
       S -= 3;
       U -= 5;
       V -= 7;
       print(S);                       // 5 7
       print(U);                       // 3 7
       print(V);                       // 3 5

       oset A;  ((A += 5) += 3) += 4;  print(A);       // 3 4 5
       oset B;  ((B += 6) += 5) += 7;  print(B);       // 5 6 7

       oset AuB(A);  AuB += B;  print(AuB);            // 3 4 5 6 7
       oset AmB(A);  AmB -= B;  print(AmB);            // 3 4
       oset AiB(A);  AiB *= B;  print(AiB);            // 5
       */
}
