#include "TransformationComposite.h"

glm::mat4 TransformationComposite::TransformMatrix()
{
    glm::mat4 matrix1 = glm::mat4(1.f);
    for (int i = 0; i < all_transformations.size(); i++) {
        matrix1 *= all_transformations[i]->TransformMatrix();
    }
    return matrix1;
}

void TransformationComposite::Add(Transformation* ts)
{
    all_transformations.push_back(ts);
}
