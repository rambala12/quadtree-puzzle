//
// Created by Ram Bala on 2019-04-22.
//

#include "QuadTree.h"
#include <ctime>

QuadTree::QTNode::~QTNode() {
    delete nw;
    delete ne;
    delete sw;
    delete se;
    delete parent;
}


void QuadTree::QTNode::subdivide(int level, QTNode *p) {
    int random = 0;
    float prob = 0.4;

    if (p->position == -3) { // root case
        nw = new QTNode(origx, origy, (width / 2), piece);
        nw->height = height + 1;
        nw->xcoord = nw->origx;
        nw->ycoord = nw->origy;
        nw->parent = p;
        nw->position = 0;
        srand(1);
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (nw->height < level)) {
            nw->subdivide(level, nw);
        }

        ne = new QTNode((width / 2), origy, (width / 2), piece);
        ne->height = height + 1;
        ne->xcoord = ne->origx;
        ne->ycoord = ne->origy;
        ne->parent = p;
        ne->position = 1;
        srand(5);
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (ne->height < level)) {
            ne->subdivide(level, ne);
        }

        sw = new QTNode((width / 2), (width / 2), (width / 2), piece);
        sw->height = height + 1;
        sw->xcoord = sw->origx;
        sw->ycoord = sw->origy;
        sw->parent = p;
        sw->position = 2;
        srand(2);
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (sw->height < level)) {
            sw->subdivide(level, sw);
        }

        se = new QTNode(origx, (width / 2), (width / 2), piece);
        se->height = height + 1;
        se->xcoord = se->origx;
        se->ycoord = se->origy;
        se->parent = p;
        se->position = 3;
        srand(7);
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (se->height < level)) {
            se->subdivide(level, se);
        }
    } else {
        nw = new QTNode(origx, origy, (width / 2), piece);
        nw->height = height + 1;
        nw->xcoord = nw->origx;
        nw->ycoord = nw->origy;
        nw->parent = p;
        nw->position = 0;
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (nw->height < level)) {
            nw->subdivide(level, nw);
        }

        ne = new QTNode((width / 2) + origx, origy, (width / 2), piece);
        ne->height = height + 1;
        ne->xcoord = ne->origx;
        ne->ycoord = ne->origy;
        ne->parent = p;
        ne->position = 1;
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (ne->height < level)) {
            ne->subdivide(level, ne);
        }

        sw = new QTNode((width / 2) + origx, (width / 2) + origy, (width / 2), piece);
        sw->height = height + 1;
        sw->xcoord = sw->origx;
        sw->ycoord = sw->origy;
        sw->parent = p;
        sw->position = 2;
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (sw->height < level)) {
            sw->subdivide(level, sw);
        }

        se = new QTNode(origx, (width / 2) + origy, (width / 2), piece);
        se->height = height + 1;
        se->xcoord = se->origx;
        se->ycoord = se->origy;
        se->parent = p;
        se->position = 3;
        random = rand();
        if (random < (int)(prob * RAND_MAX) && (se->height < level)) {
            se->subdivide(level, se);
        }
    }



}

CImg<unsigned char> QuadTree::QTNode::getPic(QTNode *node) {
    return node->piece.get_crop(node->origx, node->origy, node->origx + node->width, node->origy + node->width);
}

