#include <iostream>
#include <string>
#include <opencv2/opencv.hpp>

#include "function.hpp"

using namespace std;

void help( char *argv[] );

int main( int argc, char *argv[] )
{
  if( argc < 3 )  help( argv );
  