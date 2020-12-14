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

// À¯¿µÁØ ¸Ê ÀÛ¾÷¿ë Ä«¸Þ¶ó ÁÂÇ¥

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


// È«ÅÂÇö ½Ç¸°´õ ¿òÁ÷ÀÓ ÀÛ¾÷¿ë Ä«¸Þ¶ó ÁÂÇ¥
float Camera_xPos = 0.0f;
float Camera_yPos = 0.0f;
float Camera_zPos = 0.0f;

float Camera_xAT = 0.0f;
float Camera_yAT = 0.0f;
float Camera_zAT = 0.0f;

float x_pos = 50.0f;
float y_pos = 120.0f;
float z_pos = 70.0f;

float cam_y_dis = 1.0f;

float degree = 90.0f;
float degree_vec = 2.0f;

float camera_rt = 0.0f;
float camera_rt_vec = 10.0f;

// ¾î¶² º¯¼öÀÎÁö Àû¾î³öÁà 
float Open_Ground = 0.0f;           // ¹Ù´Ú ¿òÁ÷ÀÌ°Ô ¸¸µå´Â º¯¼ö
float Proj_degree = 100.0f;
float Wheel_R = 0.0f;               // Åé´Ï¹ÙÄû È¸Àü º¯¼ö

float light_x = -15.0;
float light_y = 15.0;
float light_z = 0.0;

float light_r = 1.0;
float light_g = 1.0;
float light_b = 1.0;


bool Open_mode = true;
bool Down_node = true;

float rad = 30.0f;

float Down_Wheel = 0.0f;        // Åé´Ï¹ÙÄû ¶³¾îÁö´Â Ã¹¹øÂ° ±¸°£
float Down_Wheel2 = 0.0f;       // Åé´Ï¹ÙÄû ¶³¾îÁö´Â µÎ¹øÂ° ±¸°£
float Down_Wheel3 = 0.0f;       // Åé´Ï¹ÙÄû ¶³¾îÁö´Â µÎ¹øÂ° ±¸°£
float Down_Wheel4 = 0.0f;        // Åé´Ï¹ÙÄû ¶³¾îÁö´Â Ã¹¹øÂ° ±¸°£
float Down_Wheel5 = 0.0f;       // Åé´Ï¹ÙÄû ¶³¾îÁö´Â µÎ¹øÂ° ±¸°£
float Down_Wheel6 = 0.0f;       // Åé´Ï¹ÙÄû ¶³¾îÁö´Â µÎ¹øÂ° ±¸°£


// ºí·° ½ºÇÇµå
float Block_speed = 0.0f;

// Äµ trans ÁÂÇ¥ º¯¼ö
float can_t_x = 50.0f;
float can_t_y = 45.0f;
float can_t_z = 0.0f;
float acceleration = 0.0f;

// ÄµÀÇ x, y ,z ¼Óµµ º¤ÅÍ
float can_x_vec = 0.05f;
float can_y_vec = 0.0f;
float can_z_vec = 0.1f;

// ÄµÀÇ x, y, z È¸Àü·ü 
float can_x_rt = 10.0f;
float can_y_rt = 10.0f;
float can_z_rt = 30.0f;

float camera_acceleration = 0.0f;
float can_rt = 0.0f;

float min_jump = 0.0f;
float jump_y_vec = 0.4f;

// ¸¶¿ì½º ºÒ º¯¼ö
bool mouse_botton;
bool jump_button;

float block_vec = 0.2f;
float wheel_degree = 0.0f;
float wheel_degree_vec = 3.5f;
float Wheel_t_x1 = 75.0f;
float Wheel_t_x2 = 10.0f;
float Wheel_vec = 0.3f;
float light_vec = 0.0001f;

//float rollwheel_x = 5.0f;
//float rollwheel_y = 138.0f;
float rollvec = 0.2f;

float rollwheel_x[10]{ 0, };
float rollwheel_y[10]{ 0, };
float rollwheel_degree[10]{ 0, };
float rollwheel_degree_vec = 3.5f;
bool wheel_roll[10] = { true, false, false, false, false, false, false, false, false, false };

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

// 1Ãþ ¹Ù´Ú
figure rect_1floor[] =
{
    0.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,

    80.0f,-2.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f,0.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f,0.0f,0.0f,1.0f,1.0f,1.0f
};

