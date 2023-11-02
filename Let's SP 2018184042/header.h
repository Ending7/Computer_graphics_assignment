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
uniform_int_distribution<int> randColor(1, 3);
uniform_int_distribution<int> polygonType(3, 6);
uniform_real_distribution<double> randPosition(0.0f, 1.0f);

/*���̴� ���α׷� ����*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*üũ ����*/
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

	/*���� �ʱ�ȭ*/
	void InitBuffer();

	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);
	void SetArray();

	/*���� Ȯ��*/
	bool GetAlive();

	/*�׸���*/
	void Draw();

	/*��ȯ*/
	void Reset();

private:
	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	float _objectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };

	/*���� ��ȭ ����*/
	bool _Alive = false;
	int _objectType;
	int _colorType;
	float _positionX, _positionY;
};
Cobject object[100];
