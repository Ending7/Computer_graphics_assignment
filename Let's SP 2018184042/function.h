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
void InitBucket(); //객체 초기화
void Draw(); // 그리기
void ShowPath(); //경로 그리기
void DrawLine(); //슬라이스 라인 그리기

/*상태 변화 함수*/
void Create();
void Collider();
void ObjectMove();
void BucketMove();
/*일반 함수*/

/*콜백 함수*/
GLvoid drawScene(GLvoid);
GLvoid Reshape(int w, int h);
GLvoid Keyboard(unsigned char button, int x, int y);
GLvoid Mouse(int button, int state, int x, int y);
GLvoid Motion(int x, int y);
GLvoid TimerObjectCreate(int value);
GLvoid TimerObjectMove(int value);
GLvoid TimerBucketMove(int value);