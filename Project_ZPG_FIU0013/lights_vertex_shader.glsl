#version 400
layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normalposition;
layout(location = 2) in vec2 uvCoords;
out vec3 ex_worldPosition;
out vec3 ex_worldNormal;
out vec2 ex_uvCoords;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
void main() {
	gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4 (position, 1.0);
	ex_worldPosition = vec3 (modelMatrix * vec4(position,1.0f));
	ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * normalposition);
	ex_uvCoords = uvCoords;
}