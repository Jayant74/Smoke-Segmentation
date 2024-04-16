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



float GaussCompute::computeFDR(const std::vector<int>& block1,const std::vector<int>& block2) {
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
    double block1_var = arma::var(armaBlock1);
    double block2_var = arma::var(armaBlock2);
    
    double within_class_variance = block1_var + block2_var;
    double between_class_variance = (armaBlock1.n_elem * armaBlock2.n_elem) / armaBlock1.n_elem + armaBlock2.n_elem * pow(block1_mean - block2_mean, 2);


    float FDR = between_class_variance / within_class_variance;

    if(std::isinf(FDR)) {
        return 30;
    } 

    return FDR;
}

arma::vec GaussCompute::fdr_storage_vector(const std::vector<cv::Rect> leafVector, cv::Mat image, cv::Mat image_blur) {
    std::vector<float> fdr_vector;
    fdr_vector.resize(leafVector.size());
    size_t index = 0;
    
    for (const auto& rect : leafVector)
    {
        std::vector<int> block1 = extractSubMatrix(rect,image);
        std::vector<int> block2 = extractSubMatrix(rect,image_blur);
        fdr_vector[index] = computeFDR(block1,block2);
        ++index;
    }

    arma::vec arma_FDR_Vec(fdr_vector.size());    // Indices of the leaf vectors below the media

    // armaFDRVec = (double)fdr_storage_vector 
    for (size_t i = 0; i < fdr_vector.size(); ++i) {
        arma_FDR_Vec(i) = static_cast<double>(fdr_vector[i]);
    }

    return arma_FDR_Vec;
}

arma::uvec GaussCompute::sort_fdr(arma::vec fdr_vector, double criteria_factor) {
    double mean = arma::mean(fdr_vector);
    std::cout << "median: " << mean << std::endl;
    arma::uvec lower_than_mean = arma::find(mean/criteria_factor < fdr_vector);

    return lower_than_mean;
}



