#include "function.hpp"

void Function::detectSingleImage( std::string src_path, std::string dst_path )
{
  bool show = dst_path.compare("") == 0 ? true : false;
  std::string imgname = src_path.substr( src_path.find_last_of('/')+1 );
  std::string write_path = dst_path + "/" + imgname;

  std::cout << "Detection on a single image: " << src_path << std::endl;

  if( show )    std::cout << "Showing detection result" << std::endl;
  else          std::cout << "Writing detection result to " << write_path << std::endl;

  Detector detector;
  detector.loadModels( "models/cat_face.cfg", "models/cat_features.cfg" );

  cv::Mat image = cv::imread( src_path );
  cv::Mat org = image.clone();
  std::vector<cv::Rect> detections = detector.detect( image );

  Detector::drawDetections( image, detections );

  if( show )
  {
    cv::namedWindow( "original", cv::WINDOW_NORMAL );
    cv::resizeWindow( "original", 800, 800 );
    cv::imshow( "original", org );

    cv::namedWindow( "detection", cv::WINDOW_NORMAL );
    cv::resizeWindow( "detection", 800, 800 );
    cv::imshow( "detection", image );
    cv::waitKey(0);
  }
  else
  {
    cv::imwrite( write_path, image );
  }
}

void Function::detectMultipleImages( std::string src_path, std::string dst_path )
{
  bool show = dst_path.compare("") == 0 ? true : false;

  std::cout << "Detection on multiple images in: " << src_path << std::endl;

  std::vector<boost::filesystem::path> paths = getImagePathsInFolder( src_path, ".jpg" );

  std::cout << "Found " << paths.size() << " images in the folder" << std::endl;

  Detector detector;
  detector.loadModels( "models/cat_face.cfg", "models/cat_features.cfg" );

  std::cout << std::endl << std::endl;

  for( std::vector<boost::filesystem::path>::iterator it = paths.begin(); it != paths.end(); ++it )
  {
    std::stri