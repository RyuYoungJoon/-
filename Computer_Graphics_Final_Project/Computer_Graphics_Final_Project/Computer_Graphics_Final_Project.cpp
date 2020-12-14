#include<iostream>
#include<time.h>
#include<random>
#include<windows.h>
#include<vector>
#include<math.h>

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
void SpecialKeyboard(int key, int x, int y);
void SpecialKeyboardup(int key, int x, int y);
void Timerfunction(int);
void Mouse(int button, int state, int x, int y);
GLvoid DrawMap();
GLvoid DrawPlayer();
GLvoid DrawObsRect();
GLvoid DrawObsWheel();
GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint s_program[3];
GLUquadricObj* qobj;

random_device rd;
default_random_engine dre{ rd() };
uniform_real_distribution<> random_pos_urd{ -20.0,20.0 };

float random_xpos = random_pos_urd(dre);
float random_zpos = random_pos_urd(dre);

// ������ �� �۾��� ī�޶� ��ǥ

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
//float z_pos = 30.0f;
//
//float degree = 90.0f;


// ȫ���� �Ǹ��� ������ �۾��� ī�޶� ��ǥ
float Camera_xPos = 0.0f;
float Camera_yPos = 0.0f;
float Camera_zPos = 0.0f;

float Camera_xAT = 0.0f;
float Camera_yAT = 0.0f;
float Camera_zAT = 0.0f;

float x_pos = 0.0f;
float y_pos = 50.0f;
float z_pos = 70.0f;

float cam_y_dis = 1.0f;

float degree = 90.0f;
float degree_vec = 2.0f;

float camera_rt = 0.0f;
float camera_rt_vec = 10.0f;

// � �������� ������� 
float Open_Ground = 0.0f;           // �ٴ� �����̰� ����� ����
float Proj_degree = 100.0f;         
float Wheel_R = 0.0f;               // ��Ϲ��� ȸ�� ����

float light_x = -15.0;
float light_y = 15.0;
float light_z = 0.0;

float light_r = 1.0;
float light_g = 1.0;
float light_b = 1.0;


bool Open_mode = true;
bool Down_node = true;

float rad = 30.0f;

float Down_Wheel = 0.0f;        // ��Ϲ��� �������� ù��° ����
float Down_Wheel2 = 0.0f;       // ��Ϲ��� �������� �ι�° ����
float Down_Wheel3 = 0.0f;       // ��Ϲ��� �������� �ι�° ����
float Down_Wheel4 = 0.0f;        // ��Ϲ��� �������� ù��° ����
float Down_Wheel5 = 0.0f;       // ��Ϲ��� �������� �ι�° ����
float Down_Wheel6 = 0.0f;       // ��Ϲ��� �������� �ι�° ����


// ���� ���ǵ�
float Block_speed = 0.0f;

// ĵ trans ��ǥ ����
float can_t_x = 0.0f;
float can_t_y = 0.0f;
float can_t_z = 0.0f;
float acceleration = 0.0f;

// ĵ�� x, y ,z �ӵ� ����
float can_x_vec = 0.05f;
float can_y_vec = 0.0f;
float can_z_vec = 0.1f;

// ĵ�� x, y, z ȸ���� 
float can_x_rt = 10.0f;
float can_y_rt = 10.0f;
float can_z_rt = 30.0f;

float camera_acceleration = 0.0f;
float can_rt = 0.0f;

float min_jump = 0.0f;
float jump_y_vec = 0.4f;

// ���콺 �� ����
bool mouse_botton;
bool jump_button;

float block_vec = 0.2f;
float wheel_degree = 0.0f;
float wheel_degree_vec = 3.5f;
float Wheel_t_x1 = 75.0f;
float Wheel_t_x2 = 10.0f;
float Wheel_vec = 0.3f;
float light_vec = 0.0001f;

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

//figure rect[] =
//{
//    -0.5f,0.5f,0.0f,1.0f,1.0f,1.0f,
//    -0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,
//    0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,
//
//    0.5f,-0.5f,0.0f,1.0f,1.0f,1.0f,
//    0.5f,0.5f,0.0f,1.0f,1.0f,1.0f,
//    -0.5f,0.5f,0.0f,1.0f,1.0f,1.0f
//};

