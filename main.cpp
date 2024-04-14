#include <stdio.h>
#include <iostream>

#include "GaussToolKit/include/GaussCompute.h"
#include "Blocker/include/QuadTree.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 

using namespace cv;



int main(int argc, char** argv)
{
    std::string image_path_2 = "/home/jayant/Desktop/fire.jpg";
    Mat img = cv::imread(image_path_2, IMREAD_COLOR);
    Mat img_resize;
    cv::resize(img, img_resize, cv::Size(750, 750), INTER_LINEAR);
    cv::Size size = img_resize.size();
    cv::Mat greyMat;
    cv::cvtColor(img_resize, greyMat, cv::COLOR_BGR2GRAY);

    if(img.empty())
    {
        std::cout << "Could not read the image. " << image_path_2 << std::endl;
        return 1;
    }

    // ----------------- Build Tree ------------------------- 
    int imageWidth = size.width;
    int imageHeight = size.height;
    std::vector<cv::Rect> leafVector;
    int leafSize = 30;

    quadTree *root = new quadTree(cv::Rect(0,0,imageWidth,imageHeight));
    root->buildTree(root, img_resize, leafVector, leafSize);
    root->traverseAndPrint(root, greyMat);
    //root->traverseAndPrint(root,img_resize);

    root->~quadTree();
    // ------------------------------------------------------

    // Parse through each leaf node compute FDR here
    size_t index = 0;
    std::vector<float> fdr_storage_vector(leafVector.size());

    cv::Mat greyMat_Blur;
    cv::GaussianBlur(greyMat, greyMat_Blur,cv::Size(9,9),8,2);

    GaussCompute GaussClass(root->region, img_resize);

    for (const auto& rect : leafVector)
    {
        std::vector<int> block1 = GaussClass.extractSubMatrix(rect,greyMat);
        std::vector<int> block2 = GaussClass.extractSubMatrix(rect,greyMat_Blur);
        fdr_storage_vector[index] = GaussClass.computeFDR(block1,block2);
        ++index;
    }

    arma::vec armaFDRVec(fdr_storage_vector.size());    // Indices of the leaf vectors below the median

    // Create a black square image
    cv::Mat blackSquare(31, 31, CV_8UC3, cv::Scalar(0, 0, 0));


    // Manually copy and convert integers to doubles
    for (size_t i = 0; i < fdr_storage_vector.size(); ++i) {
        armaFDRVec(i) = static_cast<double>(fdr_storage_vector[i]);
    }

    double median = arma::median(armaFDRVec);
    std::cout << "median: " << median << std::endl;
    arma::uvec indices = arma::find(armaFDRVec < median); // This finds indices of all elements less than the median



    for (const auto& index : indices) {
        std::cout << leafVector[index] << std::endl;
         cv::rectangle(greyMat, leafVector[index], cv::Scalar(0), cv::FILLED);
    }

    imshow("Processed", greyMat);
    imshow("Blurred", greyMat_Blur);
    imshow("regular", img_resize);
    int k = waitKey(0);

    if(k == 's')
    {
        imwrite("starry_night.png", img_resize);
    }

    return 0;
}