#include "tree.hpp"


// Global area
unsigned int Node::max_level_ = 0; //

int main(){

    Point a(0, 0, 0);
    double edge = 20;
    unsigned int levels = 3; 
   
    Cube A(a, edge);

    Tree tree(levels , a, edge);

    //cout<<" Amount of levels is: "<< Node::max_level_<<endl;
    // For check the tree
    // tree.print();

    return  0;
}