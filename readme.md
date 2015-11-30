csc 453 - templates assignment
==============================


jeremy warner | jwarn10
november 25 2015


## running
This will compile and run my submission:

    make


## files
```
.
├── Makefile   - script to compile src
├── main.cc    - oset testing main file
├── oset.h     - oset class definition
└── readme.md  - project description
```

0 directories, 4 files


## generic ordered sets
Since the lists are sorted, we can create O(n) solutions to intersection,
union, and difference operations between sets that are sorted the same way. The
programmer can provide a comparator function to sort the lists. An example of
this is given is shown below in the test code. If a list is copied, then the
comparator from the last list is used.


## features
there are oset testing and printing methods at the bottom of `oset.h`. no extra
credit was performed for this assignment. all required features for this
assignment were completed and tested, including:


#### O(n) rewrite of union, difference, and intersection
Like the merge in merge sort, we can take advantage ofthe fact that both lists
are sorted when we are performing these operations on our set, making sure that
we do not have to look at any node more than twice.

#### supporting generics through templates
This oset class is generic, and supports arbitrary types that have a ==
operator and a comparator than is passed into the constructor of the oset.
It was tested on ints, doubles and strings.

#### explicit comparator support
ordering of T was made explicit by passing in a function to the set constructor
that you want to order the elements of your set with. Strings with case
sensitive and case insensitive comparators were tested, near the bottom of
main. The comparators are called caseComp and alphaComp, for the case sensitive
and case insensitive comparators respectively.

#### different comparator support
The linear-time routines created for union, difference, and intersection check
to see if the comparator functions of the two sets are the same. If they are
not, it cannot assume that they are ordered the same way, and thus resorts back
to the O(n^2) implementation that was originally given to us.

