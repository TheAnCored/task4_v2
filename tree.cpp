#include "tree.hpp"


// ------------------POINT------------------
// Empty constructor
Point::Point(){
    this->coord_ = std::make_unique<double[]>(3);

    for(int i=0; i<3; i++){
        this->coord_[i] = 0.;
    }
}

// Constructor for <point>(x_, y_, z_)
Point::Point(double x_, double y_, double z_){
    this->coord_ = std::make_unique<double[]>(3);

    this->coord_[0] = x_;
    this->coord_[1] = y_;
    this->coord_[2] = z_;
}

// Copy constructor
Point::Point(const Point& second){

    this->coord_ = std::make_unique<double[]>(3);

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

bool Point::operator==(const Point& second){
    int index = 0;

    for(unsigned int i=0; i<3; i++){
        if(abs(this->coord_[i] - second.coord_[i]) < 
        std::numeric_limits<double>::epsilon()*std::max(abs(this->coord_[i]), abs(second.coord_[i]))){
            index++;
        }
    }

    if(index == 3){ return true; }
    return false;
}

// Print method
void Point::print(){
    for(int i=0; i<3; i++){
        if(i==0){ std::cout<<" ("<< this->coord_[i]<<", "; }
        else if(i==1){ std::cout<< this->coord_[i]<<", "; }
        else{ std::cout<< coord_[i]<<"), "<< std::endl;}
    }
}

void Point::out(FILE *out){

    for(int i=0; i<3; i++){
        if(i==0){ fprintf(out," %c",'('); fprintf(out, " %.4lf,", this->coord_[i]); }
        else if(i==1){ fprintf(out, " %.4lf,", this->coord_[i]); }
        else{ fprintf(out, " %.4lf )\n", this->coord_[i]); }
    }
}
// -----------------------------------------


// ------------------CUBE-------------------

// Empty constructor
Cube::Cube(){
    this->center_ = Point(0,0,0);
    this->vert_ = std::make_unique<Point[]>(8);

    this->edge_ = 0;
}

// Contructor with center of cube and its edge
Cube::Cube(Point center_, double edge_){

    this->center_ = center_;
    this->edge_ = edge_;

    this->vert_ = std::make_unique<Point[]>(8);

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
    this->vert_ = std::make_unique<Point[]>(8);
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

    this->vert_ = std::make_unique<Point[]>(8);

    for(int i=0; i<8; i++){
        this->vert_[i] = second[i];
    }

    return *this;
}

// Check point on location
bool Cube::IsInside(Point point){
    
    int index=0;

    for(int i=0; i<3; i++){

        if( this->vert_[0][i] < point[i] && point[i] < this->vert_[7][i] ){
            index++;
        }
        else if( abs(this->vert_[0][i] - point[i]) <= 
        std::numeric_limits<double>::epsilon()*std::max(abs(this->vert_[0][i]), abs(point[i]))){
            index++;
        }
        else if(this->vert_[0] == point || this->vert_[7] == point){
            index++;
        }
    }

    if(index == 3){ return true;}

    return false;
}

// Print cube
void Cube::print(){
    std::cout<<"-----------------------\n";
    for(int i=0; i<8; i++){
        this->vert_[i].print();
    }
    std::cout<<"\n-----------------------\n";
}

void Cube::out(FILE* out){
    
    fprintf(out, "%c",'\n');
    for(int i=0; i<8; i++){
        this->vert_[i].out(out);
    }
    fprintf(out, "%c",'\n');
}

// -----------------------------------------


// ------------------NODE-------------------
// Empty constructor
Node::Node(){
    this->cube_ = Cube();
    this->desc_ = nullptr;

    this->points_ = nullptr;
    this->amount_ = 0;

    this->level_ = 1;
}

// Constructor with depth node's level, center and edge of the cube
Node::Node(unsigned int level_, Point center_, double edge_){

    // Создаем куб для звена
    this->cube_ = Cube(center_, edge_);

    // Передаём уровень звену
    this->level_ = level_;

    this->points_ = nullptr;
    this->amount_ = 0;

    if(this->level_ < Node::max_level_){ 

        this->desc_ = std::make_unique<Node[]>(8); 
    
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

            this->desc_[i] = Node(this->level_ + 1, tmp, edge_/2);
        }
    }
    else{ this->desc_ = nullptr;}
}

// Copying constructor
Node::Node(const Node& second){
    this->cube_ = second.cube_;
    this->level_ = second.level_;

    this->desc_ = std::make_unique<Node[]>(8);

    this->amount_ = second.amount_;
    for(unsigned int i=0; i<this->amount_; i++){
        this->desc_[i] = second.desc_[i];
    }

    for(int i=0; i<8; i++){
        this->desc_[i] = second.desc_[i];
    }
}

