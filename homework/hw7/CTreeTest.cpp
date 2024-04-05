#include "CTree.h"
#include <string>
#include <cassert>
#include <iostream>
#include <sstream>

using std::cout;
using std::endl;

class CTreeTest {
public:
/* toString() and the destructor are called/tested throughout this file:
 * 1) the toString() function should create and return a
 * string of all the elements in the nodes of the tree, separated by
 * newline characters. The ordering of the nodes must be determined by
 * a depth-first pre-order traversal from the root node
 * 2) the destructor should clear all the children of the current node and all the
 * siblings to the right of the current node, freeing the dynamically
 * allocated memory. (Hint: use recursion!)
 */


/* Constructor:
 * "A constructor that is passed the character to store in the root
 * node of a new tree.
 */
    static void testConstructor() {
        // build a few trees with constructor
        CTree* t1 = new CTree('A');
        assert(t1->toString() == "A\n");
        CTree* t2 = new CTree('b');
        assert(t2->toString() == "b\n");
        CTree* t3 = new CTree('^');
        assert(t3->toString() == "^\n");
	    delete t1;
	    delete t2;
	    delete t3;
    }


/* Test adding children and siblings:
 * "An 'addChild' function, which is passed the character data to be
 * stored in the child. This function returns false if it fails
 * (because the data is already a child of this tree node) and true if
 * it succeeds. Remember that it must keep the children ordered."
 *
 * "An 'addSibling' function, which is passed the data to be stored in
 * a new sibling node. This function returns false if it fails
 * (because the data is already a sibling t * o the right of this tree
 * node) and true if it succeeds. Remember that siblings must always
 * be ordered. (This * function is really just a helper function for
 * addChild, but keeping it public will let us test it easily.)"
 */
  static void testAdd() {
    // A
    CTree* t1 = new CTree('A') ;
    assert(t1->toString() == "A\n");

    // A
    // |
    // b
    assert(t1->addChild('b'));



    assert(t1->toString() == "A\nb\n");
    // can't add again
    assert(!t1->addChild('b'));
    assert(t1->toString() == "A\nb\n");

    // A
    // |
    // b - c
    assert(t1->addChild('c'));
    assert(t1->toString() == "A\nb\nc\n");
    // can't add again
    assert(!t1->addChild('c'));
    assert(t1->toString() == "A\nb\nc\n");


    // A
    // |
    // B - b - c
    assert(t1->addChild('B'));
    // 'B' comes before 'b'
    assert(t1->toString() == "A\nB\nb\nc\n");
    // can't add repeats
    assert(!t1->addChild('B'));
    assert(!t1->addChild('b'));
    assert(!t1->addChild('c'));
    assert(t1->toString() == "A\nB\nb\nc\n");


    // can't add 'A' as sibling of 'A'
    assert(!t1->addSibling('A'));
    assert(t1->toString() == "A\nB\nb\nc\n");

    // make sure that we can't add siblings to the root
    assert(!t1->addSibling('C'));
    assert(t1->toString() == "A\nB\nb\nc\n");




    // Adding in an already built subTree
    // First build another tree
    // R
    CTree* t2 = new CTree('R');

    assert(t2->toString() == "R\n");

    // R
    // |
    // C
    assert(t2->addChild('C'));
    assert(t2->toString() == "R\nC\n");


    // R
    // |
    // C - d
    assert(t2->addChild('d'));
    assert(t2->toString() == "R\nC\nd\n");
    // can't repeat
    assert(!t2->addChild('d'));
    assert(t2->toString() == "R\nC\nd\n");

    // R
    // |
    // B - C - d
    assert(t2->addChild('B'));
    assert(t2->toString() == "R\nB\nC\nd\n");
    // can't repeat
    assert(!t2->addChild('B'));
    assert(t2->toString() == "R\nB\nC\nd\n");

    // Add t1 in as a child
    // R
    // |
    // A - B - C - d
    // |
    // B - b - c

    // t1 is as before
    assert(t1->toString() == "A\nB\nb\nc\n");
    // add t1 to t2
    assert(t2->addChild(t1));
    // t1 should now have siblings
    assert(t1->toString() == "A\nB\nb\nc\nB\nC\nd\n");
    // t2 should be updated
    assert(t2->toString() == "R\nA\nB\nb\nc\nB\nC\nd\n");



    // R
    // |
    // @ - A - B - C - d
    //     |
    //     B - b - c
    assert(t2->addChild('@'));
    assert(t2->toString() == "R\n@\nA\nB\nb\nc\nB\nC\nd\n");
    // shouldn't be able to add duplicate children
    assert(!t2->addChild('@'));
    assert(!t2->addChild('A'));
    assert(!t2->addChild('B'));
    assert(!t2->addChild('C'));
    assert(!t2->addChild('d'));

    // R
    // |
    // @ - A - B - C - D - d
    //     |
    //     B - b - c
    assert(t2->addChild('D'));
    assert(t2->toString() == "R\n@\nA\nB\nb\nc\nB\nC\nD\nd\n");

    // R
    // |
    // @ - A - B - C - D - d - e
    //     |
    //     B - b - c
    assert(t2->addChild('e'));
    assert(t2->toString() == "R\n@\nA\nB\nb\nc\nB\nC\nD\nd\ne\n");
    delete t2;
  }

