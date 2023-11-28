#pragma once
/**************************�������**************************/
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <iterator>
#include <random>
#include <vector>
using namespace std;

/**************************��������**************************/
random_device seeder;
const auto seed = seeder.entropy() ? seeder() : time(nullptr);
mt19937 eng(static_cast<mt19937::result_type>(seed));
uniform_real_distribution<double> snowPosition(-2.5f, 2.5f);
uniform_real_distribution<double> snowSpeed(2.0f, 7.0f);
uniform_real_distribution<double> moveSpeed(1.0f, 10.0f);
uniform_real_distribution<double> randomRev(0.0f, 360.0f);
uniform_real_distribution<double> randomColor(0.0f, 1.0f);
uniform_real_distribution<double> moveMin(0.0f, 1.0);
uniform_real_distribution<double> moveMax(2.0f, 3.0f);
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
bool startCheck = true;

/*���� ��ȭ ����*/
float lightX = 0.0f, lightY = 3.0f, lightZ = 0.0f;
float lightRadians = 90.0f / 360.0f * 2.0f * 3.141592f;
float lightRadiusZ = 0.0f;
float cameraX = 0.0f;
float cameraY = 7.0f;
float cameraZ = 0.0f;
float cameraRaidans = 0.0f;
float lightPower = 1.0f;
float lightVal = 90.0f;
int devideWidth = 0;
int devideHeight = 0;
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
		int _moveAnimation = 0;
		int _moveArrow = 0;
		float _speed;
		float _moveMin;
		float _moveMax;
	public:
		Cube()
		{
			_moveMin = moveMin(eng);
			_moveMax = moveMax(eng);
			_speed = moveSpeed(eng);
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
Cube object[25][25];
//vector<Cube> object;
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
Sphere snow[50];

