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
uniform_int_distribution<int> polygonType(3, 5);
uniform_int_distribution<int> moveType(1, 4);
uniform_real_distribution<double> randPosition(-0.5f, 1.0f);
uniform_real_distribution<double> randPosition2(0.4f, 0.8f);
uniform_real_distribution<double> randPosition3(-0.3f, 0.5f);

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
float tempMoveT = 0.0f;
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

enum {
	TRIANGLE = 3,
	RECTANGLE = 4,
	PENTAGON = 5,
	HEXAGON = 6
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
	void GetArray(float objectArr[6][3]);
	int GetType();
	int GetColorType();

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
	float _pathArr[4][3] = { 0.0f };

	/*상태 변화 관련*/
	bool _Alive = false;
	int _objectType;
	int _colorType;
	int _moveType;
	float _moveT;
	float _positionX1, _positionY1, _positionX2, _positionY2;
	float _positionX3, _positionY3, _positionX4, _positionY4;
	float _tempX, _tempY;
	float _controlpoint1X, _controlpoint1Y;
	float _controlpoint2X, _controlpoint2Y;
	float _angleRotate;
};
Cobject object[10];

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
	void GetArray(float sliceLineArr[2][3]);

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
	void GetArray(float bucketArr[4][3]);
	int GetBucketMoveArrow();

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

/**********슬라이스 오브젝트**********/
class CsliceObject
{
public:
	CsliceObject()
	{

	};
	/*버퍼 초기화*/
	void InitSliceObject();

	/*그리기*/
	void DrawSliceObject();

	/*객체 초기화*/
	void SetAlive(bool alive);
	void SetArray(int vertexType1, int vertexType2, float finalx, float finaly, float finalx2, float finaly2, int objectType, int objectCount, float objectArr[6][3], int colorType);

	/*상태 확인*/
	bool GetAlive();
	void GetLowestPos(float * lowestPosY, float * lowestPosX);

	/*상태 변화*/
	void SliceObjectMove();
	void SliceObjectReset();
	void ChangeFallType(int num);
	~CsliceObject()
	{

	};
private:
	/*배열 관련*/
	GLuint _vao, _vbo[2];
	float _sliceObjectArr[6][3] = { 0.0f };
	float _colorArr[6][3] = { 0.0f };
	
	/*상태 변화 관련*/
	bool _Alive = false;
	int _objectType;
	float _fallDown = -0.001f;
	int _fallType = 0;
	float positionX = 0.0f;
};
CsliceObject sliceObject[100];
