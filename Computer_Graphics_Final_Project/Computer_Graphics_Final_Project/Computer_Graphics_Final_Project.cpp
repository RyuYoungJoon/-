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
//#include "myMap.h"
#include "ReadObj.h"

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
void SpecialKeyboard_down(int, int, int);
void SpecialKeyboard_up(int, int, int);
void Timerfunction(int);
void Mouse(int button, int state, int x, int y);
GLvoid DrawMap();
GLvoid DrawPlayer();
GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint s_program[3];
GLUquadricObj* qobj;

random_device rd;
default_random_engine dre{ rd() };
uniform_real_distribution<> random_pos_urd{ -20.0,20.0 };

float random_xpos = random_pos_urd(dre);
float random_zpos = random_pos_urd(dre);

// 유영준 맵 작업용 카메라 좌표

float Camera_xPos = 0.0f;
float Camera_yPos = 15.0f;
float Camera_zPos = 0.0f;

float Camera_xAT = 0.0f;
float Camera_yAT = 0.0f;
float Camera_zAT = 0.0f;

float x_pos = 0.0f;
float y_pos = 0.0f;
float z_pos = 30.0f;

float degree = 90.0f;


// 홍태현 실린더 움직임 작업용 카메라 좌표
//float Camera_xPos = 0.0f;
//float Camera_yPos = 15.0f;
//float Camera_zPos = 0.0f;
//
//float Camera_xAT = 0.0f;
//float Camera_yAT = 0.0f;
//float Camera_zAT = 0.0f;
//
//float x_pos = 0.0f;
//float y_pos = 0.0f;
//float z_pos = 0.0f;
//
float cam_y_dis = 1.0f;
//
//float degree = 180.0f;
//
float camera_rt = 0.0f;

// 어떤 변수인지 적어놔줘 
float Open_Ground = 0.0f;           // 바닥 움직이게 만드는 변수
float Proj_degree = 100.0f;         
float Wheel_R = 0.0f;               // 톱니바퀴 회전 변수

float light_x = -15.0;
float light_y = 15.0;
float light_z = 0.0;

float light_r = 1.0;
float light_g = 1.0;
float light_b = 1.0;


bool Open_mode = true;
bool Down_node = true;

float rad = 20.0f;

float Down_Wheel = 0.0f;        // 톱니바퀴 떨어지는 첫번째 구간
float Down_Wheel2 = 0.0f;       // 톱니바퀴 떨어지는 두번째 구간
float Down_Wheel3 = 0.0f;       // 톱니바퀴 떨어지는 두번째 구간
float Down_Wheel4 = 0.0f;        // 톱니바퀴 떨어지는 첫번째 구간
float Down_Wheel5 = 0.0f;       // 톱니바퀴 떨어지는 두번째 구간
float Down_Wheel6 = 0.0f;       // 톱니바퀴 떨어지는 두번째 구간
// 캔 trans 좌표 변수
float can_t_x = -10.0f;
float can_t_y = 0.0f;
float can_t_z = -2.5f;
float acceleration = 1.0f;

// 캔의 x, y ,z 속도 벡터
float can_x_vec = 0.1f;
float can_y_vec = 0.1f;
float can_z_vec = 0.1f;

// 캔의 x, y, z 회전률 
float can_x_rt = 10.0f;
float can_y_rt = 10.0f;
float can_z_rt = 30.0f;

float camera_acceleration = 1.0f;
float can_rt = 0.0f;
// 마우스 불 변수
bool mouse_botton;
bool jump_button;


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

GLuint vao[10], vbo[10];

std::vector< glm::vec3 > cube_vertices;
std::vector< glm::vec2 > cube_uvs;
std::vector< glm::vec3 > cube_normals;

std::vector< glm::vec3 > pyramid_vertices;
std::vector< glm::vec2 > pyramid_uvs;
std::vector< glm::vec3 > pyramid_normals; // 지금은 안쓸거에요. 

