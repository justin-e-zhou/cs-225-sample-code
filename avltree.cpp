/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->right;
    t->right = temp->left;
    temp->left = t;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node* temp = t->left;
    t->left = temp->right;
    temp->right = t;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
int AVLTree<K, V>::balance(const Node* subRoot) {
    return heightOrNeg1(subRoot->right) - heightOrNeg1(subRoot->left);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if(!subtree) {
        return;
    }
    if(balance(subtree) == 2) {
        if(balance(subtree->right) == 1) {
            rotateLeft(subtree);
        }
        else {
            rotateRightLeft(subtree);
        }
    }
    else if(balance(subtree) == -2) {
        if(balance(subtree->left) == -1) {
            rotateRight(subtree);
        }
        else {
            rotateLeftRight(subtree);
        }
    }
    setHeights(subtree);
}

template <class K, class V>
int AVLTree<K, V>::setHeights(Node* subRoot) {
    if(!subRoot) {
        return 0;
    }
    int left = setHeights(subRoot->left);
    int right = setHeights(subRoot->right);

    if(left > right) {
        subRoot->height = left;
        return left + 1;
    } 
    else {
        subRoot->height = right;
        return right + 1;
    }
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    insert(root, key, value);
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if(!subtree) {
        subtree = new Node(key, value);
    }
    else if(key < subtree->key) {
        insert(subtree->left, key, value);
    }
    else if(key > subtree->key) {
        insert(subtree->right, key, value);
    }
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    remove(root, key);
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    if (subtree == NULL)
        return;
    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            delete subtree;
            subtree = NULL;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            Node* prev = subtree;
            while(temp->right) {
                if(temp->right) {
                    if(!temp->right->right) {
                        prev = temp;
                    }
                }
                temp = temp->right;
            }
            swap(subtree, temp);
            prev->right = temp->left;
            temp->left = NULL;
            delete temp;
            temp = NULL;
        } else {
            /* one-child remove */
            // your code here
            if(!subtree->left) {
                swap(subtree, subtree->right);
                Node* temp = subtree->right;
                subtree->right = temp->right;
                subtree->left = temp->left;
                temp->left = NULL;
                temp->right = NULL;
                delete temp;
                temp = NULL;
            }
            else {
                swap(subtree, subtree->left);
                Node* temp = subtree->left;
                subtree->left = temp->left;
                subtree->right = temp->right;
                temp->left = NULL;
                temp->right = NULL;
                delete temp;
                temp = NULL;
            }
            rebalance(subtree);
        }
        // your code here
        rebalance(subtree);
    }
    rebalance(subtree);
}