// 1Ãþ °è´Ü
figure rect_1wall[] =
{
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,

    84.0f, 0.0f,0.0f,1.0f,1.0f,1.0f,
    84.0f, 8.0f,0.0f,1.0f,1.0f,1.0f,
    80.0f, 8.0f,0.0f,1.0f,1.0f,1.0f
};

// 2Ãþ ¹Ù´Ú
figure rect_2floor[] =
{
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,

    70.0f, 13.0f,0.0f,1.0f,1.0f,1.0f,
    70.0f, 15.0f,0.0f,1.0f,1.0f,1.0f,
    0.0f, 15.0f,0.0f,1.0f,1.0f,1.0f
};

// 2Ãþ °è´Ü
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


bool coilision(float, float);

GLuint vao[24], vbo[26];

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

    for (int i = 0; i < 10; ++i)
    {
        rollwheel_x[i] = 5.0f;
        rollwheel_y[i] = 138.0f;
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
    DrawMap();
    DrawObsRect();
    DrawObsWheel();

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
        std::cerr << "ERROR : vertex shader ÄÄÆÄÀÏ ½ÇÆÐ\n " << errorLog << std::endl;
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
        std::cerr << "ERROR : vertex shader ÄÄÆÄÀÏ ½ÇÆÐ\n " << errorLog << std::endl;
        return;
    }
}

