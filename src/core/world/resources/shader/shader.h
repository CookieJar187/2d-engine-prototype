#pragma once

struct Shader
{
    unsigned int id = 0;

    int modelLoc = -1;
    int viewLoc = -1;
    int projectionLoc = -1;

    int textureLoc = -1;
};