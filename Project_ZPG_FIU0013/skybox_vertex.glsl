#version 450
layout(location=0) in vec3 vp;

uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 camera_Position;

out vec3 fragmentLocalPosition;

void main()
{

    gl_Position = projectionMatrix * mat4(mat3(viewMatrix)) * vec4(vp, 1.0f);
    fragmentLocalPosition = vp;
}