figure rect1[] =
{
    2.0f,141.0f,0.0f,1.0f,1.0f,1.0f,
    2.0f,135.0f,0.0f,1.0f,1.0f,1.0f,
    8.0f,135.0f,0.0f,1.0f,1.0f,1.0f,

    8.0f,135.0f,0.0f,1.0f,1.0f,1.0f,
    8.0f,141.0f,0.0f,1.0f,1.0f,1.0f,
    2.0f,141.0f,0.0f,1.0f,1.0f,1.0f
};

// 1�� �ٴ�
figure rect2[] =
{
    0.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,0.0f,0.0f,1.0f,1.0f,1.0f
};

// 1�� ���
figure rect3[] =
{
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f
};

// 2�� �ٴ�
figure rect4[] =
{
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f
};

// 2�� ���
figure rect5[] =
{
    -4.0f, 23.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,

    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 23.0f,0.0f,1.0f,1.0f,1.0f,
    -4.0f, 23.0f,0.0f,1.0f,1.0f,1.0f
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

//bb wheel_bb[] =
//{
//
//};

bool coilision(float, float);

GLuint vao[20], vbo[20];

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
bool res_player = loadOBJ("player.obj", player_vertices, player_uvs, player_normals);
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

    qobj = gluNewQuadric();

    Camera_xPos = x_pos + glm::cos(glm::radians(float(degree))) * rad;
    Camera_yPos = y_pos + 5.0f;
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
    DrawObsRect();
    DrawObsWheel();
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
        std::cerr << "ERROR : vertex shader ������ ����\n " << errorLog << std::endl;
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
        std::cerr << "ERROR : vertex shader ������ ����\n " << errorLog << std::endl;
        return;
    }
}

