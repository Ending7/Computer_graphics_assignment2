	#pragma once
	/**************************헤더파일**************************/
	#include <iostream>
	#include <stdlib.h>
	#include <fstream>
	#include <iterator>
	#include <random>
	using namespace std;

	/**************************변수선언**************************/
	random_device seeder;
	const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	mt19937 eng(static_cast<mt19937::result_type>(seed));
	uniform_real_distribution<double> snowPosition(-1.0f, 1.0f);
	uniform_real_distribution<double> snowSpeed(2.0f, 3.0f);
	uniform_real_distribution<double> randomRev(0.0f, 360.0f);
	/*셰이더 프로그램 변수*/
	GLuint shaderID;
	GLuint vertexShader;
	GLuint fragmentShader;
	/*obj파일 불러오는 변수들*/
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	/*체크 변수*/
	int lightRoate = 0;
	bool lightSwitch = true;
	int cameraRotate = 0;
	bool snowSwitch = false;
	int lightColor = 0;
	int lightPosition = 0;
	bool lightCenter = true;
	/*상태 변화 변수*/
	float lightX = 0.0f, lightY = 3.0f, lightZ = 0.0f;
	float lightRadians = 90.0f / 360.0f * 2.0f * 3.141592f;
	float lightRadiusZ = 0.0f;
	float cameraX = 0.0f;
	float cameraY = 10.0f;
	float cameraZ = 0.0f;
	float cameraRaidans = 0.0f;
	float lightPower = 1.0f;
	float lightVal = 90.0f;
	/*카메라 설정*/
	glm::vec3 cameraPos = glm::vec3(0.0f + cameraX, cameraY, 4.5f + cameraZ); //--- 카메라 위치를 이 좌표에 고정
	glm::vec3 cameraDirection = glm::vec3(0.0f + cameraX, 0.0f, 0.0f + cameraZ); //--- 카메라 바라보는 방향. 계속 이 방향만 바라본다.
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- 카메라 위쪽 방향
	/*버텍스 배열*/
	float cubeVerticles[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
		// 뒷면
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		// 앞면
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,

		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f,  0.5f,  0.5f, -1.0f,  0.0f,  0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,

		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		 0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
	};
	float pyramidVerticles[] = { //--- 버텍스 속성: 좌표값(FragPos), 노말값 (Normal)
		//뒷면
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.0f,  0.5f, -0.0f,  0.0f,  0.0f, -1.0f,
		// 앞면
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
		//왼쪽
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,
		//오른쪽
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
		//아래
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	};
	/**************************오브젝트**************************/
	/*******큐브********/
	class Cube
	{
	private:
		/*배열 관련*/
		GLuint _vao, _vbo[2];
		/*행렬 관련*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*상태 변화 관련*/
		bool _Alive = false;
		float _positionX, _positionY, _positionZ;
		float _moveX;
		float _colorR, _colorG, _colorB;
		float _scaleX, _scaleY, _scaleZ;
		int _moveArrow;
	public:
		Cube()
		{


		};
		/*객체 초기화*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		/*버퍼 초기화*/
		void InitBuffer();
		/*그리기*/
		void Draw();
		/*상태 변화*/
		void Transform();
		/*애니메이션*/
		void Move();
		~Cube()
		{


		};
	};
	Cube cube;
	/*******조명********/
	class LightCube
	{
	private:
		/*배열 관련*/
		GLuint _vao, _vbo[2];
		/*행렬 관련*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*상태 변화 관련*/
		bool _Alive = false;
		float _rotateY = 0.0f;
	public:
		LightCube()
		{


		};
		/*객체 초기화*/
		void SetAlive(bool alive);
		/*버퍼 초기화*/
		void InitBuffer();
		/*그리기*/
		void Draw();
		/*상태 변화*/
		void Transform();
		void Rotating();
		/*애니메이션*/
		~LightCube()
		{


		};
	};
	LightCube lightCube;
	/*******구********/
	class Sphere
	{
	private:
		/*배열 관련*/
		GLuint _vao, _vbo[2], _ebo;
		/*행렬 관련*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*상태 변화 관련*/
		bool _Alive = false;
		float _positionX, _positionY, _positionZ;
		float _colorR, _colorG, _colorB;
		float _revolution;
		int _revType = 0;
		float _speed = 0.0f;
	public:
		Sphere()
		{
			_revolution = (float)randomRev(eng);
			_speed = (float)snowSpeed(eng);
		};
		/*객체 초기화*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetRevType(int num);
		/*버퍼 초기화*/
		void InitBuffer();
		/*그리기*/
		void Draw();
		/*상태 변화*/
		void Transform();
		/*애니메이션*/
		~Sphere()
		{


		};
	};
	Sphere sphere[3];
	Sphere snow[50];
	/*****피라미드******/
	class Pyramid
	{
	private:
		/*배열 관련*/
		GLuint _vao, _vbo[2];
		/*행렬 관련*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*상태 변화 관련*/
		bool _Alive = false;
		float _positionX, _positionY, _positionZ;
		float _moveX;
		float _colorR, _colorG, _colorB;
		float _scaleX, _scaleY, _scaleZ;
		int _moveArrow;
	public:
		Pyramid()
		{


		};
		/*객체 초기화*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		/*버퍼 초기화*/
		void InitBuffer();
		void frontBuffer();
		/*그리기*/
		void Draw();
		/*상태 변화*/
		void Transform();
		/*애니메이션*/
	
		void Move();
		~Pyramid()
		{


		};
	};
	Pyramid pyramid;
	Pyramid frontPyramid;