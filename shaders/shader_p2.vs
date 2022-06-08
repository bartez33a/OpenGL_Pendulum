#version 330 core
layout (location = 0) in vec3 aPos;
out vec3 ourColor;

uniform mat4 transform;

bool less_than(float x, float ref, float delta)
{
	return (abs(x-ref) < delta);
}


void main()
{

//rotate vector 2d by angle in degrees
float offset_x = 0.0f;
float angle = 0.0f * 2 * 3.14f / 360.0f;

float newX = aPos.x * cos(angle) - aPos.y * sin(angle) + offset_x;
float newY = aPos.x * sin(angle) + aPos.y * cos(angle);

ourColor.x = newX;
ourColor.y = newY;
ourColor.z = aPos.z;

// macierz translacji * nasza macierz!!! nie odwrotnie
if (less_than(aPos.x, 0.0f, 0.01f) && less_than(aPos.y, 1.0f, 0.01f))
{
	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0) ;
}
else
{
	gl_Position = transform * vec4(aPos.x, aPos.y, aPos.z, 1.0) ;
}

}

//2 pi -> 360'
//rad - deg
// rad = 2pi*deg / 360