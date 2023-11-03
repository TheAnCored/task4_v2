#include <iostream>
#include <memory>
#include <limits>
#include <cmath>
#include <stdio.h>

// Space have size is 3
// Points in R3
class Point{
public:
    // Coordinates of one point
    std::unique_ptr<double[]> coord_;

    // Empty constructor
    Point();

    // Constructor with three coordinates
    Point(double, double, double);

    // Copy constructor
    Point(const Point&);

    // Operator [] for easy-way to use <point>[]
    double& operator[](int);

    // For const type
    double& operator[](int index) const;

    // Operator= for use <point1> = <point2>
    Point& operator=( const Point& );

    // Operator ==
    bool operator==(const Point&);

    void print();

    void out(FILE*);
};

// Cubes in R3
class Cube{
private:
    // The array of the vertexes of the cube
    std::unique_ptr<Point[]> vert_;

public:
    // The edge of the cube
    double edge_;

    // The center of the cube( it is the intersection point of the diagonal of the cube)
    Point center_;


    // Empty constructor
    Cube();

    // Constructor with array of its vertexes
    Cube(std::unique_ptr<Point[]>);

    // COnstructor with central point and edge of cube
    Cube(Point, double);


    // Copying constructor
    Cube(Cube&);

    // Operator [] for easy-way to use its vertexes
    Point& operator[](int);

    // For const type
    Point& operator[](int index) const;

    // Operator= for copying cubes
    Cube& operator=(const Cube&);


    // Check point
    bool IsInside(Point);

    // Print cube
    void print();

    void out(FILE*);
};

class Node{
private:
    // Cube for node
    Cube cube_;

    // Descendants of this node
    std::unique_ptr<Node[]> desc_;

    // Depth level
    unsigned int level_;
public:
    // // Array of points and its amount
    std::unique_ptr<Point[]> points_;

    // Amount of points in the cube
    unsigned int amount_;

    // General field with maximal level of tree
    static unsigned int max_level_; 

    // Empty constructor
    Node();

    // Depth level
    Node(unsigned int, Point, double);

    // Copying constructor
    Node(const Node&);

    // Operator =
    Node& operator=(const Node&);

    //Operator []
    Node& operator[](int);
    // For const type
    Node& operator[](int) const;

    // AppPoint is a function that include given point in the tree
    void AppPoint(Point);
    void AppPoint(double, double, double);

    // Delete point from arrays
    void DeletePoint(Point);
    void DeletePoint(double, double, double);

    // Print functions
    void print();
    void print_subtree();
    
    void out(FILE*);
};


class Tree{
public:

    // Root cube
    std::unique_ptr<Node> root_;

    // Maximal amount of levels
    unsigned int max_level_;

    // Empty constructor
    Tree();

    // Constructor with max_level, center of root_cube and its edge
    Tree(unsigned int, Point, double);

    void AppPoint(Point point){ this->root_->AppPoint(point);}
    void AppPoint(double x, double y, double z){ this->root_->AppPoint(x,y,z);}

    void DeletePoint(Point point){ this->root_->DeletePoint(point);}
    void DeletePoint(double x, double y, double z){ this->root_->DeletePoint(x,y,z);}

    void print();
    void out(FILE*);
};