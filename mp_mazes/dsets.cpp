/* Your code here! */

#include "dsets.h"

//Creates n unconnected root nodes at the end of the vector.
void DisjointSets::addelements(int num) {
    for (int i = 0; i < num; i++) {
        nodes.push_back(-1);
    }
}

//This function should compress paths and works as described in lecture.
int DisjointSets::find(int elem){
    if (nodes[elem] < 0) {
        return elem;
    }

    int root = find(nodes[elem]);
    nodes[elem] = root;
    return root;
}

/* 
 *This function should be implemented as union-by-size.

That is, when you setunion two disjoint sets, the smaller (in terms of number of nodes)
should point at the larger. This function works as described in lecture, except that you 
should not assume that the arguments to setunion are roots of existing uptrees.

our setunion function SHOULD find the roots of its arguments before combining the trees. 
If the two sets are the same size, make the tree containing the second argument point to 
the tree containing the first. (Note that normally we could break this tie arbitrarily, 
but in this case we want to control things for grading.)
* */
void DisjointSets::setunion(int a, int b) {
    int rootOne = find(a);
    int rootTwo = find(b);
    int newSize = (nodes[rootOne] + nodes[rootTwo]);

    if (nodes[rootOne] <= nodes[rootTwo]) {
        nodes[rootTwo] = rootOne;
        nodes[rootOne] = newSize;
    } else {
        nodes[rootOne] = rootTwo;
        nodes[rootTwo] = newSize;
    }
}

/* 
* This function should return the number of nodes in the up-tree containing the element.
* 
* @param elem - the elem whose size of the up-tree we are trying to find
* */
int DisjointSets::size(int elem) {
    int root = find(elem);
    return (-1 * (nodes[root]));
}

std::vector<int> DisjointSets::printNodes() {
    return nodes;
}