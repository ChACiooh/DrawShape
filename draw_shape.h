#ifndef DRAW_SHAPE_H_INCLUDED
#define DRAW_SHAPE_H_INCLUDED

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Canvas {
    public:
        Canvas(size_t row, size_t col);
        ~Canvas();
        // Canvas ũ�⸦ w x h �� �����Ѵ�. �׷��� ������ �����Ѵ�.
        void Resize(size_t w, size_t h);
        // (x,y) ��ġ�� ch ���ڸ� �׸���. ���� ���� x,y �� �����Ѵ�.
        bool Draw(int x, int y, char ch);
        // �׷��� ������ ��� ����� ('.'���� �ʱ�ȭ)
        void Clear();

    private:
    // �׷��� ����� ������ �� �ֵ��� �����͸���� ����.
        int wid, hgt;
        vector<char> board;
        friend ostream& operator<<(ostream& os, const Canvas& c);
};

class Shape {
    public:
        virtual ~Shape();
        void Draw(Canvas* canvas) const;
        const string GetShapeType() const;
        void SetBrush(char b);
        char GetBrush() const { return brush; }
        virtual void Dump() const = 0;
        virtual void SetInfo() = 0;
    protected:
        string shape_type;
        void SaveCoordinate(int, int);
        pair<int, int> GetCoordinate(int idx) const
        {
            if(idx >= marks.size()) return make_pair(-1, -1);
            return marks[idx];
        }
    // ������ ���� �Ӽ��� ����.
    private:
        vector< <int, int> > marks;
        char brush;
};

class Rectangle : public Shape
{ /* �ʿ��� ����� ���� */
    public:
        Rectangle() { shape_type = "rect"; }
        void Draw(Canvas* canvas) const;
        void SaveCoordinate(int, int, int, int);
        void Dump() const;
        void SetInfo(int, int, int, int);
    private:
        int s_x;
        int s_y;
        int wid;
        int hgt;
};

class UpTriangle : public Shape
{ /* �ʿ��� ����� ���� */
    public:
        UpTriangle() { shape_type = "up_tri"; }
        void Draw(Canvas* canvas) const;
        void SaveCoordinate(int, int, int);
        void Dump() const;
        void SetInfo(int, int, int);
    private:
        int s_x;
        int s_y;
        int hgt;
};

class DownTriangle : public Shape
{ /* �ʿ��� ����� ���� */
    public:
        DownTriangle() { shape_type = "down_tri"; }
        void Draw(Canvas* canvas) const;
        void SaveCoordinate(int, int, int);
        void Dump() const;
        void SetInfo(int, int, int);
    private:
        int s_x;
        int s_y;
        int hgt;
};

istream& operator>>(istream& is, Rectangle& r);
istream& operator>>(istream& is, UpTriangle& t);
istream& operator>>(istream& is, DownTriangle& d);

#endif // DRAW_SHAPE_H_INCLUDED
