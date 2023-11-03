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
void InitBucket(); //��ü �ʱ�ȭ
void Draw(); // �׸���
void ShowPath(); //��� �׸���
void DrawLine(); //�����̽� ���� �׸���

/*���� ��ȭ �Լ�*/
void Create();
void Collider();
void ObjectMove();
void BucketMove();
/*�Ϲ� �Լ�*/

/*�ݹ� �Լ�*/
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char button, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerObjectCreate(int value);
GLvoid TimerObjectMove(int value);
GLvoid TimerBucketMove(int value);