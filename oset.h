// guard against multiple includes
#ifndef _oset_h
#define _oset_h
// needed for NULL
#include <stddef.h>


template<typename T, typename C> // type T, comparator C
class oset {
    class node {
        public:
            const T val;
            node *next;
            node(T v): val(v), next(NULL) {}
    };

    node head;   // this node avoids several special cases in the methods below
    node beyond; // to simplify iterator.

    //--------------------------------------------------------- Iterator support
    public:
    class iter {
        node *pos;          // node _before_ the one with this->operator*
        // constructor is private:
        iter(node* n) : pos(n) { }
        friend class oset;      // so oset can call the (private) constructor
        public:
        const T& operator*() {
            return pos->next->val;
        }
        // support forward iteration.  This is prefix version (++p).
        iter& operator++() {
            if (pos != NULL) pos = pos->next;
            return *this;
        }
        // and this is the postfix version (p++).
        // Note that it returns a copy, _not_ a reference.
        iter operator++(T) {
            iter rtn = *this;
            if (pos != NULL) pos = pos->next;
            return rtn;
        }
        bool operator==(iter other) {return pos->next == other.pos->next;}
        bool operator!=(iter other) {return pos->next != other.pos->next;}
    };

    //--------------------------------------------------------- Set endpoints
    private:
    iter start;         // initialized in the constructors below
    iter finish;        // initialized in the constructors below

    //-------------------------------------------------------- Endpoint readers
    public:
    iter begin() { return start; }
    iter end() { return finish; }

    //-------------------------------------------------------- The Constructor
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
    node* find_prev(const T v);
    oset& operator=(oset& other);
    oset& operator+=(const T v);
};

#endif
