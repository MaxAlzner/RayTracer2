#pragma once

#include "RayTracer_setup.h"

#include <ColdBrew.h>

using namespace cb;
using namespace cb::Object;

#include "dataobjects\rayhit.h"
#include "dataobjects\lumination.h"
#include "dataobjects\lighting.h"
#include "dataobjects\fragment.h"

#include "shapes\traceshape.h"
#include "shapes\sphere.h"
#include "shapes\axiscube.h"
#include "shapes\octpartitionshape.h"

#include "components\component.h"
#include "components\transform.h"
#include "components\meshfilter.h"
#include "components\texturefilter.h"

#include "components\materials\material.h"
#include "components\materials\diffusematerial.h"
#include "components\materials\blinnmaterial.h"
#include "components\materials\phongmaterial.h"
#include "components\materials\cooktorrancematerial.h"

#include "components\cameras\camera.h"

#include "components\lights\light.h"
#include "components\lights\pointlight.h"
#include "components\lights\directionallight.h"
#include "components\lights\spotlight.h"
#include "components\lights\arealight.h"

#include "tracer\entity.h"
#include "tracer\tracestack.h"
#include "tracer\tracepath.h"
#include "tracer\photo.h"
#include "tracer\photoemitter.h"