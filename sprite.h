#pragma once

#include "main.h"

void DrawSprite(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh);
void DrawSpriteLeftTop(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh);
void DrawSpriteColor(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a);
void DrawSpriteColorRotate(int texNo, float x, float y, float width, float height, float u, float v, float uw, float vh, float r, float g, float b, float a, float rot);
void DrawSpriteColorRotateAxis(int texNo, float x, float y, float width, float height, float cx, float cy, float u, float v, float uw, float vh, float r, float g, float b, float a, float rot);

