#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <gl/glew.h>
#include <gl/freeglut.h>
#include <gl/freeglut_ext.h>
#include <gl/freeglut_std.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define winWidth 800
#define winHeight 800

using namespace std;
// ------------------------------------------- GL 함수
GLvoid drawScene(GLvoid);
GLvoid Reshape(int, int);
GLvoid Keyboard(unsigned char, int, int);
GLvoid Timer(int);
// 쉐이더 프로그램 함수
void make_vertexShaders();
void make_fragmentShaders();
void make_shaderProgram();
//----------------------------------------
// 파일 입출력
char* filetobuf(const char*);

// -------------------------------------- 전역 변수
GLuint vertexShader;
GLuint fragmentShader;
GLuint ShaderProgramID;

GLuint VAO, VBO[3];

GLuint s_program;

GLint result;
GLchar errorLog[512];
//-------------------------------------------
GLfloat stage[][9] = {
	{
	0.0f, 0.0f, -3.0f,//1
	-3.0f, 0.0f, 0.0f, //2
	3.0f, 0.0f, 0.0f, //3
	},
	{
	3.0f, 0.0f, 0.0f,//3
	-3.0f, 0.0f, 0.0f,//4
	.0f, 0.0f, 3.0f,//2
	}
};
GLfloat cube_vertex_buffer_data[][9] = {
	{
	-1.0f, 1.0f, 1.0f,//0
	-1.0f,-1.0f, 1.0f,//2
	1.0f,-1.0f, 1.0f,//1
	},
	{
	1.0f, 1.0f, 1.0f,//3
	-1.0f, 1.0f, 1.0f,//0
	1.0f,-1.0f, 1.0f,//1
	},
	{
	1.0f,-1.0f,-1.0f,//4
	1.0f, 1.0f, 1.0f,//3
	1.0f,-1.0f, 1.0f,//1
	},
	{
	1.0f, 1.0f, 1.0f,//3
	1.0f,-1.0f,-1.0f,//4
	1.0f, 1.0f,-1.0f,//5
	},
	{
	1.0f, 1.0f, 1.0f,//3
	1.0f, 1.0f,-1.0f,//5
	-1.0f, 1.0f,-1.0f,//6
	},
	{
	1.0f, 1.0f, 1.0f,//3
	-1.0f, 1.0f,-1.0f,//6
	-1.0f, 1.0f, 1.0f,//0
	},
	{
	1.0f,-1.0f, 1.0f,//1
	-1.0f,-1.0f, 1.0f,//2
	-1.0f,-1.0f,-1.0f,//7
	},
	{
	1.0f,-1.0f, 1.0f,//1
	-1.0f,-1.0f,-1.0f,//7
	1.0f,-1.0f,-1.0f,//4
	},
	{
	1.0f, 1.0f,-1.0f,//5
	1.0f,-1.0f,-1.0f,//4
	-1.0f,-1.0f,-1.0f,//7
	},
	{
	1.0f, 1.0f,-1.0f, //5
	-1.0f,-1.0f,-1.0f,//7
	-1.0f, 1.0f,-1.0f,//6
	},
	{
	-1.0f,-1.0f,-1.0f,//7
	-1.0f,-1.0f, 1.0f,//2
	-1.0f, 1.0f, 1.0f,//0
	},
	{
	-1.0f,-1.0f,-1.0f,//7
	-1.0f, 1.0f, 1.0f,//0
	-1.0f, 1.0f,-1.0f,//6
	},
};
GLfloat vertices[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,
0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,  0.0f, 0.0f, 1.0f,

1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,
1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,

0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,
0.0f, 1.0f, 0.0f,	 0.0f, 1.0f, 0.0f,  0.0f, 1.0f, 0.0f,

0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,

0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,

-1.0f, 0.0f, 0.0f,	 -1.0f, 0.0f, 0.0f,	 -1.0f, 0.0f, 0.0f,
-1.0f, 0.0f, 0.0f,	 -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
};
//GLfloat vertices[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
//0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
//0.0f, 0.0f, -1.0f,	 0.0f, 0.0f, -1.0f,  0.0f, 0.0f, -1.0f,
//
//0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,
//0.0f, 0.0f, 1.0f,	 0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 1.0f,
//
//-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
//-1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f,  -1.0f, 0.0f, 0.0f,
//
//1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,   1.0f, 0.0f, 0.0f,
//1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,	 1.0f, 0.0f, 0.0f,
//
//0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
//0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
//
//0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f,
//0.0f, 1.0f, 0.0f,	0.0f, 1.0f, 0.0f,   0.0f, 1.0f, 0.0f
//};
GLfloat stage_vertices[] = {
0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
0.0f, -1.0f, 0.0f,	 0.0f, -1.0f, 0.0f,  0.0f, -1.0f, 0.0f,
};
float Radius = 20.0f;
float Camera_angle = 0.0f;
float Camera_xPos = 0.0f;
float Camera_yPos = 0.0f;
float Camera_zPos = 50.0f;
float ambient_x = 0.1f;
float ambient_y = 0.1f;
float ambient_z = 0.1f;
float degree_cameraRotate = 0.0f;
float trans_Z = 0.0f;
float trans_X = 0.0f;
float mid_degree = 0.0f;
float rotate_degree = 0.0f;
float rotate_degree2 = 0.0f;
float light_R = 1.0f;
float light_G = 1.0f;
float light_B = 1.0f;
bool timer = false;
bool rotate_mode = false;
bool camera_mode = false;
bool camera_timer = false;
bool rotate_timer = false;
int Rotate = 0;
int lightOn = 0;
int lightmod = 0;
int main(int argc, char** argv)
{

	// 윈도우 생성하기
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(winWidth, winHeight);
	glutCreateWindow("Example1");

	// GLEW 초기화하기
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
	}

	else
		std::cout << "GLEW initialized\n";


	// 쉐이더 읽어와서 쉐이더 프로그램 만들기

	make_shaderProgram();
	glEnable(GL_DEPTH_TEST);
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(3, VBO);
	glutDisplayFunc(drawScene);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, Timer, 1);
	glutReshapeFunc(Reshape);

	glutMainLoop();
}

