#include <iostream>
#include <vector>
#include <chrono>
#include <cmath>
#include <thread> 
#include <stdio.h>
#include <algorithm>

#include <termios.h>
#include <unistd.h>
#include <fcntl.h>


namespace ZCPP { // Engine namespace

	// ___________ ZCEngine Version 1.4.0 ____________

	// _______________________________________________


	class ZCEngine {

	public: // Creation functions
		bool Build(u_int8_t ScreenWidth, u_int8_t ScreenHeight, u_int8_t TextLimit);
		bool Initiate();

	public: // Interface functions for base program
		virtual bool Start();
		// Called once upon startup
		virtual bool Update(float DeltaTime);
		// Called every frame with a in between frame time value
		virtual bool Destroy();
		// Called on program termination

	public: // Utility commands
		u_int8_t ScreenWidth(); // Returns the current screenwidth
		u_int8_t ScreenHeight(); // Returns the current screenheight
		u_int8_t TextLimit(); // Returns the width of the text ( in characters)

		// Conversion functions
		std::string ctos(const char* c) { std::string s(c); return s;} // const char* to std::string
		const char* stoc(std::string s) { return s.data(); } // std::string to const char*
		std::string ftos(float f) { return std::to_string(f); } // float to std::string
		int slen(std::string s) { return s.size(); }

