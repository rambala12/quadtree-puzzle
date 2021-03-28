#ifndef ECE309_PUZZLE_H
#define ECE309_PUZZLE_H

#include "CImg.h"
using namespace cimg_library;

#include "QuadTree.h"

class Puzzle {
private:
    CImg<unsigned char>& pic;
    int lvl;
    int size;
    QuadTree* puzzle;
    QuadTree::QTNode* root;
public:
    Puzzle(CImg<unsigned char>& image, int levels=4);
    ~Puzzle();
    CImg<unsigned char>& getImage() const;
    //
    bool downLevel();
    bool upLevel();
    bool selectRight();
    bool selectLeft();
    bool selectUp();
    bool selectDown();
    bool rotateCurrent();
    bool solved();
};

#endif //ECE309_PUZZLE_H
