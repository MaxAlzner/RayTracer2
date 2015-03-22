
#include "../include/Ray_main.h"

#ifdef RAY_BUFFERS_H_
RAY_BEGIN

ColorBuffer::ColorBuffer()
{
	this->buffer = 0;
	this->size = 0;
	this->width = 0;
	this->height = 0;
}
ColorBuffer::ColorBuffer(int width, int height)
{
	this->width = Max(width, 1);
	this->height = Max(height, 1);
	this->size = this->width * this->height;
	this->buffer = new COLOR[this->size];
}
ColorBuffer::~ColorBuffer()
{
	if (this->buffer != 0) delete [] this->buffer;
	memset(this, 0, sizeof(ColorBuffer));
}

COLOR& ColorBuffer::operator[](const int index)
{
	int i0 = index % this->size;
	return this->buffer[i0];
}

void ColorBuffer::put(const int x, const int y, COLOR& color)
{
	int x0 = x % this->width;
	int y0 = y % this->height;
	this->buffer[(y0 * this->width) + x0] = color;
}
COLOR& ColorBuffer::get(const int x, const int y)
{
	int x0 = x % this->width;
	int y0 = y % this->height;
	return this->buffer[(y0 * this->width) + x0];
}

HitBuffer::HitBuffer()
{
	this->buffer = 0;
	this->size = 0;
	this->stride = 0;
	this->width = 0;
	this->height = 0;
}
HitBuffer::HitBuffer(int width, int height, int depth)
{
	this->stride = Max(depth, 1);
	this->width = Max(width, 1);
	this->height = Max(height, 1);
	this->size = this->width * this->height * this->stride;
	this->buffer = new RayHit[this->size];
}
HitBuffer::~HitBuffer()
{
	if (this->buffer != 0) delete [] this->buffer;
	memset(this, 0, sizeof(HitBuffer));
}

RayHit& HitBuffer::operator[](const int index)
{
	int i0 = index % this->size;
	return this->buffer[i0];
}

void HitBuffer::put(const int x, const int y, const int z, RayHit& hit)
{
	int x0 = x % this->width;
	int y0 = y % this->height;
	int z0 = z % this->stride;
	this->buffer[(z0 * this->width * this->height) + (y0 * this->width) + x0] = hit;
}
RayHit& HitBuffer::get(const int x, const int y, const int z)
{
	int x0 = x % this->width;
	int y0 = y % this->height;
	int z0 = z % this->stride;
	return this->buffer[(z0 * this->width * this->height) + (y0 * this->width) + x0];
}

RAY_END
#endif