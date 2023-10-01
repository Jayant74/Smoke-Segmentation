### The Shape of Noise

# Introduction

The goal of this project is to segment smoke in an image. This project was done for term-research paper for Pattern Recognition 487 at Drexel University. I wrote the algorithm in MATLAB and used publicly available wildfire image datasets. 

# Approach

Wildfire image data is diverse in terms of things like lighting, color content, aspect ratio, and scenery. So training any kind of neural network for pixel segmentation will require a sufficient training dataset. This approach already introduces problems of generalization and accurate dataset annotation. Therefore, I designed an image pre-processing pipeline such that the information can be _clustered_ easier, and an unsupervised learning model such as K-nearest neighbors can segment the pixel into 'non-smoke' and 'smoke'. 

# Data Preprocessing

The slightly dramatic title of this repo was the general theme my algorithm plays with. The charateristic of smoke is fluid and transluscent. It's shape and color relies on the environment it resides in. Hence, smoke is a kind of specific noise in which it blurs its surroundings. The algorithm exploits this very idea, and introduces more noise into the image via applying a Gaussian blur. The regions of the image with no smoke will appear blurred. On the contrary, in the regions where smoke is present, applying blur on smoke will not affect its appearance nearly as much. So, the preprocessing of an image is to apply a Gaussian blur and measure the relative change in appearance.

# Measure of Appearance

To measure change in appearance of an image can be tackled in a number of ways. At the time of taking this class, I was learning about the different kinds of metric distances between data. This includes things like the 'total variation distance', 'Mahalanobis distance', 'KL-divergence', and so on. The simplicity of calculating a linear discriminant such as the Fisher Discriminant Ratio (FDR) piqued my interest (and my schedule) as an appropriate metric. In this algorithm, an image is duplicated and divvied into a square grid. A baseline Gaussian blur of $\Sigma$ variance was applied to the original image and a Gaussian blur of higher $\Sigma$ to its copy. The FDR was measured for each corresponding cell in the grid, and the metric distance was recorded.

# Clustering

A standard K-means clustering model was implemented to cluster the distances in the image, and it became clear which regions had greater distances of appearance to their Gaussian blurred correspondences. The grid square size could be changed from 40x40 pixels to 1x1 pixel. The variable resolution allowed for cleaner segmentation of individual pixels. 

