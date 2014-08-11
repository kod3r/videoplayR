#include <RcppArmadillo.h>
// [[Rcpp::depends(RcppArmadillo)]]
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;
using namespace Rcpp;

class Video {
  public:
    Video(std::string filename);
    bool check;
    arma::cube next_frame();
    arma::cube get_frame(int n);
    int length();
    int fps();
    NumericVector dim();
    
  protected:
    VideoCapture inputVideo;
    cv::Mat frame;
};

Video::Video(std::string filename) {
  inputVideo.open(filename);
    
  if (!inputVideo.isOpened()) {
    throw std::range_error("Could not open the video.");
  } else {
    check = true;
  }
}

arma::cube Video::next_frame() {
  if (inputVideo.get(CV_CAP_PROP_POS_FRAMES) == inputVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
    Rcout << "Warning. This is the last frame of the video. Calling this function again will loop back to the first frame." << "\n";
  }
  
  inputVideo >> frame;
  
  arma::cube reframe(frame.rows, frame.cols, 3);
  for(int i = 0; i < frame.rows; i++) {
    for(int j = 0; j < frame.cols; j++) {
      reframe(i, j, 0) = frame.at<cv::Vec3b>(i, j)[2];
      reframe(i, j, 1) = frame.at<cv::Vec3b>(i, j)[1];
      reframe(i, j, 2) = frame.at<cv::Vec3b>(i, j)[0];
    }
  }
  
  return(reframe);
}

arma::cube Video::get_frame(int n) {
  if (n > inputVideo.get(CV_CAP_PROP_FRAME_COUNT)) {
    throw std::range_error("The requested frame does not exist. Try with a lower frame number.");
  }
  
  inputVideo.set(CV_CAP_PROP_POS_FRAMES, n);
  
  inputVideo >> frame;
  
  arma::cube reframe(frame.rows, frame.cols, 3);
  for(int i = 0; i < frame.rows; i++) {
    for(int j = 0; j < frame.cols; j++) {
      reframe(i, j, 0) = frame.at<cv::Vec3b>(i, j)[2];
      reframe(i, j, 1) = frame.at<cv::Vec3b>(i, j)[1];
      reframe(i, j, 2) = frame.at<cv::Vec3b>(i, j)[0];
    }
  }
  
  return(reframe);
}

int Video::length() {
  return(inputVideo.get(CV_CAP_PROP_FRAME_COUNT));
}

int Video::fps() {
  return(inputVideo.get(CV_CAP_PROP_FPS));
}

NumericVector Video::dim() {
  return(NumericVector::create(inputVideo.get(CV_CAP_PROP_FRAME_HEIGHT), inputVideo.get(CV_CAP_PROP_FRAME_WIDTH)));
}

RCPP_MODULE(Video) {  
  class_<Video>("Video")
    .constructor<std::string>()
    .field_readonly("check", &Video::check, "If true, the video has been imported properly and can be read.")
    .method("next_frame", &Video::next_frame, "Grabs next video frame.")
    .method("get_frame", &Video::get_frame, "Grabs a specific video frame.")
    .method("length", &Video::length, "Returns total number of frames in the video.")
    .method("fps", &Video::fps, "Returns the framerate of the video.")
    .method("dim", &Video::dim, "Returns the dimensions in pixels of the video.")
  ;
}
