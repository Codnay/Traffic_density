#include <stdio.h> 
#include <iostream>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main(){
	// pts_src and pts_dst are vectors of points in source
	// and destination images. They are of type vector<Point2f>.
	// We need at least 4 corresponding points.
	Mat h = findHomography(pts_src, pts_dst);
	// The calculated homography can be used to warp
	// the source image to destination. im_src and im_dst are
	// of type Mat. Size is the size (width,height) of im_dst.
	//warpPerspective(im_src, im_dst, h, size);


	tform = projective2d(h);
	outputImage = imwarp(I, tform);
}
