#include <iostream>
#include <math.h>

#ifndef M_PI
#define M_PI (3.14159265358979323846)
#endif

using namespace std;

enum BOOL { FALSE, TRUE };

class GeneralShape
{
    public:
        GeneralShape(){};
        ~GeneralShape(){};
        virtual long GetArea() = 0;
        virtual long GetPerim()= 0;
        virtual void Draw() = 0;
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
    private:
        int itsRadius;
        int itsCircumference;
};

void Circle::Draw()
{
    cout << "Circle drawing routine here!" << endl;
    int radius = 8; // or whatever you want

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
        Rectangle(int len, int width):
        itsLength(len), itsWidth(width){}
        ~Rectangle(){}
        long GetArea() { return itsLength * itsWidth; }
        long GetPerim() {return 2*itsLength + 2*itsWidth; }
        virtual int GetLength() { return itsLength; }
        virtual int GetWidth() { return itsWidth; }
        void Draw();
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

int main()
{
 int choice;
 BOOL quit = FALSE;
 GeneralShape *sp;

    while (1)
    {
        cout << "(1)Circle (2)Rectangle (3)Square (0)Quit: ";
        cin >> choice;

        switch (choice)
        {
            case 1: sp = new Circle(5);
            break;
            case 2: sp = new Rectangle(4,6);
            break;
            case 3: sp = new Square (5);
            break;
            default: quit = TRUE;
            break;
        }

    if (quit) break;

    sp->Draw();

    cout << endl;
    }

 return 0;
}
