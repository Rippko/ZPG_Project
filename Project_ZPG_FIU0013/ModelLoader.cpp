#include "ModelLoader.h"
#include <GL/glew.h>
//Include GLFW
#include <GLFW/glfw3.h> 

#include <glm/vec3.hpp> 
#include <glm/vec4.hpp> 
#include <glm/mat4x4.hpp> 
#include <glm/gtc/matrix_transform.hpp> 
#include <glm/gtc/type_ptr.hpp> 
#include <glm/gtx/string_cast.hpp>

#include <SOIL.h>

#include<assimp/Importer.hpp>// C++ importerinterface
#include<assimp/scene.h>// aiSceneoutputdata structure
#include<assimp/postprocess.h>// Post processingflags

ModelLoader::ModelLoader() { }

std::vector<float> ModelLoader::loadModel(std::string path, int& count)
{
    std::vector<float> data;
    count = 0;
    Assimp::Importer importer;
    unsigned int importOptions = aiProcess_Triangulate
        | aiProcess_OptimizeMeshes              // reduce the number of draw calls
        | aiProcess_JoinIdenticalVertices       // identifies and joins identical vertex data sets within all imported meshes
        | aiProcess_Triangulate                 // triangulates all faces of all meshes 
        | aiProcess_CalcTangentSpace;           // calculates the tangents and bitangents for the imported meshes

    const aiScene* scene = importer.ReadFile(path, importOptions);

    if (scene) {
        aiMesh* mesh = scene->mMeshes[0];//Only first mesh 
        printf("Triangles:%d \n", mesh->mNumFaces);
        count = mesh->mNumFaces * 3;

        aiFace* f;
        for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
            aiFace face = mesh->mFaces[i];

            for (unsigned int j = 0; j < 3; j++)
            {
                int id = face.mIndices[j];

                //Vertex position
                aiVector3D pos = mesh->mVertices[id];
                data.push_back(pos.x);
                data.push_back(pos.y);
                data.push_back(pos.z);

                //Vertex normal
                aiVector3D nor = mesh->mNormals[id];
                data.push_back(nor.x);
                data.push_back(nor.y);
                data.push_back(nor.z);

                //Vertex uv
                aiVector3D uv = mesh->mTextureCoords[0][id];
                data.push_back(uv.x);
                data.push_back(uv.y);

            }
        }
    }
    else {
        printf("An error occurred while loading model.\n");
        exit(EXIT_FAILURE);
    };

    return data;
}
