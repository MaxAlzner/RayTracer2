#ifndef RAY_DEF_H_
#define RAY_DEF_H_

#define RAY_BEGIN namespace RAY {
#define RAY_END }
#define SHAPE_BEGIN namespace SHAPE {
#define SHAPE_END }
#define PIPE_BEGIN namespace PIPE {
#define PIPE_END }

RAY_BEGIN
	
typedef class Object Object;
typedef class Entity Entity;

typedef class Camera Camera;
typedef class Light Light;
typedef class Shape Shape;

typedef class Scene Scene;
	
extern bool AppRunning;

RAY_END
#endif