std::vector< glm::vec3 > wheel_vertices;
std::vector< glm::vec2 > wheel_uvs;
std::vector< glm::vec3 > wheel_normals;

//bool loadOBJ(
//    const char* path,
//    std::vector<glm::vec3>& out_vertices,
//    std::vector<glm::vec2>& out_uvs,
//    std::vector<glm::vec3>& out_normals
//)
//{
//    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
//    std::vector<glm::vec3>temp_vertices;
//    std::vector<glm::vec2>temp_uvs;
//    std::vector<glm::vec3>temp_normals;
//
//    FILE* file = fopen(path, "r");
//    if (file == NULL)
//    {
//        std::cout << "파일 열수 없음!" << std::endl;
//        return false;
//    }
//
//    while (1) {
//        char lineHeader[128];
//        int res = fscanf(file, "%s", lineHeader);
//        if (res == EOF)
//            break;;
//
//        if (strcmp(lineHeader, "v") == 0) {
//            glm::vec3 vertex;
//            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
//            temp_vertices.push_back(vertex);
//        }
//        else if (strcmp(lineHeader, "vt") == 0) {
//            glm::vec2 uv;
//            fscanf(file, "%f %f\n", &uv.x, &uv.y);
//            temp_uvs.push_back(uv);
//        }
//
//        else if (strcmp(lineHeader, "vn") == 0) {
//            glm::vec3 normal;
//            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
//            temp_normals.push_back(normal);
//        }
//
//        else if (strcmp(lineHeader, "f") == 0)
//        {
//            std::string vertex1, vertex2, vertex3;
//            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
//            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
//                &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
//            if (matches != 9) {
//                std::cout << "나의 간단한 프로그램으론 읽을수없다." << std::endl;
//                return false;
//            }
//            vertexIndices.push_back(vertexIndex[0]);
//            vertexIndices.push_back(vertexIndex[1]);
//            vertexIndices.push_back(vertexIndex[2]);
//            uvIndices.push_back(uvIndex[0]);
//            uvIndices.push_back(uvIndex[1]);
//            uvIndices.push_back(uvIndex[2]);
//            normalIndices.push_back(normalIndex[0]);
//            normalIndices.push_back(normalIndex[1]);
//            normalIndices.push_back(normalIndex[2]);
//        }
//
//        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
//            unsigned int vertexIndex = vertexIndices[i];
//            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
//            out_vertices.push_back(vertex);
//        }
//
//        for (unsigned int i = 0; i < uvIndices.size(); i++) {
//            unsigned int uvIndex = uvIndices[i];
//            glm::vec2 uv = temp_uvs[uvIndex - 1];
//            out_uvs.push_back(uv);
//        }
//
//        for (unsigned int i = 0; i < normalIndices.size(); i++) {
//            unsigned int normalIndex = normalIndices[i];
//            glm::vec3 normal = temp_normals[normalIndex - 1];
//            out_normals.push_back(normal);
//        }
//
//    }
//
//}

bool res_cube = loadOBJ("cube.obj", cube_vertices, cube_uvs, cube_normals);
bool res_pyramid = loadOBJ("pyramid.obj", pyramid_vertices, pyramid_uvs, pyramid_normals);
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

