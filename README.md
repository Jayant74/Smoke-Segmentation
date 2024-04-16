### The Shape of Noise

# Introduction

The goal of this project is to segment smoke in an image. This project was done for term-research paper for Pattern Recognition 487 at Drexel University. I wrote the algorithm in MATLAB and used publicly available wildfire image datasets. 

# Approach

Wildfire image data is diverse in terms of things like lighting, color content, aspect ratio, and scenery. So training any kind of neural network for pixel segmentation will require a sufficient training dataset. This approach already introduces problems of generalization and accurate dataset annotation. Therefore, I designed an image pre-processing pipeline such that the information can be _clustered_ easier, and an unsupervised learning model such as K-nearest neighbors can segment the pixel into 'non-smoke' and 'smoke'. 

# Data Preprocessing

The slightly dramatic title of this repo is the general theme the algorithm plays with. The charateristic of smoke is fluid and transluscent. It's shape and color relies on the environment it resides in. Hence, smoke is a kind of specific noise in which it blurs its surroundings. The algorithm exploits this very idea, and introduces more noise into the image via applying a Gaussian blur. The regions of the image with no smoke will appear blurred. On the contrary, in the regions where smoke is present, applying blur on smoke will not affect its appearance nearly as much. So, the preprocessing of an image is to apply a Gaussian blur and measure the relative change in appearance.

# Measure of Appearance

To measure change in appearance of an image can be tackled in a number of ways. At the time of taking this class, I was learning about the different kinds of metric distances between data. This includes things like the 'total variation distance', 'Mahalanobis distance', 'KL-divergence', and so on. The simplicity of calculating a linear discriminant such as the Fisher Discriminant Ratio (FDR) piqued my interest (and my schedule) as an appropriate metric. In this algorithm, an image is duplicated and divvied into a square grid. A baseline Gaussian blur of $\Sigma$ variance was applied to the original image and a Gaussian blur of higher $\Sigma$ to its copy. The FDR was measured for each corresponding cell in the grid, and the metric distance was recorded.

![example](https://github.com/Jayant74/Smoke-Segmentation/assets/129622540/8549e60b-0681-4130-ba7e-5896b99bca14)
Figure 1. Splittig the image into equall sized cells using a quad-tree algorithm. This way the leaf node size can be specified, and data retrieval is inherently faster (and better organized). 

# Thresholding

The Fisher Discriminant Ratio is computed for each leaf node between the regular image and the blurred image. The mean of the stored FDRs can be used as a threhold criteria which is how the following result was produced.


![original](https://github.com/Jayant74/Smoke-Segmentation/assets/129622540/73e6d3ec-6b85-49e4-9e8d-0fd15e7ef7fa)        
Figure 2. Original Image



![Cr_channel](https://github.com/Jayant74/Smoke-Segmentation/assets/129622540/12a214ae-331b-48fe-92a5-6ace03c1ea79)             
Figure 3. The algorithm segements everything that it considers NOT to be smoke. The threshold to produce this particular result, was: finding all FDR values greater than mean/3. This was done empirically. 



# Next Steps

Using the mean as a means to threshold is often not an accurate thresholder. The mean can be easily skewed with outliers, which would cause the sorting of FDRs to include greater distances. In the next steps I will implement a K-means algorithm to cluster the FDR data, in this way the centroids can be ranked. This would be optimal as the various scenarios of smoke can be recognized. For example, pure smoke vs. smoke layer vs. no smoke. 

The next idea has to do with hierarchically querying nodes. If a parent node's FDR is lower than its siblings' respective FDRs, then only that node will be further subdivided. In this way, the algorithm will better emphasize regional comparisons of the image, and thresholding the FDRs will be more accurate.
