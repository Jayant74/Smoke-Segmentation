#include <stdio.h>
#include <iostream>

#include "include/QuadTree.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

quadTree::quadTree(const cv::Rect& region):
    region(region), topLeft(nullptr), topRight(nullptr), botLeft(nullptr), botRight(nullptr), isLeaf(true) {}        

bool quadTree::shouldDivide(const cv::Mat& image, cv::Rect& region, const int limit) 
{
    // Implement a function to decide if the current node should be divided
    // This could be based on color variance or other criteria
    return region.width > limit && region.height > limit; // Simple size check, but it will continue to still build + 1 AFTER CRITERIA MET
};

void quadTree::buildTree(quadTree *node, const cv::Mat& image, std::vector<cv::Rect>& leafIndexVector, const int limit)
{
    // Termination Criterion
    if(!shouldDivide(image, node->region, limit)) { 
        node->isLeaf = true;
        leafIndexVector.push_back(node->region);
        return;
    }

    // Current node information
    node->isLeaf = false;
    int x = node->region.x, y = node->region.y; 
    int halfWidth = node->region.width / 2;
    int halfHeight = node->region.height / 2;

    // For each of the node members: *topLeft,*topRight,*botLeft,*botRight) 
    node->topLeft = new quadTree(cv::Rect(x, y, halfWidth, halfHeight));
    node->topRight = new quadTree(cv::Rect(x + halfWidth, y, halfWidth, halfHeight));
    node->botLeft = new quadTree(cv::Rect(x, y + halfHeight, halfWidth, halfHeight));
    node->botRight = new quadTree(cv::Rect(x + halfWidth, y + halfHeight, halfWidth, halfHeight));

    // Recursion occurs at 1 quadrant at a time
    buildTree(node->topLeft, image, leafIndexVector, limit);  
    buildTree(node->topRight, image, leafIndexVector, limit);   
    buildTree(node->botLeft, image, leafIndexVector, limit);     
    buildTree(node->botRight, image, leafIndexVector, limit);   


}

void quadTree::traverseAndPrint(const quadTree* node, const cv::Mat& image) {
    if (node == nullptr) {
        return; // Base case: stop recursion if node is null
    }

    
    // Process the current node
    /*
    std::cout << "Node covers area: x=" << node->region.x   // This dereferences the given node
              << ", y=" << node->region.y
              << ", width=" << node->region.width
              << ", height=" << node->region.height << std::endl;

    
    // Recursively visit each child via node->(quadrant name)
    */
    //cv::rectangle(image, node->region, cv::Scalar(0,0,255),1);
    traverseAndPrint(node->topLeft, image); 
    traverseAndPrint(node->topRight, image);
    traverseAndPrint(node->botLeft, image);
    traverseAndPrint(node->botRight, image);

}