﻿#include <stdio.h>
#include <time.h>
#include <math.h>
#include <CoalaMOD.h>
#pragma comment(lib, "CoalaMOD.lib")
#include <windows.h>
#include <stdbool.h>

BlockID stone = createBlock(BLOCK_STONE);
BlockID water = createWater();
BlockID lava = createLava();
BlockID green_concrete = createConcrete(COLOR_LIME, 1);
PlanksID planks = createPlanks(PLANKS_OAK);
FenceID fence = createFence(FENCE_OAK);
RailID rail = createRail(RAIL);
TorchID torch = createTorch();

OreID gold = createOre(ORE_GOLD);
OreID iron = createOre(ORE_IRON);
OreID diamond = createOre(ORE_DIAMOND);
OreID redstone = createOre(ORE_GLOWING_REDSTONE);
OreID emerald = createOre(ORE_EMERALD);
OreID coal = createOre(ORE_COAL);
OreID lapis = createOre(ORE_LAPIS_LAZULI);

#define M_PI       3.14159265358979323846

void locate_number(int x, int y, int z, int number, int direction)
{

	int* a, * b, * c;
	if (number)//number가 1일 경우 1모양의 건물을 설치한다
	{
		int add1_1[13] = { 0,0,0,0,1,2,3,4,5,5,5,6,6 };
		int add1_2[13] = { 0,1,2,3,2,2,2,2,2,1,0,2,1 };
		int add1_3[13] = { 0, };
		if (direction == 1 || direction == 2)//xy평면에 건물을 설치한다
		{
			a = add1_2;
			b = add1_1;
			c = add1_3;
		}
		else if (direction == 3 || direction == 4)//yz평면에 건물을 설치한다
		{
			a = add1_3;
			b = add1_1;
			c = add1_2;
		}
		else//xz평면에 건물을 설치한다
		{
			a = add1_1;
			b = add1_3;
			c = add1_2;
		}
		if (direction == 2 || direction == 4)//direction이 2,4일경우 방향을 반전한다
			for (int i = 0; i < 13; i++)
			{
				locateBlock(green_concrete, x + (a[12] ? 3 - a[i] : 0), y + b[i], z + (c[12] ? 3 - c[i] : 0));
			}
		else
			for (int i = 0; i < 13; i++)
			{
				locateBlock(green_concrete, x + a[i], y + b[i], z + c[i]);
			}
	}
	else //number가 0일 경우 0모양의 건물을 설치한다
	{
		int add0_1[14] = { 1,2,3,4,5,6,6,0,0,1,2,3,4,5 };
		int add0_2[14] = { 0,0,0,0,0,1,2,1,2,3,3,3,3,3 };
		int add0_3[14] = { 0, };

		if (direction == 1 || direction == 2)//xy평면에 건물을 설치한다
		{
			a = add0_2;
			b = add0_1;
			c = add0_3;
		}
		else if (direction == 3 || direction == 4)//yz평면에 건물을 설치한다
		{
			a = add0_3;
			b = add0_1;
			c = add0_2;
		}
		else//xz평면에 건물을 설치한다
		{
			a = add0_1;
			b = add0_3;
			c = add0_2;
		}
		for (int i = 0; i < 14; i++)
		{
			locateBlock(green_concrete, x + a[i], y + b[i], z + c[i]);
		}
	}
}

void locate_circle(int x, int y, int z, int r, BlockID block)
{
	for (int h = -r; h < r + 1; h++)
	{
		for (int k = -r; k < r + 1; k++)
		{
			if (h * h + k * k <= r * r + 1)
			{
				if (block == lava)
					locateLava(block, x + h, y, z + k);
				else if (block == water)
					locateWater(block, x + h, y, z + k);
				else
					locateBlock(block, x + h, y, z + k);
			}
		}
	}
}

void locate_rail(int x, int y, int z, int length, int direction)
{
	if (direction == 0)
	{
		for (int i = -9 * length; i < 9 * length; i++) {
			locatePlanks(planks, x + i, y, z);
			locateFence(fence, x + i, y - 5, z);
			installRail(rail, x + i, y + 1, z, RAIL_CONNECTING_EAST_WEST);
		}
		for (int k = -9 * length; k < 9 * length; k += 9) {
			for (int i = 2; i > -3; i--)
			{
				locateFence(fence, x + k + 4 + i, y - (3 - abs(i)), z);
				locateFence(fence, x + k + 4 + i, y - (4 - abs(i)), z);
			}
			locateFence(fence, x + k + 1, y - 1, z);
			locateFence(fence, x + k + 7, y - 1, z);
			installTorch(torch, x + 2 + k, y - 4, z, FACING_UP);
			installTorch(torch, x - 3 + k, y - 4, z, FACING_UP);
		}

	}
	else
	{
		for (int i = -9 * length; i < 9 * length; i++) {
			locatePlanks(planks, x, y, z + i);
			locateFence(fence, x, y - 5, z + i);
			installRail(rail, x, y + 1, z + i, RAIL_CONNECTING_NORTH_SOUTH);
		}
		for (int k = -9 * length; k < 9 * length; k += 9) {
			for (int i = 2; i > -3; i--)
			{
				locateFence(fence, x, y - (3 - abs(i)), z + k + 4 + i);
				locateFence(fence, x, y - (4 - abs(i)), z + k + 4 + i);
			}
			locateFence(fence, x, y - 1, z + k + 1);
			locateFence(fence, x, y - 1, z + k + 7);
			installTorch(torch, x, y - 4, z + 2 + k, FACING_UP);
			installTorch(torch, x, y - 4, z - 3 + k, FACING_UP);
		}
	}
}

