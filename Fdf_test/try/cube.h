#ifndef CUBE_H
# define CUBE_H

typedef struct Vec3d 
{
	float x;
	float y;
	float z;
}				vec3d;

typedef struct Triangle 
{
	vec3d P[3]; // P for points
}				triangle;

typedef struct Mat4x4
{
	float m[4][4] = {0};
}			   mat4x4;

/*typedef struct Mesh 
{
	triangle tris;
}				mesh;*/

#endif