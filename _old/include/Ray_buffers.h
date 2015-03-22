#ifndef RAY_BUFFERS_H_
#define RAY_BUFFERS_H_
RAY_BEGIN

typedef struct ColorBuffer
{
	ColorBuffer();
	ColorBuffer(int width, int height);
	~ColorBuffer();

	COLOR& operator[](const int index);

	void put(const int x, const int y, COLOR& color);
	COLOR& get(const int x, const int y);

	COLOR* buffer;
	int size;
	int width;
	int height;

} ColorBuffer;

typedef struct HitBuffer
{
	HitBuffer();
	HitBuffer(int width, int height, int depth);
	~HitBuffer();

	RayHit& operator[](const int index);

	void put(const int x, const int y, const int z, RayHit& hit);
	RayHit& get(const int x, const int y, const int z);

	RayHit* buffer;
	int size;
	int stride;
	int width;
	int height;

} HitBuffer;

RAY_END
#endif