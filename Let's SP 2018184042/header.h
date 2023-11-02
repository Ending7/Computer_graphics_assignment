#pragma once
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <random>

using namespace std;

/*���� �� ����*/
random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_real_distribution<double> randomColor(0.0, 1.0);
uniform_real_distribution<double> randomSpeed(0.1, 1.0);
uniform_real_distribution<double> randomPosition(-0.4, 0.4);
uniform_int_distribution<int> randomMotionType1(1, 2);
uniform_int_distribution<int> randomMotionType2(1, 4);
uniform_int_distribution<int> polygonType(3, 6);

/*���̴� ���α׷� ����*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*üũ ����*/

/*******VBO object_Type*******/
enum
{
	TRIANGLE = 1,
	RECTANGLE = 2,
	PENTAGON = 3,
	HEXAGON = 4
};
float rotateval = 0.0f;

struct coord {
	float x = 0;
	float y = 0;
	float z = 0;
	float r = 0;
	float g = 0;
	float b = 0;
};

class Cobject
{
public:
	/*���� �ʱ�ȭ*/
	void InitBuffer();

	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);
	void SetArray();

	/*�׸���*/
	void Draw();

	/*��ȯ*/
	void Reset();

public:
	/*�迭 ���� �Ҵ�*/
	int arrCount = polygonType(eng);

	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	coord * _objectArr =(coord *)malloc(arrCount*sizeof(coord));

	/*���� ��ȭ ����*/
	bool _Alive = false;
	int _objectType;
	int _objectNumber;
};
Cobject object[1];
