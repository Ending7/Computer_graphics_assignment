#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
using namespace std;

/***************************************일반 함수들*************************************/
/*바구니 화면에 바로 출력*/
void InitBucket()
{
	bucket.SetAlive(true);
	bucket.SetArray();
	bucket.InitBucketBuffer();
}
/*도형 그리기*/
void Draw()
{
	for (int i = 0; i < 10; i++)
	{
		object[i].Draw();
	}
}
/*경로 그리기*/
void ShowPath()
{
	for (int i = 0; i < 10; i++)
	{
		object[i].ShowPath();
	}
}
/*슬라이스 라인 그리기*/
void DrawLine()
{
	line.DrawLine();
}
/*잘린 도형 그리기*/
void DrawSliceObject()
{
	for (int i = 0; i < 20; i++)
	{
		sliceObject[i].DrawSliceObject();
	}
}
/*도형 생성*/
void Create()
{
	for (int i = 0; i < 100; i++)
	{
		if (object[i].GetAlive() == false)
		{
			object[i].Create();
			break;
		}
	}
}
/*슬라이스 라인과 도형 충돌*/
void Collider()
{
	if (line.GetAlive() == true && line.GetMouseClick() == false)
	{
		/*생각: 각 도형의 선분들과 슬라이스 선분의 교점을 구한다.
		교점을 구했을 때 2개가 나온다면 그 교점을 기준으로 도형을
		두개로 나누면 된다.

		/*충돌처리*/
		for (int i = 0; i < 10; i++)
		{
			if (object[i].GetAlive() == true)
			{
				/*1.슬라이스 선분 배열을 꺼내온다.*/
				float sliceLineArr[2][3] = { 1.0f };
				line.GetArray(sliceLineArr);

				/*2.도형의 배열을 꺼내온다.*/
				float objectArr[6][3] = { 1.0f };
				object[i].GetArray(objectArr);

				/*3.도형의 타입을 가져온다.*/
				int objectType = 0, colorType = 0;
				objectType = object[i].GetType();
				colorType = object[i].GetColorType();

				/*4. 먼저 슬라이스 선의 x, y를 추출한다.*/
				float x1 = sliceLineArr[0][0];
				float y1 = sliceLineArr[0][1];
				float x2 = sliceLineArr[1][0];
				float y2 = sliceLineArr[1][1];
				int vertexType1 = 0;
				int vertexType2 = 0;
				float finalx = 0.0f, finaly = 0.0f;
				float finalx2 = 0.0f, finaly2 = 0.0f;

				/*교점의 개수*/
				int count = 0;

				/*5. 이어서 도형의 모든 선분의 직선의 방정식을 구하고
				교점의 방정식을 이용하여 교점의 개수와 교점을 구한다.
				2개면 이어서 충돌처리하고, 아니면 continue해서 다음 도형 검사*/
				switch (objectType)
				{
				case TRIANGLE:
					for (int i = 0; i < 3; i++)
					{
						float t, s, _t, _s, under;
						/*첫번째 변 추출*/
						float x3 = objectArr[i][0];
						float y3 = objectArr[i][1];
						float x4 = objectArr[i + 1][0];
						float y4 = objectArr[i + 1][1];
						/*i==3일 때 x4, y4는 맨 처음 정점*/
						if (i == 2)
						{
							x4 = objectArr[0][0];
							y4 = objectArr[0][1];
						}
						/*분모*/
						under = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
						if (under == 0) //분모가 0이면 평행이다
						{
							continue;
						}
						/*분자*/
						_t = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
						_s = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
						/*최종 공식*/
						t = _t / under;
						s = _s / under;
						if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0)
						{
							continue;
						}
						if (_t == 0 && _s == 0)
						{
							continue;
						}
						/*최종적으로 finalx, finaly에 두 교점이 들어간다.*/
						if (finalx == 0.0f)
						{
							finalx = x1 + t * (x2 - x1);
							finaly = y1 + t * (y2 - y1);
						}
						else
						{
							finalx2 = x1 + t * (x2 - x1);
							finaly2 = y1 + t * (y2 - y1);
						}
						/*두 교점이 어떤 변에 들어 있는 점인지를 파악해야 한다.*/
						switch (i)
						{
						case 0:
							if (vertexType1 == 0)
							{
								vertexType1 = 0;
							}
							else
							{
								vertexType2 = 0;
							}
							break;
						case 1:
							if (vertexType1 == 0)
							{
								vertexType1 = 1;
							}
							else
							{
								vertexType2 = 1;
							}
							break;
						case 2:
							if (vertexType1 == 0)
							{
								vertexType1 = 2;
							}
							else
							{
								vertexType2 = 2;
							}
							break;
						}
						count += 1;
					}
					break;

				case RECTANGLE:
					for (int i = 0; i < 4; i++)
					{
						float t, s, _t, _s, under;
						/*첫번째 변 추출*/
						float x3 = objectArr[i][0];
						float y3 = objectArr[i][1];
						float x4 = objectArr[i + 1][0];
						float y4 = objectArr[i + 1][1];
						/*i==3일 때 x4, y4는 맨 처음 정점*/
						if (i == 3)
						{
							x4 = objectArr[0][0];
							y4 = objectArr[0][1];
						}
						/*분모*/
						under = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
						if (under == 0) //분모가 0이면 평행이다
						{
							continue;
						}
						/*분자*/
						_t = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
						_s = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
						/*최종 공식*/
						t = _t / under;
						s = _s / under;
						if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0)
						{
							continue;
						}
						if (_t == 0 && _s == 0)
						{
							continue;
						}
						/*최종적으로 finalx, finaly에 두 교점이 들어간다.*/
						if (finalx == 0.0f)
						{
							finalx = x1 + t * (x2 - x1);
							finaly = y1 + t * (y2 - y1);
						}
						else
						{
							finalx2 = x1 + t * (x2 - x1);
							finaly2 = y1 + t * (y2 - y1);
						}
						/*두 교점이 어떤 변에 들어 있는 점인지를 파악해야 한다.*/
						switch (i)
						{
						case 0:
							if (vertexType1 == 0)
							{
								vertexType1 = 0;
							}
							else
							{
								vertexType2 = 0;
							}
							break;
						case 1:
							if (vertexType1 == 0)
							{
								vertexType1 = 1;
							}
							else
							{
								vertexType2 = 1;
							}
							break;
						case 2:
							if (vertexType1 == 0)
							{
								vertexType1 = 2;
							}
							else
							{
								vertexType2 = 2;
							}
							break;
						case 3:
							if (vertexType1 == 0)
							{
								vertexType1 = 3;
							}
							else
							{
								vertexType2 = 3;
							}
							break;
						}
						count += 1;
					}
					break;
					
				case PENTAGON:
					for (int i = 0; i < 5; i++)
					{
						float t, s, _t, _s, under;
						/*첫번째 변 추출*/
						float x3 = objectArr[i][0];
						float y3 = objectArr[i][1];
						float x4 = objectArr[i + 1][0];
						float y4 = objectArr[i + 1][1];
						/*i==3일 때 x4, y4는 맨 처음 정점*/
						if (i == 4)
						{
							x4 = objectArr[0][0];
							y4 = objectArr[0][1];
						}
						/*분모*/
						under = (y4 - y3) * (x2 - x1) - (x4 - x3) * (y2 - y1);
						if (under == 0) //분모가 0이면 평행이다
						{
							continue;
						}
						/*분자*/
						_t = (x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3);
						_s = (x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3);
						/*최종 공식*/
						t = _t / under;
						s = _s / under;
						if (t < 0.0 || t>1.0 || s < 0.0 || s>1.0)
						{
							continue;
						}
						if (_t == 0 && _s == 0)
						{
							continue;
						}
						/*최종적으로 finalx, finaly에 두 교점이 들어간다.*/
						if (finalx == 0.0f)
						{
							finalx = x1 + t * (x2 - x1);
							finaly = y1 + t * (y2 - y1);
						}
						else
						{
							finalx2 = x1 + t * (x2 - x1);
							finaly2 = y1 + t * (y2 - y1);
						}
						/*두 교점이 어떤 변에 들어 있는 점인지를 파악해야 한다.*/
						switch (i)
						{
						case 0:
							if (vertexType1 == 0)
							{
								vertexType1 = 0;
							}
							else
							{
								vertexType2 = 0;
							}
							break;
						case 1:
							if (vertexType1 == 0)
							{
								vertexType1 = 1;
							}
							else
							{
								vertexType2 = 1;
							}
							break;
						case 2:
							if (vertexType1 == 0)
							{
								vertexType1 = 2;
							}
							else
							{
								vertexType2 = 2;
							}
							break;
						case 3:
							if (vertexType1 == 0)
							{
								vertexType1 = 3;
							}
							else
							{
								vertexType2 = 3;
							}
							break;
						case 4:
							if (vertexType1 == 0)
							{
								vertexType1 = 4;
							}
							else
							{
								vertexType2 = 4;
							}
							break;
						}
						count += 1;
					}
					break;
				}

				/*교점이 두개라면 도형을 자르고 잘린 부분을 다른
				클래스에 넣는다.*/
				if (count == 2)
				{
					int objectCount = 0;
					printf("count:2, ");
					switch (objectType)
					{
					case TRIANGLE:
						printf("TRIANGLE, ");
						for (int i = 0; i < 20; i++)
						{
							/*비어있는 슬라이스 오브젝트를 찾아보자.*/
							if (sliceObject[i].GetAlive() == false)
							{
								printf("objecCount, i: %d, %d\n", objectCount, i);
								/*살아있는 오브젝트로 변환*/
								sliceObject[i].SetAlive(true);
								sliceObject[i].SetArray(vertexType1, vertexType2, finalx, finaly, finalx2, finaly2, objectType, objectCount, objectArr, colorType);
								sliceObject[i].InitSliceObject();
								++objectCount;
							}

							if (objectCount == 2)
							{
								break;
							}
						}
						break;

					case RECTANGLE:
						printf("TRIANGLE, ");
						for (int i = 0; i < 20; i++)
						{
							/*비어있는 슬라이스 오브젝트를 찾아보자.*/
							if (sliceObject[i].GetAlive() == false)
							{
								printf("objecCount, i: %d, %d\n", objectCount, i);
								/*살아있는 오브젝트로 변환*/
								sliceObject[i].SetAlive(true);
								sliceObject[i].SetArray(vertexType1, vertexType2, finalx, finaly, finalx2, finaly2, objectType, objectCount, objectArr, colorType);
								sliceObject[i].InitSliceObject();
								++objectCount;
							}

							if (objectCount == 2)
							{
								break;
							}
						}
						break;

					case PENTAGON:
						printf("TRIANGLE, ");
						for (int i = 0; i < 20; i++)
						{
							/*비어있는 슬라이스 오브젝트를 찾아보자.*/
							if (sliceObject[i].GetAlive() == false)
							{
								printf("objecCount, i: %d, %d\n", objectCount, i);
								/*살아있는 오브젝트로 변환*/
								sliceObject[i].SetAlive(true);
								sliceObject[i].SetArray(vertexType1, vertexType2, finalx, finaly, finalx2, finaly2, objectType, objectCount, objectArr, colorType);
								sliceObject[i].InitSliceObject();
								++objectCount;
							}

							if (objectCount == 2)
							{
								break;
							}
						}
						break;
					}

					/*기존의 도형을 지운다*/
					/*printf("삼각형의 교점Type: %d, %d", vertexType1, vertexType2);*/
					object[i].SetAlive(false);
				}
			}	
		}
		/*충돌처리 마쳤으면 _alive == false*/
		line.ResetLineArray(); //선 초기화
		line.SetAlive(false);
	}
}
/*도형 이동*/
void ObjectMove()
{
	for (int i = 0; i < 10; i++)
	{
		object[i].ObjectMove();
	}
}
void BucketMove()
{
	bucket.BucketMove();
}
void SliceObjectMove()
{
	for (int i = 0; i < 20; i++)
	{
		sliceObject[i].SliceObjectMove();
	}
}
/**********************************************************************************************/

