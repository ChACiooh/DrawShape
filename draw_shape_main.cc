// draw_shape_main.cc
#include "draw_shape.h"

void DeleteShape(int idx, vector<Shape*>& shapes)
{
    if(idx >= shapes.size())    return;
    delete shapes[idx];
    vector<Shape*> temp;
    for(int i=0;i<idx;i++)  temp.push_back(shapes[i]);
    for(int i=idx+1;i<shapes.size();i++)    temp.push_back(shapes[i]);
    shapes = temp;
}

void DumpShapes(vector<Shape*>& shapes)
{
    for(size_t i=0;i<shapes.size();i++)
    {
        cout << i << " ";
        shapes[i]->Dump();
    }
}

int main()
{
    vector<Shape*> shapes;
    size_t row, col;
    cin >> row >> col;
    Canvas canvas(row, col);
    cout << canvas;

    while (true)
    {
        string tok;
        cin >> tok;
        if (tok == "add") {
            string type;
            cin >> type;
            if (type == "rect")
            {
                Rectangle* shape = new Rectangle();
                cin >> *shape;
                shapes.push_back(shape);
            }
            else if (type == "tri_up")
            {
                UpTriangle* shape = new UpTriangle();
                cin >> *shape;
                shapes.push_back(shape);
            }
            else if (type == "tri_down")
            {
                DownTriangle* shape = new DownTriangle();
                cin >> *shape;
                shapes.push_back(shape);
            }
            else continue;
        } else if (tok == "draw") {
            canvas.Clear();
            for (int i = 0; i < shapes.size(); ++i) shapes[i]->Draw(&canvas);
            cout << canvas;
        } else if (tok == "delete") {
            int index;
            cin >> index;
            DeleteShape(index, shapes);
        } else if (tok == "dump") {
            DumpShapes(shapes);
        } else if( tok == "resize") {
            int wid, hgt;
            cin >> wid >> hgt;
            canvas.Resize(wid, hgt);
        }else {
            break;
        }
    }
    for (int i = 0; i < shapes.size(); ++i) delete shapes[i];
    shapes.clear();
    return 0;
}
