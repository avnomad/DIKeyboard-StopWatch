//	Copyright (C) 2009, 2012 Vaptistis Anogeianakis <nomad@cornercase.gr>
/*
 *	This file is part of DIKeyboard+StopWatch.
 *
 *	DIKeyboard+StopWatch is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	DIKeyboard+StopWatch is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with DIKeyboard+StopWatch.  If not, see <http://www.gnu.org/licenses/>.
 */

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

#include <windows/common.h>
#include <StopWatch.h>
#include <direct input\DirectInput Wrapper.h>
#include <direct input\Keyboard Wrapper.h>
#include <CPU clock.h>

#include <Graphics/glut window.h>


int WINAPI WinMain(InstanceHandle currentInstance , InstanceHandle PreviusInstance , CHAR *commandLineArguments , int windowMode)
{
	GLUT::Window window("Test Window");
	ofstream output("log.txt");
	output<<std::setprecision(6)<<std::fixed;
	StopWatch timer;

	if(!output)
	{
		exit(0);
	} // end if


	CPUclock::setUnit("ìs");

	output<< "current time: " <<setw(15)<<CPUclock::currentTime()<<CPUclock::getUnit()<<endl;
	

	DirectInput directInput(currentInstance);
	DIKeyboard keyboard(directInput,window.getHandle());
	
	keyboard.acquire();
	

	BYTE keys[256];
	unsigned int i = 0;
	unsigned int n = 0;
	timer.push();
	timer.push();
	while(++i <= 1000000000)
	{
		ZeroMemory(keys,sizeof(keys));
		keyboard.getDeviceState(sizeof(keys),keys);

		if(keys[DIK_RIGHT] & 0x80)
			output << "right\t";
		if(keys[DIK_LEFT] & 0x80)
			output << "left\t";
		if(keys[DIK_UP] & 0x80)
			output << "up\t";
		if(keys[DIK_DOWN] & 0x80)
			output << "down\t";
		if(keys[DIK_RIGHT] & 0x80 || keys[DIK_LEFT] & 0x80 || keys[DIK_UP] & 0x80 || keys[DIK_DOWN] & 0x80)
			output << '\n';

		if(i%100 == 0)
		{
			double d = timer.pop();
			timer.push();
			n++;
			output << d  << timer.getUnit() << '\n';
			glClearColor(0,(n%255)/255.0,0.1,0);
			glClear(GL_COLOR_BUFFER_BIT);
			//glFlush();
			window.swapBuffers();
		} // end if

		if(keys[DIK_ESCAPE] & 0x80)
		{
			break;
		} // end if
	} // end while
	timer.pop();

	output << "average iteration duration: " << timer.pop() / i << timer.getUnit() << " (1 buffer swap every 100 iterations)" << endl;
	output << n << " 100-iteration milestones" << endl;
	output<< "current time: " <<setw(15)<<CPUclock::currentTime()<<CPUclock::getUnit()<<endl;

	output.close();
	system("start log.txt /B");
} // end function WinMain

