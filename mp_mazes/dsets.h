/* Your code here! */
#pragma once
#include <vector>
#include <map>

using std::vector;

// A disjoint set class which uses a Node struct 
// that tracks the size of the set and the next
// element in the set.
class DisjointSets
{
    public:
        void addelements(int);
        int find(int);
        void setunion(int,int);
        int size(int);
        struct Node {
            int data;
            int size;
            Node* next;
            Node(int elem) {
                data = elem;
                next = nullptr;
                size = 1;
            }
        };
    private:
        vector<Node> contents;

};
