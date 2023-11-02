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
uniform_int_distribution<int> randColor(1, 5);
uniform_int_distribution<int> polygonType(3, 6);
uniform_int_distribution<int> moveType(1, 2);
uniform_real_distribution<double> randPosition(-1.0f, 1.0f);

/*���̴� ���α׷� ����*/
GLuint shaderID;
GLuint vertexShader;
GLuint fragmentShader;

/*üũ ����*/
bool objectMode;
bool showPath;

/*�Ϲ� ����*/
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

	/*���� �ʱ�ȭ*/
	void InitBuffer();
	void InitPathBuffer();

	/*�׸���*/
	void Draw();

	/*��ü �ʱ�ȭ*/
	void SetAlive(bool alive);
	void ObjectReset();
	void SetArray();
	
	/*���� Ȯ��*/
	bool GetAlive();

	/*���� ��ȯ*/
	void Create();
	void Move();
	void ShowPath();

	/*��� ��ȯ*/
	void Reset();

	~Cobject()
	{

    }

private:
	/*�迭 ����*/
	GLuint _vao, _vbo[2];
	float _objectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };
	float _pathArr[2][3] = { 0.0f };

	/*���� ��ȭ ����*/
	bool _Alive = false;
	int _objectType;
	int _colorType;
	int _moveType;
	float _moveT;
	float _positionX1, _positionY1, _positionX2, _positionY2;
	float _tempX, _tempY;
};
Cobject object[100];