void locate_oval(int x, int y, int z, int r, bool only_stone)
{
	OreID ore = 0;
	int random;
	random = (rand()) % 9;
	switch (random)
	{
	case 0:
		ore = gold;
		break;
	case 1:
		ore = iron;
		break;
	case 2:
		ore = diamond;
		break;
	case 3:
		ore = redstone;
		break;
	case 4:
		ore = emerald;
		break;
	case 5:
		ore = coal;
		break;
	case 6:
		ore = lapis;
		break;
	}
	if (only_stone == true)
		random == 7;
	for (int i = -r; i < r + 1; i++)
	{
		for (int h = -4 * r; h < 4 * r + 1; h++)
		{
			for (int k = -r; k < r + 1; k++)
			{
				if (i * i + h * h / 4 + k * k <= r * r + 3)
					if (random == 7)
						locateBlock(stone, x + i, y + h, z + k);
					else
						locateOre(ore, x + i, y + h, z + k);
			}
		}
	}
}

void stage_3(int x, int y, int z)
{
	for (int i = -26; i < 26; i++)
	{
		for (int h = 0; h < 250; h++)
		{
			for (int k = -26; k < 26; k++)
			{
				if (i * i + k * k >= 399)
					locateBlock(stone, x + i, y + h, z + k);
			}
		}
	}
	int random;
	srand(time(NULL));
	for (int i = 0; i < 240; i += 10)
	{
		for (int k = 0; k < 15; k++)
		{
			random = (rand()) % 361;
			double radian = random * M_PI / 180.;
			random = (rand()) % 6;
			locate_oval(x + 22 * cos(radian), y + i, z + 22 * sin(radian), random, false);
		}
	}
	for (int i = 0; i < 240; i += 10)
	{
		for (int k = 0; k < 15; k++)
		{
			random = (rand()) % 361;
			double radian = random * M_PI / 180;
			locate_oval(x + 20 * cos(radian), y + i, z + 20 * sin(radian), 2, true);
		}
	}
	int rail_location[15][2] = { {5,0}, {-2,0}, {1,3}, {3,7}, {6,1}, {-5,0}, {0,-3}, {-5,2}, {0,0}, {1,5}, {7,0}, {1,1}, {2,6}, {0,0}, {2,0} };
	int i = 0;
	for (int h = 10; h < 210; h += 15)
	{
		locate_rail(x + rail_location[i][0], y + h, z + rail_location[i][1], 2, h % 2);
		i++;
	}
	locate_circle(x, y, z, 20, lava);
	locate_circle(x, y + 1, z, 2, water);
	locate_circle(x, 250, z, 22, stone);
}

void stage_5(int x, int y, int z)
{
	srand(time(NULL));
	int r1, r2;
	int random;
	int number;
	for (int direction = 1; direction < 5; direction++) {
		switch (direction)//방향에 따라 건물을 설치하는 시작 위치를 정한다.
		{
		case 1:
			r1 = -45;
			r2 = -45;
			break;
		case 2:
			r1 = -45;
			r2 = 45;
			break;
		case 3:
			r1 = 45;
			r2 = -45;
			break;
		case 4:
			r1 = -45;
			r2 = -45;
			break;
		}
		for (int i = 1; i < 85;)//i는 x또는 z좌표에 값을 더하는 변수로 이용한다.
		{
			int i_1 = 0, i_2 = 0;
			random = (rand()) % 2 + 2;
			for (int k = 0; k < random; k++)//난수를 생성하여 난수 만큼 붙어있는 줄의 갯수를 정한다. 
			{
				if (direction == 3 || direction == 4)
					i_2 = i;//yz평면에 건물을 설치하기 위해 i_2에 i의 값을 대입한다.
				else
					i_1 = i;//xy평면에 건물을 설치하기 위해 i_1에 i의 값을 대입한다.
				for (int h = 0; h < 250; h += 12)
				{
					number = (rand()) % 2;// 0과 1 모양을 무작위로 배치하기 위해 난수를 생성한다. 
					locate_number(x + i_1 + r1, y + h, z + r2 + i_2, number, direction);//x + i_1와 z + i_2는 건물의 시작 좌표이다.
					Sleep(30);
				}
				i += 7;////붙어있는 줄을 모두 설치하면 i에 다음 건물과 간격을 더한다.
			}
			i += 4;
		}
	}
	int range1, range2;
	for (int h = 0; h < 250; h += 15)
	{
		for (int k = 0; k < 10; k++)
		{
			do {
				range1 = 7 - (rand()) % 14;
				range2 = 4 - (rand()) % 8;
			} while (abs(range1) < 2 || abs(range2) < 2);
			number = (rand()) % 2;
			locate_number(x + range1 * 5, y + h, z + range2 * 10, number, 5);
			Sleep(30);
		}
	}
	int number_location[20][2] = { {5,0}, {-2,5}, {0,3}, {3,7}, {6,1}, {-5,0}, {0,-3}, {0,2}, {0,0}, {0,5}, {7,0}, {1,1}, {2,6}, {0,0}, {-2,0}, {-2,-2} };
	int i = 0;
	for (int h = 10; h < 210; h += 15)
	{
		random = (rand()) % 2;
		locate_number(x + number_location[i][0], y + h, z + number_location[i][1], random, 5);
		i++;
		Sleep(50);
	}
	locate_circle(x, y, z, 10, water);
}

int main()
{

}