
#pragma once

#include "Base.h"

namespace Gui {

    class RealSenseWrapper : public Base {
    public:
        RealSenseWrapper() {}
        ~RealSenseWrapper() {}

    public:
        void setupRealSense(int idx, rs2::context& ctx) {
            cam = new camera::RealSenseCam(idx, ctx);
            type = REALSENSE;
            id = idx;
            setupCamera();
        }

        void updateValues() override {}

    public:
        void startRecording(std::string path) override {
            cam->start_recording_to_path(path);
        }

        void stopRecording() override {
            cam->stop_recording();
        }
    };

}