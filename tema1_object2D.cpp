#include "tema1_object2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"


Mesh* tema1_object2D::CreateSquare(
    const std::string &name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner, color),
        VertexFormat(corner + glm::vec3(length, 0, 0), color),
        VertexFormat(corner + glm::vec3(length, length, 0), color),
        VertexFormat(corner + glm::vec3(0, length, 0), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    } else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* tema1_object2D::CreateCannon(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, length, 0), color),  // A 0
        VertexFormat(corner + glm::vec3(length, length/ 3, 0), color), // B 1
        VertexFormat(corner + glm::vec3(2 * length, length / 3, 0), color), // C 2
        VertexFormat(corner + glm::vec3(2 * length, (- 1) * length / 3, 0), color), //D 3
        VertexFormat(corner + glm::vec3(length, (-1) * (length /3), 0), color), // E 4
        VertexFormat(corner + glm::vec3(0, (- 1) * length, 0), color), // F 5
        VertexFormat(corner + glm::vec3((- 1) * length, 0, 0), color) // G  6
    };

    Mesh* cannon = new Mesh(name);
    //std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6};
    std::vector<unsigned int> indices;

    if (!fill) {
        cannon->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3, 4, 5, 6 };
    }
    else {
        cannon->SetDrawMode(GL_TRIANGLES);
        indices = {1, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1 };
    
    }

    cannon->InitFromData(vertices, indices);
    return cannon;
}

Mesh* tema1_object2D::CreateProjectile(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, length, 0), color),  // A
        VertexFormat(corner + glm::vec3(length / 2, 0, 0), color), // B
        VertexFormat(corner + glm::vec3(length, 0, 0), color), // C
        VertexFormat(corner + glm::vec3(length / 2, (-1) * length / 2, 0), color), //D
        VertexFormat(corner + glm::vec3(length, (-1) * length, 0), color), // E -- ok
        VertexFormat(corner + glm::vec3(0, (-1) * length / 2, 0), color), // F
        VertexFormat(corner + glm::vec3((-1) * (length), (-1) * (length) , 0), color), // G
        VertexFormat(corner + glm::vec3((-1) * (length / 2), (-1) * (length / 2), 0), color), // H -- ok
        VertexFormat(corner + glm::vec3((-1) * length, 0, 0), color), // I
        VertexFormat(corner + glm::vec3((-1) * length / 2, 0, 0), color) // G

    };

    Mesh* projectile = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        projectile->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
    }
    else {
        projectile->SetDrawMode(GL_TRIANGLES);
        indices = { 1, 2, 3, 0, 3, 4, 0, 4, 5, 0, 5, 6, 0, 6, 1, 7, 8, 9 };
    }

    projectile->InitFromData(vertices, indices);
    return projectile;
}


Mesh* tema1_object2D::CreateEnemy(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, length, 0), color),  // A
        VertexFormat(corner + glm::vec3(length, length, 0), color),  // B
        VertexFormat(corner + glm::vec3(2 * length, 0, 0), color),  // C
        VertexFormat(corner + glm::vec3(length, (-1) * length, 0), color),  // D
        VertexFormat(corner + glm::vec3(0, (-1) * length, 0), color),  // E
        VertexFormat(corner + glm::vec3((-1) * length, 0, 0), color)  // F

    };

    Mesh* projectile = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        projectile->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3, 4, 5 };
    }
    else {
        projectile->SetDrawMode(GL_TRIANGLES);
        indices = { 0, 1, 3, 1, 2, 3, 0, 3, 4, 0, 4, 5 };
    }

    projectile->InitFromData(vertices, indices);
    return projectile;
}




Mesh* tema1_object2D::CreateHearts(
    const std::string& name,
    glm::vec3 leftBottomCorner,
    float length,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 corner = leftBottomCorner;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(corner + glm::vec3(0, length/ 2, 0), color),  // A
        VertexFormat(corner + glm::vec3(length / 2, length, 0), color),  // B
        VertexFormat(corner + glm::vec3(length, length, 0), color),  // C
        VertexFormat(corner + glm::vec3(0, (-1) * (length / 2), 0), color),  // D
        VertexFormat(corner + glm::vec3((-1) * length, length, 0), color),  // E
        VertexFormat(corner + glm::vec3((-1) * (length / 2), length, 0), color)  // F

    };

    Mesh* projectile = new Mesh(name);
    std::vector<unsigned int> indices;

    if (!fill) {
        projectile->SetDrawMode(GL_LINE_LOOP);
        indices = { 0, 1, 2, 3, 4, 5 };
    }
    else {
        projectile->SetDrawMode(GL_TRIANGLES);
        indices = { 0, 1, 2, 2, 3, 0, 0, 3, 4, 0, 4, 5 };
    }

    projectile->InitFromData(vertices, indices);
    return projectile;
}
