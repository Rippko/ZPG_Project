#include "Shader.h"
#include <format>

Shader::Shader(const char* input_vertex_shader, const char* input_fragment_shader)
{
	std::string vertexShaderSource = loadShader(input_vertex_shader);
	std::string fragmentShaderSource = loadShader(input_fragment_shader);

	const char* vertexShaderCode = vertexShaderSource.c_str();
	const char* fragmentShaderCode = fragmentShaderSource.c_str();

	//creating shaders
	this->vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(this->vertexShader, 1, &vertexShaderCode, NULL);
	glCompileShader(this->vertexShader);
	this->fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(this->fragmentShader, 1, &fragmentShaderCode, NULL);
	glCompileShader(this->fragmentShader);
	this->shaderProgram = glCreateProgram();
	glAttachShader(this->shaderProgram, this->fragmentShader);
	glAttachShader(this->shaderProgram, this->vertexShader);
	glLinkProgram(this->shaderProgram);

	ShaderCheck();
}

std::string Shader::loadShader(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open()) {
		std::cerr << "Unable to open file: " << path << std::endl;
		return "";
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	return buffer.str();
}

void Shader::ShaderCheck()
{
	//compilation and linking shader check
	GLint status;
	glGetProgramiv(this->shaderProgram, GL_LINK_STATUS, &status);
	if (status == GL_FALSE)
	{
		GLint infoLogLength;
		glGetProgramiv(this->shaderProgram, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* strInfoLog = new GLchar[infoLogLength + 1];
		glGetProgramInfoLog(this->shaderProgram, infoLogLength, NULL, strInfoLog);
		fprintf(stderr, "Linker failure: %s\n", strInfoLog);
		delete[] strInfoLog;
	}
}

void Shader::UseShaderProgram()
{
	glUseProgram(shaderProgram);
}

void Shader::LinkDataToShader(const char* name, const int value)
{
	glUniform1i(glGetUniformLocation(this->shaderProgram, name), value);
}

void Shader::LinkDataToShader(const char* name, const float value)
{
	glUniform1f(glGetUniformLocation(this->shaderProgram, name), value);
}

void Shader::LinkDataToShader(const char* name, const glm::mat4& matrix)
{
	glUniformMatrix4fv(glGetUniformLocation(this->shaderProgram, name), 1, GL_FALSE, glm::value_ptr(matrix));
}

void Shader::LinkDataToShader(const char* name, const glm::vec3& vec3)
{
	glUniform3fv(glGetUniformLocation(this->shaderProgram, name), 1, glm::value_ptr(vec3));
}

void Shader::updateCamera(const glm::vec3& cameraPos, const glm::vec3& cameraFront, const glm::mat4& viewMatrix, const glm::mat4& projectionMatrix)
{
	UseShaderProgram();
	LinkDataToShader("camera_Position", cameraPos);
	LinkDataToShader("viewMatrix", viewMatrix);
	LinkDataToShader("projectionMatrix", projectionMatrix);
}

void Shader::updatePointLight(int index, const glm::vec3& lightPos, const glm::vec3& lightColor, float Kc, float Kl, float Kq)
{

	UseShaderProgram();
	LinkDataToShader("normalMatrix", glm::mat4(1.0f));
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].isDefined").c_str(), 1);
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].position").c_str(), lightPos);
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].color").c_str(), lightColor);
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].constant").c_str(), Kc);
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].linear").c_str(), Kl);
	LinkDataToShader(("pointLights[" + std::to_string(index) + "].quadratic").c_str(), Kq);
}

void Shader::updateDirLight(int index, const glm::vec3& lightDir, const glm::vec3& lightColor, float Kc, float Kl, float Kq)
{
	UseShaderProgram();
	LinkDataToShader("normalMatrix", glm::mat4(1.0f));
	LinkDataToShader(("dirLights[" + std::to_string(index) + "].isDefined").c_str(), 1);
	LinkDataToShader(("dirLights[" + std::to_string(index) + "].direction").c_str(), lightDir);
	LinkDataToShader(("dirLights[" + std::to_string(index) + "].color").c_str(), lightColor);
}

void Shader::updateSpotlight(int index, const glm::vec3& lightPos, const glm::vec3& lightDir, float cutOff, float outerCutOff, const glm::vec3& lightColor, float Kc, float Kl, float Kq)
{
	UseShaderProgram();
	LinkDataToShader("normalMatrix", glm::mat4(1.0f));
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].isDefined").c_str(), 1);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].color").c_str(), lightColor);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].position").c_str(), lightPos);
	//printf("Position: %f %f %f\n", lightPos.x, lightPos.y, lightPos.z);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].direction").c_str(), lightDir);
	//printf("Direction: %f %f %f\n", lightDir.x, lightDir.y, lightDir.z);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].cutOff").c_str(), glm::cos(glm::radians(cutOff)));
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].outerCutOff").c_str(), glm::cos(glm::radians(outerCutOff)));
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].constant").c_str(), Kc);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].linear").c_str(), Kl);
	LinkDataToShader(("spotLights[" + std::to_string(index) + "].quadratic").c_str(), Kq);
}
