#version 330
#define MAX_POINT_LIGHTS 10
#define MAX_DIR_LIGHTS 10
#define MAX_SPOTLIGHTS_LIGHTS 10

in vec4 fragColor;
in vec3 ex_worldPosition;
in vec3 ex_worldNormal;
in vec2 ex_uvCoords;
uniform sampler2D textureUnitID;
uniform int scalingConstant;
out vec4 color;

uniform vec3 camera_Position;

uniform int hasTexture;

struct Material{
    vec3 objectColor;
    vec3 ambientColor;
    vec3 diffuseColor;
    vec3 specularColor;
    float shininess;
};
uniform Material material;

struct SpotLight{
    int isDefined;
    vec3 position;
    vec3 direction;
    float cutOff;
    float outerCutOff;
    vec3 color;
    float constant;
    float linear;
    float quadratic;
};
uniform SpotLight spotLights[MAX_SPOTLIGHTS_LIGHTS];

struct DirLight{
    int isDefined;
    vec3 direction;
    vec3 color;
};
uniform DirLight dirLights[MAX_DIR_LIGHTS];

struct PointLight{
	int isDefined;
	vec3 position;
	vec3 color;
	float constant;
	float linear;
	float quadratic;
};
uniform PointLight pointLights[MAX_POINT_LIGHTS];

float getAttenuation(float c, float l, float q, vec3 lightPos, vec3 worldPos)
{
    float d = length(lightPos - worldPos);
    float att = 1.0 / (c + l * d + q * (d * d));
	return max(att, 0.0);
}

vec3 CalcPointLight(PointLight light, Material material, vec3 normal, vec3 fragPos, vec3 cameraPos)
{
    float attenuation = getAttenuation(light.constant, light.linear, light.quadratic, light.position, fragPos);
    
	vec3 lightVector = normalize(light.position - fragPos);

    vec3 lightDirection = normalize(light.position - ex_worldPosition);
	vec3 viewDirection = normalize(camera_Position - ex_worldPosition);

	vec3 halfVector = normalize(lightDirection + viewDirection);  
    float dot_product = max(dot(normal, lightDirection), 0.0);

    vec3 diffuse = dot_product * material.diffuseColor * light.color;
    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (normal) );
    float spec = pow(max(dot(halfVector, normal), 0.0), material.shininess);
    vec3 specular = material.specularColor * spec * light.color;
	    if(dot(normal, lightVector) < 0.0){
            specular = vec3(0.0, 0.0, 0.0);
        }

    vec3 ambient = material.ambientColor * light.color;

    return (ambient + diffuse + specular) * attenuation;
}

vec3 CalcDirLight(DirLight light, vec3 normal, Material material, vec3 cameraPos, vec3 fragPos)
{
    vec3 lightVector = normalize(-light.direction);
	vec3 viewDirection = normalize(camera_Position - ex_worldPosition);

	vec3 halfVector = normalize(light.direction + viewDirection);  
    float dot_product = max(dot(normal, light.direction), 0.0);

    vec3 viewDir = normalize(cameraPos - fragPos);
    vec3 reflectDir = reflect ( - normalize(lightVector ), normalize (normal) );
    float spec = pow(max(dot(halfVector, normal), 0.0), material.shininess);
    vec3 specular = material.specularColor * spec * light.color;
    vec3 diffuse = dot_product * material.diffuseColor * light.color;
    vec3 ambient = material.ambientColor * light.color;
    return (ambient + diffuse+specular);
}

vec3 CalcSpotLight(SpotLight light, vec3 normal, Material material, vec3 cameraPos, vec3 fragPos)
{
	vec3 lightVector = normalize(light.position - fragPos);

    vec3 lightDirection = normalize(light.position - ex_worldPosition);
	vec3 viewDirection = normalize(camera_Position - ex_worldPosition);

	vec3 halfVector = normalize(lightDirection + viewDirection);
    float dot_product = max(dot(normal, light.direction), 0.0);

    vec3 reflectDir = reflect (-normalize(lightVector), normalize (normal) );
    vec3 viewDir = normalize(cameraPos - fragPos);
    float spec = pow(max(dot(halfVector, normal), 0.0), material.shininess);
    float attenuation = getAttenuation(light.constant, light.linear, light.quadratic, light.position, fragPos);

    float theta = dot(lightVector, normalize(-light.direction)); 
    float epsilon = light.cutOff - light.outerCutOff;
    float intensity = clamp((theta - light.outerCutOff) / epsilon, 0.0, 1.0);

    /*
    if(intensity > 0) {
        intensity = 1;
    }*/

    vec3 diffuse = dot_product * material.diffuseColor * light.color * intensity;
    vec3 specular = material.specularColor * spec * light.color * intensity;
	vec3 ambient = material.ambientColor * light.color * intensity;

    return (ambient+diffuse+specular) * attenuation;
}

void main(void){
    vec4 objectColor = vec4(material.objectColor, 1.0f);
    vec3 norm = normalize(ex_worldNormal);
    vec3 result;

    for(int i = 0; i < MAX_DIR_LIGHTS; i++)
    {
		if(dirLights[i].isDefined == 1)
            result += CalcDirLight(dirLights[i], norm, material, camera_Position, ex_worldPosition);
    }


    for(int i = 0; i < MAX_POINT_LIGHTS; i++)
    {
		if(pointLights[i].isDefined == 1)
            result += CalcPointLight(pointLights[i], material, norm, ex_worldPosition, camera_Position);
    }

    for(int i = 0; i < MAX_SPOTLIGHTS_LIGHTS; i++)
    {
		if(spotLights[i].isDefined == 1){
            result += CalcSpotLight(spotLights[i], norm, material, camera_Position, ex_worldPosition);
        }
    }
    
    if(hasTexture == 1){
        color = vec4(result, 1.0f) * texture(textureUnitID, (ex_uvCoords * scalingConstant));
    }
    else{
        color = vec4(result, 1.0f) * objectColor;
    }
}