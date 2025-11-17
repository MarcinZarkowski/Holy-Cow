#include "../headers/pch.h"
#include"../headers/CoreWindow.h"
#include "GLFWsrc/WindowGLFW.h"

namespace Core {
    CoreWindow::CoreWindow(){
        std::cout<<"initializing window"<<std::endl;
        #ifdef CORE_GLFW
                std::cout<<"did this, making window implementation the GLFW one"<<std::endl;
                mImplementation = std::unique_ptr<WindowGLFW>(new WindowGLFW);
        #else
            #only_GLFW_is_supported
        #endif
    }

    void CoreWindow::Init() {
        if (!mInstance) mInstance = std::unique_ptr<CoreWindow>{ new CoreWindow };
    }

    std::unique_ptr<CoreWindow>& CoreWindow::GetWindow() {
        return mInstance;
    }

    void CoreWindow::CreateWindow(std::string windowName, int width, int height){
        mImplementation->CreateWindow(std::move(windowName), width, height);
    }

    int CoreWindow::GetHeight() const {
        return mImplementation->GetHeight();
    }

    int CoreWindow::GetWidth() const {
        return mImplementation->GetWidth();
    }

    void CoreWindow::SwapBuffers() {
        mImplementation->SwapBuffers();
    }

    void CoreWindow::PollEvents() {
        mImplementation->PollEvents();
    }
}