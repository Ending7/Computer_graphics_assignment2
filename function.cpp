#define _CRT_SECURE_NO_WARNINGS
#include "function.h"
#include "header.h"
using namespace std;

/***********************�ݹ� �Լ�**********************/
GLvoid drawScene()
{
	/*���� ȭ��*/
	glClearColor(0.0, 0.0, 0.0, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	/******************************************************************/
	/*���̴� ���α׷� ���*/
	glUseProgram(shaderID);
	/*�׸���*/
	Draw();
	/******************************************************************/
	glutSwapBuffers(); // ȭ�鿡 ����ϱ�
}
GLvoid Reshape(int w, int h)
{
	glViewport(0, 0, w, h);
}
GLvoid Keyboard(unsigned char button, int x, int y)
{
	unsigned int lightSwitchLocation = glGetUniformLocation(shaderID, "lightSwitch");
	switch (button)
	{
	case 'r':
		lightRoate ? lightRoate = false : lightRoate = true;
		break;
	case 's':
		snowSwitch ? snowSwitch = false : snowSwitch = true;
		break;
	case 'n':
		switch (lightPosition)
		{
		case 1:
			lightZ -= 0.1f;
			break;
		case 2:
			lightX -= 0.1f;
			break;
		case 3:
			lightZ += 0.1f;
			break;
		case 0:
			lightX += 0.1f;
			break;
		}
		break;
	case 'f':
		switch (lightPosition)
		{
		case 1:
			lightZ += 0.1f;
			break;
		case 2:
			lightX += 0.1f;
			break;
		case 3:
			lightZ -= 0.1f;
			break;
		case 0:
			lightX -= 0.1f;
			break;
		}
		break;
	case '+':
		lightPower += 0.1f;
		break;
	case '-':
		lightPower -= 0.1f;
		break;
	case 'm':
		lightSwitch ? lightSwitch = false : lightSwitch = true;
		/*���̴�: ���� ����ġ �ֱ�*/
		if (lightSwitch == true) {
			glUniform1i(lightSwitchLocation, 0);
		}
		else
		{
			glUniform1i(lightSwitchLocation, 1);
		}
		break;
	case 'c':
		switch (lightColor)
		{
		case 0:
			lightColor = 1;
			break;
		case 1:
			lightColor = 2;
			break;
		case 2:
			lightColor = 3;
			break;
		case 3:
			lightColor = 0;
			break;
		}
		break;
	case 'p':
		switch (lightPosition)
		{
		case 0:
			lightX = 0.0f, lightY = 0.0f, lightZ = 1.0f;	
			lightPosition = 1;
			break;
		case 1:
			lightX = 1.0f, lightY = 0.0f, lightZ = 0.0f;
			lightPosition = 2;
			break;
		case 2:
			lightX = 0.0f, lightY = 0.0f, lightZ = -1.0f;
			lightPosition = 3;
			break;
		case 3:
			lightX = -1.0f, lightY = 0.0f, lightZ = 0.0f;
			lightPosition = 0;
			break;
		}
		break;
	case 'q':
		exit(1);
		break;
	}
}
GLvoid TimerFunction(int value)
{
	/*��ȭ�ؾ� �� �κ�*/
	/*���� ȸ��*/
	if (lightRoate == true) {
		lightRadians = lightVal / 360.0f * 2.0f * 3.141592f;
		lightVal += 2.0f;
		if (lightVal >= 360.0f) {
			lightVal = 0.0f;
		}
	}
	unsigned int lightPowerLocation = glGetUniformLocation(shaderID, "lightPower");
	glUniform1f(lightPowerLocation, lightPower);

	/*Update�� Drawȣ��*/
	glutPostRedisplay();
	/*Ÿ�̸� ���� �ݺ�*/
	glutTimerFunc(50, TimerFunction, 1);
}
/**********************�ʱ�ȭ �Լ�*********************/
void InitObject()
{
	lightCube.SetAlive(true);
	cube.SetAlive(true);
	pyramid.SetAlive(true);
	frontPyramid.SetAlive(true);
	sphere[0].SetAlive(true);
	sphere[1].SetAlive(true);
	sphere[2].SetAlive(true);
	/*��*/
	for (int i = 0; i < 50; i++)
	{
		snow[i].SetAlive(true);
		snow[i].SetRevType(3);
		snow[i].SetPosition((float)snowPosition(eng), 4.0f, (float)snowPosition(eng));
		snow[i].SetColor(0.5f,0.5f,0.9f);
	}
	/*PLAIN*/
	cube.SetColor(0.3f, 0.3f, 0.3f);
	cube.SetScale(3.0f,0.1f,3.0f);
	/*�Ƕ�̵�*/
	pyramid.SetPosition(0.0f, 0.5f, 0.0f);
	pyramid.SetColor(0.3f, 0.7f, 0.9f);
	pyramid.SetScale(1.0f, 1.0f, 1.0f);
	/*�Ƕ�̵� �ո�*/
	frontPyramid.SetPosition(0.0f, 0.5f, 0.0f);
	frontPyramid.SetColor(0.3f, 0.7f, 0.9f);
	frontPyramid.SetScale(1.0f, 1.0f, 1.0f);
	/*��*/
	sphere[0].SetRevType(0);
	sphere[0].SetColor(1.0f, 0.0f, 0.0f);
	sphere[0].SetPosition(0.0f, 0.0f, 0.0f);
	sphere[1].SetRevType(1);
	sphere[1].SetColor(0.0f, 1.0f, 0.0f);
	sphere[1].SetPosition(0.0f, 0.0f, 0.0f);
	sphere[2].SetRevType(2);
	sphere[2].SetColor(0.0f, 0.0f, 1.0f);
	sphere[2].SetPosition(0.0f, 0.0f, 0.0f);

}
void InitBuffer()
{
	/*PLAIN*/
	cube.InitBuffer();
	/*�Ƕ�̵�*/
	pyramid.InitBuffer();
	/*�Ƕ�̵� �ո�*/
	/*��*/
	sphere[0].InitBuffer();
	sphere[1].InitBuffer();
	sphere[2].InitBuffer();
	/*��*/
	for (int i = 0; i < 50; i++)
	{
		snow[i].InitBuffer();
	}
	/*����*/
	lightCube.InitBuffer();
}
/*********************ȭ�� ��� �Լ�*******************/
void Draw()
{
	
	/*ī�޶� ��ȯ*/
	CameraTransform();
	/*���� ��ȯ*/
	LightTransform();
	/*PLAIN*/
	cube.Draw();
	/*�Ƕ�̵�*/
	pyramid.Draw();
	/*��*/
	sphere[0].Draw();
	sphere[1].Draw();
	sphere[2].Draw();
	/*��*/
	for (int i = 0; i < 50; i++)
	{
		snow[i].Draw();
	}
	/*����*/
	lightCube.Draw();
}
/*******************ī�޶� ��ȯ �Լ�*******************/
void CameraTransform()
{
	/*ī�޶� ����*/
	glm::vec3 cameraPos = glm::vec3(0.0f + cameraX, cameraY, 4.5f + cameraZ); //--- ī�޶� ��ġ�� �� ��ǥ�� ����
	glm::vec3 cameraDirection = glm::vec3(0.0f+ cameraX, 0.0f, 0.0f + cameraZ); //--- ī�޶� �ٶ󺸴� ����. ��� �� ���⸸ �ٶ󺻴�.
	glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f); //--- ī�޶� ���� ����

	glm::mat4 view = glm::mat4(1.0f);
	view = glm::lookAt(cameraPos, cameraDirection, cameraUp);

	view = glm::rotate(view, glm::radians(cameraRaidans), glm::vec3(0.0f, 1.0f, 0.0f));
	if (cameraRotate == true) {
		view = glm::translate(view, glm::vec3(-cameraX, 0.0f, -cameraZ));
	}
	unsigned int viewLocation = glGetUniformLocation(shaderID, "view"); //--- ���� ��ȯ ����
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, &view[0][0]);

	//��������
	unsigned int projLoc = glGetUniformLocation(shaderID, "projection");
	glm::mat4 pTransform = glm::mat4(1.0f);

	//��Ⱦ�� 1:1�� ����, ���� �þ߰� 60', z������ 5.0��ŭ �÷ȴ�.
	pTransform = glm::perspective(glm::radians(60.0f), (float)800 / (float)800, 0.1f, 500.0f);
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, &pTransform[0][0]);
}
/********************���� ��ȯ �Լ�********************/
void LightTransform()
{
	/*���̴�: ���� ��ǥ �ֱ�*/
	unsigned int lightPosLocation = glGetUniformLocation(shaderID, "lightPos");
	glUniform3f(lightPosLocation, lightX, lightY, lightZ);
	/*�ں��Ʈ ��*/
	unsigned int lightColorLocation = glGetUniformLocation(shaderID, "lightColor");
	switch (lightColor)
	{
	case 0:
		glUniform3f(lightColorLocation, 0.5f, 0.5f, 0.5f);
		break;
	case 1:
		glUniform3f(lightColorLocation, 0.7f, 0.2f, 0.2f);
		break;
	case 2:
		glUniform3f(lightColorLocation, 0.2f, 0.7f, 0.2f);
		break;
	case 3:
		glUniform3f(lightColorLocation, 0.2f, 0.2f, 0.7f);
		break;
	}

	/*ī�޶� ��ǥ ����*/
	unsigned int viewPosLocation = glGetUniformLocation(shaderID, "viewPos"); 
	glUniform3f(viewPosLocation, 0.0f, 3.0f, 5.0f);
}
/*****************Class::LightCube �Լ�****************/
void LightCube::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticles), cubeVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void LightCube::Draw()
{
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		/*������ ��*/
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, 0.5f, 0.5f, 0.5f);

		GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void LightCube::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void LightCube::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::translate(_mixMat, glm::vec3(0.0f + lightX, 0.0f + lightY, 0.0f + lightZ));
	_mixMat = glm::rotate(_mixMat, glm::radians(20.0f), glm::vec3(1.0f, 0.0f, 0.0f));
	_mixMat = glm::rotate(_mixMat, glm::radians(30.0f + _rotateY), glm::vec3(0.0f, 1.0f, 0.0f));
	_mixMat = glm::scale(_mixMat, glm::vec3(0.1f, 0.1f, 0.1f));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void LightCube::Rotating()
{
	_rotateY += 10.0f;
	if (_rotateY >= 360.0f) {
		_rotateY = 0.0f;
	}
}
/*******************Class::Cube �Լ�*******************/
void Cube::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticles), cubeVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void Cube::Draw()
{
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		/*������ ��*/
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, _colorR, _colorG, _colorB);

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}
}
void Cube::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void Cube::SetColor(float r, float g, float b)
{
	_colorR = r;
	_colorG = g;
	_colorB = b;
}
void Cube::SetPosition(float x, float y, float z)
{
	_positionX = x;
	_positionY = y;
	_positionZ = z;
}
void Cube::SetScale(float x, float y, float z)
{
	_scaleX = x;
	_scaleY = y;
	_scaleZ = z;
}
void Cube::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::translate(_mixMat, glm::vec3(_positionX + _moveX, _positionY, _positionZ));
	_mixMat = glm::scale(_mixMat, glm::vec3(_scaleX, _scaleY, _scaleZ));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void Cube::Move()
{
	if (_moveArrow == 0) {
		_moveX += 0.01f;
	}
	else if (_moveArrow == 1){
		_moveX -= 0.01f;
	}

	if (_moveX >= 1.0f) {
		_moveArrow = 1;
	}
	else if (_moveX <= -1.0f) {
		_moveArrow = 0;
	}
}
/*****************Class::Pyramid �Լ�******************/
void Pyramid::InitBuffer()
{
	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint nAttribute = glGetAttribLocation(shaderID, "vNormal");

	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(pyramidVerticles), pyramidVerticles, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0); //--- ��ġ �Ӽ�
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float))); //--- �븻 �Ӽ�
	glEnableVertexAttribArray(1);

	glEnableVertexAttribArray(pAttribute);
	glEnableVertexAttribArray(nAttribute);
}
void Pyramid::Draw()
{
	/*������ ��*/
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, _colorR, _colorG, _colorB);

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawArrays(GL_TRIANGLES, 0, 18);
	}
}
void Pyramid::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;

}
void Pyramid::SetColor(float r, float g, float b)
{
	_colorR = r;
	_colorG = g;
	_colorB = b;
}
void Pyramid::SetPosition(float x, float y, float z)
{
	_positionX = x;
	_positionY = y;
	_positionZ = z;
}
void Pyramid::SetScale(float x, float y, float z)
{
	_scaleX = x;
	_scaleY = y;
	_scaleZ = z;
}
void Pyramid::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	_mixMat = glm::translate(_mixMat, glm::vec3(_positionX + _moveX, _positionY, _positionZ));
	_mixMat = glm::scale(_mixMat, glm::vec3(_scaleX, _scaleY, _scaleZ));
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void Pyramid::Move()
{
	if (_moveArrow == 0) {
		_moveX += 0.01f;
	}
	else if (_moveArrow == 1) {
		_moveX -= 0.01f;
	}

	if (_moveX >= 1.0f) {
		_moveArrow = 1;
	}
	else if (_moveX <= -1.0f) {
		_moveArrow = 0;
	}
}
/******************Class::Sphere �Լ�******************/
void Sphere::InitBuffer()
{
	Load_Object("sphere.obj");

	GLint pAttribute = glGetAttribLocation(shaderID, "vPos");
	GLint vAttribute = glGetAttribLocation(shaderID, "vNormal");
	/*create buffer*/
	glGenVertexArrays(1, &_vao);
	glGenBuffers(2, _vbo);
	glGenBuffers(1, &_ebo);

	/*vao binding*/
	glBindVertexArray(_vao);

	/*vbo binding*/
	glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(pAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(vAttribute, 3, GL_FLOAT, GL_FALSE, 0, 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, vertexIndices.size() * sizeof(unsigned int), &vertexIndices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(vAttribute);
	glEnableVertexAttribArray(pAttribute);
}
void Sphere::Draw()
{
	if (_Alive == true)
	{
		glBindVertexArray(_vao);
		/*������ ��*/
		int objColorLocation = glGetUniformLocation(shaderID, "objectColor");
		glUniform3f(objColorLocation, _colorR, _colorG, _colorB);

		/*�ʱ�ȭ �� ��ȯ ��� ä���*/
		Transform();
		glDrawElements(GL_TRIANGLES, 3000, GL_UNSIGNED_INT, 0);
	}
}
void Sphere::SetAlive(bool alive)
{
	if (alive == true)
		_Alive = true;
	else
		_Alive = false;
}
void Sphere::SetColor(float r, float g, float b)
{
	_colorR = r;
	_colorG = g;
	_colorB = b;
}
void Sphere::SetPosition(float x, float y, float z)
{
	_positionX = x;
	_positionY = y;
	_positionZ = z;
}
void Sphere::Transform()
{
	unsigned int transformLocate = glGetUniformLocation(shaderID, "model");
	_revolution += 4.0f;
	
	/*���� �ѹ� ���ְ�*/
	_mixMat = glm::mat4{ 1.0f };
	if (_revType == 0) {
		_mixMat = glm::translate(_mixMat, glm::vec3(_positionX, 1.0f, _positionZ));
		_mixMat = glm::rotate(_mixMat, glm::radians(_revolution), glm::vec3(0.0f, 0.0f, 1.0f));
		_mixMat = glm::translate(_mixMat, glm::vec3(0.0f, 1.0f, 0.0f));
		_mixMat = glm::scale(_mixMat, glm::vec3(1.0f, 1.0f, 1.0f));
	}
	else if (_revType == 1) {
		_mixMat = glm::translate(_mixMat, glm::vec3(_positionX, 1.0f, _positionZ));
		_mixMat = glm::rotate(_mixMat, glm::radians(_revolution), glm::vec3(1.0f, 0.0f, 0.0f));
		_mixMat = glm::translate(_mixMat, glm::vec3(0.0f, 1.0f, 0.0f));
		_mixMat = glm::scale(_mixMat, glm::vec3(0.5f, 0.5f, 0.5f));
	}
	else if (_revType == 2) {
		_mixMat = glm::translate(_mixMat, glm::vec3(_positionX, 0.7f, _positionZ));
		_mixMat = glm::rotate(_mixMat, glm::radians(_revolution), glm::vec3(0.0f, 1.0f, 0.0f));
		_mixMat = glm::translate(_mixMat, glm::vec3(1.0f, 0.0f, 0.0f));
		_mixMat = glm::scale(_mixMat, glm::vec3(0.7f, 0.7f, 0.7f));
	}
	else if (_revType == 3) {
		if (snowSwitch == true) {
			_positionY -= 0.01f * _speed;
		}	
		if (_positionY <= 0.0f)
		{
			_positionY = 4.0f, _positionX = (float)snowPosition(eng), _positionZ = (float)snowPosition(eng);
		}
		_mixMat = glm::translate(_mixMat, glm::vec3(_positionX, _positionY, _positionZ));
		_mixMat = glm::scale(_mixMat, glm::vec3(0.1f, 0.1f, 0.1f));
		}
	glUniformMatrix4fv(transformLocate, 1, GL_FALSE, glm::value_ptr(_mixMat));
}
void Sphere::SetRevType(int revType) {
	_revType = revType;
}
/********************���̴� ���α׷�*******************/
void make_vertexShader()
{
	GLchar* vertexSource;
	GLint result;
	GLchar errorLog[512];
	//--- ���ؽ� ���̴� �о� �����ϰ� ������ �ϱ�
	//--- filetobuf: ��������� �Լ��� �ؽ�Ʈ�� �о ���ڿ��� �����ϴ� �Լ�
	vertexSource = filetobuf("vertex.glsl");
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, errorLog);
		std::cerr << "ERROR: vertex shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}
void make_fragmentShader()
{
	GLchar* fragmentSource;
	GLint result;
	GLchar errorLog[512];
	//--- �����׸�Ʈ ���̴� �о� �����ϰ� �������ϱ�
	fragmentSource = filetobuf("fragment.glsl"); // �����׼��̴� �о����
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentSource, NULL);
	glCompileShader(fragmentShader);

	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &result);
	if (!result)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, errorLog);
		std::cerr << "ERROR: frag_shader ������ ����\n" << errorLog << std::endl;
		return;
	}
}
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

	//--- ���̴� �����ϱ�
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	// ---���̴��� �� ����Ǿ����� üũ�ϱ�
	glGetProgramiv(shaderID, GL_LINK_STATUS, &result);
	if (!result) {
		glGetProgramInfoLog(shaderID, 512, NULL, errorLog);
		std::cerr << "ERROR: shader program ���� ����\n" << errorLog << std::endl;
		return;
	}

	//--- Shader Program ����ϱ�
	glUseProgram(shaderID);
}
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
bool Load_Object(const char* path)
{
	vertexIndices.clear();
	uvIndices.clear();
	normalIndices.clear();
	vertices.clear();
	uvs.clear();
	normals.clear();

	ifstream in(path);
	if (!in) {
		cerr << path << "���� ��ã��";
		exit(1);
	}

	//vector<char> lineHeader(istream_iterator<char>{in}, {});

	while (in) {
		string lineHeader;
		in >> lineHeader;
		if (lineHeader == "v") {
			glm::vec3 vertex = { 0.0f,0.0f,0.0f };
			in >> vertex.x >> vertex.y >> vertex.z;
			vertices.push_back(vertex);
		}
		else if (lineHeader == "vt") {
			glm::vec2 uv = { 0.0f,0.0f };
			in >> uv.x >> uv.y;
			uvs.push_back(uv);
		}
		else if (lineHeader == "vn") {
			glm::vec3 normal = { 0.0f,0.0f,0.0f };
			in >> normal.x >> normal.y >> normal.z;
			normals.push_back(normal);
		}
		else if (lineHeader == "f") {
			char a;
			unsigned int vertexIndex[3] = { 0 }, uvIndex[3] = { 0 }, normalIndex[3] = { 0 };

			for (int i = 0; i < 3; i++)
			{
				in >> vertexIndex[i] >> a >> uvIndex[i] >> a >> normalIndex[i];
				vertexIndices.push_back(vertexIndex[i] - 1);
				uvIndices.push_back(uvIndex[i] - 1);
				normalIndices.push_back(normalIndex[i] - 1);
			}
		}
	}
	return true;
} //obj���� �ε�
