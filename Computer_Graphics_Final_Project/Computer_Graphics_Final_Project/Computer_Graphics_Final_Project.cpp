﻿#include<iostream>
#include<time.h>
#include<random>
#include<windows.h>
#include<vector>
#include<math.h>
#include<windows.h>
#include<mmsystem.h>
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
//#include "myMap.h"
#include "ReadObj.h"
#pragma comment(lib,"winmm.lib")

#define WIDTH 1500
#define HEIGHT 900
#define PI 3.141592
#pragma warning(disable:4996)
using namespace std;

GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
void make_vertexshader();
void make_fragmentshader();
void InitShader();
void InitBuffer();
void Keyboard(unsigned char, int, int);
void SpecialKeyboard(int key, int x, int y);
void SpecialKeyboardup(int key, int x, int y);
void Timerfunction(int);
bool coilision(float, float);
bool coilsion_obs(float x, float y, float z, float can_x, float can_y, float can_z, float dist);
void get_time();
GLvoid DrawMap();
GLvoid DrawPlayer();
GLvoid DrawObsRect();
GLvoid DrawObsWheel();
GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint s_program[3];
GLUquadricObj* qobj;

float delta_time = 0.0f;

float Camera_xPos = 0.0f;
float Camera_yPos = 0.0f;
float Camera_zPos = 0.0f;

float Camera_xAT = 0.0f;
float Camera_yAT = 0.0f;
float Camera_zAT = 0.0f;

float x_pos = 60.0f;
float y_pos = 60.0f;
float z_pos = 60.0f;

bool one_cam = false;
bool thrid_cam = true;

float cam_y_dis = 1.0f;

float degree = 90.0f;
float degree_vec = 2.0f;

float camera_rt = 0.0f;
float camera_rt_vec = 10.0f;

float Proj_degree = 100.0f;

float light_x = -15.0;
float light_y = 15.0;
float light_z = 0.0;

float light_r = 1.0;
float light_g = 1.0;
float light_b = 1.0;

float rad = 1.0f;

// 블럭 스피드
float block_x[3] = { 15.0f,35.0f,55.0f };
float block_y[3] = { 58.0f,33.0f,49.0f };
float block_vec[3] = { 0.02f,0.025f,0.01f };

// 캔 trans 좌표 변수
float can_t_x = 20.0f;
float can_t_y = 60.0f;
float can_t_z = 0.0f;
float acceleration = 0.0f;

// 캔의 x, y ,z 속도 벡터
float can_x_vec = 0.03f;
float can_y_vec = 0.03f;
float can_z_vec = 0.1f;

// 캔의 x, y, z 회전률 
float can_x_rt = 10.0f;
float can_y_rt = 10.0f;
float can_z_rt = 30.0f;

float can_rt = 90.0f;
float can_rotate = 0.0f;

float min_jump = 0.0f;
float jump_y_vec = 0.03f;

// 마우스 불 변수
bool mouse_botton;
bool jump_button;
int jump_cnt = 0;

float ofwheel_degree = 0.0f;
float tfwheel_degree[3] = { 0.0f, };
float tfwheel_degree_vec[3] = { 0.3f,0.35f,0.4f };
float wheel_t_x[3] = { 75.0f,3.0f,75.0f };
float wheel_vec[3] = { 0.03f, 0.04f, 0.05f };
float Wheel_t_x1 = 75.0f;
float Wheel_t_x2 = 3.0f;
float Wheel_vec = 0.3f;
float light_vec = 0.00001f;

float rollvec = 0.02f;

float rollwheel_x[10]{ 0, };
float rollwheel_y[10]{ 0, };
float rollwheel_degree[10]{ 0, };
float rollwheel_degree_vec = 0.1f;
bool wheel_roll[10] = { true, false, false, false, false, false, false, false, false, false };
bool sound = true;

int frame = 0, timebase = 0;

int bgsound = 0;
int vicsound = 0;
int sirensound = 0;
int oversound = 0;

glm::vec3 Red = glm::vec3(1.0f, 0.0f, 0.0f);
glm::vec3 Green = glm::vec3(0.0f, 1.0f, 0.0f);
glm::vec3 Blue = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 Gray = glm::vec3(0.7f, 0.7f, 0.7f);
glm::vec3 White = glm::vec3(1.0f, 1.0f, 1.0f);
glm::vec3 Black = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 Yellow = glm::vec3(1.0f, 1.0f, 0.0f);
glm::vec3 Brown = glm::vec3(0.58f, 0.29f, 0.0f);
glm::vec3 Gold = glm::vec3(0.6f, 0.6f, 0.0f);

glm::mat4 S = glm::mat4(1.0f);
glm::mat4 T = glm::mat4(1.0f);
glm::mat4 Rx = glm::mat4(1.0f);
glm::mat4 Ry = glm::mat4(1.0f);
glm::mat4 Rz = glm::mat4(1.0f);
glm::mat4 STR = glm::mat4(1.0f);

struct figure
{
    float x, y, z;
    float r, g, b;
};

figure circle[36];

// 1층 바닥
figure rect_1floor[] =
{
    0.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,0.0f,0.0f,1.0f,1.0f,1.0f
};

// 1층 계단
figure rect_1wall[] =
{
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f
};

// 2층 바닥
figure rect_2floor[] =
{
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f
};

// 2층 계단
figure rect_2wall[] =
{
    -4.0f, 23.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 23.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 23.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_10floor[] =
{
    0.0f, 135.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 133.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 133.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 133.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 135.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 135.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_10wall[] =
{
    -4.0f, 143.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 135.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 135.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 135.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 143.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 143.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_9floor[] =
{
    10.0f, 120.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 118.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 118.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f, 118.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 120.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 120.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_9wall[] =
{
    80.0f, 128.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 120.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 120.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 120.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 128.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 128.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_8floor[] =
{
    0.0f, 105.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 103.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 103.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 103.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 105.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 105.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_8wall[] =
{
    -4.0f, 113.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 105.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 105.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 105.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 113.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 113.0f,0.0f,1.0f,1.0f,1.0f

};

figure rect_7floor[] =
{
    10.0f, 90.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 88.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 88.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f, 88.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 90.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 90.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_7wall[] =
{
    80.0f, 98.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 90.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 90.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 90.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 98.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 98.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_6floor[] =
{
    0.0f, 75.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 73.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 73.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 73.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 75.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 75.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_6wall[] =
{
    -4.0f, 83.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 75.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 75.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 75.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 83.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 83.0f,0.0f,1.0f,1.0f,1.0f

};

figure rect_5floor[] =
{
    10.0f, 60.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 58.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 58.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f, 58.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 60.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 60.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_5wall[] =
{
    80.0f, 68.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 60.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 60.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 60.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 68.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 68.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_4floor[] =
{
    0.0f, 45.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 43.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 43.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 53.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 45.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 45.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_4wall[] =
{
    -4.0f, 53.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 45.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 45.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 45.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 53.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 53.0f,0.0f,1.0f,1.0f,1.0f

};

figure rect_3floor[] =
{
    10.0f, 30.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 28.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 28.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f, 28.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 30.0f,0.0f,1.0f,1.0f,1.0f,
    10.0f, 30.0f,0.0f,1.0f,1.0f,1.0f
};

figure rect_3wall[] =
{
    80.0f, 38.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 30.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 30.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 30.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 38.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 38.0f,0.0f,1.0f,1.0f,1.0f
};

struct bb
{
    float x, y, z;
};

bb path_bb[] =
{
    0.0f, 0.0f, 0.0,
    50.0f, 0.0f, 0.0,
};

bb can_bb[] =
{
    0.0f, 0.0f, 0.0f
};

GLuint vao[7], vbo[7];

std::vector< glm::vec3 > cube_vertices;
std::vector< glm::vec2 > cube_uvs;
std::vector< glm::vec3 > cube_normals;

std::vector< glm::vec3 > player_vertices;
std::vector< glm::vec2 > player_uvs;
std::vector< glm::vec3 > player_normals;

std::vector< glm::vec3 > pyramid_vertices;
std::vector< glm::vec2 > pyramid_uvs;
std::vector< glm::vec3 > pyramid_normals;

std::vector< glm::vec3 > wheel_vertices;
std::vector< glm::vec2 > wheel_uvs;
std::vector< glm::vec3 > wheel_normals;

bool res_cube = loadOBJ("cube.obj", cube_vertices, cube_uvs, cube_normals);
bool res_wheel = loadOBJ("top.obj", wheel_vertices, wheel_uvs, wheel_normals);

char* filetobuf(const char* file)
{
    FILE* fptr;
    long length;
    char* buf;

    fptr = fopen(file, "rb");
    if (!fptr) return NULL;
    fseek(fptr, 0, SEEK_END);
    length = ftell(fptr);
    buf = (char*)malloc(length + 1);
    fseek(fptr, 0, SEEK_SET);
    fread(buf, length, 1, fptr);
    fclose(fptr);
    buf[length] = 0;

    return buf;
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Example1");
    PlaySound(L"Machine_sound-Marianne_Gagnon-88253407", 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
   

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else std::cout << "GLEW Initialized \n";

    for (int i = 0; i < 10; ++i)
    {
        rollwheel_x[i] = 5.0f;
        rollwheel_y[i] = 148.0f;
    }
    rollwheel_x[3] = 8.0f;

    InitShader();
    InitBuffer();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard);
    glutSpecialUpFunc(SpecialKeyboardup);
    glutTimerFunc(1, Timerfunction, 1);
    glutMainLoop();
}

GLvoid drawScene()
{
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUseProgram(s_program[0]);
    glUseProgram(s_program[1]);
    glUseProgram(s_program[2]);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glm::mat4 LIGHT = glm::mat4(1.0f);
    qobj = gluNewQuadric();
    
    if (one_cam)
    {
        Camera_xPos = can_t_x;
        Camera_yPos = can_t_y + 2.0f;
        Camera_zPos = can_t_z;
        Camera_xAT = can_t_x + glm::sin(glm::radians(float(camera_rt + 90.0f))) * rad;
        Camera_yAT = can_t_y + 2.0f;
        Camera_zAT = can_t_z + glm::cos(glm::radians(float(camera_rt + 90.0f))) * rad;

        glm::vec3 camerapos = glm::vec3(Camera_xPos, Camera_yPos, Camera_zPos); //EYE
        glm::vec3 cameradirection = glm::vec3(Camera_xAT, Camera_yAT, Camera_zAT); // AT
        glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f); // UP

        glm::mat4 view = glm::lookAt(camerapos, cameradirection, cameraup);
        GLuint viewlocation = glGetUniformLocation(s_program[0], "View");
        glUniformMatrix4fv(viewlocation, 1, GL_FALSE, value_ptr(view));
    }
    if (thrid_cam)
    {
        Camera_xPos = x_pos;
        Camera_yPos = y_pos + 10.0f;
        Camera_zPos = z_pos;
        Camera_xAT = x_pos;
        Camera_yAT = y_pos;
        Camera_zAT = 0.0f;

        glm::vec3 camerapos = glm::vec3(Camera_xPos, Camera_yPos, Camera_zPos); //EYE
        glm::vec3 cameradirection = glm::vec3(Camera_xAT, Camera_yAT, Camera_zAT); // AT
        glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f); // UP

        glm::mat4 view = glm::lookAt(camerapos, cameradirection, cameraup);
        GLuint viewlocation = glGetUniformLocation(s_program[0], "View");
        glUniformMatrix4fv(viewlocation, 1, GL_FALSE, value_ptr(view));
    }


    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Proj_degree), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    GLuint Projectionlocation = glGetUniformLocation(s_program[0], "Projection");
    glUniformMatrix4fv(Projectionlocation, 1, GL_FALSE, value_ptr(projection));

    unsigned int light_pos = glGetUniformLocation(s_program[2], "lightPos");
    glUniform3f(light_pos, light_x, light_y, light_z);

    unsigned int light_color = glGetUniformLocation(s_program[2], "lightColor");
    glUniform3f(light_color, light_r, light_g, light_b);

    unsigned int view_pos = glGetUniformLocation(s_program[2], "viewPos");
    glUniform3f(view_pos, Camera_xPos, Camera_yPos, Camera_zPos);

    unsigned int ambientLight_on = glGetUniformLocation(s_program[2], "ambientLight_on_off");
    glUniform3f(ambientLight_on, 1.0, 1.0, 1.0);

    unsigned int flag = glGetUniformLocation(s_program[2], "flag");
    glUniform1i(flag, 1);
    DrawPlayer();

    glUniform1i(flag, 0);
    DrawObsRect();
    DrawObsWheel();

    unsigned int Alpha = glGetUniformLocation(s_program[2], "Alpha");
    glUniform1f(Alpha, 0.7f);
    DrawMap();

    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void make_vertexshader()
{
    vertexsource = filetobuf("ver_tex.glsl");
    vertexshader = glCreateShader(GL_VERTEX_SHADER);

    glShaderSource(vertexshader, 1, (const GLchar**)&vertexsource, NULL);

    glCompileShader(vertexshader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(vertexshader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(vertexshader, 512, NULL, errorLog);
        std::cerr << "ERROR : vertex shader 컴파일 실패\n " << errorLog << std::endl;
        return;
    }
}

void make_fragmentshader()
{
    fragmentsource = filetobuf("frag_ment.glsl");
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, NULL);
    glCompileShader(fragmentshader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
        std::cerr << "ERROR : fragment shader 컴파일 실패\n " << errorLog << std::endl;
        return;
    }
}

void InitBuffer()
{
    glGenVertexArrays(6, vao);
    glGenBuffers(6, vbo);

    // 육면체
    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(glm::vec3), &cube_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glBufferData(GL_ARRAY_BUFFER, cube_normals.size() * sizeof(glm::vec3), &cube_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);


    // 톱니바퀴
    glBindVertexArray(vao[2]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);

    glBufferData(GL_ARRAY_BUFFER, wheel_vertices.size() * sizeof(glm::vec3), &wheel_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);

    glBufferData(GL_ARRAY_BUFFER, wheel_normals.size() * sizeof(glm::vec3), &wheel_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);
}

void InitShader()
{
    make_vertexshader();
    make_fragmentshader();

    for (int i = 0; i < 3; ++i)
    {
        s_program[i] = glCreateProgram();
        glAttachShader(s_program[i], vertexshader);
        glAttachShader(s_program[i], fragmentshader);
        glLinkProgram(s_program[i]);
        //checkCompileErrors(s_program, "PROGRAM");

        glDeleteShader(vertexshader);
        glDeleteShader(fragmentshader);

        glUseProgram(s_program[i]);
    }
}

void Keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 'c':
        one_cam = true;
        thrid_cam = false;
        break;
    case 'C':
        one_cam = false;
        thrid_cam = true;
        break;
    case 32:
        if (can_t_y <= min_jump)jump_button = true;
        break;
    }
}

bool lb = false, rb = false;

void SpecialKeyboard(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        lb = true;
        rb = false;
        
    }
    if (key == GLUT_KEY_RIGHT)
    {
        lb = false;
        rb = true;
    }
}

void SpecialKeyboardup(int key, int x, int y)
{
    if (key == GLUT_KEY_LEFT)
    {
        lb = false;
        rb = false;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        lb = false;
        rb = false;
    }
}

void Timerfunction(int value)
{
    get_time();

    if (lb == true) { can_t_x -= can_x_vec*delta_time, x_pos -= can_x_vec * delta_time, can_rotate += 5.0f; }
    if (rb == true) { can_t_x += can_x_vec * delta_time, x_pos += can_x_vec * delta_time, can_rotate -= 5.0f; }
    if (can_t_x < 0.0f && can_t_y <= 13.0f) { can_t_x = 0.0f, x_pos = 0.0f; }

    if (can_t_x > rect_1wall[0].x - 1.0f && can_t_y >= 0 && can_t_y < 8.0f) { can_t_x = 79.0f, x_pos = 79.0f; }
    if (can_t_x > rect_1wall[2].x - 1.0f && can_t_y >= 8.0f) { can_t_x = 83.0f, x_pos = 83.0f; }

    if (can_t_x - 0.9f < rect_2wall[2].x && can_t_y >= 15.0f && can_t_y < 23.0f) { can_t_x = 1.1f, x_pos = 1.1f; }
    if (can_t_x - 1.0f < rect_2wall[0].x && can_t_y >= 23.0f) { can_t_x = -3.0f, x_pos = -3.0f; }

    if (can_t_x > rect_3floor[2].x - 1.0f && can_t_y >= 30.0f && can_t_y < 38.0f) { can_t_x = 79.0f, x_pos = 79.0f; }

    if (can_t_x - 1.0f < rect_4floor[0].x && can_t_y >= 45.0f && can_t_y < 53.0f) { can_t_x = 1.1f, x_pos = 1.1f; }

    if (can_t_x > rect_5floor[2].x - 1.0f && can_t_y >= 60.0f && can_t_y < 68.0f) { can_t_x = 79.0f, x_pos = 79.0f; }

    if (can_t_x - 1.0f < rect_6floor[0].x && can_t_y >= 75.0f && can_t_y < 83.0f) { can_t_x = 1.1f, x_pos = 1.1f; }

    if (can_t_x > rect_7floor[2].x - 1.0f && can_t_y >= 90.0f && can_t_y < 98.0f) { can_t_x = 79.0f, x_pos = 79.0f; }

    if (can_t_x - 1.0f < rect_8floor[0].x && can_t_y >= 105.0f && can_t_y < 113.0f) { can_t_x = 1.1f, x_pos = 1.1f; }

    if (can_t_x > rect_9floor[2].x - 1.0f && can_t_y >= 120.0f && can_t_y < 128.0f) { can_t_x = 79.0f, x_pos = 79.0f; }

    if (can_t_x - 1.0f < rect_10floor[0].x && can_t_y >= 135.0f && can_t_y < 143.0f) { can_t_x = 1.1f, x_pos = 1.1f; }

    if (jump_button)
    {
        if (can_t_y <= min_jump + 10.0f)
            can_t_y += jump_y_vec * delta_time, y_pos += 0.03f * delta_time;
        else jump_button = false;
    }

    else if (coilision(can_t_y, rect_1floor[0].y)) { can_t_y = 0.0f, y_pos = 0.0f, min_jump = 0.0f, camera_rt = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && coilision(can_t_y, rect_1wall[0].y)) { can_t_y = 8.0f, y_pos = 8.0f, min_jump = 8.0f, camera_rt = 180.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 15.0f && coilision(can_t_y, rect_2floor[0].y)) { can_t_y = 15.0f, y_pos = 15.0f, min_jump = 15.0f, camera_rt = 180.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.1f && can_t_y >= 23.0f && coilision(can_t_y, rect_2wall[0].y)) { can_t_y = 23.0f, y_pos = 23.0f, min_jump = 23.0f, camera_rt = 0.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 30.0f && coilision(can_t_y, rect_3floor[0].y)) { can_t_y = 30.0f, y_pos = 30.0f, min_jump = 30.0f, camera_rt = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 38.0f && coilision(can_t_y, rect_3wall[0].y)) { can_t_y = 38.0f, y_pos = 38.0f, min_jump = 38.0f, camera_rt = 180.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 45.0f && coilision(can_t_y, rect_4floor[0].y)) { can_t_y = 45.0f, y_pos = 45.0f, min_jump = 45.0f, camera_rt = 180.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 53.0f && coilision(can_t_y, rect_4wall[0].y)) { can_t_y = 53.0f, y_pos = 53.0f, min_jump = 53.0f, camera_rt = 0.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 60.0f && coilision(can_t_y, rect_5floor[0].y)) { can_t_y = 60.0f, y_pos = 60.0f, min_jump = 60.0f, camera_rt = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 68.0f && coilision(can_t_y, rect_5wall[0].y)) { can_t_y = 68.0f, y_pos = 68.0f, min_jump = 68.0f, camera_rt = 180.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 75.0f && coilision(can_t_y, rect_6floor[0].y)) { can_t_y = 75.0f, y_pos = 75.0f, min_jump = 75.0f, camera_rt = 180.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 83.0f && coilision(can_t_y, rect_6wall[0].y)) { can_t_y = 83.0f, y_pos = 83.0f, min_jump = 83.0f, camera_rt = 0.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 90.0f && coilision(can_t_y, rect_7floor[0].y)) { can_t_y = 90.0f, y_pos = 90.0f, min_jump = 90.0f, camera_rt = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 98.0f && coilision(can_t_y, rect_7wall[0].y)) { can_t_y = 98.0f, y_pos = 98.0f, min_jump = 98.0f, camera_rt = 180.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 105.0f && coilision(can_t_y, rect_8floor[0].y)) { can_t_y = 105.0f, y_pos = 105.0f, min_jump = 105.0f, camera_rt = 180.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 113.0f && coilision(can_t_y, rect_8wall[0].y)) { can_t_y = 113.0f, y_pos = 113.0f, min_jump = 113.0f, camera_rt = 0.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 120.0f && coilision(can_t_y, rect_9floor[0].y)) { can_t_y = 120.0f, y_pos = 120.0f, min_jump = 120.0f, camera_rt = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 128.0f && coilision(can_t_y, rect_9wall[0].y)) { can_t_y = 128.0f, y_pos = 128.0f, min_jump = 128.0f, camera_rt = 180.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 135.0f && coilision(can_t_y, rect_10floor[0].y)) { can_t_y = 135.0f, y_pos = 135.0f, min_jump = 135.0f, camera_rt = 180.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 143.0f && coilision(can_t_y, rect_10wall[0].y)) 
    {
        can_t_y = 143.0f;
        y_pos = 143.0f;
        min_jump = 143.0f;
        one_cam = false;
        thrid_cam = true;        
    }
    else can_t_y -= 0.03f * delta_time, y_pos -= 0.03f * delta_time;
    
    
    if (can_t_x <= -2.0f && can_t_y >= 143) {
        can_t_y += 0.1f * delta_time;
        y_pos += 0.1f * delta_time;
        vicsound += 1;
    }
    if (vicsound == 1)
        PlaySound(L"콜라캔 따고 따르는2 (online-audio-converter.com).wav", 0, SND_FILENAME | SND_ASYNC);
    if (can_t_y >= 800)
        exit(0);

    block_y[0] -= block_vec[0] * delta_time;
    block_y[1] += block_vec[1] * delta_time;
    block_y[2] += block_vec[2] * delta_time;
    if (block_y[0] <= 34.0f || block_y[0]>=58.0f) block_vec[0] *= -1;
    if (block_y[1] <= 33.0f || block_y[1] >= 58.0f) block_vec[1] *= -1;
    if (block_y[2] <= 49.0f || block_y[2] >= 58.0f) block_vec[2] *= -1;

    wheel_t_x[0] -= wheel_vec[0] * delta_time;
    wheel_t_x[1] += wheel_vec[1] * delta_time;
    wheel_t_x[2] -= wheel_vec[2] * delta_time;
    if (wheel_t_x[0] <= 10.0f || wheel_t_x[0] >= 76.0f) wheel_vec[0] *= -1;
    if (wheel_t_x[1] <= 3.0f || wheel_t_x[1] >= 70.0f) wheel_vec[1] *= -1;
    if (wheel_t_x[2] <= 10.0f || wheel_t_x[2] >= 76.0f) wheel_vec[2] *= -1;

    ofwheel_degree += 0.1f * delta_time;

    tfwheel_degree[0] += tfwheel_degree_vec[0] * delta_time;
    tfwheel_degree[1] -= tfwheel_degree_vec[1] * delta_time;
    tfwheel_degree[2] += tfwheel_degree_vec[2] * delta_time;

    if(wheel_t_x[0] >= 75.0f) { tfwheel_degree_vec[0] = 0.3; }
    if(wheel_t_x[0] <= 10.0f) { tfwheel_degree_vec[0] = -0.3; }
    if (wheel_t_x[1] >= 70.0f) { tfwheel_degree_vec[1] = -0.35; }
    if (wheel_t_x[1] <= 3.0f) { tfwheel_degree_vec[1] = +0.35; }
    if (wheel_t_x[2] >= 75.0f) { tfwheel_degree_vec[2] = 0.4; }
    if (wheel_t_x[2] <= 10.0f) { tfwheel_degree_vec[2] = -0.4; }


    for (int i = 0; i < 10; ++i)
    {
        if (wheel_roll[i] == true)
        {
            rollwheel_degree[i] += rollwheel_degree_vec * delta_time;
            if (rollwheel_x[i] > 77.0f) { rollwheel_x[i] = 77.0f; }
            if (rollwheel_x[i] < 3.0f) { rollwheel_x[i] = 3.0f; }

            if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 135.0f && coilision(rollwheel_y[i] - 2.5f, rect_10floor[0].y)) { rollwheel_y[i] = 138.0f, rollvec = 0.02, rollwheel_degree_vec = -0.1; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 120.0f && coilision(rollwheel_y[i] - 2.5f, rect_9floor[0].y)) { rollwheel_y[i] = 123.0f, rollvec = -0.02, rollwheel_degree_vec = 0.1;}
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 105.0f && coilision(rollwheel_y[i] - 2.5f, rect_8floor[0].y)) { rollwheel_y[i] = 108.0f, rollvec = 0.02, rollwheel_degree_vec = -0.1, wheel_roll[i + 1] = true; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 90.0f && coilision(rollwheel_y[i] - 2.5f, rect_7floor[0].y)) { rollwheel_y[i] = 93.0f, rollvec = -0.02, rollwheel_degree_vec = 0.1;}
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 75.0f && coilision(rollwheel_y[i] - 2.5f, rect_6floor[0].y)) { rollwheel_y[i] = 78.0f, rollvec = 0.02, rollwheel_degree_vec = -0.1;}
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 60.0f && coilision(rollwheel_y[i] - 2.5f, rect_5floor[0].y)) { rollwheel_y[i] = 63.0f, rollvec = -0.02, rollwheel_degree_vec = 0.1;}
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 45.0f && coilision(rollwheel_y[i] - 2.5f, rect_4floor[0].y)) { rollwheel_y[i] = 48.0f, rollvec = 0.02, rollwheel_degree_vec = -0.1;}
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 30.0f && coilision(rollwheel_y[i] - 2.5f, rect_3floor[0].y)) { rollwheel_y[i] = 33.0f, rollvec = -0.02, rollwheel_degree_vec = 0.1;}
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 15.0f && coilision(rollwheel_y[i] - 2.5f, rect_2floor[0].y)) { rollwheel_y[i] = 18.0f, rollvec = 0.02, rollwheel_degree_vec = -0.1; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 0.0f && coilision(rollwheel_y[i] - 2.5f, rect_1floor[0].y)) { rollwheel_x[i]=100.0f, rollwheel_y[i] = 3.0f; wheel_roll[i] = false; }
            else rollwheel_y[i] -= 0.03f * delta_time;
            rollwheel_x[i] += rollvec * delta_time;
        }
    }
    light_r -= light_vec * delta_time;
    light_g -= light_vec * delta_time;
    light_b -= light_vec * delta_time;

    if (light_r <= 0.12f)
    {
        sirensound += 1;

    }
    if (sirensound == 1)
    {
        PlaySound(L"y2mate.com - 어몽어스 사보타지 (효과음) (online-audio-converter.com).wav", 0, SND_FILENAME | SND_ASYNC );
    }

    if (light_r <= 0.0f) oversound += 1;
    if(oversound == 1){ PlaySound(L"mixkit-game-over-trombone-1940.wav", 0, SND_FILENAME | SND_ASYNC); }
    if (light_r < -0.05f) exit(0);

    if (coilsion_obs(55.0f, 15.0f, 0.0f, can_t_x, can_t_y, can_t_z, 4.0)) { can_t_x = 65.0f, x_pos = 65.0f, can_t_y = 20.0f, y_pos = 20.0f; }
    if (coilsion_obs(35.0f, 15.0f, 0.0f, can_t_x, can_t_y, can_t_z, 4.0)) { can_t_x = 45.0f, x_pos = 45.0f, can_t_y = 20.0f, y_pos = 20.0f; }
    if (coilsion_obs(15.0f, 15.0f, 0.0f, can_t_x, can_t_y, can_t_z, 4.0)) { can_t_x = 25.0f, x_pos = 25.0f, can_t_y = 20.0f, y_pos = 20.0f; }
    if (coilsion_obs(15.0f, block_y[0], 0.0f, can_t_x, can_t_y + 3.0f , can_t_z, 4.0)) { can_t_y = 15.0f, y_pos = 15.0f, min_jump = 15.0f; }
    if (coilsion_obs(35.0f, block_y[1], 0.0f, can_t_x, can_t_y+3.0f, can_t_z, 4.0)) { can_t_y = 15.0f, y_pos = 15.0f, min_jump = 15.0f; }
    if (coilsion_obs(55.0f, block_y[2], 0.0f, can_t_x, can_t_y+3.0f, can_t_z, 4.0)) { can_t_y = 30.0f, y_pos = 30.0f, min_jump = 30.0f;}
    
    for (int i = 0; i < 10; ++i)
    {
        if (coilsion_obs(rollwheel_x[i], rollwheel_y[i], 0.0f, can_t_x, can_t_y, can_t_z, 4.0))
        {
            if (can_t_x > rollwheel_x[i]) can_t_x += can_x_vec * 2.0f * delta_time, x_pos += can_x_vec * 2.0f * delta_time;
            if (can_t_x < rollwheel_x[i])can_t_x -= can_x_vec * 2.0f * delta_time, x_pos -= can_x_vec * 2.0f * delta_time;
        }
    }

    if (coilsion_obs(wheel_t_x[0], 93.0f, 0.0f, can_t_x, can_t_y + 1.0f, can_t_z, 4.0)) { can_t_x = -2.0f, x_pos = -2.0f, can_t_y = 83.0f, y_pos = 83.0f, min_jump = 83.0f; }
    if (coilsion_obs(wheel_t_x[1], 108.0f, 0.0f, can_t_x, can_t_y + 1.0f, can_t_z, 4.0)) { can_t_x = 81.0f, x_pos = 81.0f, can_t_y = 98.0f, y_pos = 98.0f, min_jump = 98.0f; }
    if (coilsion_obs(wheel_t_x[2], 123.0f, 0.0f, can_t_x, can_t_y + 1.0f, can_t_z, 4.0)) { can_t_x = -2.0f, x_pos = -2.0f, can_t_y = 113.0f, y_pos = 113.0f, min_jump = 113.0f; }

    glutTimerFunc(1, Timerfunction, 1);
    glutPostRedisplay();
}

GLvoid DrawMap()
{
    // 경로
    // 1층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 8.0f, 0.0f));

    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 2층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-1.9f, 23.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 3층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 38.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 4층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 53.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 5층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 68.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 6층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 83.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 7층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 98.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 8층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 113.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 9층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 128.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 10층 계단
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 143.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    // 1층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(40.0, 1.0, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(40.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 2층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 15.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 3층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 30.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    // 4층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 45.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 5층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 60.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 6층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 75.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 7층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 90.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 8층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 105.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 9층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 120.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 10층 바닥
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 135.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    glDisable(GL_BLEND);
}

GLvoid DrawPlayer()
{
    qobj = gluNewQuadric();

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Ry = glm::rotate(glm::mat4(1.0f), float(glm::radians(0.0f)), glm::vec3(0.0, 1.0, 0.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y+1.0f, can_t_z));
    unsigned int player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    unsigned int player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Red.r, Red.g, Red.b);

    gluCylinder(qobj, 1.0f, 1.0f, 2.0f, 20, 20);
    /*glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, player_vertices.size());*/

    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y + 1.0f, can_t_z + 2.0f));
    player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T * Rz));
    player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Red.r, Red.g, Red.b);
    gluDisk(qobj, 0.0, 1.0f, 20, 3);

    Rz = glm::rotate(glm::mat4(1.0f), float(glm::radians(can_rotate)), glm::vec3(0.0, 0.0, 1.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y + 1.0f, can_t_z + 2.05f));
    player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T * Rz));
    player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Gray.r, Gray.g, Gray.b);
    gluDisk(qobj, 0.0, 0.73, 20, 3);

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 2.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y + 1.0f, can_t_z + 2.06f));
    player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T * Rz * S));
    player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Black.r, Black.g, Black.b);
    gluDisk(qobj, 0.0, 0.2, 20, 3);
}

