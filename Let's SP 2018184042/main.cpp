﻿#include "function.h"
#include <iostream>

int main(int argc, char** argv) 
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	/***********************************
	[순서]
	1.윈도우를 생성한다.
	2.2.0이상 확장 기능을 사용하기 위해 GLEW를 현재 버전으로 초기화한다
	3.다양한 콜백 함수들을 호출한다.
	***********************************/

	/*********윈도우 생성하기*********/
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(500, 0);
	glutInitWindowSize(1000, 1000);
	glutCreateWindow("컴그02_2018184042장진영");

	/*********GLEW 초기화하기*********/
	glewExperimental = GL_TRUE; 
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	/***********시작 초기화***********/

	/*셰이더 프로그램*/
	make_shaderProgram();
	/*객체 초기화*/
	InitObject();
	/*vao에 vbo연결하기*/
	InitBuffer();
	/*그 외*/
	/*glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);*/

	/*********콜백 함수(운영체제 호출 함수) 호출하기*********/
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
