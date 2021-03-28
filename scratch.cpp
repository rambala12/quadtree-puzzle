//
// Created by Ram Bala on 2019-04-22.
//

#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

#include "CImg.h"
using namespace cimg_library;

#include "Puzzle.h"

int main() {
    CImg<unsigned char> img(argv[1]);
    Puzzle p(img, 4);
    printf("hello world\n");
    return 0;
}