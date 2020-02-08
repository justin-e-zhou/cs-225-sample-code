<<<<<<< HEAD
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
=======

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
>>>>>>> 0d7c4e002b0619e816ecbbdc8e6847ed8320a6dc
