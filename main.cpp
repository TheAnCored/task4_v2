#include "tree.hpp"

int main(){

    Point a(2.1, 5.2, 3.7);
    double edge = 3.5;

    Cube A(a, edge);

    A.print();

    Tree tree(2, a, 4);

    return  0;
}