  // tests the caret operator
  // should behave the same as addChild. Unlike addChild, it
  // returns the resulting tree not a boolean
  static void testPlusOp() {
    CTree* t1 = new CTree('a');
    assert(t1->addChild('b'));
    assert(t1->addChild('c'));

    CTree* t2 = new CTree('d');
    assert(t2->addChild('e'));
    assert(t2->addChild('f'));
    // now test ^ operator to add t2 as a child to t1
    *t1 = *t1 + *t2;
    assert(t1->toString() == "a\nb\nc\nd\ne\nf\n");
    assert(t2->toString() == "d\ne\nf\n");
    delete t1;
  }
  // test << operator.
  // << operator should call toString to insert
  // the content of a tree into an output stream
  static void testOutputOp() {
    CTree* t1 = new CTree('a');
    assert(t1->addChild('b'));
    assert(t1->addChild('c'));
    assert(t1->addChild('d'));
    assert(t1->addChild('e'));
    assert(t1->addChild('f'));

    std::ostringstream o;
    o << *t1;
    assert(o.str() == t1->toString());
    delete t1;
  }


  // adds a single child
  static void testAddSimpleChild() {
    // A
    CTree* t1 = new CTree('A');
    assert(t1->toString() == "A\n");

    // A
    CTree* t2 = new CTree('A');
    assert(t2->toString() == "A\n");

    // A
    // |
    // A
    assert(t2->addChild(t1));
    assert(t2->toString() == "A\nA\n");
    delete t2;
  }
  // test == operator. It should return true if two CTrees match each other node
  // by node. This mean that the two CTrees should have identical structure and
  // the node values should be the same.
  static void testEqualityOp() {
    CTree* t1 = new CTree('a');
    assert(t1->addChild('b'));
    assert(t1->addChild('c'));
    assert(t1->addChild('d'));
    assert(t1->addChild('e'));
    assert(t1->addChild('f'));

    CTree* t2 = new CTree('a');
    assert(t2->addChild('b'));
    assert(t2->addChild('c'));
    assert(t2->addChild('d'));
    assert(t2->addChild('e'));
    assert(t2->addChild('f'));

    assert(*t1 == *t2);
    assert(*t1 == *t1);
    assert(*t2 == *t2);

    delete t1;
    delete t2;
  }

};


// call our test functions in the main
int main(void) {
    cout << "Testing CTree" << endl;
    CTreeTest::testConstructor();
    CTreeTest::testAdd();
    CTreeTest::testAddSimpleChild();
    CTreeTest::testPlusOp();
    CTreeTest::testOutputOp();
    CTreeTest::testEqualityOp();
    cout << "CTree tests passed" << endl;
}