	public: // Draw Functions:
		void DrawScreen();
		void Draw(int32_t x, int32_t y, const char* text);
		void DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const char* text);
		void DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, const char* text);
		void DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, const char* text);
		void DrawCircle(int32_t x, int32_t y, int32_t radius, const char* text);
		void FillRect(int32_t x, int32_t y, int32_t w, int32_t h, const char* text);
		void FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, const char* text);
		void FillCircle(int32_t x, int32_t y, int32_t radius, const char* text);
		void DrawString(int32_t x, int32_t y, const char* text);
		void DrawString(int32_t x, int32_t y, std::string text);

	public: // Inner variables
		u_int8_t	nScreenWidth = 48;
		u_int8_t	nScreenHeight = 36;
		u_int8_t	nTextLimit = 2;
		u_int8_t	FrameRate = 60;
		bool 		ENGINEACTIVE = 1;
		std::vector<std::string> screen;

	public: 
		void EngineThread();

	}; // End of class ZCEngine

	bool ZCEngine::Start() { return false; }
	bool ZCEngine::Update(float DeltaTime) { (void)DeltaTime; return false; }
	bool ZCEngine::Destroy() { return true; }

	u_int8_t ZCEngine::ScreenWidth() { return nScreenWidth; }
	u_int8_t ZCEngine::ScreenHeight() { return nScreenHeight; }
	u_int8_t ZCEngine::TextLimit() { return nTextLimit; }

	bool ZCPP::ZCEngine::Build(u_int8_t ScreenWidth, u_int8_t ScreenHeight, u_int8_t TextLimit)
	{
		if( ScreenWidth < 1 || ScreenHeight < 1 || TextLimit < 1 )
		{ std::cout << "Invalid size for"; if(ScreenWidth<1) std::cout << " ScreenWidth"; if(ScreenHeight<1) std::cout << " ScreenHeight"; if(TextLimit<1) std::cout << " TextLimit" << std::endl; return false; }
		
		nScreenWidth = (u_int8_t)(ScreenWidth);
		nScreenHeight = (u_int8_t)(ScreenHeight);
		nTextLimit = (u_int8_t)(TextLimit);

		return true;
	}

	bool ZCPP::ZCEngine::Initiate()
	{
		std::string ib;
		for(int ia = 0; ia < TextLimit(); ia++)
			ib+=" ";
		screen.resize(ScreenWidth()*ScreenHeight(), ib);
		

		printf("\033[?25l");
		std::thread t = std::thread(&ZCEngine::EngineThread, this);
		t.join();

		return true;
	}

	void ZCPP::ZCEngine::EngineThread()
	{
		if(!Start())
			ENGINEACTIVE = false;

		auto t1 = std::chrono::system_clock::now();
		auto t2 = std::chrono::system_clock::now();

		while(ENGINEACTIVE)
		{
			float DeltaTime = 0;
			while(1/DeltaTime > FrameRate)
			{
				t2 = std::chrono::system_clock::now(); // Time measurement between each frame
				std::chrono::duration<float> t3 = t2-t1;
				t1 = t2; DeltaTime += t3.count();
			}
			

			if(!Update(DeltaTime))
				ENGINEACTIVE = false;

			if(Destroy())
			{

			}

			else ENGINEACTIVE = true;
		}
	}

	void ZCEngine::DrawScreen()
	{
		// Function required to display everything in the screenbuffer
		// onto the console output screen

		std::string printscreen;
		for(int y = 0; y < ScreenHeight(); y++){
		for(int x = 0; x < ScreenWidth(); x++){
		printscreen+=screen[y*ScreenWidth()+x];}printscreen +="\n";}
		printf("\033[H%s",stoc(printscreen));
	}

	void ZCEngine::Draw(int32_t x, int32_t y, const char* text)
	{
		// Function used to draw a single dot at position x, y

		// Makes sure text fits the size limit of text
		std::string textStr = text;
		if(text!=NULL)
		{
			int strlen = textStr.length();
			int txtlmt = TextLimit();
			// If the text length is greater than the TextLimit, shorten it
			if(strlen>txtlmt)
			{
				std::string base;
				for(int i = 0; i < txtlmt; i++)
				{
					base += textStr[i];
				}
				text = stoc(base);
			}
			// If the text length is less than the TextLimit, lengthen it
			if(strlen<txtlmt)
			{
				std::string base;
				for(int i = 0; i < strlen; i++)
				{
					base += textStr[i];
				}
				for(int i = 0; i < txtlmt-strlen; i++)
				{
					base += " ";
				}
				text = stoc(base);
			}
		}
		else
		{
			// If the text is empty, EXPAND till it's full
			std::string str = "";
			for(int i = 0; i < TextLimit(); i++)
			{
				str+=" ";
			}
			text=stoc(str);
		}

		// Draws text to point on screen (ONLY IF ITS WITHIN BOUNDS)
		if(x >= 0 && x < ScreenWidth() && y >= 0 && y < ScreenHeight())
		{	
			screen[(int)(abs(y)*ScreenWidth()+abs(x))] = ctos(text);
		}
	}

	void ZCEngine::DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2, const char* text)
	{
		// Function used to draw a line going from x1, y1 to x2, y2

		int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
		dx = x2 - x1; dy = y2 - y1;

		if (dx == 0)
		{
			if (y2 < y1) std::swap(y1, y2);
			for (y = y1; y <= y2; y++)
				Draw(x1, y, text);
			return;
		}

		if (dy == 0)
		{
			if (x2 < x1) std::swap(x1, x2);
			for (x = x1; x <= x2; x++)
				Draw(x, y1, text);
			return;
		}

		dx1 = abs(dx); dy1 = abs(dy);
		px = 2 * dy1 - dx1;	py = 2 * dx1 - dy1;
		if (dy1 <= dx1)
		{
			if (dx >= 0)
			{
				x = x1; y = y1; xe = x2;
			}
			else
			{
				x = x2; y = y2; xe = x1;
			}

			Draw(x, y, text);

			for (i = 0; x<xe; i++)
			{
				x = x + 1;
				if (px<0)
					px = px + 2 * dy1;
				else
				{
					if ((dx<0 && dy<0) || (dx>0 && dy>0)) y = y + 1; else y = y - 1;
					px = px + 2 * (dy1 - dx1);
				}
				Draw(x, y, text);
			}
		}
		else
		{
			if (dy >= 0)
			{
				x = x1; y = y1; ye = y2;
			}
			else
			{
				x = x2; y = y2; ye = y1;
			}

			Draw(x, y, text);

			for (i = 0; y<ye; i++)
			{
				y = y + 1;
				if (py <= 0)
					py = py + 2 * dx1;
				else
				{
					if ((dx<0 && dy<0) || (dx>0 && dy>0)) x = x + 1; else x = x - 1;
					py = py + 2 * (dx1 - dy1);
				}
				Draw(x, y, text);
			}
		}
	}

	void ZCEngine::DrawRect(int32_t x, int32_t y, int32_t w, int32_t h, const char* text)
	{
		// Function used to draw a rectangle at position x, y
		// with given size of w, h

		DrawLine(x, y, x+w, y, text);
		DrawLine(x+w, y, x+w, y+h, text);
		DrawLine(x+w, y+h, x, y+h, text);
		DrawLine(x, y+h, x, y, text);
	}

	void ZCEngine::DrawTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, const char* text)
	{
		// Function used to draw a triangle from x1, y1, to x2, y2, to x3, y3, back to x1, y1

		DrawLine(x1, y1, x2, y2, text);
		DrawLine(x2, y2, x3, y3, text);
		DrawLine(x3, y3, x1, y1, text);
	}

	void ZCEngine::DrawCircle(int32_t x, int32_t y, int32_t radius, const char* text)
	{
		// Function used to draw a circle at x, y, with radius of radius

		int x0 = 0;
		int y0 = radius;
		int d = 3 - 2 * radius;
		if (!radius) return;

		while (y0 >= x0)
		{
			Draw(x + x0, y - y0, text);
			Draw(x + y0, y - x0, text);
			Draw(x + y0, y + x0, text);
			Draw(x + x0, y + y0, text);
			Draw(x - x0, y + y0, text);
			Draw(x - y0, y + x0, text);
			Draw(x - y0, y - x0, text);
			Draw(x - x0, y - y0, text);
			if (d < 0) d += 4 * x0++ + 6;
			else d += 4 * (x0++ - y0--) + 10;
		}
	}

	// Fill functions

	void ZCEngine::FillRect(int32_t x, int32_t y, int32_t w, int32_t h, const char* text)
	{
		// Function used to fill a rectangle at position x, y
		// with given size of w, h

		int32_t x2 = x + w;
		int32_t y2 = y + h;

		if (x < 0) x = 0;
		if (x >= (int32_t)x+w) x = (int32_t)x+w;
		if (y < 0) y = 0;
		if (y >= (int32_t)y+h) y = (int32_t)y+h;

		if (x2 < 0) x2 = 0;
		if (x2 >= (int32_t)x+w) x2 = (int32_t)x+w;
		if (y2 < 0) y2 = 0;
		if (y2 >= (int32_t)y+h) y2 = (int32_t)y+h;

		for (int i = x; i < x2; i++)
			for (int j = y; j < y2; j++)
				Draw(i, j, text);
	}

	void ZCEngine::FillTriangle(int32_t x1, int32_t y1, int32_t x2, int32_t y2, int32_t x3, int32_t y3, const char* text)
	{
		// Fill a triangle between x1, y1, to x2, y2, to x3, y3

		auto SWAP = [](int& x, int& y) { int t = x; x = y; y = t; };
		auto drawline = [&](int sx, int ex, int ny) { for (int i = sx; i <= ex; i++) Draw(i, ny, text); };

		int t1x, t2x, y, minx, maxx, t1xp, t2xp;
		bool changed1 = false;
		bool changed2 = false;
		int signx1, signx2, dx1, dy1, dx2, dy2;
		int e1, e2;
		if (y1 > y2) { SWAP(y1, y2); SWAP(x1, x2); }
		if (y1 > y3) { SWAP(y1, y3); SWAP(x1, x3); }
		if (y2 > y3) { SWAP(y2, y3); SWAP(x2, x3); }

		t1x = t2x = x1; y = y1;
		dx1 = (int)(x2 - x1); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y2 - y1);

		dx2 = (int)(x3 - x1); if (dx2 < 0) { dx2 = -dx2; signx2 = -1; }
		else signx2 = 1;
		dy2 = (int)(y3 - y1);

		if (dy1 > dx1) {
			SWAP(dx1, dy1);
			changed1 = true;
		}
		if (dy2 > dx2) {
			SWAP(dy2, dx2);
			changed2 = true;
		}

		e2 = (int)(dx2 >> 1);
		if (y1 == y2) goto next;
		e1 = (int)(dx1 >> 1);

		for (int i = 0; i < dx1;) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			while (i < dx1) {
				i++;
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) t1xp = signx1;
					else          goto next1;
				}
				if (changed1) break;
				else t1x += signx1;
			}
		next1:
			while (1) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next2;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next2:
			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y == y2) break;

		}
	next:
		dx1 = (int)(x3 - x2); if (dx1 < 0) { dx1 = -dx1; signx1 = -1; }
		else signx1 = 1;
		dy1 = (int)(y3 - y2);
		t1x = x2;

		if (dy1 > dx1) {
			SWAP(dy1, dx1);
			changed1 = true;
		}
		else changed1 = false;

		e1 = (int)(dx1 >> 1);

		for (int i = 0; i <= dx1; i++) {
			t1xp = 0; t2xp = 0;
			if (t1x < t2x) { minx = t1x; maxx = t2x; }
			else { minx = t2x; maxx = t1x; }
			while (i < dx1) {
				e1 += dy1;
				while (e1 >= dx1) {
					e1 -= dx1;
					if (changed1) { t1xp = signx1; break; }
					else          goto next3;
				}
				if (changed1) break;
				else   	   	  t1x += signx1;
				if (i < dx1) i++;
			}
		next3:

			while (t2x != x3) {
				e2 += dy2;
				while (e2 >= dx2) {
					e2 -= dx2;
					if (changed2) t2xp = signx2;
					else          goto next4;
				}
				if (changed2)     break;
				else              t2x += signx2;
			}
		next4:

			if (minx > t1x) minx = t1x;
			if (minx > t2x) minx = t2x;
			if (maxx < t1x) maxx = t1x;
			if (maxx < t2x) maxx = t2x;
			drawline(minx, maxx, y);
			if (!changed1) t1x += signx1;
			t1x += t1xp;
			if (!changed2) t2x += signx2;
			t2x += t2xp;
			y += 1;
			if (y > y3) return;
		}
	}

	void ZCEngine::FillCircle(int32_t x, int32_t y, int32_t radius, const char* text)
	{
		// Fill a circle at x, y, inside of radius of radius

		int x0 = 0;
		int y0 = radius;
		int d = 3 - 2 * radius;
		if (!radius) return;

		auto drawline = [&](int sx, int ex, int ny)
		{
			for (int i = sx; i <= ex; i++)
				Draw(i, ny, text);
		};

		while (y0 >= x0)
		{
			drawline(x - x0, x + x0, y - y0);
			drawline(x - y0, x + y0, y - x0);
			drawline(x - x0, x + x0, y + y0);
			drawline(x - y0, x + y0, y + x0);
			if (d < 0) d += 4 * x0++ + 6;
			else d += 4 * (x0++ - y0--) + 10;
		}
	}

	void ZCEngine::DrawString(int32_t x, int32_t y, const char* text)
	{
		// Draw a string at x, y with the string text, going right

		std::string textStr = ctos(text);

		int txtlmt = TextLimit(); // 2
		int size = textStr.size(); // 11
		float wrap = size/txtlmt; // 5.5
		if(wrap > (int)wrap) // 5.5 > 5
			size+=txtlmt; // size = 13

		for(int i = 0; i < size; i+=txtlmt)
		{
			std::string base;
			for(int ii = 0; ii < txtlmt; ii++)
			{
				base += text[i+ii];
			}
			Draw(x+(i/txtlmt),y,stoc(base));
		}
	}

	void ZCEngine::DrawString(int32_t x, int32_t y, std::string text)
	{
		// Draw a string at x, y with the string text, going right

		int txtlmt = TextLimit();
		int size = text.size();
		float wrap = size/txtlmt;
		if(wrap > (int)wrap)
			size+=txtlmt;

		for(int i = 0; i < size; i+=txtlmt)
		{
			std::string base;
			for(int ii = 0; ii < txtlmt; ii++)
			{
				base += text[i+ii];
			}
			Draw(x+(i/txtlmt),y,stoc(base));
		}
	}
} // End of ZCEngine definition

// ____________ Custom Structs ____________


using namespace ZCPP;

class Program : public ZCPP::ZCEngine
{
public:
	Program()
	{

	}

public:
	bool Start() override
	{
		FrameRate = 30;
		return true;
	}

	bool Update(float DeltaTime) override
	{
		DrawScreen();
		return true;
	}

	bool Destroy() override
	{
		return true;
	}
};

int main()
{
  Program Main;
	if(Main.Build(16*3.5,9*3.5,2)) // 16*3.2, 9*3.2
		Main.Initiate();
}
