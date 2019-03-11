#include "shape.hpp"


//This program takes input from textfiles and creates different objects of the shape class depending on the input.
//The proram also does basic calculations of the shapes attributes.
//Partners : Luis Aragon(laragon2), Manam Mittal (manansm2)
//Base class
//Please implement Shape's member functions
//constructor, getName()

Shape::Shape(string name){
    name_=name;
    //TODO
}
string Shape::getName(){
    //TODO
    return name_;
}


//Rectangle
//Please implement the member functions of Rectangle:
//getArea(), getVolume(), operator+, operator-
//copy(), clear()

void Rectangle::copy(const Rectangle& other){
    spec = new double[2];
    spec[0]= other.spec[0];
    spec[1]= other.spec[1];
    //TODO
}
void Rectangle::clear(){
    delete(spec);
    //TODO
}
Rectangle::Rectangle(double width, double length):Shape("Rectangle"){
    spec = new double[2];
    spec[0] = width;
    spec[1] = length;
}
Rectangle::Rectangle(const Rectangle& other):Shape("Rectangle"){
    copy(other);
}
Rectangle::~Rectangle(){
    clear();
}
const Rectangle& Rectangle::operator = (const Rectangle& other){
    clear();
    copy(other);
    return *this;
}
double Rectangle::getArea()const{
    //TODO
    return spec[0]*spec[1];
}
double Rectangle::getVolume()const{
    //TODO
    return 0;
}
Rectangle Rectangle::operator + (const Rectangle& rhs){
    //TODO
    return Rectangle(spec[0]+rhs.spec[0],spec[1]+rhs.spec[1]);
}

Rectangle Rectangle::operator - (const Rectangle& rhs){
    //TODO
    return Rectangle(max(0.0,spec[0]-rhs.spec[0]),max(0.0,spec[1]-rhs.spec[1]));
}

// double * spec;
//spec[0] should be width
//spec[1] should be length
double Rectangle::getWidth()const{return spec? spec[0]:0;}
double Rectangle::getLength()const{return spec? spec[1]:0;}
void Rectangle::setWidth(double width){
    if (spec == NULL)
        return;

    spec[0] = width;
}
void Rectangle::setLength(double length){
    if (spec == NULL)
        return;

    spec[1] = length;
}


//Rectprism
//Please implement the member functions of RectPrism:
//constructor, getArea(), getVolume(), operator+, operator-
//@@Insert your code here
void RectPrism::copy(const RectPrism& other){
  spec = new double[3];
  spec[0]= other.spec[0];
  spec[1]= other.spec[1];
  spec[2]= other.spec[2];

    //TODO
}
void RectPrism::clear(){
    delete(spec);
    //TODO
}
RectPrism::RectPrism(double width, double length, double height):Shape("RectPrism"){
    spec = new double[3];
    spec[0] = length;
    spec[1] = width;
    spec[2] = height;
}
RectPrism::RectPrism(const RectPrism& other):Shape("RectPrism"){
    copy(other);
}
RectPrism::~RectPrism(){
    clear();
}
const RectPrism& RectPrism::operator = (const RectPrism& other){
    clear();
    copy(other);
    return *this;
}
double RectPrism::getVolume()const{
    //TODO
    return spec[0]*spec[1]*spec[2];
}
double RectPrism::getArea()const{
    //TODO
    return 2*((spec[0]*spec[1])+(spec[2]*spec[1])+(spec[0]*spec[2]));
}
RectPrism RectPrism::operator + (const RectPrism& rhs){
    //TODO
    return RectPrism(spec[0]+rhs.spec[0],spec[1]+rhs.spec[1],spec[2]+rhs.spec[2]);
}

RectPrism RectPrism::operator - (const RectPrism& rhs){
    //TODO
    return RectPrism(max(0.0,spec[1]-rhs.spec[1]),max(0.0,spec[0]-rhs.spec[0]),max(0.0,spec[2]-rhs.spec[2]));
}

// double * spec;
//spec[0] should be length
//spec[1] should be width
//spec[2] should be height
double RectPrism::getWidth()const{return spec? spec[1]:0;}
double RectPrism::getHeight()const{return spec? spec[2]:0;}
double RectPrism::getLength()const{return spec? spec[0]:0;}
void RectPrism::setWidth(double width){
    if (spec == NULL)
        return;

    spec[1] = width;
}
void RectPrism::setHeight(double height){
    if (spec == NULL)
        return;

    spec[2] = height;
}
void RectPrism::setLength(double length){
    if (spec == NULL)
        return;

    spec[0] = length;
}



// Read shapes from test.txt and initialize the objects
// Return a vector of pointers that points to the objects
vector<Shape*> CreateShapes(char* file_name){
    //@@Insert your code here

    ifstream ifs (file_name, std::ifstream::in);
    double num_shapes = 0;
    ifs >> num_shapes;
    vector<Shape*> shape_ptrs(num_shapes, NULL);
    //TODO
    string name;
    double w=0,l=0,h=0;
    for(int i=0;i<num_shapes;i++)
    {
      ifs >> name;
      if(name=="Rectangle")
      {
          ifs>> w >> l;
          shape_ptrs[i]= new Rectangle(w,l);
      }

      else if(name=="RectPrism")
      {
          ifs>> w >> l >> h;
          shape_ptrs[i]= new RectPrism(w,l,h);
      }

    }
    ifs.close();
    return shape_ptrs;
}

// call getArea() of each object
// return the max area
double MaxArea(vector<Shape*> shapes){
    double max_area = 0;
    //@@Insert your code here
    for(int i=0; i<shapes.size();i++)
    {
       if(shapes[i]->getArea()>max_area)
       max_area=shapes[i]->getArea();
    }
    return max_area;
}


// call getVolume() of each object
// return the max volume
double MaxVolume(vector<Shape*> shapes){
    double max_volume = 0;
    //@@Insert your code here
    for(int i=0; i<shapes.size();i++)
    {
       if(shapes[i]->getVolume()>max_volume)
       max_volume=shapes[i]->getVolume();
    }

    return max_volume;
}