GLvoid drawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	float camX = sin(Camera_angle) * Radius;
	float camZ = cos(Camera_angle) * Radius;
	glm::mat4 Smatrix = glm::mat4(1.0f);
	glm::mat4 Rmatrix = glm::mat4(1.0f);
	glm::mat4 R2matrix = glm::mat4(1.0f);
	glm::mat4 Tmatrix = glm::mat4(1.0f);

	glm::mat4 matparent = glm::mat4(1.0f);
	glm::mat4 transform_stage = glm::mat4(1.0f);
	glm::mat4 transform_2 = glm::mat4(1.0f);

	glm::mat4 transform_3 = glm::mat4(1.0f);
	glm::mat4 transform_4 = glm::mat4(1.0f);
	glm::mat4 transform_5 = glm::mat4(1.0f);


	glm::vec4 cameraPos = glm::rotate(glm::mat4(1.0f), glm::radians(degree_cameraRotate), glm::vec3(0.0f, 2.0f, 0.0f)) * glm::vec4(glm::vec3(Camera_xPos, Camera_yPos, Camera_zPos), 1.0f);
	glm::mat4 view = glm::lookAt(glm::vec3(cameraPos), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 proj = glm::perspective(glm::radians(60.0f), winWidth / (float)winHeight, 0.001f, 1000.f);
	
	
	GLuint viewlocation = glGetUniformLocation(s_program, "g_view");
	glUniformMatrix4fv(viewlocation, 1, GL_FALSE, value_ptr(view));

	//projection = glm::translate(projection, glm::vec3(0.0, 0.0, -2.5f));
	GLuint Projectionlocation = glGetUniformLocation(s_program, "g_projection");
	glUniformMatrix4fv(Projectionlocation, 1, GL_FALSE, value_ptr(proj));

	/*Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -1.0f));
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(1.0f, 0.0f, 0.0f));*/
	glm::vec3 lightAmbient = glm::vec3(ambient_x, ambient_y, ambient_z);
	GLuint lightAmbientLocation = glGetUniformLocation(s_program, "g_lightAmbient");
	glUniform3fv(lightAmbientLocation, 1, (float*)&lightAmbient);

	glm::vec3 lightPos = glm::vec3(camX, 20.0, camZ);
	GLuint lightPosLocation = glGetUniformLocation(s_program, "g_lightPos");
	glUniform3fv(lightPosLocation, 1, (float*)&lightPos);

	glm::vec3 lightColor = glm::vec3(light_R, light_G, light_B);
	GLuint lightColorLocation = glGetUniformLocation(s_program, "g_lightColor");
	glUniform3fv(lightColorLocation, 1, (float*)&lightColor);

	glm::vec3 objColor = glm::vec3(0.7, 0.7, 0.7);
	GLuint objColorLocation = glGetUniformLocation(s_program, "g_objectColor");
	glUniform3fv(objColorLocation, 1, (float*)&objColor);

	GLuint cameraPosLocation = glGetUniformLocation(s_program, "g_cameraPos");
	glUniform3fv(cameraPosLocation, 1, (float*)&cameraPos);
	Smatrix = glm::scale(glm::mat4(1.0f), glm::vec3(10.0f, 10.0f, 10.0f));
	Rmatrix = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	//Rmatrix = glm::rotate(Rmatrix, glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	//Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, -0.1f, 0.0f));
	matparent = Tmatrix * Rmatrix * Smatrix;
	GLuint TransformLocation = glGetUniformLocation(s_program, "g_modelTransform");
	glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, value_ptr(matparent));

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stage), stage, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(stage_vertices), stage_vertices, GL_STATIC_DRAW);
	int normalLocation = glGetAttribLocation(s_program, "in_normal");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalLocation);

	/*glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_color_1), cube_color_1, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);*/

	glDrawArrays(GL_TRIANGLES, 0, 6);

	// 맨 밑 빨강색
	Smatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.4f, 0.15f, 0.4f));
	Rmatrix = glm::rotate(glm::mat4(1.0f), glm::radians(30.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(trans_X, 0.1f, trans_Z));
	transform_2 = matparent * Tmatrix * Smatrix;
	TransformLocation = glGetUniformLocation(s_program, "g_modelTransform");
	glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, value_ptr(transform_2));

	objColor = glm::vec3(1.0, 0.0, 0.0);
	objColorLocation = glGetUniformLocation(s_program, "g_objectColor");
	glUniform3fv(objColorLocation, 1, (float*)&objColor);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	normalLocation = glGetAttribLocation(s_program, "in_normal");
	glVertexAttribPointer(normalLocation, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(normalLocation);
	/*glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(c_color_buffer_data), c_color_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);*/
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 중간 노란색

	objColor = glm::vec3(0.0, 1.0, 0.0);
	objColorLocation = glGetUniformLocation(s_program, "g_objectColor");
	glUniform3fv(objColorLocation, 1, (float*)&objColor);

	Smatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.3f, 0.15f, 0.2f));
	Rmatrix = glm::rotate(glm::mat4(1.0f), glm::radians(mid_degree), glm::vec3(0.0f, 1.0f, 0.0f));
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(trans_X, 0.3f, trans_Z));
	transform_2 = matparent * Tmatrix * Rmatrix * Smatrix;
	TransformLocation = glGetUniformLocation(s_program, "g_modelTransform");
	glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, value_ptr(transform_2));

	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);



	glDrawArrays(GL_TRIANGLES, 0, 36);
	// 왼쪽 크레인
	objColor = glm::vec3(0.0, 0.0, 1.0);
	objColorLocation = glGetUniformLocation(s_program, "g_objectColor");
	glUniform3fv(objColorLocation, 1, (float*)&objColor);

	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(-0.1f + trans_X, 0.6f, 0.0f));
	Smatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.2f, 0.05f));
	Rmatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotate_degree), glm::vec3(1.0f, 0.0f, 0.0f));
	R2matrix = glm::rotate(glm::mat4(1.0f), glm::radians(mid_degree), glm::vec3(0.0f, 1.0f, 0.0f));
	transform_3 = matparent * R2matrix * Tmatrix * Rmatrix * Smatrix;

	TransformLocation = glGetUniformLocation(s_program, "g_modelTransform");
	glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, value_ptr(transform_3));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 36);

	// 오른쪽 크레인
	Tmatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0.1f + trans_X, 0.6f, 0.0f));
	Smatrix = glm::scale(glm::mat4(1.0f), glm::vec3(0.05f, 0.2f, 0.05f));
	Rmatrix = glm::rotate(glm::mat4(1.0f), glm::radians(rotate_degree2), glm::vec3(1.0f, 0.0f, 0.0f));
	R2matrix = glm::rotate(glm::mat4(1.0f), glm::radians(mid_degree), glm::vec3(0.0f, 1.0f, 0.0f));
	transform_4 = matparent * R2matrix * Tmatrix * Rmatrix * Smatrix;

	TransformLocation = glGetUniformLocation(s_program, "g_modelTransform");
	glUniformMatrix4fv(TransformLocation, 1, GL_FALSE, value_ptr(transform_4));
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cube_vertex_buffer_data), cube_vertex_buffer_data, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 36);
	glutPostRedisplay();
	glUseProgram(s_program);
	glutSwapBuffers();
}
GLvoid Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'c':							// 조명 색 변환
	case 'C':
		if (lightmod == 0)
		{
			light_R = 1.0f;
			light_G = 0.0f;
			light_B = 0.0f;
		}
		else if (lightmod == 1)
		{
			light_R = 0.0f;
			light_G = 1.0f;
			light_B = 0.0f;
		}
		else if (lightmod == 2)
		{
			light_R = 0.0f;
			light_G = 0.0f;
			light_B = 1.0f;
		}
		lightmod++;
		lightmod = lightmod % 3;
		break;
	case 'b':							//크레인 이동
		trans_X += 2.0f;
		break;
	case'B':
		trans_X -= 2.0f;
		break;
	case 'm':							// 조명 ON/OFF
	case 'M':
		if (lightOn == 0)
		{
			ambient_x = 0.6f;
			ambient_y = 0.6f;
			ambient_z = 0.6f;
		}
		else if (lightOn == 1)
		{
			ambient_x = 0.1f;
			ambient_y = 0.1f;
			ambient_z = 0.1f;
		}
		lightOn++;
		lightOn = lightOn % 2;
		break;
	case 's':							// 화면 멈추기
	case 'S':
		timer = false;
		camera_timer = false;
		rotate_timer = false;
		break;
	case 'q':
	case 'Q':							// 프로그램 종료
		cout << "프로그램 종료" << endl;
		exit(1);
		break;
	case 'x':							// 카메라 x축 이동
		Camera_xPos += 2.0f;
		break;
	case 'X':
		Camera_xPos -= 2.0f;
		break;
	case 'z':							// 카메라 z축 이동
		Camera_zPos += 2.0f;
		break;
	case'Z':
		Camera_zPos -= 2.0f;
		break;
	case 'r':							// 조명 회전
		camera_timer = true;
		camera_mode = true;
		break;
	case 'R':
		//Camera_angle += 0.2f;
		camera_timer = true;
		camera_mode = false;
		break;
	case 't':
	case 'T':
		rotate_timer = true;
		break;
	case 'w':
	case 'W':
		Radius = 15.0f;
		Camera_angle = 0.0f;
		Camera_xPos = 0.0f;
		Camera_yPos = 0.0f;
		Camera_zPos = 0.0f;
		trans_Z = 0.0f;
		trans_X = 0.0f;
		mid_degree = 0.0f;
		rotate_degree = 0.0f;
		rotate_degree2 = 0.0f;
		break;

	}


}

