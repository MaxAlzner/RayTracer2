#ifndef RAY_PHOTO_H_
#define RAY_PHOTO_H_
RAY_BEGIN

class Photo
{
public:

	Photo();
	Photo(int width, int height);
	~Photo();

	void registerRay(int x, int y, RayPath& path);

	void flatten();
	void package();

	ColorBuffer* render;

};

RAY_END
#endif