/*************************************클래스 함수(도형 제작)***********************************/
/*그리기*/
void Cobject::Draw()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	if (_Alive == true)
	{
		Reset();
		InitBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_POLYGON, 0, _objectType);
	}

}
void Cobject::ShowPath()
{
	if (_Alive == true)
	{
		InitPathBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
	}
}
void Cline::DrawLine()
{
	if (_Alive == true)
	{
		InitLineBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
	}
}
void Cbucket::DrawBucket()
{
	if (_Alive == true)
	{
		InitBucketBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_POLYGON, 0, 4);
	}
}
void CsliceObject::DrawSliceObject()
{
	if (_Alive == true)
	{
		InitSliceObject();
		glBindVertexArray(_vao);
		glDrawArrays(GL_POLYGON, 0, _objectType);
	}
}
/*도형 생성*/
void Cobject::Create()
{
	/*생성*/
	SetAlive(true);
	ObjectReset();
	SetArray();
	InitBuffer();
}
/*도형 이동*/
void Cobject::ObjectMove()
{
	if (_Alive == true)
	{
		switch (_moveType)
		{
		case 1:
			_positionX1 = (1 - _moveT) * _tempX + _moveT * _positionX2;
			_positionY1 = (1 - _moveT) * _tempY + _moveT * _positionY2;
			_moveT += 0.005f;
			if (_moveT >= 1.0f)
				_Alive = false;
			SetArray();
			InitBuffer();
			break;

		case 2:
			_positionX2 = (1 - _moveT) * _tempX + _moveT * _positionX1;
			_positionY2 = (1 - _moveT) * _tempY + _moveT * _positionY1;
			_moveT += 0.005f;
			if (_moveT >= 1.0f)
				_Alive = false;
			SetArray();
			InitBuffer();
			break;
		}
	}
}
void Cbucket::BucketMove()
{
	/*선형보간*/
	positionX1 = (1 - _moveT) * _lineX + _moveT * _lineX2;
	/*방향 전환*/
	if (_moveT >= 1.0f)
		_moveArrow = LEFT;
	else if (_moveT <= 0.0f)
		_moveArrow = RIGHT;

	/*방향에 따른 이동*/
	if (_moveArrow == LEFT)
	{
		_moveT -= 0.005f;
	}
	else if (_moveArrow == RIGHT)
	{
		_moveT += 0.005f;
	}
	/*버퍼에 배열 값 업데이트*/
	SetArray();
	InitBucketBuffer();
}
void CsliceObject::SliceObjectMove()
{
	if (_Alive == true)
	{
		for (int i = 0; i < 6; i++)
		{
			/*배열에서 0.0f는 존재하지 않는 좌표라는 것*/
			if (_sliceObjectArr[i][1] != 0.0f)
			{
				_sliceObjectArr[i][1] += _fallDown;
			}

			/*화면 밖으로 완전히 사라지면 제거*/
			if (_sliceObjectArr[i][1] < -1.2f)
			{
				/*초기화*/
				SliceObjectReset();
				_Alive = false;
			}
		}

		/*중력 가속도*/
		_fallDown -= 0.0001f;
	}
}
/*도형 초기화*/
void Cobject::ObjectReset()
{
	_objectType = polygonType(eng);
	_colorType = randColor(eng);
	_moveType = moveType(eng);
	_moveT = 0.0f;
	_positionX1 = -1.2f;
	_positionX2 = 1.2f;
	_positionY1 = (float)randPosition(eng);
	_positionY2 = (float)randPosition(eng);


	/*_moveType1 = 왼->오, moveType2 = 오->왼*/
	if (_moveType == 1)
	{
		_tempX = _positionX1;
		_tempY = _positionY1;

		_pathArr[0][0] = _tempX;
		_pathArr[0][1] = _tempY;
		_pathArr[0][2] = 0.0f;
		_pathArr[1][0] = _positionX2;
		_pathArr[1][1] = _positionY2;
		_pathArr[1][2] = 0.0f;
	}
	else if (_moveType == 2)
	{
		_tempX = _positionX2;
		_tempY = _positionY2;

		_pathArr[0][0] = _tempX;
		_pathArr[0][1] = _tempY;
		_pathArr[0][2] = 0.0f;
		_pathArr[1][0] = _positionX1;
		_pathArr[1][1] = _positionY1;
		_pathArr[1][2] = 0.0f;
	}
}
void CsliceObject::SliceObjectReset()
{
	/*배열 초기화*/
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			_sliceObjectArr[i][j] = 0.0f;
			_colorArr[i][j] = 0.0f;
		}
	}

	/*비활성화*/
	_Alive = false;

	/*나머지 초기화*/
	_fallDown = -0.001f;
	_objectType = 0;
}
/*선 초기화*/
void Cline::ResetLineArray()
{
	_lineArr[0][0] = 0.0f;
	_lineArr[0][1] = 0.0f;
	_lineArr[1][0] = 0.0f;
	_lineArr[1][1] = 0.0f;
}
/*마우스 클릭 시 선에 좌표 삽입*/
void Cline::InsertPosition1(float glPosX, float glPosY)
{
	_lineArr[0][0] = glPosX;
	_lineArr[0][1] = glPosY;
	_lineArr[1][0] = glPosX;
	_lineArr[1][1] = glPosY;
}
void Cline::InsertPosition2(float glPosX, float glPosY)
{
	_lineArr[1][0] = glPosX;
	_lineArr[1][1] = glPosY;
}
/*VAO 설정*/
void Cobject::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_objectArr), _objectArr, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_colorArr), _colorArr, GL_STATIC_DRAW);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(cAttribute);
}
void Cobject::InitPathBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_pathArr), _pathArr, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_colorArr), _colorArr, GL_STATIC_DRAW);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(cAttribute);
}
void Cline::InitLineBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_lineArr), _lineArr, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_colorArr), _colorArr, GL_STATIC_DRAW);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(cAttribute);
}
void Cbucket::InitBucketBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_bucketArr), _bucketArr, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_colorArr), _colorArr, GL_STATIC_DRAW);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(cAttribute);
}
void CsliceObject::InitSliceObject()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "in_Position");
	GLint cAttribute = glGetAttribLocation(shaderID, "in_Color");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_sliceObjectArr), _sliceObjectArr, GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(_colorArr), _colorArr, GL_STATIC_DRAW);
	glVertexAttribPointer(cAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(cAttribute);
}
/*도형 활성화*/
void Cobject::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}
void Cline::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}
void Cline::SetMouseClick(bool mouseClick)
{
	if (mouseClick == true)
		_MouseClick = true;
	else
		_MouseClick = false;
}
void Cbucket::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}
void CsliceObject::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}
/*vertex, color 배열 할당*/
void Cobject::SetArray()
{
	for (int i = 0; i < _objectType; i++)
	{
		float angle = 2 * glm::pi<float>() * i / _objectType;
		switch (_moveType)
		{
		case 1:
			_objectArr[i][0] = _positionX1 + 0.175f * glm::cos(angle);
			_objectArr[i][1] = _positionY1 + 0.175f * glm::sin(angle);
			_objectArr[i][2] = 0.0f;
			break;
		case 2:
			_objectArr[i][0] = _positionX2 + 0.175f * glm::cos(angle);
			_objectArr[i][1] = _positionY2 + 0.175f * glm::sin(angle);
			_objectArr[i][2] = 0.0f;
			break;
		}
	}

	switch (_colorType)
	{
	case RED:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	case GREEN:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 0.0f;
			_colorArr[i][1] = 1.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	case BLUE:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 0.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 1.0f;
		}
		break;
	case CYAN:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 1.0f;
		}
		break;
	case YELLOW:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 1.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	}
}
void Cbucket::SetArray()
{
	/*좌상*/
	_bucketArr[0][0] = positionX1 - 0.2f;
	_bucketArr[0][1] = -0.8f;
	/*좌하*/
	_bucketArr[1][0] = positionX1 - 0.2f;
	_bucketArr[1][1] = -0.9f;
	/*우하*/
	_bucketArr[2][0] = positionX1 + 0.2f;
	_bucketArr[2][1] = -0.9f;
	/*우상*/
	_bucketArr[3][0] = positionX1 + 0.2f;
	_bucketArr[3][1] = -0.8f;
}
void CsliceObject::SetArray(int vertexType1, int vertexType2, float finalx, float finaly, float finalx2, float finaly2, int objectType, int objectCount, float objectArr[6][3], int colorType)
{
	switch (objectType)
	{
	case TRIANGLE:
		if (vertexType1 == 1 && vertexType2 == 2)
		{
			if (objectCount == 0)
			{	
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[2][0];
				_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
				_sliceObjectArr[1][0] = finalx;
				_sliceObjectArr[1][1] = finaly- 0.01f;
				_sliceObjectArr[2][0] = finalx2;
				_sliceObjectArr[2][1] = finaly2- 0.01f;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[0][0]+0.01f;
				_sliceObjectArr[0][1] = objectArr[0][1];
				_sliceObjectArr[1][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[1][1] = objectArr[1][1];
				_sliceObjectArr[2][0] = finalx + 0.01f;
				_sliceObjectArr[2][1] = finaly;
				_sliceObjectArr[3][0] = finalx2 + 0.01f;
				_sliceObjectArr[3][1] = finaly2;
				_objectType = RECTANGLE;
			}
		}
		else if (vertexType1 == 2 && vertexType2 == 0)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[0][0];
				_sliceObjectArr[0][1] = objectArr[0][1] - 0.01f;
				_sliceObjectArr[1][0] = finalx;
				_sliceObjectArr[1][1] = finaly - 0.01f;
				_sliceObjectArr[2][0] = finalx2;
				_sliceObjectArr[2][1] = finaly2 - 0.01f;
				_objectType = TRIANGLE;
			}
			if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
				_sliceObjectArr[1][1] = objectArr[2][1];
				_sliceObjectArr[2][0] = finalx2 + 0.01f;
				_sliceObjectArr[2][1] = finaly2;
				_sliceObjectArr[3][0] = finalx + 0.01f;
				_sliceObjectArr[3][1] = finaly;
				_objectType = RECTANGLE;
			}
		}
		else if (vertexType1 == 1 && vertexType2 == 0)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[1][0];
				_sliceObjectArr[0][1] = objectArr[1][1] - 0.01f;
				_sliceObjectArr[1][0] = finalx;
				_sliceObjectArr[1][1] = finaly - 0.01f;
				_sliceObjectArr[2][0] = finalx2;
				_sliceObjectArr[2][1] = finaly2 - 0.01f;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = finalx+ 0.01f;
				_sliceObjectArr[0][1] = finaly;
				_sliceObjectArr[1][0] = finalx2 + 0.01f;
				_sliceObjectArr[1][1] = finaly2;
				_sliceObjectArr[2][0] = objectArr[2][0] + 0.01f;
				_sliceObjectArr[2][1] = objectArr[2][1];
				_sliceObjectArr[3][0] = objectArr[0][0] + 0.01f;
				_sliceObjectArr[3][1] = objectArr[0][1];
				_objectType = RECTANGLE;
			}
		}
		break;

	case RECTANGLE:
		if (vertexType1 == 1 && vertexType2 == 0)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.02f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = finalx2 + 0.02f;
				_sliceObjectArr[1][1] = finaly2 ;
				_sliceObjectArr[2][0] = finalx + 0.02f;
				_sliceObjectArr[2][1] = finaly ;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[2][0];
				_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
				_sliceObjectArr[1][0] = objectArr[3][0];
				_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
				_sliceObjectArr[2][0] = objectArr[0][0];
				_sliceObjectArr[2][1] = objectArr[0][1] - 0.01f;
				_sliceObjectArr[3][0] = finalx;
				_sliceObjectArr[3][1] = finaly - 0.01f;
				_sliceObjectArr[4][0] = finalx2;
				_sliceObjectArr[4][1] = finaly2 - 0.01f;
				_objectType = PENTAGON;
			}
		}
		else if (vertexType1 == 1 && vertexType2 == 2)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = finalx;
				_sliceObjectArr[0][1] = finaly - 0.01f;
				_sliceObjectArr[1][0] = objectArr[2][0];
				_sliceObjectArr[1][1] = objectArr[2][1] - 0.01f;
				_sliceObjectArr[2][0] = finalx2;
				_sliceObjectArr[2][1] = finaly2 - 0.01f;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = finalx + 0.01f;
				_sliceObjectArr[1][1] = finaly;
				_sliceObjectArr[2][0] = finalx2 + 0.01f;
				_sliceObjectArr[2][1] = finaly2;
				_sliceObjectArr[3][0] = objectArr[3][0] + 0.01f;
				_sliceObjectArr[3][1] = objectArr[3][1];
				_sliceObjectArr[4][0] = objectArr[0][0] + 0.01f;
				_sliceObjectArr[4][1] = objectArr[0][1];
				_objectType = PENTAGON;
			}
		}
		else if (vertexType1 == 2 && vertexType2 == 3)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = finalx + 0.02f;
				_sliceObjectArr[0][1] = finaly - 0.01f;
				_sliceObjectArr[1][0] = objectArr[3][0] + 0.02f;
				_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
				_sliceObjectArr[2][0] = finalx2 + 0.02;
				_sliceObjectArr[2][1] = finaly2 - 0.01f;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
				_sliceObjectArr[1][1] = objectArr[2][1];
				_sliceObjectArr[2][0] = finalx + 0.01f;
				_sliceObjectArr[2][1] = finaly;
				_sliceObjectArr[3][0] = finalx2 + 0.01f;
				_sliceObjectArr[3][1] = finaly2;
				_sliceObjectArr[4][0] = objectArr[0][0] + 0.01f;
				_sliceObjectArr[4][1] = objectArr[0][1];
				_objectType = PENTAGON;
			}
		}
		else if (vertexType1 == 3 && vertexType2 == 0)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = finalx + 0.02f;
				_sliceObjectArr[0][1] = finaly - 0.01f;
				_sliceObjectArr[1][0] = finalx2 + 0.02;
				_sliceObjectArr[1][1] = finaly2 - 0.01f;
				_sliceObjectArr[2][0] = objectArr[0][0] + 0.02f;
				_sliceObjectArr[2][1] = objectArr[0][1] - 0.01f;
				_objectType = TRIANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
				_sliceObjectArr[1][1] = objectArr[2][1];
				_sliceObjectArr[2][0] = objectArr[3][0] + 0.01f;
				_sliceObjectArr[2][1] = objectArr[3][1];
				_sliceObjectArr[3][0] = finalx2 + 0.01f;
				_sliceObjectArr[3][1] = finaly2;
				_sliceObjectArr[4][0] = finalx + 0.01f;
				_sliceObjectArr[4][1] = finaly;
				_objectType = PENTAGON;
			}
		}
		else if (vertexType1 == 1 && vertexType2 == 3)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[2][0] + 0.02f;
				_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
				_sliceObjectArr[1][0] = objectArr[3][0] + 0.02f;
				_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
				_sliceObjectArr[2][0] = finalx2 + 0.02;
				_sliceObjectArr[2][1] = finaly2 - 0.01f;
				_sliceObjectArr[3][0] = finalx + 0.02f;
				_sliceObjectArr[3][1] = finaly - 0.01f;
				_objectType = RECTANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = finalx+0.01f;
				_sliceObjectArr[1][1] = finaly;
				_sliceObjectArr[2][0] = finalx2 + 0.01f;
				_sliceObjectArr[2][1] = finaly2;
				_sliceObjectArr[3][0] = objectArr[0][0] + 0.01f;
				_sliceObjectArr[3][1] = objectArr[0][1];
				_objectType = RECTANGLE;
			}
		}
		else if (vertexType1 == 2 && vertexType2 == 0)
		{
			if (objectCount == 0)
			{
				printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
				_sliceObjectArr[0][0] = objectArr[1][0];
				_sliceObjectArr[0][1] = objectArr[1][1];
				_sliceObjectArr[1][0] = objectArr[2][0];
				_sliceObjectArr[1][1] = objectArr[2][1];
				_sliceObjectArr[2][0] = finalx2;
				_sliceObjectArr[2][1] = finaly2;
				_sliceObjectArr[3][0] = finalx;
				_sliceObjectArr[3][1] = finaly;
				_objectType = RECTANGLE;
			}
			else if (objectCount == 1)
			{
				_sliceObjectArr[0][0] = objectArr[3][0] + 0.01f;
				_sliceObjectArr[0][1] = objectArr[3][1] - 0.01f;
				_sliceObjectArr[1][0] = objectArr[0][0] + 0.01f;
				_sliceObjectArr[1][1] = objectArr[0][1] - 0.01f;
				_sliceObjectArr[2][0] = finalx + 0.01f;
				_sliceObjectArr[2][1] = finaly - 0.01f;
				_sliceObjectArr[3][0] = finalx2 + 0.01f;
				_sliceObjectArr[3][1] = finaly2 - 0.01f;
				_objectType = RECTANGLE;
			}
		}
		break;

		case PENTAGON:
			if (vertexType1 == 1 && vertexType2 == 0)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.02f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = finalx2 + 0.02f;
					_sliceObjectArr[1][1] = finaly2;
					_sliceObjectArr[2][0] = finalx + 0.02f;
					_sliceObjectArr[2][1] = finaly;
					_objectType = TRIANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[2][0];
					_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[3][0];
					_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
					_sliceObjectArr[2][0] = objectArr[4][0];
					_sliceObjectArr[2][1] = objectArr[4][1] - 0.01f;
					_sliceObjectArr[3][0] = objectArr[0][0];
					_sliceObjectArr[3][1] = objectArr[0][1] - 0.01f;
					_sliceObjectArr[4][0] = finalx;
					_sliceObjectArr[4][1] = finaly - 0.01f;
					_sliceObjectArr[5][0] = finalx2;
					_sliceObjectArr[5][1] = finaly2 - 0.01f;
					_objectType = HEXAGON;
				}
			}
			else if (vertexType1 == 1 && vertexType2 == 2)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = finalx;
					_sliceObjectArr[0][1] = finaly - 0.01f;
					_sliceObjectArr[1][0] = objectArr[2][0];
					_sliceObjectArr[1][1] = objectArr[2][1] - 0.01f;
					_sliceObjectArr[2][0] = finalx2;
					_sliceObjectArr[2][1] = finaly2 - 0.01f;
					_objectType = TRIANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = finalx + 0.01f;
					_sliceObjectArr[1][1] = finaly;
					_sliceObjectArr[2][0] = finalx2 + 0.01f;
					_sliceObjectArr[2][1] = finaly2;
					_sliceObjectArr[3][0] = objectArr[3][0] + 0.01f;
					_sliceObjectArr[3][1] = objectArr[3][1];
					_sliceObjectArr[4][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[4][1] = objectArr[4][1];
					_sliceObjectArr[5][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[5][1] = objectArr[0][1];
					_objectType = HEXAGON;
				}
			}
			else if (vertexType1 == 2 && vertexType2 == 3)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = finalx - 0.01f;
					_sliceObjectArr[0][1] = finaly - 0.01f;
					_sliceObjectArr[1][0] = objectArr[3][0] - 0.01f;
					_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
					_sliceObjectArr[2][0] = finalx2 - 0.01;
					_sliceObjectArr[2][1] = finaly2 - 0.01f;
					_objectType = TRIANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[2][1];
					_sliceObjectArr[2][0] = finalx + 0.01f;
					_sliceObjectArr[2][1] = finaly;
					_sliceObjectArr[3][0] = finalx2 + 0.01f;
					_sliceObjectArr[3][1] = finaly2;
					_sliceObjectArr[4][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[4][1] = objectArr[4][1];
					_sliceObjectArr[5][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[5][1] = objectArr[0][1];
					_objectType = HEXAGON;
				}
			}
			else if (vertexType1 == 3 && vertexType2 == 4)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = finalx + 0.02f;
					_sliceObjectArr[0][1] = finaly - 0.01f;
					_sliceObjectArr[1][0] = finalx2 + 0.02;
					_sliceObjectArr[1][1] = finaly2 - 0.01f;
					_sliceObjectArr[2][0] = objectArr[4][0] + 0.02f;
					_sliceObjectArr[2][1] = objectArr[4][1] - 0.01f;
					_objectType = TRIANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[2][1];
					_sliceObjectArr[2][0] = objectArr[3][0] + 0.01f;
					_sliceObjectArr[2][1] = objectArr[3][1];
					_sliceObjectArr[3][0] = finalx + 0.01f;
					_sliceObjectArr[3][1] = finaly;
					_sliceObjectArr[4][0] = finalx2 + 0.01f;
					_sliceObjectArr[4][1] = finaly2;
					_sliceObjectArr[5][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[5][1] = objectArr[0][1];
					_objectType = HEXAGON;
				}
			}
			else if (vertexType1 == 4 && vertexType2 == 0)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = finalx + 0.02f;
					_sliceObjectArr[0][1] = finaly - 0.01f;
					_sliceObjectArr[1][0] = finalx2 + 0.02;
					_sliceObjectArr[1][1] = finaly2 - 0.01f;
					_sliceObjectArr[2][0] = objectArr[0][0] + 0.02f;
					_sliceObjectArr[2][1] = objectArr[0][1] - 0.01f;
					_objectType = TRIANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[2][1];
					_sliceObjectArr[2][0] = objectArr[3][0] + 0.01f;
					_sliceObjectArr[2][1] = objectArr[3][1];
					_sliceObjectArr[3][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[3][1] = objectArr[4][1];
					_sliceObjectArr[4][0] = finalx2 + 0.01f;
					_sliceObjectArr[4][1] = finaly2;
					_sliceObjectArr[5][0] = finalx + 0.01f;
					_sliceObjectArr[5][1] = finaly;
					_objectType = HEXAGON;
				}
			}
			/******/
			else if (vertexType1 == 1 && vertexType2 == 3)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[2][0] + 0.02f;
					_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[3][0] + 0.02f;
					_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
					_sliceObjectArr[2][0] = finalx2 + 0.02;
					_sliceObjectArr[2][1] = finaly2 - 0.01f;
					_sliceObjectArr[3][0] = finalx + 0.02f;
					_sliceObjectArr[3][1] = finaly - 0.01f;
					_objectType = RECTANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = finalx + 0.01f;
					_sliceObjectArr[1][1] = finaly;
					_sliceObjectArr[2][0] = finalx2 + 0.01f;
					_sliceObjectArr[2][1] = finaly2;
					_sliceObjectArr[3][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[3][1] = objectArr[4][1];
					_sliceObjectArr[4][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[4][1] = objectArr[0][1];
					_objectType = PENTAGON;
				}
			}
			else if (vertexType1 == 1 && vertexType2 == 4)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[2][0] + 0.02f;
					_sliceObjectArr[0][1] = objectArr[2][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[3][0] + 0.02f;
					_sliceObjectArr[1][1] = objectArr[3][1] - 0.01f;
					_sliceObjectArr[2][0] = objectArr[4][0] + 0.02f;
					_sliceObjectArr[2][1] = objectArr[4][1] - 0.01f;
					_sliceObjectArr[3][0] = finalx2 + 0.02;
					_sliceObjectArr[3][1] = finaly2 - 0.01f;
					_sliceObjectArr[4][0] = finalx + 0.02f;
					_sliceObjectArr[4][1] = finaly - 0.01f;
					_objectType = PENTAGON;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = finalx + 0.01f;
					_sliceObjectArr[1][1] = finaly;
					_sliceObjectArr[2][0] = finalx2 + 0.01f;
					_sliceObjectArr[2][1] = finaly2;
					_sliceObjectArr[3][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[3][1] = objectArr[0][1];
					_objectType = RECTANGLE;
				}
			}
			else if (vertexType1 == 2 && vertexType2 == 0)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[1][0];
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = objectArr[2][0];
					_sliceObjectArr[1][1] = objectArr[2][1];
					_sliceObjectArr[2][0] = finalx2;
					_sliceObjectArr[2][1] = finaly2;
					_sliceObjectArr[3][0] = finalx;
					_sliceObjectArr[3][1] = finaly;
					_objectType = RECTANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[3][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[3][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[4][1] - 0.01f;
					_sliceObjectArr[2][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[2][1] = objectArr[0][1] - 0.01f;
					_sliceObjectArr[3][0] = finalx + 0.01f;
					_sliceObjectArr[3][1] = finaly - 0.01f;
					_sliceObjectArr[4][0] = finalx2 + 0.01f;
					_sliceObjectArr[4][1] = finaly2 - 0.01f;
					_objectType = PENTAGON;
				}
			}
			else if (vertexType1 == 2 && vertexType2 == 4)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[3][0];
					_sliceObjectArr[0][1] = objectArr[3][1];
					_sliceObjectArr[1][0] = objectArr[4][0];
					_sliceObjectArr[1][1] = objectArr[4][1];
					_sliceObjectArr[2][0] = finalx2;
					_sliceObjectArr[2][1] = finaly2;
					_sliceObjectArr[3][0] = finalx;
					_sliceObjectArr[3][1] = finaly;
					_objectType = RECTANGLE;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[1][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[1][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[2][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[2][1] - 0.01f;
					_sliceObjectArr[2][0] = finalx + 0.01f;
					_sliceObjectArr[2][1] = finaly - 0.01f;
					_sliceObjectArr[3][0] = finalx2 + 0.01f;
					_sliceObjectArr[3][1] = finaly2 - 0.01f;
					_sliceObjectArr[4][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[4][1] = objectArr[0][1] - 0.01f;
					_objectType = PENTAGON;
				}
			}
			else if (vertexType1 == 3 && vertexType2 == 0)
			{
				if (objectCount == 0)
				{
					printf("x1,x2,y1,y2: %f %f %f %f", finalx, finalx2, finaly, finaly2);
					_sliceObjectArr[0][0] = objectArr[1][0];
					_sliceObjectArr[0][1] = objectArr[1][1];
					_sliceObjectArr[1][0] = objectArr[2][0];
					_sliceObjectArr[1][1] = objectArr[2][1];
					_sliceObjectArr[2][0] = objectArr[3][0];
					_sliceObjectArr[2][1] = objectArr[3][1];
					_sliceObjectArr[3][0] = finalx2;
					_sliceObjectArr[3][1] = finaly2;
					_sliceObjectArr[4][0] = finalx;
					_sliceObjectArr[4][1] = finaly;
					_sliceObjectArr[5][0] = objectArr[0][0];
					_sliceObjectArr[5][1] = objectArr[0][1];
					_objectType = PENTAGON;
				}
				else if (objectCount == 1)
				{
					_sliceObjectArr[0][0] = objectArr[4][0] + 0.01f;
					_sliceObjectArr[0][1] = objectArr[4][1] - 0.01f;
					_sliceObjectArr[1][0] = objectArr[0][0] + 0.01f;
					_sliceObjectArr[1][1] = objectArr[0][1] - 0.01f;
					_sliceObjectArr[2][0] = finalx + 0.01f;
					_sliceObjectArr[2][1] = finaly - 0.01f;
					_sliceObjectArr[3][0] = finalx2 + 0.01f;
					_sliceObjectArr[3][1] = finaly2 - 0.01f;
					_objectType = RECTANGLE;
				}
			}
		break;
	}

	switch (colorType)
	{
	case RED:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	case GREEN:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 0.0f;
			_colorArr[i][1] = 1.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	case BLUE:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 0.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 1.0f;
		}
		break;
	case CYAN:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 0.0f;
			_colorArr[i][2] = 1.0f;
		}
		break;
	case YELLOW:
		for (int i = 0; i < _objectType; i++)
		{
			_colorArr[i][0] = 1.0f;
			_colorArr[i][1] = 1.0f;
			_colorArr[i][2] = 0.0f;
		}
		break;
	}
}
/**********************************************************************************************/

