//
// Created by Ram Bala on 2019-04-22.
//

#ifndef PUZZLE_QUADTREE_H
#define PUZZLE_QUADTREE_H

#include "CImg.h"
using namespace cimg_library;
#include <stdlib.h>

class QuadTree {
public:
    class QTNode {
    public:
        const CImg<unsigned char> &piece; // original image
        // points where the image will be placed
        int xcoord = 0;
        int ycoord = 0;
        int origx;
        int origy;
        int position; // current position of node
        int selected = 0;
        int height = 0; // height of where node is in the tree
        int width; // width of the piece

        // 4 children
        QTNode *nw;
        QTNode *ne;
        QTNode *sw;
        QTNode *se;

        QTNode *parent;

        QTNode(int x, int y, int w, const CImg<unsigned char> &pic)
                : piece(pic), origx(x), origy(y), width(w), nw(nullptr), ne(nullptr),
                  sw(nullptr), se(nullptr) {
            // set placement coordinates to orig initially
            xcoord = origx;
            ycoord = origy;
            position = -1;
        }

        ~QTNode();
        void subdivide(int level, QTNode *p);
        CImg<unsigned char> getPic(QTNode *node);
        bool correct(QTNode* node);
        QTNode* get0(QTNode* node);
        QTNode* get1(QTNode* node);
        QTNode* get2(QTNode* node);
        QTNode* get3(QTNode* node);
        void rotate(QTNode* node);

    };

    CImg<unsigned char> &puzzle;
    QTNode* selected;

    QuadTree(CImg<unsigned char> &puz) : puzzle(puz), selected(nullptr) {}
    void makePuzzle(QuadTree* tree, QTNode *node);
    void drawSelected(QuadTree* tree);
    CImg<unsigned char>& getPuzzle();
    void markSelected();
};



// to-do:
// traverse
// rotate randomly
// all puzzle functions



#endif //PUZZLE_QUADTREE_H
