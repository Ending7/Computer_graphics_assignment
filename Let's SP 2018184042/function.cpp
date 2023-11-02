#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
using namespace std;

/***************************************일반 함수들*************************************/
void InitObject() //오브젝트 소환
{
	/*AXIS*/
	object[0].SetAlive(true);
	object[0].SetType(VBO_AXIS);
	object[0].SetNumber(AXIS);
	object[0].SetArray();
}

void InitBuffer()
{
	for (int i = 0; i < 1; i++)
	{
		object[i].InitBuffer();
	}
}

void Draw()
{
	for (int i = 0; i < 1; i++)
	{
		object[i].Draw();
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
		glBindVertexArray(_vao);
		Reset();
		switch (_objectNumber)
		{
		case AXIS:
			glDrawArrays(GL_LINES, 0, 6);
			break;
		}
	}
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

/*도형 활성화*/
void Cobject::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}

/*VBO*/
void Cobject::SetVertexType(GLint type)
{
	_vertexType = type;
}

/*도형 타입*/
void Cobject::SetType(GLint type)
{
	_objectType = type;
}

/*도형 ID*/
void Cobject::SetNumber(GLint number)
{
	_objectNumber = number;
}

/*vertex, color*/
void Cobject::SetArray()
{
	switch (_objectType)
	{
	case VBO_AXIS:
	/*vertex*/
	{_objectArr[0][0] = 1.0f, _objectArr[0][1] = 0.0f, _objectArr[0][2] = 0.0f; } //x1
	{_objectArr[1][0] = -1.0f, _objectArr[1][1] = 0.0f, _objectArr[1][2] = 0.0f; } //x2
	{_objectArr[2][0] = 0.0f, _objectArr[2][1] = 1.0f, _objectArr[2][2] = 0.0f; } //y1
	{_objectArr[3][0] = 0.0f, _objectArr[3][1] = -1.0f, _objectArr[3][2] = 0.0f; } //y2
	{_objectArr[4][0] = 0.0f, _objectArr[4][1] = 0.0f, _objectArr[4][2] = 1.0f; } //z1
	{_objectArr[5][0] = 0.0f, _objectArr[5][1] = 0.0f, _objectArr[5][2] = -1.0f; }//z2
	/*color*/
	{_colorArr[0][0] = 0.0f, _colorArr[0][1] = 0.0f, _colorArr[0][2] = 1.0f; }
	{_colorArr[1][0] = 0.0f, _colorArr[1][1] = 0.0f, _colorArr[1][2] = 1.0f; }
	{_colorArr[2][0] = 1.0f, _colorArr[2][1] = 0.0f, _colorArr[2][2] = 0.0f; }
	{_colorArr[3][0] = 1.0f, _colorArr[3][1] = 0.0f, _colorArr[3][2] = 0.0f; }
	{_colorArr[4][0] = 0.0f, _colorArr[4][1] = 1.0f, _colorArr[4][2] = 0.0f; }
	{_colorArr[5][0] = 0.0f, _colorArr[5][1] = 1.0f, _colorArr[5][2] = 0.0f; }
	break;
	}
}
/**********************************************************************************************/

/***************************************클래스 관련(변환)**************************************/
void Cobject::Reset()
{
	unsigned transformLocate = glGetUniformLocation(shaderID, "Transform");
	glm::mat4 mixMat = glm::mat4{ 1.0f };

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

	/*더블 버퍼링(화면 출력)*/
	glutSwapBuffers();
}

GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}


GLvoid Keyboard(unsigned char button, int x, int y)
{
	/*switch (button)
	{

	}*/
	glutPostRedisplay();
}


GLvoid TimerFunction(int value)
{
	/*Update와 Draw호출*/
	glutPostRedisplay();

	/*타이머 무한 반복*/
	glutTimerFunc(50, TimerFunction, 1);
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