void QuadTree::makePuzzle(QuadTree* tree, QuadTree::QTNode *node) {
    const unsigned char black[] = {0, 0, 0};

    if (node->nw == nullptr) { // if the node has no more children, draw the node and its siblings
        // print node and siblings, but check if siblings have children before printing
        if (node->parent->nw->nw == nullptr) { // if sibling of node has no children, draw
            tree->puzzle.draw_image(node->parent->nw->xcoord, node->parent->nw->ycoord, node->getPic(node->parent->nw));
            // draw line for node
            if (node->parent->nw->selected == 0) {
                // if not selected, draw normal black border
                tree->puzzle.draw_line(node->parent->nw->xcoord, node->parent->nw->ycoord,
                        node->parent->nw->xcoord + node->width, node->parent->nw->ycoord, black);
                tree->puzzle.draw_line(node->parent->nw->xcoord + node->width, node->parent->nw->ycoord,
                        node->parent->nw->xcoord + node->width, node->parent->nw->ycoord + node->width, black);
            }
        }


        if (node->parent->ne->nw == nullptr) {
            tree->puzzle.draw_image(node->parent->ne->xcoord, node->parent->ne->ycoord, node->getPic(node->parent->ne));
            // draw line for node
            if (node->parent->ne->selected == 0) {
                // if not selected, draw normal black border
                tree->puzzle.draw_line(node->parent->ne->xcoord, node->parent->ne->ycoord,
                        node->parent->ne->xcoord + node->width, node->parent->ne->ycoord, black);
                tree->puzzle.draw_line(node->parent->ne->xcoord + node->width, node->parent->ne->ycoord,
                        node->parent->ne->xcoord + node->width, node->parent->ne->ycoord + node->width, black);
            }

        }

        if (node->parent->sw->nw == nullptr) {
            tree->puzzle.draw_image(node->parent->sw->xcoord, node->parent->sw->ycoord, node->getPic(node->parent->sw));

            // draw line for node
            if (node->parent->sw->selected == 0) {
                // if not selected, draw normal black border
                tree->puzzle.draw_line(node->parent->sw->xcoord, node->parent->sw->ycoord,
                        node->parent->sw->xcoord + node->width, node->parent->sw->ycoord, black);
                tree->puzzle.draw_line(node->parent->sw->xcoord + node->width, node->parent->sw->ycoord,
                        node->parent->sw->xcoord + node->width, node->parent->sw->ycoord + node->width, black);
            }

        }

        if (node->parent->se->nw == nullptr) {
            tree->puzzle.draw_image(node->parent->se->xcoord, node->parent->se->ycoord, node->getPic(node->parent->se));
            // draw line for node
            if (node->parent->se->selected == 0) {
                // if not selected, draw normal black border
                tree->puzzle.draw_line(node->parent->se->xcoord, node->parent->se->ycoord,
                        node->parent->se->xcoord + node->width, node->parent->se->ycoord, black);
                tree->puzzle.draw_line(node->parent->se->xcoord + node->width, node->parent->se->ycoord,
                        node->parent->se->xcoord + node->width, node->parent->se->ycoord + node->width, black);
            }


        }
    } else { // if node has children, call function again
        tree->makePuzzle(tree, node->nw);
        tree->makePuzzle(tree, node->ne);
        tree->makePuzzle(tree, node->sw);
        tree->makePuzzle(tree, node->se);

    }

}

CImg<unsigned char> & QuadTree::getPuzzle() {
    return puzzle;
}

bool QuadTree::QTNode::correct(QuadTree::QTNode *node) {
    if ((node->origx == node->xcoord) && (node->origy == node->ycoord)) {
        return true;
    }
    return false;
}

void QuadTree::markSelected() {
    selected->selected = 1;
}

void QuadTree::drawSelected(QuadTree *tree) {
    const unsigned char white[] = {255, 255, 255};
    // if node is selected draw white
    tree->puzzle.draw_line(selected->xcoord, selected->ycoord,
            selected->xcoord + selected->width, selected->ycoord, white);
    // right
    tree->puzzle.draw_line(selected->xcoord + selected->width, selected->ycoord,
            selected->xcoord + selected->width, selected->ycoord + selected->width, white);
    // bottom
    tree->puzzle.draw_line(selected->xcoord, selected->ycoord + selected->width,
            selected->xcoord + selected->width, selected->ycoord + selected->width, white);
    // left
    tree->puzzle.draw_line(selected->xcoord, selected->ycoord,
            selected->xcoord, selected->ycoord + selected->width, white);
}

QuadTree::QTNode* QuadTree::QTNode::get0(QuadTree::QTNode *node) { // returns child at 0 pos
    if (node->nw->position == 0) return node->nw;
    if (node->ne->position == 0) return node->ne;
    if (node->sw->position == 0) return node->sw;
    if (node->se->position == 0) return node->se;
    return nullptr;
}

QuadTree::QTNode* QuadTree::QTNode::get1(QuadTree::QTNode *node) { // return child at 1 pos
    if (node->nw->position == 1) return node->nw;
    if (node->ne->position == 1) return node->ne;
    if (node->sw->position == 1) return node->sw;
    if (node->se->position == 1) return node->se;
    return nullptr;

}

