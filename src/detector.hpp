#ifndef _DETECTOR_H
#define _DETECTOR_H

#include <opencv2/opencv.hpp>
#include <string>

#include "darknet.hpp"

#define NUM_FEATURES 6

enum
{
  FACE,
  LEFT_EAR,
  RIGHT_EAR,
  LEFT_EYE,
  RIGHT_EYE,
  MOUTH
};

class Detector
{
  Darknet _face_detector;
  Darknet _feature_detector;

  cv::Rect detectFace( cv::Mat image );
  void detectFeatures( cv::Mat image, std::vector<cv::Rect> &features );

public:
  struct sortProb {
    bool operator() ( const Darknet::Detection &a, const Darknet::Detection &b )
    {
      return (a.prob > b.prob);
    }
  } sort_prob;
  static void drawDetections( cv::Mat &image, std::vector<cv::Rect> detections );
  static cv