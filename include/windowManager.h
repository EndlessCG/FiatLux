#ifndef LIQSURFACE_WINDOWMANAGER_H
#define LIQSURFACE_WINDOWMANAGER_H


#include <GLFW/glfw3.h>

class windowManager {
public:
    windowManager();
    int createWindow(int len, int wid);
    void renderLoop();
private:
    GLFWwindow* window {};
};


#endif //LIQSURFACE_WINDOWMANAGER_H
