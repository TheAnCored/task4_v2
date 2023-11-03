#include "tree.hpp"

// Global area
unsigned int Node::max_level_ = 0; //

int main(){

    FILE *out;

    Point a;
    double edge, x_, y_, z_;
    unsigned int max_depth;

    std::cout<<" Input the center point of the main cube: ";
    std::cin >> x_ >> y_ >> z_; std::cout<<std::endl;

    a[0] = x_; a[1] = y_; a[2] = z_;

    std::cout<<" Input the edge of the main cube: "; std::cin >> edge; std::cout<< std::endl;
    
    std::cout<<" Input the maximum depht level of your tree: "; std::cin >> max_depth; std::cout << std::endl;

    Cube A(a, edge);

    std::cout<<" Main cube: \n"; A.print();

    // std::cout<<" Your tree: \n";
    Tree tree(max_depth , a, edge);

    //tree.print();
    char answ = 'a';

    while(answ != '\n'){
        std::cout<<" What do you want to do ( add point(a), delete point(d), output tree(o), exit(e)):\n";
        std::cin >> answ;

        switch(answ){
            case 'a':
                double x1 , y1, z1;
                std::cout << " Input coordinates (x_, y_, z_): \n";
                std::cin >> x1 >> y1 >> z1; std::cout<<std::endl;

                tree.AppPoint(x1,y1,z1);
                break;
            case 'd':
                double x2, y2, z2;
                std::cout << " Input coordinates (x_, y_, z_): \n";
                std::cin >> x2 >> y2 >> z2; std::cout<<std::endl;

                tree.DeletePoint(x2,y2,z2);
                break;
            case 'e':
                answ = '\n';
                std::cout<< "\n\n GOOD BYE!!! \n\n";
                break;

            case 'o':

                out = fopen("output.txt", "w");
                fclose(out); 

                out = fopen("output.txt", "a+");
                tree.out(out);

                fclose(out);
                std::cout<<" Output complete!\n\n";
                break;

            default:
                std::cout<< " Input again (a, d, n): \n";
                std::cin >> answ; std::cout<<std::endl;

                break;
        }
    }



    return  0;
}