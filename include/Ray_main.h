#pragma once

#define WIN32_LEAN_AND_MEAN
#define _MATH_DEFINES_DEFINED
//#define _MALIB_DONT_DEFINE_UINT

//#pragma comment(lib, "MLib.lib")

#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <time.h>

#include "..\libraries\glm\ext.hpp"
#include "..\libraries\rapidxml-1.13\rapidxml.hpp"
#include "mlib\mlib.h"

using namespace glm;
using namespace rapidxml;
using namespace mlib;

#include "Ray_def.h"

#include "core\Ray_primitives.h"
#include "core\Ray_buffers.h"
#include "core\Ray_photo.h"
#include "core\Ray_object.h"
#include "core\Ray_transform.h"
#include "core\Ray_material.h"
#include "core\Ray_entity.h"
#include "core\Ray_scene.h"

#include "entities\Ray_camera.h"
#include "entities\Ray_light.h"
#include "entities\Ray_shape.h"

#include "shapes\Shape_cube.h"
#include "shapes\Shape_invsphere.h"
#include "shapes\Shape_sphere.h"
