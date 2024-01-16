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
		color = vec4(fragColor, 1.0f);
		vec4 lightColor = vec4(light_Color, 1.0f);
		vec4 specularColor = vec4(specularColor, 1.0);
		vec4 ambient = vec4(ambientColor, 1.0);
		vec3 normal = normalize(ex_worldNormal);

		float distance = length(ex_worldPosition - light_Position);
		float attenuation = 1.0 / (Kc + Kl * distance + Kq * distance * distance);

		vec3 lightDirection = normalize(light_Position - ex_worldPosition);
		vec3 reflectDirection = reflect(-lightDirection, normal);
		vec3 viewDirection = normalize(camera_Position - ex_worldPosition);

		float dot_product = max(dot(normal, lightDirection), 0.0);
		vec4 diffuse = dot_product * lightColor * specularColor;
		float spec = pow(max(dot(reflectDirection, viewDirection), 0.0), shininess);
		vec4 specular = specularColor * spec;
		color = (ambient + specular + diffuse) * vec4(0.5f, 0.5f, 0.5f, 1.0f) * attenuation;
	};