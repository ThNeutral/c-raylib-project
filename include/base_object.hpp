#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <stdio.h>
#include <stdlib.h>
#include "raylib.h"
#include "raymath.h"

class BaseObject {
protected:
    Vector2 pos;
    Vector2 speed;
    Color color;
public:
    BaseObject(Vector2 p, Vector2 sp, Color c) {
        this->pos = p;
        this->speed = sp;
        this->color = c;
    }

    virtual void MoveSelf(float deltaTime) {
        if (this->speed.x == 0 && this->speed.y == 0) return;
        this->pos = Vector2Add(this->pos, Vector2Scale(this->speed, deltaTime));
    }
    virtual void DrawSelf() = 0;

    void SetSpeed(Vector2 sp) {
        this->speed = sp;
    };
    Vector2 GetSpeed() {
        return this->speed;
    };
    void ReverseSpeed(bool xReverse, bool yReverse) {
        int xCoef = xReverse ? -1 : 1;
        int yCoef = yReverse ? -1 : 1;
        this->SetSpeed(Vector2{this->speed.x * xCoef, this->speed.y * yCoef});
    };

    Vector2 GetPosition() {
        return this->pos;
    }
};

#endif