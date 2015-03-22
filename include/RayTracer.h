#pragma once

#include "RayTracer_setup.h"

#include <ColdBrew.h>

using namespace cb;
using namespace cb::Object;

#include "primitives\rayhit.h"
#include "primitives\hitbuffer.h"

#include "components\component.h"
#include "components\transform.h"
#include "components\material.h"
#include "components\meshfilter.h"
#include "components\camera.h"

#include "tracer\entity.h"
#include "tracer\tracestack.h"
#include "tracer\photo.h"