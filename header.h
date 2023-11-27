	#pragma once
	/**************************�������**************************/
	#include <iostream>
	#include <stdlib.h>
	#include <fstream>
	#include <iterator>
	#include <random>
	using namespace std;

	/**************************��������**************************/
	random_device seeder;
	const auto seed = seeder.entropy() ? seeder() : time(nullptr);
	mt19937 eng(static_cast<mt19937::result_type>(seed));
	uniform_real_distribution<double> snowPosition(-1.0f, 1.0f);
	uniform_real_distribution<double> snowSpeed(2.0f, 3.0f);
	uniform_real_distribution<double> randomRev(0.0f, 360.0f);
	/*���̴� ���α׷� ����*/
	GLuint shaderID;
	GLuint vertexShader;
	GLuint fragmentShader;
	/*obj���� �ҷ����� ������*/
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > vertices;
	std::vector< glm::vec2 > uvs;
	std::vector< glm::vec3 > normals;
	/*üũ ����*/
	int lightRoate = 0;
	bool lightSwitch = true;
	int cameraRotate = 0;
	bool snowSwitch = false;
	int lightColor = 0;
	int lightPosition = 0;
	bool lightCenter = true;
	/*���� ��ȭ ����*/
	float lightX = 0.0f, lightY = 3.0f, lightZ = 0.0f;
	float lightRadians = 90.0f / 360.0f * 2.0f * 3.141592f;
	float lightRadiusZ = 0.0f;
	float cameraX = 0.0f;
	float cameraY = 10.0f;
	float cameraZ = 0.0f;
	float cameraRaidans = 0.0f;
	float lightPower = 1.0f;
	float lightVal = 90.0f;
	/*ī�޶� ����*/
	glm::vec3 cameraPos = glm::vec3(0.0f + cameraX, cameraY, 4.5f + cameraZ); //--- ī�޶� ��ġ�� �� ��ǥ�� ����
	glm::vec3 cameraDirection = glm::vec3(0.0f + cameraX, 0.0f, 0.0f + cameraZ); //--- ī�޶� �ٶ󺸴� ����. ��� �� ���⸸ �ٶ󺻴�.
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����
	/*���ؽ� �迭*/
	float cubeVerticles[] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
		// �޸�
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		// �ո�
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
	float pyramidVerticles[] = { //--- ���ؽ� �Ӽ�: ��ǥ��(FragPos), �븻�� (Normal)
		//�޸�
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
		 0.0f,  0.5f, -0.0f,  0.0f,  0.0f, -1.0f,
		// �ո�
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  1.0f,
		 0.0f,  0.5f,  0.0f,  0.0f,  0.0f,  1.0f,
		//����
		-0.5f, -0.5f,  0.5f, -1.0f,  0.0f,  0.0f,
		-0.5f, -0.5f, -0.5f, -1.0f,  0.0f,  0.0f,
		 0.0f,  0.5f,  0.0f, -1.0f,  0.0f,  0.0f,
		//������
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  0.0f,
		 0.0f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,
		//�Ʒ�
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
	};
	/**************************������Ʈ**************************/
	/*******ť��********/
	class Cube
	{
	private:
		/*�迭 ����*/
		GLuint _vao, _vbo[2];
		/*��� ����*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*���� ��ȭ ����*/
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
		/*��ü �ʱ�ȭ*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		/*���� �ʱ�ȭ*/
		void InitBuffer();
		/*�׸���*/
		void Draw();
		/*���� ��ȭ*/
		void Transform();
		/*�ִϸ��̼�*/
		void Move();
		~Cube()
		{


		};
	};
	Cube cube;
	/*******����********/
	class LightCube
	{
	private:
		/*�迭 ����*/
		GLuint _vao, _vbo[2];
		/*��� ����*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*���� ��ȭ ����*/
		bool _Alive = false;
		float _rotateY = 0.0f;
	public:
		LightCube()
		{


		};
		/*��ü �ʱ�ȭ*/
		void SetAlive(bool alive);
		/*���� �ʱ�ȭ*/
		void InitBuffer();
		/*�׸���*/
		void Draw();
		/*���� ��ȭ*/
		void Transform();
		void Rotating();
		/*�ִϸ��̼�*/
		~LightCube()
		{


		};
	};
	LightCube lightCube;
	/*******��********/
	class Sphere
	{
	private:
		/*�迭 ����*/
		GLuint _vao, _vbo[2], _ebo;
		/*��� ����*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*���� ��ȭ ����*/
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
		/*��ü �ʱ�ȭ*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetRevType(int num);
		/*���� �ʱ�ȭ*/
		void InitBuffer();
		/*�׸���*/
		void Draw();
		/*���� ��ȭ*/
		void Transform();
		/*�ִϸ��̼�*/
		~Sphere()
		{


		};
	};
	Sphere sphere[3];
	Sphere snow[50];
	/*****�Ƕ�̵�******/
	class Pyramid
	{
	private:
		/*�迭 ����*/
		GLuint _vao, _vbo[2];
		/*��� ����*/
		glm::mat4 _mixMat = glm::mat4{ 1.0f };
		/*���� ��ȭ ����*/
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
		/*��ü �ʱ�ȭ*/
		void SetAlive(bool alive);
		void SetColor(float r, float g, float b);
		void SetPosition(float x, float y, float z);
		void SetScale(float x, float y, float z);
		/*���� �ʱ�ȭ*/
		void InitBuffer();
		void frontBuffer();
		/*�׸���*/
		void Draw();
		/*���� ��ȭ*/
		void Transform();
		/*�ִϸ��̼�*/
	
		void Move();
		~Pyramid()
		{


		};
	};
	Pyramid pyramid;
	Pyramid frontPyramid;