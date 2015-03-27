#pragma once

#include "RayTracer_setup.h"

#include <ColdBrew.h>

using namespace cb;
using namespace cb::Object;

#include "components\component.h"
#include "components\transform.h"
#include "components\material.h"
#include "components\meshfilter.h"
#include "components\light.h"
#include "components\camera.h"

#include "tracer\lumination.h"
#include "tracer\hitbuffer.h"
#include "tracer\entity.h"
#include "tracer\tracestack.h"
#include "tracer\photo.h"

#include "shapes\sphere.h"
#include "shapes\axiscube.h"