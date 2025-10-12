#include"..headers/pch.h"
#include"../headers/CoreWindow.h"

namespace Core {
    void CoreWindow::CreateWindow(std::string windowName, int width, int height){
        mImplementation->CreateWindow(move(windowName), width, height);
    }

    int CoreWindow::GetHeight() const {
        return mImplementation->GetHeight();
    }

    int CoreWindow::GetWidth() const {
        return mImplementation->GetWidth();
    }
}