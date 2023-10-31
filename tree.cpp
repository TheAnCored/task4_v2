#include "tree.hpp"


// ------------------POINT------------------
// Empty constructor
Point::Point(){
    this->coord_ = make_unique<double[]>(3);

    for(int i=0; i<3; i++){
        this->coord_[i] = 0.;
    }
}

// Constructor for <point>(x_, y_, z_)
Point::Point(double x_, double y_, double z_){
    this->coord_ = make_unique<double[]>(3);

    this->coord_[0] = x_;
    this->coord_[1] = y_;
    this->coord_[2] = z_;
}

// Copy constructor
Point::Point(const Point& second){

    this->coord_ = make_unique<double[]>(3);

    for(int i=0; i<3; i++){
        this->coord_[i] = second.coord_[i];
    }
}

// Operator [] for easy-way to use <point>[]
double& Point::operator[](int index){ return this->coord_[index]; }

// Operator [] for const type
double& Point::operator[](int index) const { return this->coord_[index]; }

// Operator = for equals <point1> = <point2>
Point& Point::operator=(const Point& second){
    
    if(this != &second){
        for(int i=0; i<3; i++){
            this->coord_[i] = second[i];
        }
    }

    return *this;
}

// Print method
void Point::print(){
    for(int i=0; i<3; i++){
        if(i==0){ cout<<" ("<< this->coord_[i]<<", "; }
        else if(i==1){ cout<< this->coord_[i]<<", "; }
        else{ cout<< coord_[i]<<")\n"<<endl;}
    }
}
// -----------------------------------------


// ------------------CUBE-------------------

// Empty constructor
Cube::Cube(){
    this->center_ = Point(0,0,0);
    this->vert_ = make_unique<Point[]>(8);

    this->edge_ = 0;
}

// Contructor with center of cube and its edge
Cube::Cube(Point center_, double edge_){

    this->center_ = center_;
    this->edge_ = edge_;

    this->vert_ = make_unique<Point[]>(8);

    this->vert_[0] = center_;
    this->vert_[7] = center_;

    for(int i=0; i<3; i++){
        this->vert_[0][i] -= edge_/2;
        this->vert_[7][i] += edge_/2;
    }

    for(int i=0; i<3; i++){
        this->vert_[i+1] = this->vert_[0];
        this->vert_[i+4] = this->vert_[7];

        this->vert_[i+1][i] += edge_;
        this->vert_[i+4][i] -= edge_;
    }
}

// Copy constructor
Cube::Cube(Cube& second){
    this->vert_ = make_unique<Point[]>(8);
    this->edge_ = second.edge_;
    this->center_ = second.center_;

    for(int i=0; i<8; i++){
        this->vert_[i] = second[i];
    }
}

// Operator [] for easy-way to use its vertexes
Point& Cube::operator[](int index){
    return this->vert_[index];
}
// For const type
Point& Cube::operator[](int index) const {
    return this->vert_[index];
}

// Operator= for copying cubes
Cube& Cube::operator=(const Cube& second){
    this->center_ = second.center_;
    this->edge_ = second.edge_;

    this->vert_ = make_unique<Point[]>(8);

    for(int i=0; i<8; i++){
        this->vert_[i] = second[i];
    }

    return *this;
}

// Print cube
void Cube::print(){
    cout<<"-----------------------\n";
    for(int i=0; i<8; i++){
        this->vert_[i].print();
    }
    cout<<"-----------------------\n";
}

// -----------------------------------------


// ------------------NODE-------------------
// Empty constructor
Node::Node(){
    this->cube_ = Cube();
    this->desc_ = nullptr;

    this->level_ = 1;
    this->max_level_ = 1;
}

// Constructor with depth node's level, center and edge of the cube
Node::Node(unsigned int level_, unsigned int max_level_, Point center_, double edge_){

    this->cube_ = Cube(center_, edge_);
    this->level_ = level_;
    this->max_level_ = max_level_;

    this->cube_.print();

    if(this->level_ < this->max_level_){ 

        this->desc_ = make_unique<Node[]>(8); 
    
        for(int i=0; i<8; i++){
            Point tmp;

            switch(i){
                case 0: 
                    tmp = this->cube_.center_;
                    for(int j=0; j<3; j++){ tmp[j] -= edge_/4;}
                    break;
                
                case 1: 
                    tmp = this->cube_.center_;

                    tmp[0] += edge_/4;
                    tmp[1] -= edge_/4;
                    tmp[2] -= edge_/4;

                    break;
                
                case 2: 
                    tmp = this->cube_.center_;
        
                    tmp[0] -= edge_/4;
                    tmp[1] += edge_/4;
                    tmp[2] -= edge_/4;

                    break;
                
                case 3: 
                    tmp = this->cube_.center_;
                    
                    tmp[0] -= edge_/4;
                    tmp[1] -= edge_/4;
                    tmp[2] += edge_/4;

                    break;
                
                case 4:
                    tmp = this->cube_.center_;

                    tmp[0] += edge_/4;
                    tmp[1] += edge_/4;
                    tmp[2] -= edge_/4;

                    break;
                
                case 5:
                    tmp = this->cube_.center_;

                    tmp[0] += edge_/4;
                    tmp[1] -= edge_/4;
                    tmp[2] += edge_/4;

                    break;

                case 6:
                    tmp = this->cube_.center_;

                    tmp[0] -= edge_/4;
                    tmp[1] += edge_/4;
                    tmp[2] += edge_/4;

                    break;

                case 7:
                    tmp = this->cube_.center_;
                    for(int j=0; j<3; j++){ tmp[j] += edge_/4;}
                    break;
            }

            this->desc_[i] = Node(this->level_ + 1, max_level_, tmp, edge_/2);
        }
    }
    else{ this->desc_ = nullptr;}
}

// Copying constructor
Node::Node(const Node& second){
    this->cube_ = second.cube_;

    this->desc_ = make_unique<Node[]>(8);

    for(int i=0; i<8; i++){
        this->desc_[i] = second.desc_[i];
    }
}

// Operator =
Node& Node::operator=(const Node& second){
    this->cube_ = second.cube_;

    this->desc_ = make_unique<Node[]>(8);
    
    if(second.desc_ != nullptr){
        for(int i=0; i<8; i++){
            this->desc_[i] = second[i];
        }
    }
    else{
        this->desc_ = nullptr;
    }    

    return *this;
}

// Operator[]
Node& Node::operator[](int index){
    return this->desc_[index];
}

// For const type
Node& Node::operator[](int index) const{
    return this->desc_[index];
}
// -----------------------------------------


// ------------------TREE-------------------
// Empty constructor
Tree::Tree(){
    this->root_ = make_unique<Node>();
    this->max_level_ = 1;
}

// Constructor with max_level, center of root_cube and its edge
Tree::Tree(unsigned int max_level_, Point center_, double edge_){

    // For root_cube deph level always 1
    this->root_ = make_unique<Node>(1,max_level_, center_, edge_);

    this->max_level_= max_level_;

    this->root_->max_level_ = this->max_level_;
}
// -----------------------------------------