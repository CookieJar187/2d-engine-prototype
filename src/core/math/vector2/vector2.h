#pragma once

struct Vector2 {
    float x = 0;
    float y = 0;

    Vector2() : x(0), y(0) {}

    Vector2(float px, float py) {
        x = px;
        y = py;
    }

    Vector2 operator+(const Vector2& other) const {
        return Vector2(x + other.x, y + other.y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(x - other.x, y - other.y);
    }

    Vector2 operator*(const Vector2& other) const {
        return Vector2(x * other.x, y * other.y);
    }

    Vector2 operator/(const Vector2& other) const {
        return Vector2(x / other.x, y / other.y);
    }
};