/*************************************클래스 함수(상태 확인)***********************************/
bool Cobject::GetAlive()
{
	return _Alive;
}
bool Cline::GetAlive()
{
	return _Alive;
}
bool CsliceObject::GetAlive()
{
	return _Alive;
}
bool Cline::GetMouseClick()
{
	return _MouseClick;
}
void Cline::GetArray(float sliceLineArr[2][3])
{
	for (int i = 0; i < 2; i++)
	{
		sliceLineArr[i][0] = _lineArr[i][0];
		sliceLineArr[i][1] = _lineArr[i][1];
		sliceLineArr[i][2] = _lineArr[i][2];
	}

}
void Cobject::GetArray(float objectArr[6][3])
{
	for (int i = 0; i < 6; i++)
	{
		objectArr[i][0] = _objectArr[i][0];
		objectArr[i][1] = _objectArr[i][1];
		objectArr[i][2] = _objectArr[i][2];
	}

}
int Cobject::GetType()
{
	return _objectType;
}
int Cobject::GetColorType()
{
	return _colorType;
}
/**********************************************************************************************/

/***************************************클래스 함수(변환)**************************************/
void Cobject::Reset()
{
	unsigned transformLocate = glGetUniformLocation(shaderID, "Transform");
	glm::mat4 mixMat = glm::mat4{ 1.0f };
	mixMat = glm::rotate(mixMat, glm::radians(rotateval), glm::vec3(0.0f, 0.0f, 1.0f));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(mixMat));
}
/**********************************************************************************************/

