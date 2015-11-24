// guard against multiple includes
#ifndef _oset_h
#define _oset_h
// needed for NULL
#include <stddef.h>


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
    // new empty set:
    oset() : head(0), beyond(0), start(&head), finish(&beyond) {
        head.next = NULL;
    }

    // new singleton set:
    oset(T v) : head(0), beyond(0), start(&head), finish(&beyond) {
        head.next = new node(v);
    }

    // copy constructor:
    oset(oset& other) : head(0), beyond(0), start(&head), finish(&beyond) {
        node *o = other.head.next;
        node *n = &head;
        while (o) {
            n->next = new node(o->val);
            o = o->next;
            n = n->next;
        }
        n->next = NULL;
    }


    //-------------------------------------------------------- The Destructor
    private:
    void clear() {
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
    node* find_prev(const T v) {
        node* p = &head;
        while (true) {
            if (p->next == NULL) return p;
            if (p->next->val >= v) return p;
            p = p->next;
        }
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
        node* p = find_prev(v); // get * to item
        if (p->next == NULL || p->next->val != v) {
            node* n = new node(v);
            n->next = p->next;
            p->next = n;
        }
        return *this;
    }


    //-------------------------------------------------------- Union
    oset& operator+=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i)
            operator+=(*i);
        return *this;
    }


    //-------------------------------------------------------- Removal
    // remove v if present; return ref to self
    //
    oset& operator-=(const T v) {
        node* p = find_prev(v);
        node* t;
        if ((t = p->next) != NULL && p->next->val == v) {
            // already present
            p->next = t->next;
            delete t;
        }
        return *this;
    }


    //-------------------------------------------------------- Difference
    oset& operator-=(oset& other) {
        for (iter i = other.begin(); i != other.end(); ++i)
            operator-=(*i);
        return *this;
    }


    //-------------------------------------------------------- Intersection
    oset& operator*=(oset& other) {
        oset temp; // empty
        for (iter i = begin(); i != end(); ++i)
            if (other[*i]) temp+=(*i);
        clear();
        operator+=(temp); // union call
        return *this; // temp is DESTROYED
    }
};

#endif
