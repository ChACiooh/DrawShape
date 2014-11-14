// draw_shape.cc
#include "draw_shape.h"
#include <cstdio>
/*** Canvas ***/
Canvas::Canvas(size_t row, size_t col):wid(col), hgt(row)
{
    board.resize(wid*hgt);
    Clear();
    /*for(size_t i=0;i<hgt;i++)
        for(size_t j=0;j<wid;j++)
            board[i*wid+j] = '.';*/
}

Canvas::~Canvas() { board.clear(); }

void Canvas::Resize(size_t w, size_t h)
{
    board.resize((wid = w)*(hgt = h));
    Clear();
}

bool Canvas::Draw(int x, int y, char ch)
{
    if(x>=wid || y>=hgt)    return false;
    board[y*wid+x] = ch;
    return true;
}

void Canvas::Clear()
{
    for(size_t i=0;i<hgt;i++)
        for(size_t j=0;j<wid;j++)
            board[i*wid+j] = '.';
}

ostream& operator<<(ostream& os, const Canvas& c)
{
    for(size_t i=0;i<c.hgt;i++)
    {
        if(i == 0)
        {
            os << " ";
            for(size_t j=0;j<c.wid;j++)
                os << j%10;
            os << endl;
        }
        for(size_t j=0;j<c.wid;j++)
        {
            if(j == 0) os << i%10;
            os << c.board[i*c.wid+j];
        }
        os << endl;
    }
    return os;
}



/*** Shape ***/
Shape::~Shape(){ marks.clear(); }

const string Shape::GetShapeType() const { return shape_type; }

void Shape::SaveCoordinate(int x, int y)
{
    marks.push_back(make_pair(x, y));
}

void Shape::Draw(Canvas* canvas) const
{
    int i = 0;
    pair<int, int> end = make_pair(-1, -1);
    pair<int, int> now = GetCoordinate(i);
    while(now != end)
    {
        i++;
        canvas->Draw(now.first, now.second, GetBrush());
        now = GetCoordinate(i);
    }
}


/*** Rectangle ***/
void Rectangle::SaveCoordinate()
{
    for(int i=s_y;i-s_y<hgt;i++)
    {
        for(int j=s_x;j-s_x<wid;j++)
        {
            Shape::SaveCoordinate(j, i);
        }
    }
}

void Rectangle::SetInfo(int a, int b, int c, int d)
{
    s_x = a;
    s_y = b;
    wid = c;
    hgt = d;
    SaveCoordinate();
}

void Rectangle::Dump() const
{
    printf("%s %d %d %d %d %c\n", GetShapeType().c_str(), s_x, s_y, wid, hgt, GetBrush());
}

/*** Triangle ***/
void UpTriangle::SaveCoordinate()
{
    for(int i=s_y;i-s_y<hgt;i++)
    {
        int k = i-s_y;
        for(int j=s_x-k;j<=s_x+k;j++)
        {
            Shape::SaveCoordinate(j, i);
        }
    }
}

void UpTriangle::SetInfo(int a, int b, int c)
{
    s_x = a;
    s_y = b;
    hgt = c;
    SaveCoordinate();
}

void UpTriangle::Dump() const
{
    printf("%s %d %d %d %c\n", GetShapeType().c_str(), s_x, s_y, hgt, GetBrush());
}

void DownTriangle::SaveCoordinate()
{
    for(int i=s_y;s_y-i<hgt;i--)
    {
        int k = s_y - i;
        for(int j=s_x-k;j<=s_x+k;j++)
        {
            Shape::SaveCoordinate(j, i);
        }
    }
}

void DownTriangle::SetInfo(int a, int b, int c)
{
    s_x = a;
    s_y = b;
    hgt = c;
    SaveCoordinate();
}

void DownTriangle::Dump() const
{
    printf("%s %d %d %d %c\n", GetShapeType().c_str(), s_x, s_y, hgt, GetBrush());
}

istream& operator>>(istream& is, Rectangle& r)
{
    int s_x, s_y, wid, hgt;
    char brush;
    is >> s_x >> s_y >> wid >> hgt >> brush;
    r.SetInfo(s_x, s_y, wid, hgt);
    r.SetBrush(brush);
    return is;
}

istream& operator>>(istream& is, UpTriangle& t)
{
    int s_x, s_y, hgt;
    char brush;
    is >> s_x >> s_y >> hgt >> brush;
    t.SetInfo(s_x, s_y, hgt);
    t.SetBrush(brush);
    return is;
}

istream& operator>>(istream& is, DownTriangle& d)
{
    int s_x, s_y, hgt;
    char brush;
    is >> s_x >> s_y >> hgt >> brush;
    d.SetInfo(s_x, s_y, hgt);
    d.SetBrush(brush);
    return is;
}