/*****************************************GL관련 함수들****************************************/
GLvoid drawScene()
{
	/*바탕 화면*/
	glClearColor(1.0, 1.0, 1.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/*셰이더 프로그램 사용*/
	glUseProgram(shaderID);

	/*바구니 그리기*/
	bucket.DrawBucket();

	/*그리기*/
	Draw();

	/*잘린 물체 그리기*/
	DrawSliceObject();

	/*경로 출력하기*/
	if (showPath == true) {
		ShowPath();
	}

	/*슬라이스 라인 그리기*/
	DrawLine();

	/*도형과 충돌 체크*/
	Collider();

	/*더블 버퍼링(화면 출력)*/
	glutSwapBuffers();
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char button, int x, int y)
{
	switch (button)
	{
	case 'm':
		objectMode = !objectMode;
		objectMode ? glPolygonMode(GL_FRONT_AND_BACK, GL_LINE) : glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		break;

	case 'p':
		showPath = !showPath;
		break;

	case '+':
		if (timerSpeed > 10)
		{
			timerSpeed -= 10;
		}
		break;

	case '-':
		if (timerSpeed < 50)
		{
			timerSpeed += 10;
		}
		break;

	case 'q':
		exit(1);
		break;
	}
	glutPostRedisplay();
}
GLvoid Mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
	{
		GLfloat glPosX = (GLfloat)x / 500 - 1;
		GLfloat glPosY = -((GLfloat)y / 500 - 1);

		line.SetAlive(true);
		line.SetMouseClick(true);
		line.InsertPosition1(glPosX, glPosY);
	}

	else if (button == GLUT_LEFT_BUTTON && state == GLUT_UP)
	{
		line.SetMouseClick(false);
	}

	glutPostRedisplay();
}
GLvoid Motion(int x, int y)
{
	if (line.GetAlive() == true)
	{
		GLfloat glPosX = (GLfloat)x / 500 - 1;
		GLfloat glPosY = -((GLfloat)y / 500 - 1);
		line.InsertPosition2(glPosX, glPosY);
	}
	glutPostRedisplay();
}
GLvoid TimerObjectCreate(int value)
{
	/*생성*/
	Create();

	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(2000, TimerObjectCreate, 1);
}
GLvoid TimerObjectMove(int value)
{
	/*이동*/
	ObjectMove();

	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(timerSpeed, TimerObjectMove, 1);
}
GLvoid TimerOtherMove(int value)
{
	/*이동*/
	BucketMove();
	SliceObjectMove();

	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(10, TimerOtherMove, 1);
}
/**********************************************************************************************/

























































































































