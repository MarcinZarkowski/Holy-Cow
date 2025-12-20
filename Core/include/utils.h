#pragma once

#define START_CORE_GAME(ClassName) \
int main()\
{\
    ClassName _gameObject;\
    _gameObject.Run();\
    return 0;\
}

#if CORE_DEBUG==2
    #define CORE_ERROR(msg) std::cout<<msg<<std::endl;
    #define CORE_LOG(msg) std::cout<<msg<<std::endl;
#elif CORE_DEBUG==1
    #define CORE_ERROR(msg) std::cout<<msg<<std::endl;
    #define CORE_LOG(msg)
#else
    #define CORE_ERROR(msg)
    #define CORE_LOG(msg)
#endif


#ifdef CORE_MSVC
    #ifdef CORE_LIB
        #define CORE_API __declspec(dllexport)
    #else
        #define CORE_API __declspec(dllimport)
    #endif
#else
    #define CORE_API
#endif
