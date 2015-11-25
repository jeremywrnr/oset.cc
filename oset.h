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
        node *o = other.head.next;
        comp = other.comp;
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
    node* find_prev(const T v) { return find_prev(v, &head); }


    //-------------------------------------------------------- Assignment
    // make a new ordered set, overwriting
    //
    oset& operator=(oset& other) {
        clear(); // then do union
        for (iter i = other.begin(); i != other.end(); ++i)
            operator+=(*i);
        return *this;
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
    oset& operator+=(const T v) { // default, use find prev to get node
        node* p = find_prev(v); // get * to item, check if included
        if (p->next == NULL || p->next->val != v) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        } return *this;
    }

    private:
    // pass in the node to insert onto
    node* append(const T v, node* p) {
        node* n = new node(v);
        n->next = NULL;
        p->next = n;
        return n;
    }


    //-------------------------------------------------------- Union
    // helper method for checking if more nodes exist in set
    int more(node *p) { return (p->next != NULL); }

    // the actual oset union method
    public:
    oset& operator+=(oset& other) {
        if(comp == other.comp) { // same ordering -> O(n) solution

            oset temp1(comp); // make a copy of ours
            node* tmphead1 = &temp1.head;
            for (iter i = begin(); i != end(); ++i)
                append(*i, tmphead1);

            oset temp2(comp); // making a copy of theirs
            node* tmphead2 = &temp2.head;
            for (iter i = other.begin(); i != other.end(); ++i)
                append(*i, tmphead2);

            clear(); // empty out the current list
            node* tail = &head; // point currenthead

            // go til end of one list, continue
            iter i = temp1.begin();
            iter j = temp2.begin();
            while (i != temp1.end() && j != temp2.end()){

                if (*i == *j) { // same element, add, move both
                    tail = append(*i, tail);
                    i++;
                    j++;
                } else { // not equal, check which one to add next
                    if (comp(*j, *i)) { // append, shift l
                        tail = append(*i, tail);
                        i++;
                    } else { // append, then shift right side
                        tail = append(*j, tail);
                        j++;
                    }
                }
            }

            // flush out the rest of the list into output
            while (i != temp1.end()){ tail = append(*i, tail); i++; }
            while (j != temp2.end()){ tail = append(*j, tail); j++; }

        } else { // different comparators, we must xcheck each element O(n^2)
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
        clear(); // clear, do basic union call
        for (iter i = temp.begin(); i != temp.end(); ++i)
            operator+=(*i);
        return *this; // temp is DESTROYED
    }
};


//--------------------------------------------------------------------- Helpers
// mosty for testing / printing code in main
//
// OSET Printer
template<class T>
void print(oset<T>& OS) {
    for (typename oset<T>::iter i = OS.begin(); i != OS.end(); ++i)
        cout << *i << " ";
    cout << endl;
}


// OSET Helper
int testno = 0;
void pass() { cout << "GOOD: passed test number " << ++testno << endl; }
template<class T>
void assert(T exp, T act) {
    if (exp != act) { // something strange is going on
        cerr << "FAILURE: failed test number " << ++testno << endl;
        cerr << "Expected (" << exp << "), got (" << act << ")" << endl;
        //exit(1); // ERR AND DIE
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


#endif