GLvoid DrawObsRect()
{
    for (int i = 0; i < 3; ++i)
    {
        S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f));
        T = glm::translate(glm::mat4(1.0f), glm::vec3(block_x[i], block_y[i], 0.0f));

        unsigned int path = glGetUniformLocation(s_program[0], "Transform");
        glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

        unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
        glUniform3f(path_Color, Brown.r, Brown.g, Brown.b);

        glBindVertexArray(vao[0]);
        glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
    }
}

GLvoid DrawObsWheel()
{
    // 2층 장애물
    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 2.0f));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(ofwheel_degree), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 15.0f, 0.0f));

    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 15.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(55.0f, 15.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    // 저어기 위에 톱니바퀴 왔다갔다
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(tfwheel_degree[0]), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(wheel_t_x[0], 93.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Brown.r, Brown.g, Brown.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(tfwheel_degree[1]), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(wheel_t_x[1], 108.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(tfwheel_degree[2]), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(wheel_t_x[2], 123.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());


    // 꼭대기 톱니바퀴
    for (int i = 0; i < 10; ++i)
    {
        if (wheel_roll[i] == true)
        {
            S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 3.0));
            Rz = glm::rotate(glm::mat4(1.0f), glm::radians(rollwheel_degree[i]), glm::vec3(0.0f, 0.0f, 1.0f));
            T = glm::translate(glm::mat4(1.0f), glm::vec3(rollwheel_x[i], rollwheel_y[i], 0.0f));

            path = glGetUniformLocation(s_program[0], "Transform");
            glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

            path_Color = glGetUniformLocation(s_program[1], "in_Color");
            glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

            glBindVertexArray(vao[2]);
            glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());
        }
    }
}

void make_circle()
{
    float r = 30.0;

    for (int i = 0; i < 36; ++i)
    {
        circle[i].x = glm::cos(glm::radians(float(i * 10))) * r;
        circle[i].z = rad + glm::sin(glm::radians(float(i * 10))) * r;
    }
}

bool coilision(float can_y, float path_y)
{
    int dis = can_y - path_y;

    if (dis <= 0) return true;
    else return false;
}

bool coilsion_obs(float x, float y, float z, float can_x, float can_y, float can_z, float dist)
{
    float dis = sqrt(pow(can_x - x, 2.0) + pow(can_y - y, 2.0) + pow(can_z - z, 2.0));
    if (dis <= dist) return true;
    else return false;
}

void get_time()
{
    frame++;
    float time = glutGet(GLUT_ELAPSED_TIME);
    if (time - timebase > 12)
    {
        delta_time = frame * 12.0 / (time - timebase);
        timebase = time;
        frame = 0;
    }
}