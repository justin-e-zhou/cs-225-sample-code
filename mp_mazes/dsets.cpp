/* Your code here! */
#include <iostream>
#include <stdio.h>
#include "dsets.h"

// Add n disjoint elements to a set. This is stored
// in a vector of nodes.
void DisjointSets::addelements(int n) {
    for (int i = 0; i < n; ++i) {
        contents.push_back(Node(contents.size()));
    }
}

// Finds the base of the set given an element in
// the disjoint set.
int DisjointSets::find(int el) {
    Node* n = &contents[el];
    vector<Node*> path;
    path.push_back(n);
    while (n->next) {
        n = n->next;
        path.push_back(n);
    }
    path.pop_back();
    for (auto it = path.begin(); it != path.end(); it++) {
        (*it)->next = n;
    }
    return n->data;
}

// Unions two sets, with the larger set taking 
// priority in order to reduce brancing.
// If the two sizes are the same, element a takes
// priority.
void DisjointSets::setunion(int a, int b) {
    int lhN = find(a);
    int rhN = find(b);
    Node& A = contents[lhN];
    Node& B = contents[rhN];
    if (b > a) {
        A.next = &B;
        B.size += A.size;
        return;
    }
    B.next = &A;
    B.size += A.size;
}

// Finds the size of the set that contains el.
int DisjointSets::size(int el) {
    return contents[find(el)].size;
}
