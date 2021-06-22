#ifndef UTILS_H
#define UTILS_H
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

namespace utils{
struct data {
    float batchIdx = 0.0f;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    float cls = 0.0f;
    float reg[3];
};

struct point{
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
};

struct point2d{
    float x = 0.0f;
    float y = 0.0f;
public:
    point2d(const float& x_i, const float& y_i):x(x_i), y(y_i) {}
};
std::vector<utils::data> ReadKittiBinByPath(const std::string & path);

template<class T>
T* FindRootNode(T* p1, T* p2)
{
    if (p1->parent != p2) {
        p1->parent = FindRootNode(p1->parent, p2->parent);
    }
    return p1->parent;
}

template<class T>
T* FindRootNode(T* p)
{
    T* nodeTmp = p->parent;
    if (p->parent == nodeTmp) {
        return nodeTmp;
    }
    T* root = FindRootNode(p, p->parent);
    p->parent = root;
    p->parent = root;
    return root;
}

template<class T>
void JointUnionNode(T* node1, T* node2)
{
    node1 = FindRootNode(node1);
    node2 = FindRootNode(node2);
    if (node1 == node2) {
        return;
    }
    if (node1->rank < node2->rank) {
        node1->parent = node2;
    } else if(node2->rank < node1->rank) {
        node2->parent = node1;
    } else {
        node1->parent = node2;
        node2->rank++;
    }
}
};
#endif