QuadTree::QTNode* QuadTree::QTNode::get2(QuadTree::QTNode *node) { // return child at 2
    if (node->nw->position == 2) return node->nw;
    if (node->ne->position == 2) return node->ne;
    if (node->sw->position == 2) return node->sw;
    if (node->se->position == 2) return node->se;
    return nullptr;

}

QuadTree::QTNode* QuadTree::QTNode::get3(QuadTree::QTNode *node) { // return child at 3
    if (node->nw->position == 3) return node->nw;
    if (node->ne->position == 3) return node->ne;
    if (node->sw->position == 3) return node->sw;
    if (node->se->position == 3) return node->se;
    return nullptr;
}


// Rotate node and its siblings ALWAYS PASS IN NODE NW
void QuadTree::QTNode::rotate(QuadTree::QTNode *node) {
    // based on position of current node, move around node and other nodes
    // only make changes to coord values (keep orig unchanged)
    if (node->position == 0) {
        // move 0 to 1
        node->position = 1;
        node->xcoord = node->xcoord + node->width;
        node->ycoord = node->ycoord;

        // move 1 to 2
        node->parent->ne->xcoord = node->parent->ne->xcoord;
        node->parent->ne->ycoord = node->parent->ne->ycoord - node->width;
        node->parent->ne->position = 2;

        // move 2 to 3
        node->parent->sw->xcoord = node->parent->sw->xcoord - node->width;
        node->parent->sw->ycoord = node->parent->sw->ycoord;
        node->parent->sw->position = 3;

        // move 3 to 0
        node->parent->se->xcoord = node->parent->se->xcoord;
        node->parent->se->ycoord = node->parent->se->ycoord - node->width;
        node->parent->se->position = 0;

    } else if (node->position == 1) {
        // move 1 to 2
        node->position = 2;
        node->xcoord = node->xcoord;
        node->ycoord = node->ycoord + node->width;

        // move 2 to 3
        node->parent->ne->xcoord = node->parent->sw->xcoord - node->width;
        node->parent->ne->ycoord = node->parent->sw->ycoord;
        node->parent->ne->position = 3;

        // move 3 to 0
        node->parent->sw->xcoord = node->parent->se->xcoord;
        node->parent->sw->ycoord = node->parent->se->ycoord - node->width;
        node->parent->sw->position = 0;

        // move 0 to 1
        node->parent->se->xcoord = node->parent->nw->xcoord + node->width;
        node->parent->se->ycoord = node->parent->nw->ycoord;
        node->parent->se->position = 1;

    } else if (node->position == 2) {
        // move 2 to 3
        node->position = 3;
        node->xcoord = node->xcoord - node->width;
        node->ycoord = node->ycoord;

        // move 3 to 0
        node->parent->ne->xcoord = node->parent->se->xcoord;
        node->parent->ne->ycoord = node->parent->se->ycoord - node->width;
        node->parent->ne->position = 0;

        // move 0 to 1
        node->parent->sw->xcoord = node->parent->nw->xcoord + node->width;
        node->parent->sw->ycoord = node->parent->nw->ycoord;
        node->parent->sw->position = 1;

        // move 1 to 2
        node->parent->se->xcoord = node->parent->ne->xcoord;
        node->parent->se->ycoord = node->parent->ne->ycoord - node->width;
        node->parent->se->position = 2;

    } else if (node->position == 3) {
        // move 3 to 0
        node->position = 0;
        node->xcoord = node->xcoord;
        node->ycoord = node->ycoord - node->width;

        // move 0 to 1
        node->parent->ne->xcoord = node->parent->nw->xcoord + node->width;
        node->parent->ne->ycoord = node->parent->nw->ycoord;
        node->parent->ne->position = 1;

        // move 1 to 2
        node->parent->sw->xcoord = node->parent->ne->xcoord;
        node->parent->sw->ycoord = node->parent->ne->ycoord - node->width;
        node->parent->sw->position = 2;

        // move 2 to 3
        node->parent->se->xcoord = node->parent->sw->xcoord - node->width;
        node->parent->se->ycoord = node->parent->sw->ycoord;
        node->parent->se->position = 3;
    }
}