void InitBuffer()
{
    glGenVertexArrays(24, vao);
    glGenBuffers(26, vbo);

    // À°¸éÃ¼
    glBindVertexArray(vao[0]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

    glBufferData(GL_ARRAY_BUFFER, cube_vertices.size() * sizeof(glm::vec3), &cube_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);

    glBufferData(GL_ARRAY_BUFFER, cube_normals.size() * sizeof(glm::vec3), &cube_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    // ÇÃ·¹ÀÌ¾î
    glBindVertexArray(vao[1]);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[2]);

    glBufferData(GL_ARRAY_BUFFER, player_vertices.size() * sizeof(glm::vec3), &player_vertices[0], GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo[3]);

    glBufferData(GL_ARRAY_BUFFER, player_normals.size() * sizeof(glm::vec3), &player_normals[0], GL_STATIC_DRAW);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(1);

    // Åé´Ï¹ÙÄû
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

    // 1Ãþ ¹Ù´Ú
    glBindVertexArray(vao[4]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[7]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_1floor), rect_1floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 1Ãþ °è´Ü
    glBindVertexArray(vao[5]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[8]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_1wall), rect_1wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 2Ãþ ¹Ù´Ú
    glBindVertexArray(vao[6]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[9]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_2floor), rect_2floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // 2Ãþ °è´Ü
    glBindVertexArray(vao[7]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_2wall), rect_2wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //10Ãþ ¹Ù´Ú
    glBindVertexArray(vao[8]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[10]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_10floor), rect_10floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //10Ãþ °è´Ü
    glBindVertexArray(vao[9]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[11]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_10wall), rect_10wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //9Ãþ ¹Ù´Ú
    glBindVertexArray(vao[10]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[12]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_9floor), rect_9floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //9Ãþ °è´Ü

    glBindVertexArray(vao[11]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[13]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_9wall), rect_9wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //8Ãþ ¹Ù´Ú
    glBindVertexArray(vao[12]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[14]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_8floor), rect_8floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //8Ãþ °è´Ü

    glBindVertexArray(vao[13]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[15]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_8wall), rect_8wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //7Ãþ ¹Ù´Ú
    glBindVertexArray(vao[14]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[16]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_7floor), rect_7floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //7Ãþ °è´Ü

    glBindVertexArray(vao[15]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[17]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_7wall), rect_7wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //6Ãþ ¹Ù´Ú
    glBindVertexArray(vao[16]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[18]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_6floor), rect_6floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //6Ãþ °è´Ü

    glBindVertexArray(vao[17]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[19]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_6wall), rect_6wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //5Ãþ ¹Ù´Ú
    glBindVertexArray(vao[18]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[20]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_5floor), rect_5floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //5Ãþ °è´Ü

    glBindVertexArray(vao[19]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[21]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_5wall), rect_5wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //4Ãþ ¹Ù´Ú
    glBindVertexArray(vao[20]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[22]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_4floor), rect_4floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //4Ãþ °è´Ü

    glBindVertexArray(vao[21]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[23]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_4wall), rect_4wall, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //3Ãþ ¹Ù´Ú
    glBindVertexArray(vao[22]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[24]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_3floor), rect_3floor, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //3Ãþ °è´Ü

    glBindVertexArray(vao[23]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[25]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(rect_3wall), rect_3wall, GL_STATIC_DRAW);

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

    if (can_t_x < 0.0f && can_t_y<=13.0f) { can_t_x = 0.0f, x_pos = 0.0f; }

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

    //if ((can_t_x - 1.0f > rect4[2].x && can_t_x - 1.0f < rect4[2].x+0.01f)&& ( (can_t_y + 1.0f < 15.0f && can_t_y + 1.0f > 13.0f) || (can_t_y - 1.0f < 14.9f && can_t_y - 1.0f > 13.0f) )) { can_t_x = 71.0f, x_pos = 71.0f; }

    if (jump_button)
    {
        if (can_t_y <= min_jump + 11.0f)
            can_t_y += jump_y_vec;
        else jump_button = false;
    }

    else if (coilision(can_t_y, rect_1floor[0].y)) { can_t_y = 0.0f, min_jump = 0.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && coilision(can_t_y, rect_1wall[0].y)) { can_t_y = 8.0f, min_jump = 8.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 15.0f && coilision(can_t_y, rect_2floor[0].y)) { can_t_y = 15.0f, min_jump = 15.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.1f && can_t_y >= 23.0f && coilision(can_t_y, rect_2wall[0].y)) { can_t_y = 23.0f, min_jump = 23.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 30.0f && coilision(can_t_y, rect_3floor[0].y)) { can_t_y = 30.0f, min_jump = 30.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 38.0f && coilision(can_t_y, rect_3wall[0].y)) { can_t_y = 38.0f, min_jump = 38.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 45.0f && coilision(can_t_y, rect_4floor[0].y)) { can_t_y = 45.0f, min_jump = 45.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 53.0f && coilision(can_t_y, rect_4wall[0].y)) { can_t_y = 53.0f, min_jump = 53.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 60.0f && coilision(can_t_y, rect_5floor[0].y)) { can_t_y = 60.0f, min_jump = 60.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 68.0f && coilision(can_t_y, rect_5wall[0].y)) { can_t_y = 68.0f, min_jump = 68.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 75.0f && coilision(can_t_y, rect_6floor[0].y)) { can_t_y = 75.0f, min_jump = 75.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 83.0f && coilision(can_t_y, rect_6wall[0].y)) { can_t_y = 83.0f, min_jump = 83.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 90.0f && coilision(can_t_y, rect_7floor[0].y)) { can_t_y = 90.0f, min_jump = 90.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 98.0f && coilision(can_t_y, rect_7wall[0].y)) { can_t_y = 98.0f, min_jump = 98.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 105.0f && coilision(can_t_y, rect_8floor[0].y)) { can_t_y = 105.0f, min_jump = 105.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 113.0f && coilision(can_t_y, rect_8wall[0].y)) { can_t_y = 113.0f, min_jump = 113.0f; }

    else if (can_t_x > 9.0f && can_t_x < 80.0f && can_t_y >= 120.0f && coilision(can_t_y, rect_9floor[0].y)) { can_t_y = 120.0f, min_jump = 120.0f; }
    else if (can_t_x > 80.0f && can_t_x < 84.0f && can_t_y >= 128.0f && coilision(can_t_y, rect_9wall[0].y)) { can_t_y = 128.0f, min_jump = 128.0f; }

    else if (can_t_x < 71.0f && can_t_x > 0.0f && can_t_y >= 135.0f && coilision(can_t_y, rect_10floor[0].y)) { can_t_y = 135.0f, min_jump = 135.0f; }
    else if (can_t_x > -4.0f && can_t_x < 0.0f && can_t_y >= 143.0f && coilision(can_t_y, rect_10wall[0].y)) { can_t_y = 143.0f, min_jump = 143.0f; }

    else can_t_y -= 0.4f;

    Block_speed += block_vec;
    if (Block_speed >= 28.0f || Block_speed <= 0.0f)
        block_vec *= -1;

    wheel_degree += wheel_degree_vec;

    Wheel_t_x1 -= Wheel_vec;
    Wheel_t_x2 += Wheel_vec;

    if (Wheel_t_x1 >= 75.0f || Wheel_t_x1 <= 10.0f) { Wheel_vec *= -1, wheel_degree_vec *= -1; }

    for (int i = 0; i < 10; ++i)
    {
        if (wheel_roll[i] == true)
        {
            if (rollwheel_x[i] > 77.0f) { rollwheel_x[i] = 77.0f; }
            if (rollwheel_x[i] < 3.0f) { rollwheel_x[i] = 3.0f; }

            if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 135.0f && coilision(rollwheel_y[i] - 2.5f, rect_10floor[0].y)) { rollwheel_y[i] = 138.0f, rollvec = 0.2; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 120.0f && coilision(rollwheel_y[i] - 2.5f, rect_9floor[0].y)) { rollwheel_y[i] = 123.0f, rollvec = -0.2; }
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 105.0f && coilision(rollwheel_y[i] - 2.5f, rect_8floor[0].y)) { rollwheel_y[i] = 108.0f, rollvec = 0.2, wheel_roll[i + 1] = true; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 90.0f && coilision(rollwheel_y[i] - 2.5f, rect_7floor[0].y)) { rollwheel_y[i] = 93.0f, rollvec = -0.2; }
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 75.0f && coilision(rollwheel_y[i] - 2.5f, rect_6floor[0].y)) { rollwheel_y[i] = 78.0f, rollvec = 0.2; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 60.0f && coilision(rollwheel_y[i] - 2.5f, rect_5floor[0].y)) { rollwheel_y[i] = 63.0f, rollvec = -0.2; }
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 45.0f && coilision(rollwheel_y[i] - 2.5f, rect_4floor[0].y)) { rollwheel_y[i] = 48.0f, rollvec = 0.2; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 30.0f && coilision(rollwheel_y[i] - 2.5f, rect_3floor[0].y)) { rollwheel_y[i] = 33.0f, rollvec = -0.2; }
            else if (rollwheel_x[i] < 74.0f && rollwheel_x[i] > 0.0f && rollwheel_y[i] >= 15.0f && coilision(rollwheel_y[i] - 2.5f, rect_2floor[0].y)) { rollwheel_y[i] = 18.0f, rollvec = 0.2; }
            else if (rollwheel_x[i] < 79.0f && rollwheel_x[i] > 10.0f && rollwheel_y[i] >= 0.0f && coilision(rollwheel_y[i] - 2.5f, rect_1floor[0].y)) { rollwheel_y[i] = 3.0f; wheel_roll[i] = false; }
            else rollwheel_y[i] -= 0.5f;
            rollwheel_x[i] += rollvec;
        }
    }
    light_r -= light_vec * 2.0f;
    light_g -= light_vec * 2.0f;
    light_b -= light_vec * 2.0f;

    glutTimerFunc(10, Timerfunction, 1);
    glutPostRedisplay();
}

