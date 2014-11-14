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
        // Canvas 크기를 w x h 로 변경한다. 그려진 내용은 보존한다.
        void Resize(size_t w, size_t h);
        // (x,y) 위치에 ch 문자를 그린다. 범위 밖의 x,y 는 무시한다.
        bool Draw(int x, int y, char ch);
        // 그려진 내용을 모두 지운다 ('.'으로 초기화)
        void Clear();

    private:
    // 그려진 모양을 저장할 수 있도록 데이터멤버를 정의.
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
    // 도형의 공통 속성을 정의.
    private:
        vector<pair<int, int> > marks;
};

class Rectangle : public Shape
{ /* 필요한 멤버를 정의 */
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
{ /* 필요한 멤버를 정의 */
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
{ /* 필요한 멤버를 정의 */
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
