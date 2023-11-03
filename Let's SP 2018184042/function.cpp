#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
using namespace std;

/***************************************일반 함수들*************************************/
/*초기 오브젝트*/
void InitObject() //오브젝트 소환
{

}

/*도형 버퍼 초기화(사용X)*/
void InitBuffer()
{

}

/*경로 버퍼 초기화(사용X)*/
void InitPathBuffer()
{

}

/*도형 그리기*/
void Draw()
{
	for (int i = 0; i < 100; i++)
	{
		object[i].Draw();
	}
}

/*경로 그리기*/
void ShowPath()
{
	for (int i = 0; i < 100; i++)
	{
		object[i].ShowPath();
	}
}

/*슬라이스 라인 그리기*/
void DrawLine()
{
	line.DrawLine();
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
		/*충돌처리 하고 _alive == false*/
		line.ResetLineArray(); //선 초기화
		line.SetAlive(false);
	}
}

/*도형 이동*/
void Move() 
{
	for (int i = 0; i < 100; i++)
	{
		
			object[i].Move();
		
	}
}
/**********************************************************************************************/

/*************************************클래스 함수(도형 제작)***********************************/
/*밑에서 얻어진 도형을 각 타입에 맞게 화면에 그린다.*/
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

/*경로 그리기*/
void Cobject::ShowPath()
{
	if (_Alive == true)
	{
		InitPathBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
	}
}

/*슬라이스 라인 그리기*/
void Cline::DrawLine()
{
	if (_Alive == true)
	{
		InitLineBuffer();
		glBindVertexArray(_vao);
		glDrawArrays(GL_LINES, 0, 2);
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
void Cobject::Move()
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

/*vertex, color*/
void Cobject::SetArray()
{
	for (int i = 0; i < _objectType; i++)
	{
		float angle = 2 * glm::pi<float>() * i / _objectType;
		switch (_moveType )
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
bool Cline::GetMouseClick()
{
	return _MouseClick;
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

	/*그리기*/
	Draw();

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

GLvoid TimerCreate(int value)
{
	/*생성*/
	Create();

	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(2000, TimerCreate, 1);
}

GLvoid TimerMove(int value)
{
	/*이동*/
	Move();

	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(timerSpeed, TimerMove, 1);
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
