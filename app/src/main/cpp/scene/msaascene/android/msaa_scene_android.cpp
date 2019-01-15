﻿#ifdef __ANDROID__

#include "../msaa_scene.h"
#include "../msaa_scene_renderer.h"
#include <android_native_app_glue.h>
#include "../../../log/log.h"

using std::chrono::duration;
using std::chrono::seconds;

static bool OnActivate();
static void OnDeactivate();

static void OnStart(void);
static void OnResume(void);
static void OnPause(void);
static void OnStop(void);
static void OnDestroy(void);

static void OnInitWindow(android_app* app);
static void OnTermWindow(void);
static void OnGainFocus(void);
static void OnLostFocus(void);

static void OnSaveInstanceState(void**, size_t*);
static void OnLowMemory(void);

MSAAScene::MSAAScene(void *state) : Scene(state)
{
    eventLoop.onActivate = OnActivate;
    eventLoop.onDeactivate = OnDeactivate;
    eventLoop.onStep = [this]() -> bool {
        return Update();
    };

    eventLoop.onStart = OnStart;
    eventLoop.onResume = OnResume;
    eventLoop.onPause = OnPause;
    eventLoop.onStop = OnStop;
    eventLoop.onDestroy = OnDestroy;

    eventLoop.onInitWindow = [this](android_app* app) -> void {

        int32_t w = ANativeWindow_getWidth(app->window);
        int32_t h = ANativeWindow_getHeight(app->window);
        renderer = new MSAASceneRenderer(app, w, h);

        OnInitWindow(app);
    };

    eventLoop.onTermWindow = OnTermWindow;
    eventLoop.onGainFocus = OnGainFocus;
    eventLoop.onLostFocus = OnLostFocus;

    eventLoop.onSaveInstanceState = OnSaveInstanceState;
    eventLoop.onConfigurationChanged = [this](android_app* app) -> void {
        DebugLog("App OnConfigurationChanged");
        int32_t width = ANativeWindow_getWidth(app->window);
        int32_t height = ANativeWindow_getHeight(app->window);
        DebugLog("Old (width, height) = (%d, %d)", width, height);
        renderer->SetScreenSize(height, width);
        renderer->ChangeOrientation();
    };
    eventLoop.onLowMemory = OnLowMemory;

    eventLoop.Run();
}

MSAAScene::~MSAAScene()
{
    delete renderer;
    renderer = nullptr;
}

bool MSAAScene::UpdateImpl()
{
    static MSAASceneRenderer* concreteRenderer = (MSAASceneRenderer*)renderer;
    auto now = high_resolution_clock::now();
    float elapsedTime = duration<float, seconds::period>(now - startTime).count();
    concreteRenderer->Update(elapsedTime);
    return true;
}

bool OnActivate()
{
    DebugLog("App OnActivate");
    return true;
}

void OnDeactivate()
{
    DebugLog("App OnDeactivate");
}

void OnStart(void)
{
    DebugLog("App OnStart");
}

void OnResume(void)
{
    DebugLog("App OnResume");
}

void OnPause(void)
{
    DebugLog("App OnPause");
}

void OnStop(void)
{
    DebugLog("App OnStop");
}

void OnDestroy(void)
{
    DebugLog("App OnDestroy");
}

void OnInitWindow(android_app* app)
{
    DebugLog("App OnInitWindow");
}

void OnTermWindow(void)
{
    DebugLog("App OnTermWindow");
}

void OnGainFocus(void)
{
    DebugLog("App OnGainFocus");
}

void OnLostFocus(void)
{
    DebugLog("App OnLostFocus");
}

void OnSaveInstanceState(void**, size_t*)
{
    DebugLog("App OnSaveInstanceState");
}

void OnLowMemory(void)
{
    DebugLog("App OnLowMemory");
}

#endif