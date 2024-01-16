#version 330
	in vec3 fragColor;
	out vec4 color;
	in vec3 ex_worldNormal;
	in vec3 ex_worldPosition;
	in mat4 normalMatrix;
	uniform vec3 light_Color;
	uniform vec3 light_Position;
	uniform vec3 camera_Position;

	uniform vec3 ambientColor;
	uniform vec3 diffuseColor;
	uniform vec3 specularColor;
	uniform float shininess;
	uniform float Kc;
	uniform float Kl;
	uniform float Kq;

	void main () {
		float spec = 0.0f;
		color = vec4(fragColor, 1.0f);
		vec4 lightColor = vec4(light_Color, 1.0f);
		vec4 specularColor = vec4(specularColor, 1.0);
		vec4 ambient = vec4(ambientColor, 1.0);

		vec3 normal = normalize(ex_worldNormal);
		vec3 lightDirection = normalize(light_Position - ex_worldPosition);
		vec3 viewDirection = normalize(camera_Position - ex_worldPosition);	

		vec3 halfVector = normalize(lightDirection + viewDirection);  
		spec = pow(max(dot(normal, halfVector), 0.0), shininess);

		float dot_product = max(dot(normal, halfVector), 0.0);
		vec4 diffuse = dot_product * lightColor * specularColor;
		vec4 specular = lightColor * spec;
		color = (ambient + specular + diffuse) * vec4(fragColor, 1.0f);
	};