GLvoid Timer(int value)
{
	if (timer)
	{
		if (rotate_mode)
			mid_degree += 4.5f;
		else
			mid_degree -= 4.5f;


	}
	if (camera_timer)
	{
		if (camera_mode) // 카메라가 돌고있슴 이거 해결해야함!
		{
			Camera_angle += 0.2f;

		}
		else
		{
			Camera_angle -= 0.2f;
		}
	}
	if (rotate_timer)
	{
		if (Rotate == 0)
		{
			rotate_degree += 4.5f;
			rotate_degree2 -= 4.5f;
			if (rotate_degree >= 18.f)
				Rotate = 1;
		}
		else
		{
			rotate_degree -= 4.5f;
			rotate_degree2 += 4.5f;
			if (rotate_degree <= -18.f)
				Rotate = 0;
		}

	}

	glutTimerFunc(100, Timer, 1);

}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}

void make_vertexShaders() // 런타임때 컴파일 됨
{

	GLchar* vertexsource;
	vertexsource = filetobuf("vertex.glsl");

	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, (const GLchar**)&vertexsource, 0);

	glCompileShader(vertexShader);
	// 컴파일 실패 경우를 나타내줌


	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		cerr << "ERROR: vertexShader 컴파일 실패\n" << errorLog << endl;
		return;
	}

}

void make_fragmentShaders()
{
	GLchar* fragmentsource;

	fragmentsource = filetobuf("fragment.glsl");


	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, (const GLchar**)&fragmentsource, 0);
	glCompileShader(fragmentShader);



	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);


	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		cerr << "ERROR: vertexShader 컴파일 실패\n" << errorLog << endl;
		return;
	}

}

void make_shaderProgram()
{

	make_vertexShaders();
	make_fragmentShaders();

	s_program = glCreateProgram();

	glAttachShader(s_program, vertexShader);
	glAttachShader(s_program, fragmentShader);
	glLinkProgram(s_program);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	if (!result)
	{
		glGetProgramInfoLog(ShaderProgramID, 512, NULL, errorLog);
		cerr << "Error : shader program 연결 실패 \n" << errorLog << endl;
	}

	glUseProgram(s_program);

}
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading
	if (!fptr) // Return NULL on failure
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file
	length = ftell(fptr); // Find out how many bytes into the file we are
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer
	fclose(fptr); // Close the file
	buf[length] = 0; // Null terminator
	return buf;
}
