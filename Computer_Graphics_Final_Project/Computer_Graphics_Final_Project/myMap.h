#pragma once

#include<iostream>
#include<time.h>
#include<random>
#include<windows.h>
#include<vector>

//#include<gl/glew.h>
//#include<gl/freeglut.h> 
//#include<gl/freeglut_ext.h> 
//#include<gl/glm/glm/glm.hpp>
//#include<gl/glm/glm/ext.hpp>
//#include<gl/glm/glm/gtc/matrix_transform.hpp>
//#include<gl/glm/glm/gtc/type_ptr.hpp>
#include "glew.h"
#include "freeglut.h"
#include "freeglut_ext.h"
#include "freeglut_std.h"
#include "glm.hpp"
#include "ext.hpp"
#include "gtc/matrix_transform.hpp"
#include "ReadObj.h"

std::vector< glm::vec3 > cube_vertices;
std::vector< glm::vec2 > cube_uvs;
std::vector< glm::vec3 > cube_normals;

std::vector< glm::vec3 > pyramid_vertices;
std::vector< glm::vec2 > pyramid_uvs;
std::vector< glm::vec3 > pyramid_normals;

std::vector< glm::vec3 > wheel_vertices;
std::vector< glm::vec2 > wheel_uvs;
std::vector< glm::vec3 > wheel_normals;

glm::vec3 Red = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Green = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Blue = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Gray = glm::vec3(0.7f, 0.7f, 0.7f);
glm::vec3 White = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 Black = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Yellow = glm::vec3(1.0f, 1.0f, 0.0f);
glm::vec3 Brown = glm::vec3(0.58f, 0.29f, 0.0f);

glm::mat4 S = glm::mat4(1.0f);
glm::mat4 T = glm::mat4(1.0f);
glm::mat4 Rx = glm::mat4(1.0f);
glm::mat4 Ry = glm::mat4(1.0f);
glm::mat4 Rz = glm::mat4(1.0f);
glm::mat4 STR = glm::mat4(1.0f);

float Wheel_R = 0.0f;

void DrawMap();