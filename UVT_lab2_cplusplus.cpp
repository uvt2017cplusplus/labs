#include <iostream>
#include <vector>
#include <math.h>
#include <typeinfo>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

using namespace std;

enum BOOL { FALSE, TRUE };

class GeneralShape
{
        string figureName="unnamed";
    public:
        GeneralShape(){};
        ~GeneralShape(){};
        virtual long GetArea() = 0;
        virtual long GetPerim()= 0;
        virtual void Draw() = 0;
        virtual string mytype() = 0;
        friend ostream& operator<<(ostream &output, GeneralShape &shape);
        friend istream& operator>>(istream &input, GeneralShape &shape);
};

void GeneralShape::Draw()
{
    cout << "drawing mechanism!" << endl;
}

class Circle : public GeneralShape
{
    public:
        Circle(int radius):itsRadius(radius){}
        ~Circle(){}
        long GetArea() { return M_PI * itsRadius * itsRadius; }
        long GetPerim() { return 2 * M_PI * itsRadius; }
        void Draw();
        string mytype(){return typeid(*this).name();};
    private:
        int itsRadius;
        int itsCircumference;
};

void Circle::Draw()
{
    cout << "Circle drawing routine here!" << endl;
    auto radius = 8; // or whatever you want

    for (int i = 0; i <= 2*radius; i++)
    {
        for (int j = 0; j <= 2*radius; j++)
        {
            float distance_to_centre = sqrt((i - radius)*(i - radius)
                                            + (j - radius)*(j - radius));
            if (distance_to_centre > radius-0.5 &&
                distance_to_centre < radius+0.5)
            {
                 cout << "*";
            }
            else
            {
                 cout << " ";
            }
        }
        cout << endl;
    }
    GeneralShape::Draw();
}

class Rectangle : public GeneralShape
{
    public:
        Rectangle(int len, int width): itsLength(len), itsWidth(width){}
        ~Rectangle(){}
        long GetArea() { return itsLength * itsWidth; }
        long GetPerim() {return 2*itsLength + 2*itsWidth; }
        virtual int GetLength() { return itsLength; }
        virtual int GetWidth() { return itsWidth; }
        void Draw();
        string mytype(){return typeid(*this).name();};
    private:
        int itsWidth;
        int itsLength;
};

void Rectangle::Draw()
{
    for (int i = 0; i<itsLength; i++)
    {
        for (int j = 0; j<itsWidth; j++) cout << "x ";

     cout << endl;
    }
 GeneralShape::Draw();
}


class Square : public Rectangle
{
    public:
        string mytype(){return typeid(*this).name();};
        Square();
        Square(int len);
        Square(int len, int width);
        ~Square(){}
        long GetPerim() {return 4 * GetLength();}
};

Square::Square(int len):
Rectangle(len,len)
{}

Square::Square(int len, int width):
Rectangle(len,width)
{
 if (GetLength() != GetWidth())
  cout << "Error, not a square... a Rectangle??\n";
}


ostream &operator<<(ostream &output, GeneralShape &shape) {
 output << "Shape: " << shape.figureName << " GetPerim:  " << shape.GetPerim();
 return output;
}

istream &operator>>(istream &input, GeneralShape &shape) {
 input >> shape.figureName;
 return input;
}

int main()
{
 int choice;
 BOOL quit = FALSE;
 GeneralShape *sp;
 vector<GeneralShape*> shapes;

    while (1)
    {
        cout << "(1)Circle (2)Rectangle (3)Square (0)Quit: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                sp = new Circle{5};
                shapes.push_back(sp);
            break;
            case 2:
                sp = new Rectangle{4,6};
                cin >> (*sp);
                cout << (*sp) << endl;
                shapes.push_back(sp);
            break;
            case 3:
                sp = new Square {5};
                shapes.push_back(sp);
            break;
            default: quit = TRUE;
            break;
        }

    if (quit) break;

    sp->Draw();

    cout << endl;
    }

    std::vector<GeneralShape*>::iterator it;

    for(it = shapes.begin(); it != shapes.end(); ++it)
    {
      cout<< (*it)->mytype() << endl;
    }
    cout << "shapes vector size= " << shapes.size()<< endl;

    delete sp;

 return 0;
}
