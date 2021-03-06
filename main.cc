/*
 * Jeremy Warner for Assignment 5, CSC 254, F2015
 * oset.h provides code for generic ordered sets.
 * main() tests this ordered set class.
 * see readme and comments for details.
 * */


#include <algorithm>
#include <iostream>
#include <string>
#include "oset.h"
using std::transform;
using std::string;
using std::cout;
using std::cerr;
using std::endl;


// Comparator definitions for testing
// Int comparison (increasing order)
int intComp(int a, int b) { return a-b; }

// Double comparison (increasing order)
int doubleComp(double a, double b) { return (int)a-b; }

// String case sensitive comparator (dont convert)
int caseComp(string a, string b) { return a.compare(b); }

// String case in-sensitive comparator (convert)
int alphaComp(string a, string b) { // convert to lower
    transform(a.begin(), a.end(), a.begin(), ::tolower);
    transform(b.begin(), b.end(), b.begin(), ::tolower);
    return a.compare(b);
}


// testing code for the oset class (ordered set)
int main() {
    // 1 | create an empty set, then add 4 and 3
    // + making sure it orders elements added in
    oset <int> A(&intComp); A += 4; A += 3;
    int ta[]= {3, 4}; test(ta, A);

    // 2 | Create an empty set, then add 4 and 5
    oset <int> B(&intComp); B += 4; B += 5;
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

    // 7 | Copying constructor
    A = B; test(tbua, A);

    // 8 | Create a double set, then add 4 and 3 {3, 4}
    oset <double> C(&doubleComp); (C += 4) += 3;
    double tc[]= {3, 4}; test(tc, C);

    // 9 | Make set w/ 6, then add 5 and 4 {4, 5, 6}
    // + testing removing fake elements
    oset <double> D(6, &doubleComp); (D += 5) += 4;
    D -= 10; D -= 20; D -= 30; D -= 40;
    double td[]= {4, 5, 6}; test(td, D);

    // 10 | Union of a double set -> 3456
    C += D; double tduc[]= {3, 4, 5, 6}; test(tduc, C);

    // 11 | Difference of a double set -> 3
    C -= D; double tcdd[]= {3}; test(tcdd, C);

    // 12 | String ordering
    oset <string> E(&caseComp); E += "yo"; E += "hi";
    string te[] = {"hi", "yo"}; test(te, E);

    // 13 | String case ordering
    oset <string> F(&caseComp); F += "hai"; F += "YO";
    string tf[] = {"YO", "hai"}; test(tf, F);

    // 13 | String case insensitive ordering
    oset <string> G(&alphaComp); G += "haii"; G += "YO";
    string tg[] = {"haii", "YO"}; test(tg, G);

    // extra test somewehere, things pass to easy
    // also, write up your readme and submit this shit
    // 14 | String union - same comparator
    E += F; string teuf[]= {"YO", "hai", "hi", "yo"}; test(teuf, E);

    // 15 | String intersect - different comparators (case sensitive)
    F += "haii"; // add a word so you can see the different ordering
    F *= G; string tfig[]= {"YO", "haii"}; test(tfig, F);

    // 16 | String difference - different comparators (case insensitve)
    E -= "YO"; G += "Diff"; // remove a word to see different ordering
    G -= E; string tgde[]= {"Diff", "haii", "YO"}; test(tgde, G);

    // Program compiled, ran and tested successfully!
    cout << "PASS: compiles and runs tests successfully." << endl;

    /*
    cout << "Ending set data:" << endl;
    print(A); print(B); print(C); print(D);
    print(E); print(F); print(G);
     */
}

