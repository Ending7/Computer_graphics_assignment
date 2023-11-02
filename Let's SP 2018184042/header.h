#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <random>

using namespace std;

/*랜덤 값 설정*/
random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_int_distribution<int> randColor(1, 3);
uniform_int_distribution<int> polygonType(3, 6);
uniform_real_distribution<double> randPosition(0.0f, 1.0f);

/*셰이더 프로그램 변수*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*체크 변수*/
float rotateval = 0.0f;

enum {
	RED = 1,
	GREEN = 2,
	BLUE = 3,
	CYAN = 4
};

class Cobject
{
public:
	Cobject()
	{
		_objectType = polygonType(eng);
		_colorType = randColor(eng);
		_positionX = randPosition(eng);
		_positionY = randPosition(eng);
	};

	/*버퍼 초기화*/
	void InitBuffer();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void SetArray();

	/*상태 확인*/
	bool GetAlive();

	/*그리기*/
	void Draw();

	/*변환*/
	void Reset();

private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float _objectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };

	/*상태 변화 관련*/
	bool _Alive = false;
	int _objectType;
	int _colorType;
	float _positionX, _positionY;
};
Cobject object[100];
