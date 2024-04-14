#include <stdio.h>
#include <iostream>
#include <cmath>

#include "include/GaussCompute.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <armadillo>

using namespace arma;

GaussCompute::GaussCompute(const cv::Rect& region, const cv::Mat& image):
    region(region), image(image) {}


std::vector<int> GaussCompute::extractSubMatrix(const cv::Rect& region, const cv::Mat& image) {
    cv::Mat submatrix = image(cv::Range(region.x,region.x+region.width),cv::Range(region.y,region.y+region.width));
    std::vector<int> array;
    array.reserve(submatrix.rows*submatrix.cols);

    if(submatrix.isContinuous()) {
        array.assign(submatrix.datastart, submatrix.dataend);
    }

    else {
        for (int i = 0; i<submatrix.rows; ++i) {
            float* row = submatrix.ptr<float>(i);
            array.insert(array.end(),row,row+submatrix.cols);
        }
    }
    return array;
}



float GaussCompute::computeFDR(std::vector<int>& block1, std::vector<int>& block2) {
    // Initialize Armadillo vectors of the appropriate size
    arma::vec armaBlock1(block1.size());
    arma::vec armaBlock2(block2.size());

    // Manually copy and convert integers to doubles
    for (size_t i = 0; i < block1.size(); ++i) {
        armaBlock1(i) = static_cast<double>(block1[i]);
    }
    for (size_t i = 0; i < block2.size(); ++i) {
        armaBlock2(i) = static_cast<double>(block2[i]);
    }

    // Calculate means
    double block1_mean = arma::mean(armaBlock1);
    double block2_mean = arma::mean(armaBlock2);

    // Calculate standard deviations
    double block1_std = arma::stddev(armaBlock1);
    double block2_std = arma::stddev(armaBlock2);


    float FDR = ( pow((block1_mean-block2_mean),2) )/( pow(block1_std,2)+pow(block2_std,2) );

    return FDR;
}



