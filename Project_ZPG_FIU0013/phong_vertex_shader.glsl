#version 400
		layout(location=0) in vec3 inPosition;
		layout(location=1) in vec3 inColor;
		out vec3 fragColor;
		out vec3 ex_worldNormal;
		out vec3 ex_worldPosition;
		out mat4 normalMatrix;
		uniform mat4 modelMatrix;
		uniform mat4 viewMatrix;
		uniform mat4 projectionMatrix;
		void main () {
			gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(inPosition, 1.f);
			fragColor = inColor;
			mat4 normalMatrix = transpose(inverse(modelMatrix));
			ex_worldNormal = normalize(transpose(inverse(mat3(modelMatrix))) * inColor);
			ex_worldPosition = vec3(modelMatrix * vec4(inPosition, 1.0));
		};