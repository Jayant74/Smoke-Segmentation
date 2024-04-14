#pragma once
#ifndef GAUSS_COMPUTE_H
#define GAUSS_COMPUTE_H

#include <stdio.h>
#include <iostream>

#include <opencv2/core.hpp>
#include <gsl/gsl_statistics_float.h>

class GaussCompute {
    public:
    //std::vector<float> block1;
    //std::vector<float> block2;
    cv::Rect region;
    cv::Mat image;

    GaussCompute(const cv::Rect& region, const cv::Mat& image);
    
    std::vector<float> extractSubMatrix(const cv::Rect& region, const cv::Mat& image);  // Extract array given by node->rect, perform twice on both image blocks
    float computeFDR(std::vector<float>& block1, std::vector<float>& block2);   // Compute FDR betwen two blocks

};

#endif 
