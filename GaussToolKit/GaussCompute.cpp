#include <stdio.h>
#include <iostream>
#include <cmath>

#include "include/GaussCompute.h"
#include "gsl/gsl_statistics_float.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>


GaussCompute::GaussCompute(const cv::Rect& region, const cv::Mat& image):
    region(region), image(image) {}


std::vector<float> GaussCompute::extractSubMatrix(const cv::Rect& region, const cv::Mat& image) {
    cv::Mat submatrix = image(cv::Range(region.x,region.x+region.width),cv::Range(region.y,region.y+region.width));
    std::vector<float> array;
    array.reserve(submatrix.rows*submatrix.cols*submatrix.channels());

    if(submatrix.isContinuous()) {
        array.assign(submatrix.datastart, submatrix.dataend);
    }

    else {
        for (int i = 0; i<submatrix.rows; ++i) {
            float* row = submatrix.ptr<float>(i);
            array.insert(array.end(),row,row+submatrix.cols*submatrix.channels());
        }
    }
    return array;
}

float GaussCompute::computeFDR(std::vector<float>& block1, std::vector<float>& block2) {
    float block1_mean = gsl_stats_float_mean(reinterpret_cast<float*>(block1.data()),sizeof(float),block1.size());
    float block2_mean = gsl_stats_float_mean(reinterpret_cast<float*>(block2.data()),sizeof(float),block2.size());

    float block1_var = gsl_stats_float_variance_m(reinterpret_cast<float*>(block1.data()),sizeof(float),block1.size(),block1_mean);
    float block2_var = gsl_stats_float_variance_m(reinterpret_cast<float*>(block2.data()),sizeof(float),block2.size(),block2_mean);
    float FDR = ( pow((block1_mean-block2_mean),2) )/( pow(block1_var,2)+pow(block2_var,2) );

    return FDR;
}


