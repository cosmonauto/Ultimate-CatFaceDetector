
#include "detector.hpp"

void Detector::loadModels( std::string path_to_face_model, std::string path_to_features_model )
{
  cudaSetDevice(0);

  std::string path_to_face_weights = "models/cat_face.weights";
  _face_detector.loadModel( path_to_face_model, path_to_face_weights );

  std::string path_to_features_weights = "models/cat_features.weights";
  _feature_detector.loadModel( path_to_features_model, path_to_features_weights );
}

std::vector<cv::Rect> Detector::detect( cv::Mat image )
{
  std::vector<cv::Rect> features;
  features.push_back(detectFace( image ));

  if( features[FACE].area() == 0 )  return features;

  detectFeatures( image, features );

  return features;
}

cv::Rect Detector::detectFace( cv::Mat image )
{
  std::vector<Darknet::Detection> detections = _face_detector.detect( image );

  if( detections.size() == 0 )  return cv::Rect();

  int max_index = 0;
  float max_prob = 0;
  for( int i = 0; i < detections.size(); i++ )
  {
    if( detections[i].prob > max_prob )
    {
      max_prob = detections[i].prob;
      max_index = i;
    }
  }

  return detections[max_index].rect;
}

void Detector::detectFeatures( cv::Mat image, std::vector<cv::Rect> &features )
{
  cv::Rect bigger_face = enlargeRect( image, features[FACE], 0.1, 0.1 );
  cv::Mat crop = image( bigger_face );
  std::vector<Darknet::Detection> detections = _feature_detector.detect( crop );

  std::vector<Darknet::Detection> ears;
  std::vector<Darknet::Detection> eyes;
  std::vector<Darknet::Detection> mouths;

  for( int i = 0; i < detections.size(); i++ )
  {
    // detections[i].rect += features[FACE].tl();
    detections[i].rect += bigger_face.tl();
    if( detections[i].obj == 0 )        ears.push_back( detections[i] );
    else if( detections[i].obj == 1 )   eyes.push_back( detections[i] );
    else                                mouths.push_back( detections[i] );
  }
