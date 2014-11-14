// draw_shape.cc
#include "draw_shape.h"

Canvas::Canvas(size_t row, size_t col):wid(col), hgt(row)
{
    board.resize(wid*hgt);
    for(size_t i=0;i<hgt;i++)
        for(size_t j=0;j<wid;j++)
            board[i*wid+j] = '.';
}

Canvas::~Canvas() { board.clear(); }

void Canvas::Resize(size_t w, size_t h)
{
    vector<char> temp = board;
    board.resize(w*h);
    wid = wid < w ? wid : w;
    hgt = hgt < h ? hgt : h;
    for(size_t i=0;i<h;i++)
        for(size_t j=0;j<w;j++)
            board[i*wid+j] = '.';

    for(size_t i=0;i<hgt;i++)
    {
        for(size_t j=0;j<wid;j++)
        {
            board[i*wid+j] = temp[i*wid+j];
        }
    }
    wid = w;
    hgt = h;
}

bool Canvas::Draw(int x, int y, char ch)
{
    if(x>=wid || y>=hgt)
    {
        vector<char> temp = board;
        board.resize((x+1)*(y+1));
        for(int i=0;i<hgt;i++)
        {
            for(int j=0;j<wid;j++)
            {
                board[i*wid+j] = temp[i*wid+j];
            }
        }
        for(int i=0;i<y;i++)
        {
            for(int j=0;j<x;j++)
            {
                if(board[i*x+j] == 0)
                    board[i*x+j] = '.';
            }
        }
    }
    board[y*wid+x] = ch;
    return true;
}

void Canvas::Clear()
{
    for(size_t i=0;i<hgt;i++)
        for(size_t j=0;j<wid;j++)
            board[i*wid+j] = '.';
}

ostream& Canvas::operator<<(ostream& os, const Canvas& c)
{
    for(size_t i=0;i<hgt;i++)
    {
        for(size_t j=0;j<wid;j++)
        {
            os << board[i*wid+j] << " ";
        }
        os << endl;
    }
    return os;
}

Shape::~Shape(){ marks.clear(); }

const string Shape::GetShapeType() const { return shape_type; }

void Shape::SaveCoordinate(int x, int y)
{
    marks.push_back(make_pair(x, y));
}

void Rectangle::SaveCoordinate(int s_x, int s_y, int wid, int hgt)
{
    for(int i=s_y;i-s_y<hgt;i++)
    {
        for(int j=s_x;j-s_x<wid;j++)
        {
            SaveCoordinate(j, i);
        }
    }
}

void Shape::Draw(Canvas& canvas) const
{
    int i = 0;
    pair<int, int> end = make_pair(-1, -1);
    while(GetCoordinate(i) != end)
    {
        pair<int, int> now = GetCoordinate(i);
        i++;
        canvas.Draw(now.first, now.second, GetBrush());
    }
}

void UpTriangle::SaveCoordinate(int s_x, int s_y, int hgt)
{
    for(int i=s_y;i-s_y<hgt;i++)
    {
        int k = i-s_y;
        for(int j=s_x-k;j<=s_x+k;j++)
        {
            SaveCoordinate(j, i);
        }
    }
}

void DownTriangle::SaveCoordinate(int s_x, int s_y, int hgt)
{
    for(int i=s_y;s_y-i<hgt;i--)
    {
        int k = s_y - i;
        for(int j=s_x-k;j<=s_x+k;j++)
        {
            SaveCoordinate(j, i);
        }
    }
}

istream& operator>>(istream& is, Rectangle& r)
{
    int s_x, s_y, wid, hgt;
    char brush;
    is >> s_x >> s_y >> wid >> hgt >> brush;
    r.SaveCoordinate(s_x, s_y, wid, hgt);
    r.SetBrush(brush);
}

istream& operator>>(istream& is, UpTriangle& t)
{
    int s_x, s_y, hgt;
    char brush;
    is >> s_x >> s_y >> hgt >> brush;
    t.SaveCoordinate(s_x, s_y, hgt);
    t.SetBrush(bursh);
}

istream& operator>>(istream& is, DownTriangle& d)
{
    int s_x, s_y, hgt;
    char brush;
    is >> s_x >> s_y >> hgt >> brush;
    d.SaveCoordinate(s_x, s_y, hgt);
    d.SetBrush(bursh);
}
