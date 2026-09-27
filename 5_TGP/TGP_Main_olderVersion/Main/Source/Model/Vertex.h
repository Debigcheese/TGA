#pragma once

struct Vertex
{
	float x, y, z, w;
	float r, g, b, a;

	float u, v;
	float nx, ny, nz;

	float tx, ty, tz;  // tangent
	float bx, by, bz;  // bitangent
};
