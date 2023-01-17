#include "Recorder.h"

namespace Gui {

    std::string Recorder::getCurrTimeRootDirStr() {
        time_t rawTime;
        struct tm * timeInfo;
        char buf[100];

        time(&rawTime);
        timeInfo = localtime(&rawTime);

        strftime(buf, sizeof(buf), "%y%m%d_%H%M%S", timeInfo);
        return std::string(buf);
    }

    void Recorder::makeCameraSubDirsAndRecord(std::string rootDir) {
        std::string targetDir = workDir + "/" + rootDir;

        int i = 0;
        for(Base* cam : camRefs) {
            std::string camDir = targetDir + "/" + cam->getType() + "_" + std::to_string(i);
            boost::filesystem::create_directories(camDir);

            // Prophesee camera
            if(cam->getType() == PROPHESEE) {
                PropheseeWrapper* pCam = (PropheseeWrapper*) cam;
                pCam->startRecording(camDir + "/" + PROPHESEE_RAW_OUTPUT_FILENAME);
            }

            i++;
        }
    }

    void Recorder::stopRecording() {
        for(Base* cam : camRefs) {
            // Prophesee camera
            if(cam->getType() == PROPHESEE) {
                PropheseeWrapper* pCam = (PropheseeWrapper*) cam;
                pCam->stopRecording();
            }
        }
    }

    void Recorder::demoRecorder() {
        ImGuiIO &io = ImGui::GetIO();

        ImVec2 demoShowSpaceScale = ImVec2(0.25f, 0.25f);
        ImVec2 demoShowSpace = ImVec2(io.DisplaySize.x * demoShowSpaceScale.x,
                                      io.DisplaySize.y * demoShowSpaceScale.y);

        ImVec2 offset, windowPos, windowSize;

        offset = ImVec2(io.DisplaySize.x * (1 - demoShowSpaceScale.x),
                        io.DisplaySize.y * 0.00675f);

        windowPos = ImVec2(demoShowSpace .x / 2 + offset.x,
                           demoShowSpace .y / 2 + offset.y);

        windowSize = ImVec2(demoShowSpace .x * (1 - 0.0275f),
                            demoShowSpace .y * (1 - 0.0565f));

        ImGui::SetNextWindowSize(windowSize);
        ImGui::SetNextWindowPos(windowPos, 0, ImVec2(0.5f, 0.5f));

        ImGui::Begin("Recorder", NULL, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);

        bool propExists = false;
        for(Base* cam : camRefs) {
            if(cam->getType() == PROPHESEE) {
                propExists = true;
            }
        }

        if(propExists) {
            ImGui::TextUnformatted(PROPHESEE.c_str());
            ImGui::Spacing();

            std::string rootDir = getCurrTimeRootDirStr();

            if(ImGui::Button("Record")) {
                if(!recording) {
                    makeCameraSubDirsAndRecord(rootDir);

                    recording = true; status = "Recording in progress . .";
                }

                else if(recording) { ImGui::OpenPopup("recordingPopup"); }
            }

            if(ImGui::BeginPopup("recordingPopup")) {
                ImGui::Text("Currently recording. Proceed anyway?");
                if(ImGui::Selectable("Yes")) {
                    stopRecording();
                    makeCameraSubDirsAndRecord(rootDir);
                }
                ImGui::Selectable("No");
                ImGui::EndPopup();
            }

            ImGui::SameLine();

            if(ImGui::Button("Stop")) {
                if(recording) {
                    stopRecording();
                    recording = false; status = "Recording successfully ended.";
                }
            }

        } else {
            ImGui::Text("No camera capable of recording found.");
        }

        ImGui::Spacing();
        ImGui::TextUnformatted(status.c_str());
        ImGui::End();
    }

    void Recorder::show() {
        demoRecorder();
    }

}