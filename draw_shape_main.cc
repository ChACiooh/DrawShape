// draw_shape_main.cc
#include <iostream>
#include <string>
#include <vector>
#include "draw_shape.h"

using namespace std;

void DeleteShape(int idx, vector<Shape*>& shapes)
{
    if(idx >= shapes.size())    return;
    shapes.erase(idx);
}

void DumpShapes(vector<Shape*>& shapes)
{
    for(size_t i=0;i<shapes.size();i++)
    {
        cout << i << " " << shapes[i]->GetShapeType() <<
    }
}

int main()
{
    vector<Shape*> shapes;
    size_t row, col;
    cin >> row >> col;
    Canvas canvas(row, col);
    canvas.Draw(cout);

    while (true)
    {
        string tok;
        cin >> tok;
        if (tok == "add") {
            string type;
            cin >> type;
            Shape* shape = NULL;
            if (type == "rect") shape = new Rectangle();
            else if (type == "tri_up") shape = new UpTriangle();
            else if (type == "tri_down") shape = new DownTriangle();
            else continue;
            cin >> *shape;
            shapes.push_back(shape);
        } else if (tok == "draw") {
            canvas.Clear();
            for (int i = 0; i < shapes.size(); ++i) shapes[i]->Draw(&canvas);
            cout << canvas;
        } else if (tok == "delete") {
            int index;
            cin >> index;
            // Remove the corresponding shape - don't forget to delete it.
            // ...
            DeleteShape(index, shapes);
        } else if (tok == "dump") {
            // Implement dump functionality here.
            // ...

        } else {
            break;
        }
    }
    for (int i = 0; i < shapes.size(); ++i) delete shapes[i];
    shapes.clear();
    return 0;
}
