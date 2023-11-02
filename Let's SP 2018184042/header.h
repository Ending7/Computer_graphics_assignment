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
uniform_real_distribution<double> randomColor(0.0, 1.0);
uniform_real_distribution<double> randomSpeed(0.1, 1.0);
uniform_real_distribution<double> randomPosition(-0.4, 0.4);
uniform_int_distribution<int> randomMotionType1(1, 2);
uniform_int_distribution<int> randomMotionType2(1, 4);

/*셰이더 프로그램 변수*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*체크 변수*/
/*******VBO object_Type*******/
enum
{
	VBO_AXIS = 1
};

/************PARTS************/
enum
{
	AXIS = 1,
};

class Cobject
{
public:
	/*버퍼 초기화*/
	void InitBuffer();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void SetVertexType(GLint type);
	void SetType(GLint type);
	void SetNumber(GLint number);
	void SetArray();

	/*그리기*/
	void Draw();

	/*변환*/
	void Reset();

	/*상태 변화*/


	/*애니메이션*/


private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float _objectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };

	/*행렬 관련*/

	/*상태 변화 관련*/
	bool _Alive = false;
	int _objectType;
	int _objectNumber;
	int _vertexType;
};
Cobject object[1];
