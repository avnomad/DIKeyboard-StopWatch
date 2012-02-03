#include <iostream>
using std::cout;
using std::cin;
using std::endl;
using std::cerr;
using std::clog;
using std::left;

#include <iomanip>
using std::setw;
using std::setprecision;

#include <fstream>
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::ios;

#include <cstdlib>
using std::system;
using std::exit;

#include <string>

#include "../../unsorted/windows common.h"
#include "../../unsorted/StopWatch.h"
#include "../../unsorted/DirectInput Wrapper.h"
#include "../../unsorted/Keyboard Wrapper.h"
#include "../../unsorted/CPU clock.h"

#include <GL/glut.h>
//#include <Shellapi.h>
//#include <DXUT.h>



void OnDraw()
{
	/*glClearColor(0,0,0.1,0);
	glClear(GL_COLOR_BUFFER_BIT);*/
	throw 0;
}

void OnSpecial(int key , int x , int y)
{
	/*if(key == GLUT_KEY_RIGHT)
		output << "right\t";
	if(key == GLUT_KEY_LEFT)
		output << "left\t";
	if(key == GLUT_KEY_UP)
		output << "up\t";
	if(key == GLUT_KEY_DOWN)
		output << "down\t";
	if(key == GLUT_KEY_LEFT || key == GLUT_KEY_RIGHT || key == GLUT_KEY_UP || key == GLUT_KEY_DOWN)
		output << endl;*/
}

void onIdle(void)
{
	//static int i = 0;
	////if(!i)
	////{
	////	system("PAUSE");
	////} // end if
	//
	//if(++i > 1000000) throw 0;
	//
	//

	//glClearColor(0,(i%10000)/10000.0,0.1,0);
	//glClear(GL_COLOR_BUFFER_BIT);
	////glFlush();
	//glutSwapBuffers();

	
} // end fuction onIdle


int WINAPI WinMain(InstanceHandle currentInstance , InstanceHandle PreviusInstance , CHAR *commandLineArguments , int windowMode)
{
	ofstream output("c:/output/test.txt");
	output<<std::setprecision(6)<<std::fixed;
	StopWatch timer;

	if(!output)
	{
		exit(0);
	} // end if

	int argc = 1;
	char *p = "hi!";
	char **argv = &p;
	glutInit(&argc,argv);
	glutInitWindowPosition(320,320);
	glutInitWindowSize(320,320);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutCreateWindow("Test Window");

	CPUclock::setTimeUnit("ìs");

	output<<setw(15)<<CPUclock::currentTime()<<CPUclock::getTimeUnit()<<endl;
	

	

	//glutFullScreen();
	glutDisplayFunc(OnDraw);
	glutIdleFunc(onIdle);
	glutSpecialFunc(OnSpecial);

	//timer.push();
	try
	{
		glutMainLoop();
	}
	catch(int)
	{
		// do nothing
	} // end catch
	//output << timer.pop() / 1000000 << timer.getUnit() << endl;

	DirectInput directInput(currentInstance);
	DIKeyboard keyboard(directInput.iObject,FindWindow(0,"Test Window"));
	
	keyboard.acquire();
	

	BYTE keys[256];
	unsigned int i = 0;
	unsigned int n = 0;
	timer.push();
	timer.push();
	while(++i <= 1000000000)
	{
		ZeroMemory(keys,sizeof(keys));
		keyboard->GetDeviceState(sizeof(keys),keys);

		if(keys[DIK_RIGHT] & 0x80)
			output << "right\t";
		if(keys[DIK_LEFT] & 0x80)
			output << "left\t";
		if(keys[DIK_UP] & 0x80)
			output << "up\t";
		if(keys[DIK_DOWN] & 0x80)
			output << "down\t";
		if(keys[DIK_RIGHT] & 0x80 || keys[DIK_LEFT] & 0x80 || keys[DIK_UP] & 0x80 || keys[DIK_DOWN] & 0x80)
			output << endl;

		if(i%100 == 0)
		{
			timer.pop();
			timer.push();
			n++;
			glClearColor(0,(n%255)/255.0,0.1,0);
			glClear(GL_COLOR_BUFFER_BIT);
			//glFlush();
			glutSwapBuffers();
		} // end if

		if(keys[DIK_ESCAPE] & 0x80)
		{
			break;
		} // end if
	} // end while
	timer.pop();

	output << timer.pop() / 1000000 << timer.getUnit() << endl;
	output << n <<endl;
	output<<setw(15)<<CPUclock::currentTime()<<CPUclock::getTimeUnit()<<endl;

	output.close();
	system("start c:/output/test.txt /B");
} // end function WinMain

