<<<<<<< HEAD
/* Your code here! */
#include <iostream>
#include <stdio.h>
#include "dsets.h"


void DisjointSets::addelements(int n) {
    for (int i = 0; i < n; ++i) {
        contents.push_back(Node(contents.size()));
    }
}

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

int DisjointSets::size(int el) {
    return contents[find(el)].size;
}
=======
/* Your code here! */
#include <iostream>
#include <stdio.h>
#include "dsets.h"


void DisjointSets::addelements(int n) {
    for (int i = 0; i < n; ++i) {
        contents.push_back(Node(contents.size()));
    }
}

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

int DisjointSets::size(int el) {
    return contents[find(el)].size;
}
>>>>>>> 0d7c4e002b0619e816ecbbdc8e6847ed8320a6dc
