#ifndef RIP_COCAPTURE_GUI_PARAMETERS_H
#define RIP_COCAPTURE_GUI_PARAMETERS_H

#include <iostream>
#include <string.h>

#include <opencv2/core.hpp>


struct Parameters {
    cv::Matx33d homography;
    bool do_warp;
    int target_width;
    int target_height;
    bool overlay;
    bool show_snr;
    bool roi;
};

struct PropheseeParams {
    bool set_rois;
};

struct BaslerParams {
    bool do_warp;
    int target_width;
    int target_height;
    cv::Matx33d homography;
};

#endif //RIP_COCAPTURE_GUI_PARAMETERS_H
