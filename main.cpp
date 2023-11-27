#include "function.h"
#include <iostream>

int main(int argc, char** argv) 
{
	/***********************************
	[순서]
	1.윈도우를 생성한다.
	2.2.0이상 확장 기능을 사용하기 위해 GLEW를 현재 버전으로 초기화한다
	3.다양한 콜백 함수들을 호출한다.
	***********************************/

	/*********윈도우 생성하기*********/
	glutInit(&argc, argv); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowPosition(550, 100);
	glutInitWindowSize(800, 800);
	glutCreateWindow("Drill29");

	/*********GLEW 초기화하기*********/
	glewExperimental = GL_TRUE; 
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "Unable to initialize GLEW" << std::endl;
		exit(EXIT_FAILURE);
	}
	else
		std::cout << "GLEW Initialized\n";

	/***********시작 초기화***********/
	/*셰이더 프로그램*/
	make_shaderProgram();
	/*객체 초기화*/
	InitObject();
	/*vao에 vbo연결하기*/
	InitBuffer();
	/*그 외*/
	glEnable(GL_DEPTH_TEST); //은면 제거
	printf("[m]:조명을 켜기/끄기\n");
	printf("[c]:조명 색을 다른 색으로 바뀌도록 한다. 3종류의 다른 색을 적용해본다.\n");
	printf("[p]:조명을 (1, 0, 0) (-1, 0, 0) (0, 0, 1) (0, 0, -1) 쪽의 위치로 옮긴다. (즉, xz 평면의 좌우상하 위치로, y값은 본인이 결정한다).\n");
	printf("[n/f]:조명이 멀어지고, 가까워지고.\nglsl 함수: float distance (vec3 a, vec3 b); // 두 벡터의 거리를 계산한다.\n");
	printf("[q]:프로그램 종료\n");
	/*********콜백 함수(운영체제 호출 함수) 호출하기*********/
	
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
