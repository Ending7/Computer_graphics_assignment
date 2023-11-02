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
uniform_int_distribution<int> randColor(1, 5);
uniform_int_distribution<int> polygonType(3, 6);
uniform_int_distribution<int> moveType(1, 2);
uniform_real_distribution<double> randPosition(-1.0f, 1.0f);

/*셰이더 프로그램 변수*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*체크 변수*/
bool objectMode;
bool showPath;

/*일반 변수*/
int timerSpeed = 50;
float rotateval = 0.0f;

enum {
	RED = 1,
	GREEN = 2,
	BLUE = 3,
	CYAN = 4,
	YELLOW = 5
};

class Cobject
{
public:
	Cobject()
	{
		
	};

	/*버퍼 초기화*/
	void InitBuffer();
	void InitPathBuffer();

	/*그리기*/
	void Draw();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void ObjectReset();
	void SetArray();
	
	/*상태 확인*/
	bool GetAlive();

	/*상태 변환*/
	void Create();
	void Move();
	void ShowPath();

	/*행렬 변환*/
	void Reset();

	~Cobject()
	{

    }

private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float _objectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };
	float _pathArr[2][3] = { 0.0f };

	/*상태 변화 관련*/
	bool _Alive = false;
	int _objectType;
	int _colorType;
	int _moveType;
	float _moveT;
	float _positionX1, _positionY1, _positionX2, _positionY2;
	float _tempX, _tempY;
};
Cobject object[100];
