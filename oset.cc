#include "oset.h"

// TODO make private
// find -- return true iff present:
template<typename T, typename C> // type T, comparator C
typename oset<T, C>::node* oset<T, C>::find_prev(const T v) {
    node* p = &head;
    while (true) {
        if (p->next == NULL) return p;
        if (p->next->val >= v) return p;
        p = p->next;
    }
}



/*
// assignment
oset& oset::operator=(oset& other) {
clear();
operator+=(other);      // union (see below)
}

oset& oset::operator+=(const T v) {
node* p = find_prev(v);
if (p->next == NULL || p->next->val != v) {
node* n = new node(v);
n->next = p->next;
p->next = n;
}
return *this;
}
*/



/*

   bool oset::operator[](const int v) {
   node* p = find_prev(v);
   return (p->next != NULL && p->next->val == v);
   }

// remove v if present; return ref to self
oset& oset::operator-=(const int v) {
node* p = find_prev(v);
node* t;
if ((t = p->next) != NULL && p->next->val == v) {
// already present
p->next = t->next;
delete t;
}
return *this;
}

// insert v if not already present; return ref to self

//--------------------------------------
// Union, intersection and difference.

// Union.
// *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
oset& oset::operator+=(oset& other) {
for (iter i = other.begin(); i != other.end(); ++i)
operator+=(*i);
return *this;
}

// Set difference.
// *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
oset& oset::operator-=(oset& other) {
for (iter i = other.begin(); i != other.end(); ++i)
operator-=(*i);
return *this;
}

// Intersection.
// *** THIS CODE HAS COST O(N^2).  IT SHOULD BE O(N).
oset& oset::operator*=(oset& other) {
oset temp;      // empty
for (iter i = begin(); i != end(); ++i)
if (other[*i]) temp+=(*i);
clear();
operator+=(temp);   // union
// NB: temp is destructed as we leave this scope
return *this;
}
*/
