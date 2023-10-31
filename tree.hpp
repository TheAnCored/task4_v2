#include <iostream>
#include <memory>
#include <limits>

using namespace std;

// Space have size is 3
// Points in R3
class Point{
private:
    // Coordinates of one point
    unique_ptr<double[]> coord_;

public:
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

    void print();
};

// Cubes in R3
class Cube{
private:
    // The array of the vertexes of the cube
    unique_ptr<Point[]> vert_;

public:
    // The edge of the cube
    double edge_;

    // The center of the cube( it is the intersection point of the diagonal of the cube)
    Point center_;

    // Empty constructor
    Cube();

    // Constructor with array of its vertexes
    Cube(unique_ptr<Point[]>);

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

    // Print cube
    void print();
};

class Node{
private:
    // Cube for node
    Cube cube_;

    // Descendants of this node
    unique_ptr<Node[]> desc_;

    // Depth level
    unsigned int level_;

public:
    // General field with maximal level of tree
    unsigned int max_level_; 

    // Empty constructor
    Node();

    // Depth level
    Node(unsigned int, unsigned int, Point, double);

    // Copying constructor
    Node(const Node&);

    // Operator =
    Node& operator=(const Node&);

    //Operator []
    Node& operator[](int);
    // For const type
    Node& operator[](int) const;

    void print(){ this->cube_.print(); }
};

class Tree{
private:
    // Root cube
    unique_ptr<Node> root_;

    // Maximal amount of levels
    unsigned int max_level_;

public:
    // Empty constructor
    Tree();

    // Constructor with max_level, center of root_cube and its edge
    Tree(unsigned int, Point, double);
};