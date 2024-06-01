#include <Cube.hpp>
#include <Renderer.hpp>

Cube::Cube()
{
    faces = {
        {{{-1, -1, -1}, {1, -1, -1}, {1, 1, -1}, {-1, 1, -1}}, {1.0f, 0.0f, 0.0f, 1.0f}}, // back face, red
        {{{-1, -1, 1}, {1, -1, 1}, {1, 1, 1}, {-1, 1, 1}}, {0.0f, 1.0f, 0.0f, 1.0f}},     // front face, green
        {{{-1, -1, -1}, {-1, 1, -1}, {-1, 1, 1}, {-1, -1, 1}}, {0.0f, 0.0f, 1.0f, 1.0f}}, // left face, blue
        {{{1, -1, -1}, {1, 1, -1}, {1, 1, 1}, {1, -1, 1}}, {1.0f, 1.0f, 0.0f, 1.0f}},     // right face, yellow
        {{{-1, -1, -1}, {1, -1, -1}, {1, -1, 1}, {-1, -1, 1}}, {1.0f, 0.0f, 1.0f, 1.0f}}, // bottom face, magenta
        {{{-1, 1, -1}, {1, 1, -1}, {1, 1, 1}, {-1, 1, 1}}, {0.0f, 1.0f, 1.0f, 1.0f}}      // top face, cyan
    };
}

Cube::~Cube() = default;

void Cube::render()
{
    glPushMatrix();
    glTranslatef(position.x, position.y, position.z);
    glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
    glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
    glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);
    glScalef(scale.x, scale.y, scale.z);

    glBegin(GL_QUADS);

    for (const auto &face : faces)
    {
        glColor4f(face.color.r, face.color.g, face.color.b, face.color.a);
        for (const auto &vertex : face.vertices)
        {
            glVertex3f(vertex.x, vertex.y, vertex.z);
        }
    }

    glEnd();
    glPopMatrix();
}

void Cube::update(float deltaTime)
{
    rotation.y += 90.0f * deltaTime;
}