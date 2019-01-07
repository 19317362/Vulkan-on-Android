﻿#ifndef EARTH_SCENE_H
#define EARTH_SCENE_H

#include "../scene.h"
#include "../../vulkan/model.h"
#include <vector>

using Vulkan::Model;
using std::vector;

class EarthScene : public Scene
{
public:
    EarthScene(void* state);
    ~EarthScene();

    bool UpdateImpl() override;

private:
    // ==== Vulkan ==== //
    vector<Model> _models;
};


#endif // EARTH_SCENE_H