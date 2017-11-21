#include <iostream>
#include <cmath>

#include "quadtree.h"



Quadtree::Quadtree(int left, int top, int width, int height):
    rect_shape_(sf::Vector2f(width, height)), rect_(left, top, width, height) {
    rect_shape_.setPosition(left, top);
    rect_shape_.setOutlineThickness(KQuadtreeOutlineThickness);
    rect_shape_.setOutlineColor(sf::Color::Black);
    rect_shape_.setFillColor(sf::Color(255, 255, 255, 0));
    //std::cout << "quadtree created";//, address: " << this;// << std::endl;
    //auto r = GetRect();
    //std::cout << ", rect: (" << r.left << ", " << r.top << ", " <<
    //r.width << ", " << r.height << ")" << std::endl;
}


bool Quadtree::InsertElement(Ball *b) {
    //std::cout << "\n============================================" << std::endl;
    //auto r = GetRect();
    //std::cout << "in insert element with node " <<
    //"(" << r.left << ", " << r.top << ", " <<
    //r.width << ", " << r.height << ")";//  << std::endl;
    //std::cout << ", ball: (" << b->GetX() << ", " << b->GetY() <<
    //"), address: " << b << std::endl;

    //std::cout << "x: " << b->GetX() << ", y: " << b->GetY() <<
    //", r: " << b->GetR() << std::endl;
    //std::cout << "left - r: " << GetRect().left - b->GetR() << std::endl;
    //std::cout << "top - r: " << GetRect().top - b->GetR() << std::endl;

    bool intersects_left = b->GetX() >= GetRect().left - b->GetR();
    bool intersects_right = b->GetX() <= GetRect().left + GetRect().width + b->GetR();
    bool intersects_horizontal = intersects_left && intersects_right;
    bool intersects_top = b->GetY() >= GetRect().top - b->GetR();
    bool intersects_bottom = b->GetY() <= GetRect().top + GetRect().height + b->GetR();
    bool intersects_vertical = intersects_top && intersects_bottom;
    bool intersects = intersects_horizontal && intersects_vertical;
    //std::cout << "intersects: " << intersects_left << ", " << intersects_right <<
    //", " << intersects_top << ", " << intersects_bottom << std::endl;
    if(!intersects) {
        //std::cout << "DOES NOT intersect\n" << std::endl;
        return false;
    }
    //std::cout << "intersects, size: " << GetSize() << std::endl;
    //std::cout << std::endl;
    if(GetSize() < kQuadtreeNodeCapacity) {
        children_.push_back(b);
        //std::cout << "added (" << b->GetX() << ", " << b->GetY() <<
        //") as child of (" << r.left << ", " << r.top << ", " <<
        //r.width << ", " << r.height << ")" << std::endl;
        return true;
    }

    if(NW_ == nullptr) {
        //std::cout << "NEED to subdivide" << std::endl;
        Subdivide(this);
    }
    bool insert_NW = NW_->InsertElement(b);
    bool insert_NE = NE_->InsertElement(b);
    bool insert_SW = SW_->InsertElement(b);
    bool insert_SE = SE_->InsertElement(b);
    if(insert_NW || insert_NE || insert_SW || insert_SE) {
        return true;
    }
    //std::cout << "Insert element, this should never happen." << std::endl;
    return false;
}


void Quadtree::Subdivide(Quadtree *root) {
    //std::cout << "IN subdivide with root " << root << std::endl;
    int new_width = GetRect().width / 2;
    int new_height = GetRect().height / 2;
    NW_ = new Quadtree(GetRect().left, GetRect().top, new_width, new_height);
    NE_ = new Quadtree(GetRect().left + new_width, GetRect().top, new_width, new_height);
    SW_ = new Quadtree(GetRect().left, GetRect().top + new_height, new_width, new_height);
    SE_ = new Quadtree(GetRect().left + new_width, GetRect().top + new_height, new_width, new_height);
    for (auto &node: root->children_) {
        NW_->InsertElement(node);
        NE_->InsertElement(node);
        SW_->InsertElement(node);
        SE_->InsertElement(node);
    }
}


void Quadtree::QtreeCheckCollisions(int &cnt) {
    Quadtree *NW = GetNW();
    Quadtree *NE = GetNE();
    Quadtree *SW = GetSW();
    Quadtree *SE = GetSE();

    if (NW != nullptr) {
        NW->QtreeCheckCollisions(cnt);
        NE->QtreeCheckCollisions(cnt);
        SW->QtreeCheckCollisions(cnt);
        SE->QtreeCheckCollisions(cnt);
        return;
    }

    //std::cout << "reached" << std::endl;
    //std::cout << "collision reached, size: " << GetSize() << std::endl;
    std::vector<Ball *> children_vec = GetChildren();
    for (auto node_one: children_vec) {
        for (auto node_two: children_vec) {
            //std::cout << "node one: " << node_one << ", node two: " <<
            //node_two << std::endl;
            if (node_one == node_two) {
                continue;
            }
            //std::cout << "check collision of " << node_one << " with " << node_two << std::endl;
            node_one->CheckCollisionWithBall(node_two);
            ++cnt;
        }
    }
}


void Quadtree::QtreeFreeMemory() {
    if(GetNW()){
        GetNW()->QtreeFreeMemory();
        GetNE()->QtreeFreeMemory();
        GetSW()->QtreeFreeMemory();
        GetSE()->QtreeFreeMemory();
    }
    delete this;
}
