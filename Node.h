/* Jesus Galindo*/

#ifndef NODE_
#define NODE_
#include <iostream>
#include <string>

using namespace std;


//Binary Tree Node
template <typename DATATYPE, typename KEYTYPE>
class Node 
{
private:
    KEYTYPE key;
    DATATYPE data; 
    Node* left;
    Node* right;
    Node* parent;
public:
    Node() { key = -1; left = nullptr; right = nullptr; parent = nullptr; };
    void setData(DATATYPE adata) { data = adata; };
    void setKey(KEYTYPE aKey) { key = aKey; };
    void setLeft(Node* aLeft) { left = aLeft; };
    void setRight(Node* aRight) { right = aRight; };
    void setParent(Node* aParent) { parent = aParent; };
    DATATYPE Data() { return data; }; 
    KEYTYPE Key() { return key; };
    Node* Left() { return left; };
    Node* Right() { return right; };
    Node* Parent() { return parent; };

};
#endif