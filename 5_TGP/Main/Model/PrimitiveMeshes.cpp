#include "PrimitiveMeshes.h"

const Vertex Primitives::CubeVertices[8] =
{
	{ -0.5f, -0.5f, -0.5f, 1.0f,   1.0f, 0.2f, 0.2f, 1.0f },
	{  0.5f, -0.5f, -0.5f, 1.0f,   0.2f, 1.0f, 0.2f, 1.0f },
	{  0.5f,  0.5f, -0.5f, 1.0f,   0.2f, 0.2f, 1.0f, 1.0f },
	{ -0.5f,  0.5f, -0.5f, 1.0f,   1.0f, 1.0f, 0.2f, 1.0f },
	{ -0.5f, -0.5f,  0.5f, 1.0f,   0.2f, 1.0f, 1.0f, 1.0f },
	{  0.5f, -0.5f,  0.5f, 1.0f,   1.0f, 0.2f, 1.0f, 1.0f },
	{  0.5f,  0.5f,  0.5f, 1.0f,   1.0f, 1.0f, 1.0f, 1.0f },
	{ -0.5f,  0.5f,  0.5f, 1.0f,   0.5f, 0.5f, 0.5f, 1.0f },
};

const unsigned int Primitives::CubeIndices[36] =
{
	0,2,1,  0,3,2,
	1,6,5,  1,2,6,
	5,7,4,  5,6,7,
	4,3,0,  4,7,3,
	3,6,2,  3,7,6,
	4,1,5,  4,0,1,
};

const Vertex Primitives::PyramidVertices[5] =
{
	{ -0.5f, 0.0f, -0.5f, 1.0f,   1.0f, 0.5f, 0.0f, 1.0f },
	{  0.5f, 0.0f, -0.5f, 1.0f,   1.0f, 0.8f, 0.0f, 1.0f },
	{  0.5f, 0.0f,  0.5f, 1.0f,   0.8f, 0.5f, 0.0f, 1.0f },
	{ -0.5f, 0.0f,  0.5f, 1.0f,   1.0f, 0.3f, 0.0f, 1.0f },
	{  0.0f, 1.0f,  0.0f, 1.0f,   1.0f, 1.0f, 0.5f, 1.0f },
};

const unsigned int Primitives::PyramidIndices[18] =
{
	0,2,1,  0,3,2,
	0,1,4,
	1,2,4,
	2,3,4,
	3,0,4,
};