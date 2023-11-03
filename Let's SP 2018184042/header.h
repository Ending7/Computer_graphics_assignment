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
uniform_real_distribution<double> randPosition(-0.5f, 1.0f);

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

enum {
	LEFT = 0,
	RIGHT = 1,
};
/**********도형**********/
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
	void Create();

	/*상태 확인*/
	bool GetAlive();

	/*상태 변화*/
	void ObjectMove();
	void ShowPath();

	/*행렬 변환*/
	void Reset();

	~Cobject()
	{

	};

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

/**********슬라이스 선**********/
class Cline
{
public:
	Cline()
	{
		
	};
	/*버퍼 초기화*/
	void InitLineBuffer();

	/*그리기*/
	void DrawLine();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void SetMouseClick(bool mouseClick);

	/*상태 확인*/
	bool GetAlive();
	bool GetMouseClick();

	/*상태 변화*/
	void InsertPosition1(float glPosX, float glPosY);
	void InsertPosition2(float glPosX, float glPosY);
	void ResetLineArray();

	~Cline()
	{

	};
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float _lineArr[2][3] = { 0.0f };
	float _colorArr[2][3] = { {1.0f, 0.0f,0.0f },{1.0f, 0.0f,0.0f }};

	/*상태 변화 관련*/
	bool _Alive = false;
	bool _MouseClick = false;
};
Cline line;

/**********바구니**********/
class Cbucket
{
public:
	Cbucket()
	{

	};
	/*버퍼 초기화*/
	void InitBucketBuffer();

	/*그리기*/
	void DrawBucket();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void SetArray();

	/*상태 변화*/
	void BucketMove();

	~Cbucket()
	{

	};
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float positionX1 = 0.0f;
	float _bucketArr[4][3] = { 0.0f };
	float _colorArr[4][3] = { {0.0f, 0.0f,1.0f },{0.0f, 0.0f,1.0f },{0.0f, 0.0f,1.0f },{0.0f, 0.0f,1.0f } };
	float _lineX = -0.8f, _lineX2 = 0.8f; //바구니가 이동할 경로
	float _moveT = 0.5f; //가운데서부터 선형보간
	
	/*상태 변화 관련*/
	bool _Alive = false;
	bool _MouseClick = false;
	int _moveArrow = RIGHT;

};
Cbucket bucket;