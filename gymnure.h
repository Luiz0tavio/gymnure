#ifndef GYMNURE_H
#define GYMNURE_H

#include <Window/SDLWindow.hpp>
#include <Application.hpp>
#include <Util/Debug.hpp>

#define GB (1024 * 1024 * 1024)

class Gymnure
{
private:

    Engine::Window::SDLWindow* window_;

public:

    Gymnure(unsigned int windowWidth, unsigned int windowHeight)
    {
        mem::Provider::initPool(1*GB);
        window_ = new Engine::Window::SDLWindow(windowWidth, windowHeight);
        Engine::Application::create(window_->getInstanceExtensionNames());
    #ifdef DEBUG
        Engine::Debug::init();
    #endif
        window_->createSurface();
        Engine::Application::setupSurface(windowWidth, windowHeight);
    }

    ~Gymnure()
    {
        delete window_;
        mem::Provider::destroyPool();
    }

    uint initPhongProgram()
    {
        return Engine::Application::createPhongProgram();
    }

    uint initSkyboxProgram()
    {
        return Engine::Application::createSkyboxProgram();
    }

    void addObjData(uint program_id, const GymnureObjData& gymnure_data)
    {
        Engine::Application::addObjData(program_id, gymnure_data);
    }

    void prepare()
    {
        Engine::Application::prepare();
    }

    bool draw()
    {
        ///if(Engine::Application::poolEvent() == WindowEvent::Close)
        ///    return false;

        Engine::Application::draw();
        return true;
    }

};

#endif //GYMNURE_GYMNURE_H
