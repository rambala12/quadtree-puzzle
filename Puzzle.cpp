//
// Created by Ram Bala on 4/21/19.
//

#include "Puzzle.h"

Puzzle::Puzzle(CImg<unsigned char> &image, int levels) : pic(image), puzzle(nullptr), root(nullptr) {
    lvl = levels;
    size = image.width();
    puzzle = new QuadTree(pic);
    root = new QuadTree::QTNode(0, 0, size, pic);
    root->position = -3; // root identifier
    root->parent = nullptr;
    root->subdivide(levels, root);
    puzzle->selected = root;
    puzzle->markSelected();
}

Puzzle::~Puzzle() {
    return;
}

CImg<unsigned char> & Puzzle::getImage() const {
    puzzle->makePuzzle(puzzle, root);
    puzzle->drawSelected(puzzle);
    return puzzle->getPuzzle();
}

bool Puzzle::downLevel() {
    if (puzzle->selected->get0(puzzle->selected) != nullptr) {
        QuadTree::QTNode *temp;
        temp = puzzle->selected;
        puzzle->selected = puzzle->selected->get0(puzzle->selected);
        puzzle->markSelected();
        temp->selected = 0;
        return 1;
    }
    return 0;
}

bool Puzzle::upLevel() {
    if (puzzle->selected->parent != nullptr) {
        QuadTree::QTNode *temp;
        temp = puzzle->selected;
        puzzle->selected = puzzle->selected->parent;
        puzzle->markSelected();
        temp->selected = 0;
        return 1;
    }
    return 0;
}

bool Puzzle::selectRight() {
    if (puzzle->selected->position == -3) { // root case
        return 0;
    }
    QuadTree::QTNode *temp; // use for replacement
    //QuadTree::QTNode *big;
    if (puzzle->selected->position == 0) {
        // go to sibling 1
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get1(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    if (puzzle->selected->position == 3) {
        // go to sibling 2
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get2(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    return 0;
}

bool Puzzle::selectLeft() {
    if (puzzle->selected->position == -3) { // root case
        return 0;
    }
    QuadTree::QTNode *temp; // use for replacement
    //QuadTree::QTNode *big;
    if (puzzle->selected->position == 1) {
        // go to sibling 1
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get0(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    if (puzzle->selected->position == 2) {
        // go to sibling 2
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get3(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }


    return 0;
}

bool Puzzle::selectUp() {
    if (puzzle->selected->position == -3) { // root case
        return 0;
    }
    QuadTree::QTNode *temp; // use for replacement
    //QuadTree::QTNode *big;
    if (puzzle->selected->position == 3) {
        // go to sibling 1
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get0(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    if (puzzle->selected->position == 2) {
        // go to sibling 2
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get1(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    return 0;
}

bool Puzzle::selectDown() {
    if (puzzle->selected->position == -3) { // root case
        return 0;
    }
    QuadTree::QTNode *temp; // use for replacement
    //QuadTree::QTNode *big;
    if (puzzle->selected->position == 0) {
        // go to sibling 1
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get3(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    if (puzzle->selected->position == 1) {
        // go to sibling 2
        temp = puzzle->selected; // currently selected
        puzzle->selected = temp->get2(temp->parent); // updated selected
        temp->selected = 0; // remove previous selected
        return 1;
    }
    return 0;
}

bool Puzzle::rotateCurrent() {
    puzzle->selected->rotate(puzzle->selected->nw);
    return 0;
}

bool Puzzle::solved() {
    return 0;
}

