#pragma once
#include "myMap.h"

bool res_cube = loadOBJ("cube.obj", cube_vertices, cube_uvs, cube_normals);
bool res_pyramid = loadOBJ("pyramid.obj", pyramid_vertices, pyramid_uvs, pyramid_normals);
bool res_wheel = loadOBJ("top.obj", wheel_vertices, wheel_uvs, wheel_normals);

void DrawMap()
{

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 2.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(Wheel_R), glm::vec3(0.0f, 0.0f, 1.0f));
    unsigned int Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(Rz * S));
    unsigned int Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    // ∞Ê∑Œ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(40.0, 0.5, 5.0));
    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(S));
    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(50.0, 5.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(65.0, 10.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(80.0, 7.5, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    //≈È¥œ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(Wheel_R), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, 0.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T * Rz * S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());
    S = glm::scale(glm::mat4(1.0f), glm::vec3(24.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(110.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    Ry = glm::rotate(glm::mat4(1.0f), float(glm::radians(90.0)), glm::vec3(0.0, 1.0, 0.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(130.0, 0.0, 19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(150.0, 0.0, 38.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(170.0, 0.0, 19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(190.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(210.0, 0.0, -19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(230.0, 0.0, -38.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(250.0, 0.0, -19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(270.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(295.0 - Open_Ground, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    T = glm::translate(glm::mat4(1.0f), glm::vec3(315.0 + Open_Ground, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 0.5f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(335.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0, -19.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
}