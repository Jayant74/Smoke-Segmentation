#pragma once
#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>

// This should be called a quadNode class or something
class quadTree
{
    public:
    quadTree *topLeft, *topRight, *botLeft, *botRight;
    cv::Rect region;
    bool isLeaf;
    std::vector<cv::Rect> leafIndexVector;
    

    quadTree(const cv::Rect& region);
    ~quadTree() 
    {
        delete topLeft;
        delete topRight;
        delete botLeft;
        delete botRight;
    };

    // You should include this in a separate class called quadTree
    bool shouldDivide(const cv::Mat& image, cv::Rect& region, const int limit);
    void buildTree(quadTree *node, const cv::Mat& image, std::vector<cv::Rect>& leafIndexVector,const int limit);
    void traverseAndPrint(const quadTree* node, const cv::Mat& image); 
};

#endif