GLvoid DrawMap()
{
    // °æ·Î
    // 1Ãþ 
    S = glm::scale(glm::mat4(1.0f), glm::vec3(40.0, 1.0, 5.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(40.0, 0.0, 0.0));
    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[4]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

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


    // 2Ãþ
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

    // 3Ãþ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 30.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 38.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 3Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[22]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 3Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[23]);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    // 4Ãþ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 45.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 53.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());


    // 4Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[20]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 4Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[21]);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    // 5Ãþ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 60.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 68.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 5Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[18]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 5Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[19]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 6Ãþ
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 75.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 83.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 6Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[16]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 6Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[17]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 7Ãþ

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 90.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 98.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 7Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[14]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 7Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[15]);
    glDrawArrays(GL_TRIANGLES, 0, 6);


    // 8Ãþ 
    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 105.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 113.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());
    // 8Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[12]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 8Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[13]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 9Ãþ

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(45.0f, 120.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(83.0f - 1.0f, 128.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    // 9Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[10]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 9Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[11]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    // 10Ãþ

    S = glm::scale(glm::mat4(1.0f), glm::vec3(35.0f, 1.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(35.0f, 135.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);


    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(2.0f, 5.0f, 5.0f));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(-3.0f + 1.0f, 143.0f, 0.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    //10Ãþ ¹Ù´Ú
    T = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 5.0f));

    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[8]);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    //10Ãþ °è´Ü
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T));

    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Green.r, Green.g, Green.b);

    glBindVertexArray(vao[9]);
    glDrawArrays(GL_TRIANGLES, 0, 6);
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
    // 2Ãþ Àå¾Ö¹°
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

    // Àú¾î±â À§¿¡ Åé´Ï¹ÙÄû ¿Ô´Ù°¬´Ù
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


    // ²À´ë±â Åé´Ï¹ÙÄû
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
    //¹Ú½º
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