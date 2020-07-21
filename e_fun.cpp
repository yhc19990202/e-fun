#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// 排序函數 
void swap(int* x_1, long long int* y_1, int* x_2, long long int* y_2)
{
	int z;
	long long int w;
	
	z = *x_1;
	*x_1 = *x_2;
	*x_2 = z; 

	w = *y_1;
	*y_1 = *y_2;
	*y_2 = w; 
}

// 抽球函數 
int dice()
{
	int x = 0;
	int y = 0;
	
	// 十顆抽兩顆出來 在機率上等價於 抽兩次後_如果相同則重抽 
	while( x == y )
	{
		x = rand() % 10;
		y = rand() % 10;
	}
	
	return (x+y)%10;//相加之後取尾數 
}

//遊戲模擬 
void game(long long int* record, int* map, long long int* random_times)
{
	int i = 0;
	int j;
	int pos = 0;
	int step;//要走幾步 
	int old[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//紀錄地圖的位置是否已經走過(中獎) 
	
	while(i < 7)//不斷重複，直到7人中獎前 
	{
		step = dice();//擲骰子決定要走幾步 
		*random_times += 1;
		
		for(j=0;j<step;j++)//總共要走 'step' 步 
		{
			pos++;
			pos %= 12;
			while(old[pos])//只要走到已經中獎的格子，就往下一格移動 
			{
				pos++;
				pos %= 12;
			}
		}
		
		if( *(map+pos) >= 0 )//如果停在數字上 
		{
			*(record+pos) += 1;//該數字中獎次數+1 
			old[pos] = 1;//該格子被紀錄為'已中獎' 
			i++;//中獎人數+1 
		}
	}
}

//主程式 
int main()
{
	srand(time(NULL));
	
	int map[12] = {-1,5,9,7,1,4,-1,6,0,3,8,2};//紀錄地圖對應的數字 -1代表特殊的格子 
	long long int record[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//每個位置的累計中獎次數 
	long long int simu_time = 1000000000;//模擬次數 
	long long int random_times = 0;//紀錄總共抽了幾輪球 
	
	long long int i;
	int j;
	int k;
	
	//遊戲模擬 
	for(i=0;i<simu_time;i++)
	{
		game(record, map, &random_times);
	}
	
	printf("\n");
	
	//按照中獎次數從小排到大 
	for(j=0;j<12;j++)
	{
		for(k=j+1;k<12;k++)
		{
			if(record[j] > record[k])
			{
				swap(&map[j], &record[j], &map[k], &record[k]);
			}
		}
	}
	
	//輸出結果 
	for(j=0;j<12;j++)
	{
		if( map[j] >= 0 )
		{
			printf("%d %lld\n", map[j], record[j]);
		}
	}
	
	printf("random_times = %lld\n",random_times);
	
	return 0;
}
