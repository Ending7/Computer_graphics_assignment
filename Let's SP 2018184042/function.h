#pragma once
#include <gl/glew.h> 
#include <gl/freeglut.h> 
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

/*세이더 함수*/
void make_vertexShader();
void make_fragmentShader();
void make_shaderProgram();
char* filetobuf(const char* file);

/*초기화 함수*/
void InitObject(); //객체 초기화
void InitBuffer(); // vao, vbo 연결
void Draw(); // 그리기

/*상태 변화 함수*/
void Move();
void Create();

/*일반 함수*/

/*콜백 함수*/
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char button, int x, int y);
GLvoid TimerCreate(int value);
GLvoid TimerMove(int value);
