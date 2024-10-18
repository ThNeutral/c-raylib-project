#ifndef PONG_OBJECTS_H
#define PONG_OBJECTS_H

#include "base_object.hpp"
#include "consts.h"

class Circle : public BaseObject {
protected:
    float radius;
public:
    Circle(Vector2 p, Vector2 sp, float r, Color c) : BaseObject(p, sp, c) {
        this->radius = r;
    };

    void DrawSelf() {
        DrawCircle(this->pos.x, this->pos.y, this->radius, this->color);
    };

    float GetRadius() {
        return this->radius;
    }

    void ScaleSpeed(float scalar) {
        this->speed = Vector2Scale(this->speed, scalar);
    }

    Circle* Copy() {
        return new Circle(this->pos, this->speed, this->radius, this->color);
    }
};

class Rect : public BaseObject {
protected:
    Vector2 size;
public:
    Rect(Vector2 p, Vector2 s, Vector2 sp, Color c) : BaseObject(p, sp, c) {
        this->size = s;
    };

    void DrawSelf() {
        DrawRectangle(this->pos.x, this->pos.y, this->size.x, this->size.y, this->color);
    };

    Rectangle ToRect() {
        return Rectangle{this->pos.x, this->pos.y, this->size.x, this->size.y};
    };
};

class Player : public Rect {
public:
    Player(Vector2 p, Vector2 s, Color c) : Rect(p, s, Vector2{0, 0}, c) {

    };

    void MoveSelf(Vector2 mousePosition) {
        if ((mousePosition.y < (10 + this->size.y / 2)) || (mousePosition.y > (GAME_HEIGHT - 10 - this->size.y / 2))) return;
        this->pos = Vector2{this->pos.x, mousePosition.y - this->size.y / 2};
    }
};

#endif