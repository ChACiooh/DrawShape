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
        virtual const string GetShapeType() const = 0;
        virtual void SetBrush(char b) = 0;
        virtual char GetBrush() const = 0;
        virtual void Dump() const = 0;
    protected:
        string shape_type;
        char brush;
        void SaveCoordinate(int, int);
        virtual void SaveCoordinate() = 0;
        pair<int, int> GetCoordinate(int idx) const
        {
            if(idx >= marks.size()) return make_pair(-1, -1);
            return marks[idx];
        }
    // ������ ���� �Ӽ��� ����.
    private:
        vector<pair<int, int> > marks;
};

class Rectangle : public Shape
{ /* �ʿ��� ����� ���� */
    public:
        Rectangle() { shape_type = "rect"; }
        void Draw(Canvas* canvas) const;
        const string GetShapeType() const { return shape_type; }
        void SetBrush(char b){ brush = b; }
        char GetBrush() const { return brush; }
        void Dump() const;
        void SetInfo(int, int, int, int);

    protected:
        void SaveCoordinate();
    private:
        int s_x;
        int s_y;
        int wid;
        int hgt;
};

class UpTriangle : public Shape
{ /* �ʿ��� ����� ���� */
    public:
        UpTriangle() { shape_type = "tri_up"; }
        void Draw(Canvas* canvas) const;
        const string GetShapeType() const { return shape_type; }
        void SetBrush(char b){ brush = b; }
        char GetBrush() const { return brush; }
        void SaveCoordinate();
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
        DownTriangle() { shape_type = "tri_down"; }
        void Draw(Canvas* canvas) const;
        const string GetShapeType() const { return shape_type; }
        void SetBrush(char b){ brush = b; }
        char GetBrush() const { return brush; }
        void SaveCoordinate();
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
