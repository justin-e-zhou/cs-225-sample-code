
/* Your code here! */
#pragma once
#include <vector>
#include <map>

using std::vector;

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
