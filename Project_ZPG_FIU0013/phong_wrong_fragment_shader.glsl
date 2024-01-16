#version 330
		in vec3 fragColor;
		out vec4 color;
		in vec3 ex_worldNormal;
		in vec3 ex_worldPosition;
		in mat4 normalMatrix;
		uniform vec3 light_Color;
		uniform vec3 light_Position;
		uniform vec3 specular_Color;
		uniform float specularStrength;
		uniform float diffuseStrength;
		uniform vec3 camera_Position;

		void main () {
			color = vec4(fragColor, 1.0f);
			vec4 lightColor = vec4(light_Color, 1.0f);
			vec4 specularColor = vec4(specular_Color, 1.0);
			vec3 normal = normalize(ex_worldNormal);
			vec3 lightDirection = normalize(light_Position - ex_worldPosition);
			vec3 reflectDirection = reflect(-lightDirection, normal);
			vec3 viewDirection = normalize(camera_Position - ex_worldPosition);
			vec4 ambient = vec4(0.1, 0.1, 0.1, 1.0);
			float dot_product = max(dot(normal, lightDirection), 0.0);
			vec4 diffuse = dot_product * lightColor * diffuseStrength;
			float spec = pow(max(dot(reflectDirection, viewDirection), 0.0), 1);
			vec4 specular = specularStrength * spec * specularColor ;
			color = (ambient + specular + diffuse) * vec4(fragColor, 1.0f);

		};