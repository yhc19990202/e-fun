#include<stdio.h>
#include<stdlib.h>
#include<time.h>

// �ƧǨ�� 
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

// ��y��� 
int dice()
{
	int x = 0;
	int y = 0;
	
	// �Q��������X�� �b���v�W������ ��⦸��_�p�G�ۦP�h���� 
	while( x == y )
	{
		x = rand() % 10;
		y = rand() % 10;
	}
	
	return (x+y)%10;//�ۥ[��������� 
}

//�C������ 
void game(long long int* record, int* map, long long int* random_times)
{
	int i = 0;
	int j;
	int pos = 0;
	int step;//�n���X�B 
	int old[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//�����a�Ϫ���m�O�_�w�g���L(����) 
	
	while(i < 7)//���_���ơA����7�H�����e 
	{
		step = dice();//�Y��l�M�w�n���X�B 
		*random_times += 1;
		
		for(j=0;j<step;j++)//�`�@�n�� 'step' �B 
		{
			pos++;
			pos %= 12;
			while(old[pos])//�u�n����w�g��������l�A�N���U�@�沾�� 
			{
				pos++;
				pos %= 12;
			}
		}
		
		if( *(map+pos) >= 0 )//�p�G���b�Ʀr�W 
		{
			*(record+pos) += 1;//�ӼƦr��������+1 
			old[pos] = 1;//�Ӯ�l�Q������'�w����' 
			i++;//�����H��+1 
		}
	}
}

//�D�{�� 
int main()
{
	srand(time(NULL));
	
	int map[12] = {-1,5,9,7,1,4,-1,6,0,3,8,2};//�����a�Ϲ������Ʀr -1�N��S����l 
	long long int record[12] = {0,0,0,0,0,0,0,0,0,0,0,0};//�C�Ӧ�m���֭p�������� 
	long long int simu_time = 1000000000;//�������� 
	long long int random_times = 0;//�����`�@��F�X���y 
	
	long long int i;
	int j;
	int k;
	
	//�C������ 
	for(i=0;i<simu_time;i++)
	{
		game(record, map, &random_times);
	}
	
	printf("\n");
	
	//���Ӥ������Ʊq�p�ƨ�j 
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
	
	//��X���G 
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
