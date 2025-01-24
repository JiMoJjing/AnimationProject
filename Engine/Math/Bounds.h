#pragma once

// 사각형 영역을 표현하는 클래스
class Bounds
{
public:
    // 생성자
    Bounds(int x, int y, int width = 1, int height = 1)
        : x(x), y(y), width(width), height(height)
    {
    }

    // Getter
    int GetX() const { return x; }
    int GetY() const { return y; }
    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

    int GetMaxX() const { return x + width; }
    int GetMaxY() const { return y + height; }

    // Setter
    void SetX(int x) { this->x = x; }
    void SetY(int y) { this->y = y; }
    void SetWidth(int width) { this->width = width; }
    void SetHeight(int height) { this->height = height; }

    // 다른 사각형과 겹치는지 확인.
    bool Intersects(const Bounds& other) const
    {
        return !(other.x > x + width || other.x + other.width < x ||
            other.y > y + height || other.y + other.height < y);
    }

private:
    int x;
    int y;
    int width;
    int height;
};