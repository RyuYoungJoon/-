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
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/freeglut_std.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
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
void Timerfunction(int);

GLchar* vertexsource, * fragmentsource;
GLuint vertexshader, fragmentshader;
GLuint s_program[3];
GLUquadricObj* qobj;

random_device rd;
default_random_engine dre{ rd() };
uniform_real_distribution<> random_pos_urd{ -20.0,20.0 };

float random_xpos = random_pos_urd(dre);
float random_zpos = random_pos_urd(dre);

float Camera_xPos = 60.0f;
float Camera_yPos = 0.0f;
float Camera_zPos = 50.0f;

float Proj_degree = 100.0f;

float light_x = -15.0;
float light_y = 15.0;
float light_z = 0.0;

float light_r = 1.0;
float light_g = 1.0;
float light_b = 1.0;

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

std::vector< glm::vec3 > bottom_vertices;
std::vector< glm::vec2 > bottom_uvs;
std::vector< glm::vec3 > bottom_normals;

bool loadOBJ(
    const char* path,
    std::vector<glm::vec3>& out_vertices,
    std::vector<glm::vec2>& out_uvs,
    std::vector<glm::vec3>& out_normals
)
{
    std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    std::vector<glm::vec3>temp_vertices;
    std::vector<glm::vec2>temp_uvs;
    std::vector<glm::vec3>temp_normals;

    FILE* file = fopen(path, "r");
    if (file == NULL)
    {
        std::cout << "파일 열수 없음!" << std::endl;
        return false;
    }

    while (1) {
        char lineHeader[128];
        int res = fscanf(file, "%s", lineHeader);
        if (res == EOF)
            break;;

        if (strcmp(lineHeader, "v") == 0) {
            glm::vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        }
        else if (strcmp(lineHeader, "vt") == 0) {
            glm::vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            temp_uvs.push_back(uv);
        }

        else if (strcmp(lineHeader, "vn") == 0) {
            glm::vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        }

        else if (strcmp(lineHeader, "f") == 0)
        {
            std::string vertex1, vertex2, vertex3;
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0],
                &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                std::cout << "나의 간단한 프로그램으론 읽을수없다." << std::endl;
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices.push_back(uvIndex[0]);
            uvIndices.push_back(uvIndex[1]);
            uvIndices.push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        }

        for (unsigned int i = 0; i < vertexIndices.size(); i++) {
            unsigned int vertexIndex = vertexIndices[i];
            glm::vec3 vertex = temp_vertices[vertexIndex - 1];
            out_vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < uvIndices.size(); i++) {
            unsigned int uvIndex = uvIndices[i];
            glm::vec2 uv = temp_uvs[uvIndex - 1];
            out_uvs.push_back(uv);
        }

        for (unsigned int i = 0; i < normalIndices.size(); i++) {
            unsigned int normalIndex = normalIndices[i];
            glm::vec3 normal = temp_normals[normalIndex - 1];
            out_normals.push_back(normal);
        }

    }

}

bool res_cube = loadOBJ("cube.obj", cube_vertices, cube_uvs, cube_normals);
bool res_pyramid = loadOBJ("pyramid.obj", pyramid_vertices, pyramid_uvs, pyramid_normals);

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

    glm::mat4 LIGHT = glm::mat4(1.0f);

    glm::vec3 camerapos = glm::vec3(Camera_xPos, Camera_yPos, Camera_zPos); //EYE
    glm::vec3 cameradirection = glm::vec3(60.0f, 0.0f, 0.0f); // AT
    glm::vec3 cameraup = glm::vec3(0.0f, 1.0f, 0.0f); // UP
    glm::mat4 view = glm::mat4(1.0f);

    view = glm::lookAt(camerapos, cameradirection, cameraup);
    GLuint viewlocation = glGetUniformLocation(s_program[0], "View");
    glUniformMatrix4fv(viewlocation, 1, GL_FALSE, value_ptr(view));

    glm::mat4 projection = glm::mat4(1.0f);
    projection = glm::perspective(glm::radians(Proj_degree), (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    GLuint Projectionlocation = glGetUniformLocation(s_program[0], "Projection");
    glUniformMatrix4fv(Projectionlocation, 1, GL_FALSE, value_ptr(projection));

    S = glm::scale(glm::mat4(1.0f), glm::vec3(40.0, 0.5, 1.0));
    unsigned int path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(S));
    unsigned int path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 1.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(50.0, 5.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 1.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(65.0, 10.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(5.0, 0.5, 1.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(80.0, 7.5, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0, 0.5, 1.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(110.0, 0.0, 0.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    S = glm::scale(glm::mat4(1.0f), glm::vec3(20.0, 0.5, 1.0));
    Ry = glm::rotate(glm::mat4(1.0f), float(glm::radians(90.0)), glm::vec3(0.0, 1.0, 0.0));
    T = glm::translate(glm::mat4(1.0f), glm::vec3(130.0, 0.0, 20.0));
    path = glGetUniformLocation(s_program[0], "Transform");
    glUniformMatrix4fv(path, 1, GL_FALSE, glm::value_ptr(T * Ry * S));
    path_Color = glGetUniformLocation(s_program[1], "in_Color");
    glUniform3f(path_Color, Gray.r, Gray.g, Gray.b);

    glBindVertexArray(vao[0]);
    glDrawArrays(GL_TRIANGLES, 0, cube_vertices.size());

    unsigned int light_pos = glGetUniformLocation(s_program[2], "lightPos");
    glUniform3f(light_pos, light_x, light_y, light_z);

    unsigned int light_color = glGetUniformLocation(s_program[2], "lightColor");
    glUniform3f(light_color, light_r, light_g, light_b);

    unsigned int view_pos = glGetUniformLocation(s_program[2], "viewPos");
    glUniform3f(view_pos, Camera_xPos, Camera_yPos, Camera_zPos);

    unsigned int ambientLight_on = glGetUniformLocation(s_program[2], "ambientLight_on_off");
    glUniform3f(ambientLight_on, 0.7, 0.7, 0.7);

    glutPostRedisplay();
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

    // 원
    glBindVertexArray(vao[2]);
    glBindBuffer(GL_ARRAY_BUFFER, vbo[4]);

    glBufferData(GL_ARRAY_BUFFER, sizeof(circle), circle, GL_STATIC_DRAW);

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

}

void Timerfunction(int value)
{
    glutTimerFunc(10, Timerfunction, 1);
}