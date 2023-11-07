#include "detector.hpp"
#include "video.hpp"

#include <opencv2/tracking.hpp>
#include <pthread.h>

#include <boost/filesystem.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
using namespace boost::filesystem;

//struct updateTrackingThreadArgs {
//  cv