#include "PreCompiledHeader.h"
#include "Vector2.h"

Vector2::Vector2(int x, int y)
    : x(x), y(y)
{
}

Vector2 Vector2::operator+(const Vector2& other)
{
    return Vector2(x + other.x, y + other.y);
}

Vector2 Vector2::operator-(const Vector2& other)
{
    return Vector2(x - other.x, y - other.y);
}

bool Vector2::operator==(const Vector2& other)
{
    return (x == other.x && y == other.y);
}

bool Vector2::operator!=(const Vector2& other)
{
    return (x != other.x || y != other.y);
}

Vector2 Vector2::operator=(const Vector2& other)
{
    x = other.x;
    y = other.y;
    return Vector2(x, y);
}

void Vector2::Normalize()
{
    if (x > 0)
    {
        x = 1;
    }
    else if (x < 0)
    {
        x = -1;
    }

    if (y > 0)
    {
        y = 1;
    }
    else if (y < 0)
    {
        y = -1;
    }
}
