#ifndef QUADTREE_H_
#define QUADTREE_H_


#include <vector>

#include "ball.h"

class Quadtree {
public:
    Quadtree(int left, int top, int width, int height);
    bool InsertElement(Ball *b);
    void Subdivide(Quadtree *root);
    int GetSize() {
        return children_.size();
    }
    Quadtree *GetNW() {
        return NW_;
    }
    Quadtree *GetNE() {
        return NE_;
    }
    Quadtree *GetSW() {
        return SW_;
    }
    Quadtree *GetSE() {
        return SE_;
    }
    sf::IntRect GetRect() {
        return rect_;
    }
    sf::RectangleShape GetRectShape() {
        return rect_shape_;
    }
    std::vector<Ball *> GetChildren() {
        return children_;
    }
    void QtreeCheckCollisions(int &num_collisions);
    void QtreeFreeMemory();
private:
    std::vector<Ball *> children_;
    Quadtree *NW_ = nullptr;
    Quadtree *NE_ = nullptr;
    Quadtree *SW_ = nullptr;
    Quadtree *SE_ = nullptr;
    sf::RectangleShape rect_shape_;
    sf::IntRect rect_;
};
#endif // QUADTREE_H_
