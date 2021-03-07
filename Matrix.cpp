#include "Matrix.h"

std::unordered_map<std::string, glm::mat4> Matrix::playerModelMatrix()
{
    std::unordered_map<std::string, glm::mat4> playerModel;
    float scaleX = 1.2f, scaleZ = 1.4f;
    float scale = 1.5f;
    
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(scaleX, 1, scaleZ);
    playerModel["body"] = modelMatrix;
    
    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Translate(0, 0, -1 * scaleX * scale);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(scaleX, 1, 1);
    playerModel["front"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Translate(-0.25f * scaleX * scale, 0, 0.5f * scaleZ * scale);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
    playerModel["thruster1"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Translate(0.25f * scaleX * scale, 0, 0.5f * scaleZ * scale);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
    playerModel["thruster2"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Translate(0, 0, 0.3f);
    modelMatrix *= Transform3D::Translate(-0.25f * scaleX * scale, 0, 0.5f * scaleZ * scale);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.6f, 1.5f, 0.5f);
    modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
    playerModel["flame1"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Scale(0.35f, 0.35f, 0.35f);
    modelMatrix *= Transform3D::Translate(0, 0, 0.3f);
    modelMatrix *= Transform3D::Translate(0.25f * scaleX * scale, 0, 0.5f * scaleZ * scale);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.6f, 1.5f, 0.5f);
    modelMatrix *= Transform3D::Scale(0.3f, 0.3f, 0.3f);
    playerModel["flame2"] = modelMatrix;

    return playerModel;
}

std::unordered_map<std::string, glm::mat4> Matrix::alienModelMatrix()
{
    std::unordered_map<std::string, glm::mat4> alienModel;
    float scaleX = 1.7f, scaleY = 0.45f, scaleZ = 1.7f;
    float scale = 5;

    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90)); 
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(scaleX, scaleZ, scaleY);
    alienModel["body"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(0, 0.5f * scaleY * 0.8f * scale, 0);
    modelMatrix *= Transform3D::RotateOX(RADIANS(-90));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.8f, 0.8f, 0.8f);
    alienModel["cockpit"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(0, -0.7f * scaleY * scale, 0);
    modelMatrix *= Transform3D::RotateOX(RADIANS(180));
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.2f, 0.2f, 0.2f);
    alienModel["ray"] = modelMatrix;

    modelMatrix = glm::mat4(1);
    modelMatrix *= Transform3D::Translate(0, -0.9f * scaleY * scale, 0);
    modelMatrix *= Transform3D::Scale(scale, scale, scale);
    modelMatrix *= Transform3D::Scale(0.05f, 0.05f, 0.05f);
    alienModel["light"] = modelMatrix;

    return alienModel;
}