void main(int argc, char** argv)
{
    srand((unsigned int)time(NULL));

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutCreateWindow("Example1");

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Unable to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }
    else std::cout << "GLEW Initialized \n";

    InitShader();
    InitBuffer();

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_CULL_FACE);

    glutDisplayFunc(drawScene);
    glutReshapeFunc(Reshape);
    glutKeyboardFunc(Keyboard);
    glutSpecialFunc(SpecialKeyboard_down);
    glutSpecialUpFunc(SpecialKeyboard_up);
    glutMouseFunc(Mouse);
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

    qobj = gluNewQuadric();

    Camera_xPos = x_pos + glm::cos(glm::radians(float(degree))) * rad;
    Camera_yPos = y_pos + 15.0f * cam_y_dis;
    Camera_zPos = z_pos + glm::sin(glm::radians(float(degree))) * rad;
    Camera_xAT = x_pos;
    Camera_yAT = y_pos;
    Camera_zAT = z_pos;
    glm::mat4 LIGHT = glm::mat4(1.0f);

    glm::mat4 CAMERA_ROTATE = glm::rotate(glm::mat4(1.0f), float(glm::radians(camera_rt)), glm::vec3(1.0, 0.0, 0.0));
    glm::vec3 camerapos = glm::vec3(Camera_xPos, Camera_yPos, Camera_zPos); //EYE
    glm::vec3 cameradirection = glm::vec3(Camera_xAT, Camera_yAT, Camera_zAT); // AT
    glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f); // UP
    
    glm::mat4 view = glm::lookAt(camerapos, cameradirection, cameraup) * CAMERA_ROTATE;
    
    GLuint viewlocation = glGetUniformLocation(s_program[0], "View");
    glUniformMatrix4fv(viewlocation, 1, GL_FALSE, value_ptr(view));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Proj_degree), (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);
    GLuint Projectionlocation = glGetUniformLocation(s_program[0], "Projection");
    glUniformMatrix4fv(Projectionlocation, 1, GL_FALSE, value_ptr(projection));

    DrawMap();
    DrawPlayer();
 
    unsigned int light_pos = glGetUniformLocation(s_program[2], "lightPos");
    glUniform3f(light_pos, light_x, light_y, light_z);

    unsigned int light_color = glGetUniformLocation(s_program[2], "lightColor");
    glUniform3f(light_color, light_r, light_g, light_b);

    unsigned int view_pos = glGetUniformLocation(s_program[2], "viewPos");
    glUniform3f(view_pos, Camera_xPos, Camera_yPos, Camera_zPos);

    unsigned int ambientLight_on = glGetUniformLocation(s_program[2], "ambientLight_on_off");
    glUniform3f(ambientLight_on, 0.7, 0.7, 0.7);

    glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
}

void make_vertexshader()
{
    vertexsource = filetobuf("vertex.glsl");
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
    fragmentsource = filetobuf("fragment.glsl");
    fragmentshader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentshader, 1, (const GLchar**)&fragmentsource, NULL);
    glCompileShader(fragmentshader);

    GLint result;
    GLchar errorLog[512];

    glGetShaderiv(fragmentshader, GL_COMPILE_STATUS, &result);
    if (!result)
    {
        glGetShaderInfoLog(fragmentshader, 512, NULL, errorLog);
        std::cerr << "ERROR : vertex shader 컴파일 실패\n " << errorLog << std::endl;
        return;
    }
}

void InitBuffer()
{
    glGenVertexArrays(10, vao);
    glGenBuffers(10, vbo);

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

    // 피라미드
    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

    glBufferData(GL_ARRAY_BUFFER, pyramid_vertices.size() * sizeof(glm::vec3), &pyramid_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);

    glBufferData(GL_ARRAY_BUFFER, pyramid_normals.size() * sizeof(glm::vec3), &pyramid_normals[0], GL_STATIC_DRAW);

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
    // 원
    /*
    glBindVertexArray(vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);*/
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
    case 'x':
        x_pos -= 2.0f;
        Camera_xAT -= 2.0f;
        break;
    case 'X':
        x_pos += 2.0f;
        Camera_xAT += 2.0f;
        break;
    case 'y':
        y_pos -= 2.f;
        Camera_yAT -= 2.0f;
        break;
    case 'Y':
        y_pos += 2.0f;
        Camera_yAT += 2.0f;
        break;
    case 'z':
        z_pos -= 2.0f;
        Camera_zAT -= 2.0f;
        break;
    case 'Z':
        z_pos += 2.0f;
        Camera_zAT += 2.0f;
        break;
    case 'r':
        degree += 2.0;
        break;
    case 'R':
        degree -= 2.0;
        break;
    }
}