void InitBuffer()
{
    glGenVertexArrays(20, vao);
    glGenBuffers(20, vbo);

    // ����ü
    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(glm::vec3), &cube_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glBufferData(GL_ARRAY_BUFFER, cube_normals.size() * sizeof(glm::vec3), &cube_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    // �÷��̾�
    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

    glBufferData(GL_ARRAY_BUFFER, player_vertices.size() * sizeof(glm::vec3), &player_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);

    glBufferData(GL_ARRAY_BUFFER, player_normals.size() * sizeof(glm::vec3), &player_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    // ��Ϲ���
    glBindVertexArray(vao[2]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);

    glBufferData(GL_ARRAY_BUFFER, wheel_vertices.size() * sizeof(glm::vec3), &wheel_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[5]);

    glBufferData(GL_ARRAY_BUFFER, wheel_normals.size() * sizeof(glm::vec3), &wheel_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    
    glBindVertexArray(vao[3]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[6]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect1), rect1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 1�� �ٴ�
    glBindVertexArray(vao[4]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect2), rect2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 1�� ���
    glBindVertexArray(vao[5]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect3), rect3, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 2�� �ٴ�
    glBindVertexArray(vao[6]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect4), rect4, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 2�� ���
    glBindVertexArray(vao[7]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect5), rect5, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
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
    case 32:
        jump_button = true;
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
    if (lb == true) { can_t_x -= 0.25, x_pos -= 0.25; }
    if (rb == true) { can_t_x += 0.25, x_pos += 0.25; }

    if (can_t_x < 0.0f) { can_t_x = 0.0f, x_pos = 0.0f; }
    if (can_t_x > rect3[0].x - 1.0f && can_t_y < 8.0f) { can_t_x = 79.0f, x_pos = 79.0f; }
    if (can_t_x > rect3[2].x - 1.0f && can_t_y >= 8.0f) { can_t_x = 83.0f, x_pos = 83.0f; }
    //if ((can_t_x - 1.0f > rect4[2].x && can_t_x - 1.0f < rect4[2].x+0.01f)&& ( (can_t_y + 1.0f < 15.0f && can_t_y + 1.0f > 13.0f) || (can_t_y - 1.0f < 14.9f && can_t_y - 1.0f > 13.0f) )) { can_t_x = 71.0f, x_pos = 71.0f; }
   
    if (jump_button)
    {
        if (can_t_y <= min_jump + 11.0f)
            can_t_y += jump_y_vec;
        else jump_button = false;
    }
    else if (coilision(can_t_y, rect2[0].y)) { can_t_y =0.0f, min_jump = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && coilision(can_t_y, rect3[0].y)) { can_t_y = 8.0f, min_jump = 8.0f; }
    else if (can_t_x<71.0f && can_t_x>0.0f && can_t_y>=15.0f && coilision(can_t_y, rect4[0].y)) { can_t_y = 15.0f, min_jump = 15.0f; }
    //else if (can_t_x > 80.0f && can_t_x < 84.0f && coilision(can_t_y, rect3[0].y)) { can_t_y = 8.0f, min_jump = 10.0f; }
    else can_t_y -= 0.4f;

    Block_speed += block_vec;
    if (Block_speed >= 28.0f || Block_speed<=0.0f)
        block_vec *= -1;

    wheel_degree += wheel_degree_vec;

    Wheel_t_x1 -= Wheel_vec;
    Wheel_t_x2 += Wheel_vec;
    if (Wheel_t_x1 >= 75.0f || Wheel_t_x1 <= 10.0f) { Wheel_vec *= -1, wheel_degree_vec *= -1; }

    light_r -= light_vec;
    light_g -= light_vec;
    light_b -= light_vec;



    glutTimerFunc(10, Timerfunction, 1);
    glutPostRedisplay();
}

GLvoid DrawMap()
{
    // ���
    // 1�� 
    S = glm::scale(glm::mat4(1.0f), glm::vec3(40.0, 1.0, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(40.0, 0.0, 0.0));
    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f,0.0f,5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[4]);
    glDrawArrays(GL_TRIANGLES, 0,6);

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 4.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 8.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[5]);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    // 2��
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 15.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
   
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[6]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 4.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-1.9f, 23.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[7]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    // 3��
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 30.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 40.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 4��
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 45.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 55.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 5��
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 60.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 70.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());



    // 6��
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 75.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 85.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 7��

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 90.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 100.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

   


    // 8�� 
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 105.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 115.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 9��

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 120.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 130.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 10��

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 135.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 145.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T* S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
}

GLvoid DrawPlayer()
{
    Ry = glm::rotate(glm::mat4(1.0f), float(glm::radians(can_rt)), glm::vec3(0.0, 1.0, 0.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(can_t_x, can_t_y, can_t_z));
    unsigned int player = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(player, 1, GL_FALSE, glm::value_ptr(T));
    unsigned int player_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(player_Color, Red.r, Red.g, Red.b);
    
    glBindVertexArray(vao[1]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
}

GLvoid DrawObsRect()
{
    
    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(40.0f, 30.0f + Block_speed, 0.0f));

    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(15.0f, 60.0f - Block_speed, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 2.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(60.0f, 60.0f - Block_speed, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
}

GLvoid DrawObsWheel()
{
    // 2�� ��ֹ�
    S = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f, 1.0f, 1.0f));
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(wheel_degree), glm::vec3(0.0f, 0.0f, 1.0f));
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

    // ����� ���� ��Ϲ��� �Դٰ���
    T = glm::translate(glm::mat4(1.0f), glm::vec3(Wheel_t_x1, 93.0f, 2.5f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());

    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(-wheel_degree), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(Wheel_t_x2, 93.0f, -2.5f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());


    // ����� ��Ϲ���
    Rz = glm::rotate(glm::mat4(1.0f), glm::radians(wheel_degree), glm::vec3(0.0f, 0.0f, 1.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(5.0f, 138.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Rz * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gold.r, Gold.g, Gold.b);

    glBindVertexArray(vao[2]);
    glDrawArrays(GL_TRIANGLES, 0, wheel_vertices.size());
    
    //�ڽ�
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0, 0.0f, 0.0f));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Blue.r, Blue.g, Blue.b);

    glBindVertexArray(vao[3]);
    glDrawArrays(GL_TRIANGLES, 0, 13);
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