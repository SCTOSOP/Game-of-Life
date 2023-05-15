#include <iostream>
#include <graphics.h>

constexpr const int SCREEN_WEIGHT = 600;
constexpr const int SCREEN_HEIGHT = 400;

HWND InitWorld(bool** world)
{
	HWND hwnd = initgraph(SCREEN_WEIGHT, SCREEN_HEIGHT, EW_SHOWCONSOLE);

	for (size_t i = 0; i < 3; i++)
	{
		for (size_t j = 0; j < 3; j++)
		{
			for (size_t w = 0; w < 16; w++)
			{
				for (size_t h = 0; h < 16; h++)
				{
					world[SCREEN_WEIGHT / 3 * i + w][SCREEN_HEIGHT / 3 * j + h] = \
						bool(abs(rand()) % 2);
				}
			}
		}
	}

	return hwnd;
}

void ClearScreen()
{
	setbkcolor(WHITE);
	cleardevice();
}

void ClearWorld(bool** world)
{
	for (int w = 0; w < SCREEN_WEIGHT; w++)
	{
		for (int h = 0; h < SCREEN_HEIGHT; h++)
		{
			world[w][h] = false;
		}
	}
}

void ShowWorld(bool** world)
{
	for (int w = 0; w < SCREEN_WEIGHT; w++)
	{
		for (int h = 0; h < SCREEN_HEIGHT; h++)
		{
			putpixel(w, h, world[w][h] ? BLACK : WHITE);
		}
	}
}

int CountNeightbors(bool** world, int x, int y)
{
	int re = 0;
	
	if (x > 0)
	{
		if (world[x - 1][y])
			re++;
	}
	if (x < SCREEN_WEIGHT - 1)
	{
		if (world[x + 1][y])
			re++;
	}
	if (y > 0)
	{
		if (world[x][y - 1])
			re++;
	}
	if (y < SCREEN_HEIGHT - 1)
	{
		if (world[x][y + 1])
			re++;
	}
	if (x > 0 && y > 0)
	{
		if (world[x - 1][y - 1])
			re++;
	}
	if (x > 0 && y < SCREEN_HEIGHT - 1)
	{
		if (world[x - 1][y + 1])
			re++;
	}
	if (x < SCREEN_WEIGHT - 1 && y>0)
	{
		if (world[x + 1][y - 1])
			re++;
	}
	if (x < SCREEN_WEIGHT - 1 && y < SCREEN_HEIGHT - 1)
	{
		if (world[x + 1][y + 1])
			re++;
	}
	return re;
}

void CopyWI2WII(bool** WI, bool** WII)
{
	for (int w = 0; w < SCREEN_WEIGHT; w++)
	{
		for (int h = 0; h < SCREEN_HEIGHT; h++)
		{
			WII[w][h] = WI[w][h];
		}
	}
}

int main()
{
	bool** world_I = new(bool*[SCREEN_WEIGHT]);
	for (size_t i = 0; i <SCREEN_WEIGHT; i++)
	{
		world_I[i] = new bool[SCREEN_HEIGHT];
		memset(world_I[i], 0, SCREEN_HEIGHT);
	}

	bool** world_II = new(bool* [SCREEN_WEIGHT]);
	for (size_t i = 0; i < SCREEN_WEIGHT; i++)
	{
		world_II[i] = new bool[SCREEN_HEIGHT];
		memset(world_II[i], 0, SCREEN_HEIGHT);
	}
	
	InitWorld(world_I);
	CopyWI2WII(world_I, world_II);
	bool** world_NOW = world_I;
	bool** world_BACK = world_II;
	
	for (size_t i = 0; i < 100000; i++)
	{
		BeginBatchDraw();
		ClearScreen();

		ClearWorld(world_BACK);
		for (int w = 0; w < SCREEN_WEIGHT; w++)
		{
			for (int h = 0; h < SCREEN_HEIGHT; h++)
			{
				int c = CountNeightbors(world_NOW, w, h);
				if (c < 2 || c > 2)
					world_BACK[w][h] = false;
				else
					world_BACK[w][h] = true;
			}
		}

		ShowWorld(world_BACK);
		EndBatchDraw();

		bool** tmp = world_NOW;
		world_NOW = world_BACK;
		world_BACK = tmp;
		
		if (i % 15 == 0)
		{
			IMAGE img;
			TCHAR file_name[128];
			swprintf_s(file_name, 128, L"e:\\IMG\\Ä£ÄâµÚ%llu´Î.png", i);
			getimage(&img, 0, 0, SCREEN_WEIGHT, SCREEN_HEIGHT);
			saveimage(file_name, &img);
		}
		//Sleep(16);
	}


	return 0;
}