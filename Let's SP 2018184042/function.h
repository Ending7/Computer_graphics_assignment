#pragma once
#include <gl/glew.h> 
#include <gl/freeglut.h> 
#include <gl/freeglut_ext.h>
#include <gl/glm/glm.hpp>
#include <gl/glm/ext.hpp>
#include <gl/glm/gtc/matrix_transform.hpp>

/*���̴� �Լ�*/
void make_vertexShader();
void make_fragmentShader();
void make_shaderProgram();
char* filetobuf(const char* file);

/*�ʱ�ȭ �Լ�*/
void InitObject(); //��ü �ʱ�ȭ
void InitBuffer(); // vao, vbo ����
void Draw(); // �׸���

/*���� ��ȭ �Լ�*/
void Move();
void Create();

/*�Ϲ� �Լ�*/

/*�ݹ� �Լ�*/
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char button, int x, int y);
GLvoid TimerCreate(int value);
GLvoid TimerMove(int value);
