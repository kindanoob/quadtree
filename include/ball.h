#ifndef BALL_H_
#define BALL_H_

#include <random>
#include <vector>
#include <SFML/Graphics.hpp>

#include "config.h"

enum Direction {
    kHorizontal,
    kVertical
};

class Ball {
public:
    Ball(double x, double y, double dx, double dy, double r = kBallRadius, sf::Color color = sf::Color::Black):
        x_(x), y_(y), dx_(dx), dy_(dy), r_(r), shape_(r) {
        shape_.setOrigin(sf::Vector2f(GetR(), GetR()));
        shape_.setPosition(x, y);
        shape_.setFillColor(color);
        shape_.setOutlineThickness(kBallOutlineThickness);
        shape_.setOutlineColor(sf::Color::Black);

    }
    double GetX() {
        return x_;
    }
    double GetY() {
        return y_;
    }
    double GetR() {
        return r_;
    }
    void SetX(double x) {
        x_ = x;
    }
    void SetY(double y) {
        y_ = y;
    }
    double GetDx() {
        return dx_;
    }
    double GetDy() {
        return dy_;
    }
    void SetDx(double dx) {
        dx_ = dx;
    }
    void SetDy(double dy) {
        dy_ = dy;
    }
    sf::CircleShape& GetShape() {
        return shape_;
    }
    void Update(double dt);
    void UpdateTemperatureColor(double max_speed, double avg_abs_speed);
    void CheckCollisionWithBall(Ball *ball);
    void CheckCollisionWithMap(Direction dir);


private:
    double x_ = 0.0;
    double y_ = 0.0;
    double dx_ = 0.0;
    double dy_ = 0.0;
    double r_ = 0.0;
    sf::CircleShape shape_;
    sf::Text speed_text_;
    static sf::Font ball_font_;
};
#endif // BALL_H_
