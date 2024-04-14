#pragma once
#ifndef GAUSS_COMPUTE_H
#define GAUSS_COMPUTE_H

#include <stdio.h>
#include <iostream>
#include <armadillo>

#include <opencv2/core.hpp>

class GaussCompute {
    public:
    //std::vector<float> block1;
    //std::vector<float> block2;
    cv::Rect region;
    cv::Mat image;

    GaussCompute(const cv::Rect& region, const cv::Mat& image);
    
    std::vector<int> extractSubMatrix(const cv::Rect& region, const cv::Mat& image);  // Extract array given by node->rect, perform twice on both image blocks
    float computeFDR(std::vector<int>& block1, std::vector<int>& block2);   // Compute FDR betwen two blocks

};

#endif 
