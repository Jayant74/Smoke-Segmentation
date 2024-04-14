#include <stdio.h>
#include <iostream>

#include "Blocker/include/QuadTree.h"
#include "GaussToolKit/include/GaussCompute.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp> 

#include <gsl/gsl_statistics_float.h>

using namespace cv;



int main(int argc, char** argv)
{
    std::string image_path_2 = "/home/jayant/Desktop/the_scream.jpg";
    Mat img = cv::imread(image_path_2, IMREAD_COLOR);
    Mat img_resize;
    cv::resize(img, img_resize, cv::Size(500, 500), INTER_LINEAR);
    cv::Size size = img_resize.size();

    if(img.empty())
    {
        std::cout << "Could not read the image. " << image_path_2 << std::endl;
        return 1;
    }

    // ----------------- Build Tree ------------------------- 
    int imageWidth = size.width;
    int imageHeight = size.height;
    std::vector<cv::Rect> leafVector;

    quadTree *root = new quadTree(cv::Rect(0,0,imageWidth,imageHeight));
    root->buildTree(root, img_resize, leafVector, 200);
    root->traverseAndPrint(root, img_resize);
    root->traverseAndPrint(root,img_resize);

    root->~quadTree();
    // ------------------------------------------------------

    // Parse through each leaf node compute FDR here
    size_t index = 0;
    std::vector<float> fdr_storage_vector(leafVector.size());

    cv::Mat img_resize_blur;
    cv::GaussianBlur(img_resize, img_resize_blur,cv::Size(5,5),3,0);

    GaussCompute GaussClass(root->region, img_resize);

    for (const auto& rect : leafVector) {
        std::vector<float> block1 = GaussClass.extractSubMatrix(rect,img_resize);
        std::vector<float> block2 = GaussClass.extractSubMatrix(rect,img_resize_blur);
        fdr_storage_vector[index] = GaussClass.computeFDR(block1, block2);
        std::cout << "Leaf node rect: (" << rect << ")" 
                    << "fdr at leaf node:" << fdr_storage_vector[index] << std::endl;
        ++index;
    }

    //imshow("Display window", resize_new);
    imshow("Display window 2", img_resize);
    int k = waitKey(0);

    if(k == 's')
    {
        imwrite("starry_night.png", img_resize);
    }

    return 0;
}