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
     