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
	glutCreateWindow("CG_assignment2");

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
	printf("[t]:조명을 켜기/끄기\n");
	printf("[c]:조명 색을 다른 색으로 바뀌도록 한다. 3종류의 다른 색을 적용.\n");
	printf("[o]:조명을 센터에 위치.\n");
	printf("[u,U]:조명을 위/아래로 이동\n");
	printf("[r,R]:조명을 바닥의 y축을 기준으로 양/음 방향으로 회전. \n");
	printf("[n,f]:조명을 가까이/멀리 이동\n");
	printf("[[,]]:조명 밝기 감소/증가(바닥과 조명의 거리에 따른 밝기 증가 및 감소)\n");
	printf("[y,Y]:카메라를 바닥의 y축 기준으로 시계/반시계 방향으로 공전(다시 누르면 회전을 중지)\n");
	printf("[s,S]:눈 내리기/멈추기\n");
	printf("[q]:프로그램 종료\n");
	/*********콜백 함수(운영체제 호출 함수) 호출하기*********/
	
	glutDisplayFunc(drawScene); 
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Keyboard);
	glutTimerFunc(50, TimerFunction, 1);
	glutMainLoop();

	return 0;
}
