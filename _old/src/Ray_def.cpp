
#include "../include/Ray_main.h"

#ifdef RAY_DEF_H_
RAY_BEGIN

bool AppRunning = true;
MA::RECT SurfaceRect(800, 600);

Camera* MainCamera = 0;
ARRAY<Shape*> Renderable;

RAY_END
#endif