// Operator =
Node& Node::operator=(const Node& second){
    this->cube_ = second.cube_;
    this->level_ = second.level_;

    this->desc_ = std::make_unique<Node[]>(8);

    this->amount_ = second.amount_;
    for(unsigned int i=0; i<this->amount_; i++){
        this->desc_[i] = second.desc_[i];
    }
    
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

// Print cube of note
void Node::print(){ this->cube_.print(); }

// Print function for subtree for recursion
void Node::print_subtree(){

    this->print();

    if(this->level_ < Node::max_level_){
        for(int i=0; i<8; i++){
            this->desc_[i].print_subtree();
        }
    }
}
//
void Node::AppPoint(Point point){

    for(int i=0; i< this->amount_; i++){
        if(this->points_[i] == point && this->level_ == 1){return;}
    }

    if(this->cube_.IsInside(point)){

        std::unique_ptr<Point[]> tmp = std::make_unique<Point[]>(this->amount_+1);

        for(unsigned int i=0; i < this->amount_; i++){
            tmp[i] = this->points_[i];
        }

        tmp[this->amount_] = point;

        this->amount_++;
        this->points_ = move(tmp);
        
        if(this->level_ < this->max_level_){
            for(int i=0; i<8; i++){
                this->desc_[i].AppPoint(point);
            }
        }
    }
    else{
        if(this->level_ == 1){
            std::cout<< "The point outside of the main cube\n";
        }
    }
}

void Node::AppPoint(double x_, double y_, double z_){
    Point point(x_,y_,z_);

    for(int i=0; i< this->amount_; i++){
        if(this->points_[i] == point && this->level_ == 1){return;}
    }

    if(this->cube_.IsInside(point)){
    
        std::unique_ptr<Point[]> tmp = std::make_unique<Point[]>(this->amount_+1);

        for(unsigned int i=0; i < this->amount_; i++){
            tmp[i] = this->points_[i];
        }

        tmp[this->amount_] = point;

        this->amount_++;
        this->points_ = move(tmp);
        

        if(this->level_ < this->max_level_){
            for(int i=0; i<8; i++){
                this->desc_[i].AppPoint(point);
            }
        }
    }
    else{
        if(this->level_ == 1){
            std::cout<< "The point outside of the main cube\n";
        }
    }
}

void Node::DeletePoint(Point point){

    for(unsigned int i=0; i < this->amount_; i++){
        if(point == this->points_[i]){

            if(this->amount_ == 1){
                this->amount_ = 0;
                this->points_ = nullptr;
            }
            else{
                std::unique_ptr<Point[]> tmp = std::make_unique<Point[]>(this->amount_-1);

                for(unsigned int j=0; j < this->amount_; j++){
                    if(j<i){ tmp[j] = this->points_[j]; }
                    else if(i==j){ continue; }
                    else{ tmp[j-1] = this->points_[j]; }
                }

                this->amount_--;
                this->points_ = move(tmp);
            }

            if(this->level_ < this->max_level_){
                for(int i=0; i<8; i++){
                    this->desc_[i].DeletePoint(point);
                }
            }
        }
    }
}

void Node::DeletePoint(double x_, double y_, double z_){

    Point point(x_,y_,z_);

    for(unsigned int i=0; i < this->amount_; i++){
        if(point == this->points_[i]){
            
            if(this->amount_ == 1){
                this->amount_--;
                this->points_ = nullptr;
            }
            else{
                std::unique_ptr<Point[]> tmp = std::make_unique<Point[]>(this->amount_-1);

                for(unsigned int j=0; j < this->amount_; j++){
                    if(j<i){ tmp[j] = this->points_[j]; }
                    else if(i==j){ continue; }
                    else{ tmp[j-1] = this->points_[j]; }
                }

                this->amount_--;
                this->points_ = move(tmp);
            }

            if(this->level_ < this->max_level_){
                for(int i=0; i<8; i++){
                    this->desc_[i].DeletePoint(point);
                }
            }
        }        
    }
}

void Node::out(FILE* out){
    
    this->cube_.out(out);

    if(this->level_ < this->max_level_){
        for(int i=0; i<8; i++){
            this->desc_[i].out(out);
        }
    }

    if(this->level_ == 1){
        fprintf(out, " POINTS IN MAIN CUBE: \n");

        std::cout<< this->amount_<< std::endl;

        for(unsigned int i=0; i < this->amount_; i++){
            this->points_[i].out(out);
        }
    }
}
// -----------------------------------------


// ------------------TREE-------------------
// Empty constructor
Tree::Tree(){
    this->root_ = std::make_unique<Node>();

    // In Tree class
    this->max_level_ = 1;

    // In Node class
    Node::max_level_ = 1;
}

// Constructor with max_level, center of root_cube and its edge
Tree::Tree(unsigned int max_level_, Point center_, double edge_){

    // Maximal level of recursion( in Tree class )
    this->max_level_= max_level_;

    // Maximal level of recursion( in Node class )
    Node::max_level_ = this->max_level_;

    // For root_cube deph level always 1
    this->root_ = std::make_unique<Node>(1, center_, edge_);
}

void Tree::print(){
    this->root_->print_subtree();
}

void Tree::out(FILE *out){
    this->root_->out(out);
}
// -----------------------------------------