/****************************************Shader Pragram****************************************/
/*버텍스 셰이더 객체 만들기*/
void make_vertexShader()
{
	GLchar* vertexSource;
	GLint result;
	GLchar errorLog[512];
	//--- 버텍스 세이더 읽어 저장하고 컴파일 하기
	//--- filetobuf: 사용자정의 함수로 텍스트를 읽어서 문자열에 저장하는 함수
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

/*프래그먼트 셰이더 객체 만들기*/
void make_fragmentShader()
{
	GLchar* fragmentSource;
	GLint result;
	GLchar errorLog[512];
	//--- 프래그먼트 세이더 읽어 저장하고 컴파일하기
	fragmentSource = filetobuf("fragment.glsl"); // 프래그세이더 읽어오기
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader 컴파일 실패\n" << errorLog << std::endl;
		return;
	}
}

/*셰이더 프로그램 만들기*/
void make_shaderProgram()
{
	GLchar errorLog[512];
	GLint result;
	make_vertexShader();
	make_fragmentShader();

	//-- shader Program
	shaderID = glCreateProgram();
	glAttachShader(shaderID, vertexShader);
	glAttachShader(shaderID, fragmentShader);
	glLinkProgram(shaderID);

	//--- 세이더 삭제하기
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ---세이더가 잘 연결되었는지 체크하기
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program 연결 실패\n" << errorLog << std::endl;
		return;
	}

	//--- Shader Program 사용하기
	glUseProgram(shaderID);
}

/*셰이더 파일 읽기*/
char* filetobuf(const char* file)
{
	FILE* fptr;
	long length;
	char* buf;
	fptr = fopen(file, "rb"); // Open file for reading 
	if (!fptr) // Return NULL on failure 
		return NULL;
	fseek(fptr, 0, SEEK_END); // Seek to the end of the file 
	length = ftell(fptr); // Find out how many bytes into the file we are 
	buf = (char*)malloc(length + 1); // Allocate a buffer for the entire length of the file and a null terminator 
	fseek(fptr, 0, SEEK_SET); // Go back to the beginning of the file 
	fread(buf, length, 1, fptr); // Read the contents of the file in to the buffer 
	fclose(fptr); // Close the file 
	buf[length] = 0; // Null terminator 
	return buf; // Return the buffer
}
