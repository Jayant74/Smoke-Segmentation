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
<<<<<<< HEAD
    std::string image_path_2 = "/home/jayant/Desktop/fire.jpg";
    Mat img = cv::imread(image_path_2, IMREAD_COLOR);
    Mat img_resize;
    cv::resize(img, img_resize, cv::Size(750, 750), INTER_LINEAR);
    cv::Size size = img_resize.size();
    cv::Mat greyMat;
    cv::cvtColor(img_resize, greyMat, cv::COLOR_BGR2GRAY);
=======
    std::string image_path_2 = "/home/jayant/Desktop/smoke.jpg";
    Mat img = cv::imread(image_path_2, IMREAD_COLOR);
    Mat img_resize;
    cv::resize(img, img_resize, cv::Size(750, 750), INTER_LINEAR);

    // Convert the image from BGR to any domain
    Mat img_change;
    cvtColor(img_resize, img_change, COLOR_BGR2BGRA);

    // Best channels so far: HSV: S; Luv: V; Lab: V; YCrCB: H, S; 

    // Split imagethree separate channels
    Mat C1, C2, C3;
    std::vector<Mat> channels;
    split(img_change, channels);
    cv::Size size = img_resize.size();

    C1 = channels[0]; 
    C2 = channels[1]; 
    C3 = channels[2]; 
>>>>>>> ARMA_BUILD

    if(img.empty())
    {
        std::cout << "Could not read the image. " << image_path_2 << std::endl;
        return 1;
    }

    // ----------------- Build Tree ------------------------- 
    int imageWidth = size.width;
    int imageHeight = size.height;
    std::vector<cv::Rect> leafVector;
<<<<<<< HEAD
    int leafSize = 10;

    quadTree *root = new quadTree(cv::Rect(0,0,imageWidth,imageHeight));
    root->buildTree(root, img_resize, leafVector, leafSize);
    root->traverseAndPrint(root, greyMat);
=======
    int leafSize = 15;

    quadTree *root = new quadTree(cv::Rect(0,0,imageWidth,imageHeight));
    root->buildTree(root, img_resize, leafVector, leafSize);
    root->traverseAndPrint(root, C2);
>>>>>>> ARMA_BUILD
    //root->traverseAndPrint(root,img_resize);

    root->~quadTree();
    // ------------------------------------------------------

<<<<<<< HEAD
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

=======
    // Blur each channel
    cv::Mat H_Blur;
    cv::Mat S_Blur;
    cv::Mat V_Blur;

    cv::GaussianBlur(C1, H_Blur,cv::Size(9,9),10,10);
    cv::GaussianBlur(C2, S_Blur,cv::Size(9,9),10,10);
    cv::GaussianBlur(C3, V_Blur,cv::Size(9,9),10,10);

    // Declare GaussCompute class
    GaussCompute GaussClass(root->region, img_resize);

    // Compute FDR for each leaf node for each Channel
    arma::vec vC1;
    arma::vec vC2;
    arma::vec vC3;

    vC1 = GaussClass.fdr_storage_vector(leafVector, C1, H_Blur);
    vC2 = GaussClass.fdr_storage_vector(leafVector, C2, S_Blur);
    vC3 = GaussClass.fdr_storage_vector(leafVector, C3, V_Blur);

    // Sort FDR vectors for each Channel
    arma::uvec sortedC1 = GaussClass.sort_fdr(vC1,3);
    arma::uvec sortedC2 = GaussClass.sort_fdr(vC2,3);
    arma::uvec sortedC3 = GaussClass.sort_fdr(vC3,3);

    // draw rectangle for each leaf node lower than the mean
    for (const auto& index : sortedC1) {
         cv::rectangle(C1, leafVector[index], cv::Scalar(1), 3);
    }

    for (const auto& index : sortedC2) {
         cv::rectangle(img_resize, leafVector[index], cv::Scalar(1), 3);
    }

    for (const auto& index : sortedC3) {
         cv::rectangle(C3, leafVector[index], cv::Scalar(1), 3);
    }

    std::cout << "size of leafVector: " << leafVector.size() << 
        "\n" << "size of sorted channel 1: " << sortedC1.size() <<
        "\n" << "size of sorted channel 2: " << sortedC2.size() << 
        "\n" << "size of sorted channel 3: " << sortedC3.size() << std::endl;

    // show images
    imshow("ch1", C1);
    imshow("ch2", C2);
    imshow("ch3", C3);
    imshow("Original", img_resize);
    
    int k = waitKey(0);

>>>>>>> ARMA_BUILD
    return 0;
}