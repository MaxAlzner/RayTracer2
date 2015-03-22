
#include "../include/Ray_main.h"

#ifdef RAY_PHOTO_H_
RAY_BEGIN

Photo::Photo()
{
	this->render = 0;
}
Photo::Photo(int width, int height)
{
	this->render = new ColorBuffer(width, height);
}
Photo::~Photo()
{
	delete this->render;
}

void Photo::registerRay(int x, int y, RayPath& path)
{
	COLOR color(0.3f);

	if (path.path.length() > 0)
	{
		RayHit* hit = &path.path[0];
		SurfaceLumination* lum = hit->lumination;
		Material* mat = hit->surface->material;

		color = (mat->overlay * lum->diffuse/* * lum->attenuation*/) + (mat->highlight * lum->specular * lum->brdf);
		//color = COLOR(hit->texcoord.x, hit->texcoord.y, 0.0f);
		//color = COLOR(0.0f, 0.0f, hit->traveled / 8.0f);
	}

	this->render->put(x, y, color);
}

void Photo::flatten()
{
}
void Photo::package()
{
	SURFACE* surface = 0;
	int width = this->render->width;
	int height = this->render->height;
	CreateSurface(&surface, "RenderTest.bmp", width, height, PIXELFORMAT_BGR);

	for (int i = 0; i < this->render->size; i++)
	{
		COLOR color = (*this->render)[i];
		PutPixel(surface, i % width, height - (i / width) - 1, color);
	}

	ExportBMPFile(surface->name, surface);
	FreeSurface(&surface);
}

RAY_END
#endif