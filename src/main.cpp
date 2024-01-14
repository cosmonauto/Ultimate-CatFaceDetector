#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "function.hpp"

using namespace std;

void help( char *argv[] );

int main( int argc, char *argv[] )
{
  if( argc < 3 )  help( argv );
  else
  {
    string function( argv[1] );
    string src_path = argv[2];
    string dst_path="";
    if( argc > 3 )  dst_path = string( argv[3] );

    if( !function.compare( "image" ) )          Function::detectSingleImage( src_path, dst_path );
    else if( !function.compare( "images" ) )    Function::detectMultipleImages( src_path, dst_path );
    else if( !function.compare( "video" ) )
    {
      bool use_tracking = false;
      dst_path = "";
      if( argc > 3 )  use_tracking = atoi( argv[3] );
      if( argc > 4 )  dst_path = string( argv[4] );
      Function::detectVideo( src_path, dst_path, use_tracking );
    }
    else if( !function.compare( "help" ) )      help( argv );
    else
    {
      cout << "'" << function << "' is an invalid function!" << endl << endl;
      help( argv );
    }
  }

  return 0;
}

void help( char *argv[] )
{
  cout << "usage: " << string( argv[0] ) << " [function] [src_path] (video?)(tracking) (dst_path)" << endl << endl;
  cout << "function: ['image', 'images', 'video', 'help']" << endl;
  cout << "\timage: run detection on a single image" << endl;
  cout << "\timages: run det