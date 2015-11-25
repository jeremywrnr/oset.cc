// guard against multiple includes
#ifndef _oset_h
#define _oset_h
#include <stddef.h>  // needed for NULL
#include <algorithm> // needed for lowercase
#include <string>    // needed for lowercasw
using std::string;
using std::cout;
using std::cerr;
using std::endl;


//----------------------------------------------------------------------- Type T
template<class T>
class oset {

    //-------------------------------------------------------- Set Element Class
    class node {
        public:
            const T val;
            node *next;
            node(T v): val(v), next(NULL) {}
    };

    node head; // this node avoids several special cases in the methods below
    node beyond; // to simplify iterator.


    //--------------------------------------------------------- Iterator support
    public:
    class iter {
        friend class oset; // let oset call (private) constructor
        node *pos; // node _before_ the one with this->operator*
        iter(node* n): pos(n) {} // constructor is private:
        public:
        const T& operator*() { return pos->next->val; }

        // support forward iteration. This is prefix version (++p).
        iter& operator++() {
            if (pos != NULL) pos = pos->next;
            return *this;
        }

        // and this is the postfix version (p++).
        // Note that it returns a copy, _not_ a reference.
        iter operator++(int) {
            iter rtn = *this;
            if (pos != NULL) pos = pos->next;
            return rtn;
        }

        bool operator==(iter other) {return pos->next == other.pos->next;}
        bool operator!=(iter other) {return pos->next != other.pos->next;}
    };


    //--------------------------------------------------------- Set endpoints
    private:
    iter start; // initialized in the constructors below
    iter finish; // initialized in the constructors below


    //-------------------------------------------------------- Endpoint readers
    public:
    iter begin() { return start; }
    iter end() { return finish; }


    //-------------------------------------------------------- The Constructor
    // handling the comparator
    typedef int (*orderer)(T, T);
    orderer comp;

    // new empty set, with a comparator passed in
    oset(int (*f)(T, T)) : head(0), beyond(0),
    start(&head), finish(&beyond) {
        //cout << "reached constructor" << endl;
        head.next = NULL;
        comp = *f;
    }

    // new singleton set, with a comparator passed in
    oset(T v, int (*f)(T, T)) : head(0), beyond(0),
    start(&head), finish(&beyond) {
        head.next = new node(v);
        comp = *f;
    }

    // copy constructor, use their constructor instead of passing in one
    oset(oset& other) : head(0), beyond(0), start(&head), finish(&beyond) {
        comp = other.comp;
        node *o = other.head.next;
        node *n = &head;
        while (o) {
            n->next = new node(o->val);
            o = o->next;
            n = n->next;
        } n->next = NULL;
    }


    //-------------------------------------------------------- The Destructor
    private:
    void clear() { // remove all nodes currently in the set
        node *n = head.next;
        while (n) {
            node* t = n->next;
            delete n;
            n = t;
        }
        head.next = NULL;
    }

    public:
    ~oset() { clear(); }


    //-------------------------------------------------------- Class Methods
    //
    //---------------------------------------------- Find (true iff present)
    // overloaded version, start at a specific node in the tree
    node* find_prev(const T v, node* p) {
        while (true) {
            if (p->next == NULL) return p; // reached end of list
            if (comp(p->next->val, v)) return p; // use class comparator
            p = p->next; // move onto the next element
        }
    }

    // original version, start at the head of the ordered set
    node* find_prev(const T v) {
        return find_prev(v, &head);
    }


    //-------------------------------------------------------- Assignment
    // make a new ordered set, overwriting
    //
    oset& operator=(oset& other) {
        clear(); // then do union
        return operator+=(other);
    }


    //-------------------------------------------------------- Includes
    // is the given element in this set?
    //
    bool operator[](const T v) {
        node* p = find_prev(v);
        return (p->next != NULL && p->next->val == v);
    }


    //-------------------------------------------------------- Insertion
    // insert v if not already present; return ref to self
    //
    oset& operator+=(const T v) {
        node* p = find_prev(v); // get * to item, check if included
        if (p->next == NULL || p->next->val != v) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        } return *this;
    }


    //-------------------------------------------------------- Union
    oset& operator+=(oset& other) {
        // take advantage of same ordering with O(n) solution
        if(comp == other.comp){
            for (iter i = other.begin(); i != other.end(); ++i)
                operator+=(*i);

        } else { // different comparators, we must check each element O(n)
            for (iter i = other.begin(); i != other.end(); ++i)
                operator+=(*i);
        } return *this;
    }


    //-------------------------------------------------------- Deletion
    // remove v if present; return ref to self
    //
    oset& operator-=(const T v) {
        node* p = find_prev(v);
        node* t;
        if ((t = p->next) != NULL && p->next->val == v) {
            // already present
            p->next = t->next;
            delete t;
        } return *this;
    }


    //-------------------------------------------------------- Difference
    oset& operator-=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i)
            operator-=(*i);
        return *this;
    }


    //-------------------------------------------------------- Intersection
    oset& operator*=(oset& other) {
        oset temp(comp); // empty, with old comp
        for (iter i = begin(); i != end(); ++i)
            if (other[*i]) temp+=(*i);
        clear();
        operator+=(temp); // union call
        return *this; // temp is DESTROYED
    }
};


//--------------------------------------------------------------------- Helpers
// mosty for testing / printing code in main
//
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


#endif
