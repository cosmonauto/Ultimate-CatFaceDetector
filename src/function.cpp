#include "function.hpp"

void Function::detectSingleImage( std::string src_path, std::string dst_path )
{
  bool show = dst_path.compare("") == 0 ? true : false;
  std::string imgname = src_path.substr( src_path.find_last_of('/')+1 );
  std::string write_path = dst_path + "/" + imgname;

  std::cout << "Detection on a single image: " << src_path << std::endl;

  if( show )    std::cout << "Showing detection result" << std::endl;
  else          std::cout << "Writing detection result to " <<