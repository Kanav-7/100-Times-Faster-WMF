# DIP Project
## Team Mob_Psycho
* Kanav Gupta (20161151)
* Anurag Mehta (20161016)

## Fast Weighted Median Filtering

The main goal of the project is to perform weighted median filtering of a given image in an efficient manner. The time complexity of original weighted median filtering (WMF) is O(r^2), where r is the size of the kernel. In our project, we will reduce this complexity to O(r) making it 100+ times faster than general method. The repository consists of reimplementation of actual algorithm.

## Installation

The algorithm uses mostly data structures and hence implemented in C++.

For image processing in general we require opencv
[Installing opencv](http://www.codebind.com/cpp-tutorial/install-opencv-ubuntu-cpp/) refernece

We have used gcc complier for implementation purpose
[Installing gcc](https://linuxconfig.org/how-to-install-g-the-c-compiler-on-ubuntu-18-04-bionic-beaver-linux)

# Running the code commands
- make
- ./output
## Using filter
In the main.cpp file, in main function change the image path to required path to implement the algorithm, by default it takes sap.png as its input.
Furhter parameters passed in req_filter(Mat &I, Mat &F, int r) can be changed as per requirement. 
Mat I = image
Mat F = feature/weights
int r =  radius of the filter required 

## An example implementation:


![noisy image](https://github.com/Kanav-7/DIP-Project/blob/master/sap.png)

![image filtered](https://github.com/Kanav-7/DIP-Project/blob/master/results/output.jpeg)