// 마우스로 만들까 키보드로 만들까 시발 둘다 ㅈㄴ 어려운데 ㅈ 됬음
void SpecialKeyboard_down(int key, int x, int y)
{
    if (key == GLUT_KEY_UP)
    {
        can_t_x += can_x_vec * acceleration;
        acceleration += 0.1f;

        x_pos += can_x_vec * camera_acceleration;
        camera_acceleration += 0.1f;

        if (acceleration >= 15.0f) acceleration = 15.0f;
        if (camera_acceleration >= 15.0f) camera_acceleration = 15.0f;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        if (can_rt == -90.0f)  degree = -90.0f, can_z_rt = 0.0;
        //degree += 10.0f;
        can_rt -= can_z_rt;

        can_t_z += can_z_vec * acceleration;
        acceleration += 0.1f;

        z_pos += can_z_vec * camera_acceleration;
        camera_acceleration += 0.1f;

        if (acceleration >= 15.0f) acceleration = 15.0f;
        if (camera_acceleration >= 15.0f) camera_acceleration = 15.0f;
    }
}

void SpecialKeyboard_up(int key, int x, int y)
{

 }

void Timerfunction(int value)
{
    // 장애물 땅 열리기
    if (Open_mode)
    {
        Open_Ground += 0.2f;
        if (Open_Ground >= 10.0f)
            Open_mode = false;
    }
    else
    {
        Open_Ground -= 0.2f;
        if (Open_Ground <= 0.0f)
            Open_mode = true;
    }
    // 톱니바퀴 회전
    Wheel_R += 2.0f;

    Down_Wheel += 0.4f;
    if (Down_Wheel >= 40.0f)
        Down_Wheel = 0.0f;

    Down_Wheel2 += 0.5f;
    if (Down_Wheel2 >= 60.0f)
        Down_Wheel2 = 0.0f;

    Down_Wheel3 += 1.0f;
    if (Down_Wheel3 >= 100.0f)
        Down_Wheel3 = 0.0f;
    Down_Wheel4 += 1.0f;
    if (Down_Wheel4 >= 110.0f)
        Down_Wheel4 = 0.0f;
    Down_Wheel5 += 1.0f;
    if (Down_Wheel5 >= 120.0f)
        Down_Wheel5 = 0.0f;
    Down_Wheel6 += 1.0f;
    if (Down_Wheel6 >= 130.0f)
        Down_Wheel6 = 0.0f;

    if (mouse_botton)
    {
        if (can_t_x < 358.0f && can_t_y == 0.0f)
        {
            can_t_x += can_x_vec * acceleration;
            acceleration += 0.01f;

            x_pos += can_x_vec * camera_acceleration;
            camera_acceleration += 0.01f;

            if (acceleration >= 5.0f) acceleration = 5.0f;
            if (camera_acceleration >= 5.0f) camera_acceleration = 5.0f;
        }

        if (can_t_x >= 357.0f && can_t_x <= 358.0f)
        {
            degree = 0.0;
            can_t_y -= can_y_vec * acceleration;
            acceleration += 0.01f;

            y_pos -= can_y_vec * camera_acceleration;
            camera_acceleration += 0.01f;

            if (acceleration >= 5.0f) acceleration = 5.0f;
            if (camera_acceleration >= 5.0f) camera_acceleration = 5.0f;
        }

        if (can_t_x <= 358.0f && can_t_y<=-43.0f)
        {
            y_pos = 40.0f;
            degree = 90.0f;
            //cam_y_dis = -1.0f;
            camera_rt = 180.0f;
            can_t_x -= can_x_vec * acceleration;
            acceleration += 0.01f;

            x_pos -= can_x_vec * camera_acceleration;
            camera_acceleration += 0.01f;

            if (acceleration >= 5.0f) acceleration = 5.0f;
            if (camera_acceleration >= 5.0f) camera_acceleration = 5.0f;
        }


    }
    if (jump_button)
    {
        can_t_y += 0.2f;
        if (can_t_y >= 5.0f)
            jump_button = false;

    }
    else
    {
        can_t_y -= 0.2f;
        if (can_t_y <= 0.0f)
            can_t_y = 0;
    }
    glutTimerFunc(10, Timerfunction, 1);
    glutPostRedisplay();
}

void Mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        mouse_botton = true;
    }
    if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
    {
        acceleration = 1.0f;
        camera_acceleration = 1.0f;
        mouse_botton = false;
    }
    if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
    {
        jump_button = true;


    }
}

GLvoid DrawMap()
{
    // 경로
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
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(170.0, 0.0, 19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Ry* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(190.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(210.0, 0.0, -19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Ry* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(230.0, 0.0, -38.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(250.0, 0.0, -19.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Ry* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(270.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(295.0 - Open_Ground, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    T = glm::translate(glm::mat4(1.0f), glm::vec3(315.0 + Open_Ground, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 0.5f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(335.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 20.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0, -20.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(350.0f, -40.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(335.0f - Open_Ground, -40, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 0.5f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(300.0f, -40, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(270.0f, -50.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(250.0f, -60.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 0.5f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(220.0f, -50.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(10.0, 0.5, 5.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(193.0f, -57.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz *S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(180.0f - Open_Ground, -70.0f - Open_Ground, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0f, 0.5f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(150.0f, -100.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz *S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(S, glm::vec3(2.0f, 1.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(96.0f, -114.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(-45.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(28.0f, -86.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.7, 5.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0, -53.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(-10.0f, -53.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(-5.0f, -49.0f, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    // 실린더
    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0, 0.0, -5.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);
    gluCylinder(qobj, 0.5, 0.5, 10.0, 20, 20);

    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0, -40.0, -5.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Red.r, Red.g, Red.b);
    gluCylinder(qobj, 0.5, 0.5, 10.0, 20, 20);

    T = glm::translate(glm::mat4(1.0f), glm::vec3(200.0, -50.0, -5.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Red.r, Red.g, Red.b);
    gluCylinder(qobj, 0.5, 0.5, 10.0, 20, 20);

    T = glm::translate(glm::mat4(1.0f), glm::vec3(136.0, -114.0, -5.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Red.r, Red.g, Red.b);
    gluCylinder(qobj, 0.5, 0.5, 10.0, 20, 20);

    
    // 톱니

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 2.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(Wheel_R), glm::vec3(0.0f, 0.0f, 1.0f));
    unsigned int Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(Rz* S));
    unsigned int Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(Wheel_R), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(120.0f, 0.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0, 1.0, 1.0));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(Wheel_R), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0f, -10.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(355.0f, -25.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 0.5f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(278.0f, -70.0f + Down_Wheel, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(260.0f, -90.0f + Down_Wheel2, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(225.0f, -50.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());
    
    T = glm::translate(glm::mat4(1.0f), glm::vec3(210.0f, -50.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(115.0f, -114.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(90.0f, -114.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(65.0f, -114.0f, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, -130.0f+Down_Wheel3, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(30.0f, -140.0f+Down_Wheel4, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(10.0f, -150.0f+Down_Wheel5, 0.0f));
    Wheel = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(Wheel, 1, GL_FALSE, glm::value_ptr(T* Rz* S));
    Wheel_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(Wheel_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

}

GLvoid DrawPlayer()
{
    Ry = glm::rotate(glm::mat4(1.0f), float(glm::radians(can_rt)), glm::vec3(0.0, 1.0, 0.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y + 1.5f , can_t_z));
    unsigned int player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T*Ry));
    unsigned int player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Red.r, Red.g, Red.b);
    gluCylinder(qobj, 1.5, 1.5, 5.0, 20, 20);
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