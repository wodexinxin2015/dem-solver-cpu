/************************************************************************************
DEM-Solver-CPU
Dsicrete Element Method Program for landsldies, debris flows and other geohazards
--parallelized and optimized for SMP (Symmetric multiprocessing) architecture.
--optimized for AVX2 instructions.
--Copyright (c) 2018-2024, Weijie ZHANG, GeoHohai, Hohai University.
************************************************************************************/
/************************************************************************************
DEM-0-Main.cpp: defines all the functions in the DEM calculations.
************************************************************************************/
/************************************************************************************
revision list:
2023-12-11: V0.0.1
			initial coding.
************************************************************************************/

#define _CRT_SECURE_NO_DEPRECATE
#include <stdlib.h>
#include <stdio.h>
#include "string.h"
#include <time.h>
#include "DEM-Common.h"

/*the main calculation procedure of DEM solver*/
int DEM_Calculation(int argc, char* argv);

/*main function*/
int main(int argc, char* argv[])
{

	char* direct_name, temp[100];
	int i;
	time_t start, end;
	int result, run_result;
	FILE* fpch;

	run_result = 0;

	/*SPH simulation process with arguments: argc, argv*/
	if (argc > 2)
	{

		printf("-------------------------------------------------------------------\n");
		printf("--||The simulation has    %3d working project.||----------\n", (argc - 2) < 1 ? 1 : (argc - 2));
		printf("-------------------------------------------------------------------\n");

		if (argv[1][0] == '-' && argv[1][1] == 'p')
		{
			for (i = 2; i < argc; i++)
			{
				printf("-------------------------------------------------------------------\n");
				printf("--||The Working Project No.%3d is now running.||----------\n", i - 1);
				printf("--<%53s>--\n", argv[i]);
				printf("-------------------------------------------------------------------\n");

				memset(temp, 0, 100);
				direct_name = argv[i];

				/*start calculation*/
				start = time(NULL);

				run_result = DEM_Calculation(argc, argv[i]);

				/*consumed time calculation*/
				end = time(NULL);
				result = (int)difftime(end, start);

				//path for windows
				if (win32)
				{
					//file for log output
					strcpy(temp, direct_name);
					strcat(temp, "\\Consumed time.txt");
				}
				//path for Linux
				else
				{
					//file for log output
					strcpy(temp, direct_name);
					strcat(temp, "/Consumed time.txt");
				}

				if ((fpch = fopen(temp, "w")) != NULL)
				{
					fprintf(fpch, "Time used for DEM simulation:%3d : %2d : %2d\n", (int)(result / 3600),
						(int)((result % 3600) / 60), (int)((result % 3600) % 60));
					fclose(fpch);
				}

				if (run_result == 0)
				{
					printf("-------------------------------------------------------------------\n");
					printf("--||The Working Project No.%3d is finished.||-------------\n", i - 1);
					printf("-------------------------------------------------------------------\n");
				}
				else
				{
					printf("-------------------------------------------------------------------\n");
					printf("--||Simulation of Project No.%3d raised an error.|| ------\n", i - 1);
					printf("-------------------------------------------------------------------\n");
				}
			}
		}
		else
		{
			printf("Error 200: option is not -p.\n");
			printf("-------------------------------------------------------------------\n");
			printf("Multi-Phase and Parallelized SPH program\n");
			printf("--Copyright (c) 2018-2023, Weijie ZHANG, GeoHohai, Hohai University.\n");
			printf("-------------------------------------------------------------------\n");
			printf("     Please using no arguments or following arguments.\n");
			printf("-------------------------------------------------------------------\n");
			printf("     Argument list: -p directory1 directory2 ...\n");
			printf("               -p         ---specifying working directory;\n");
			printf("               directory1 ---directory path 1;\n");
			printf("               directory2 ---directory path 2;\n");
			printf("               ...        ---more directory path.\n");
			printf("-------------------------------------------------------------------\n");

			return 200;
		}
	}
	else if (argc == 2)
	{
		printf("Error 100: Argument is not correct, Exit.\n");
		printf("-------------------------------------------------------------------\n");
		printf("Multi-Phase and Parallelized SPH program\n");
		printf("--Copyright (c) 2018-2023, Weijie ZHANG, GeoHohai, Hohai University.\n");
		printf("-------------------------------------------------------------------\n");
		printf("     Please using no arguments or following arguments.\n");
		printf("-------------------------------------------------------------------\n");
		printf("     Argument list: -p directory1 directory2 ...\n");
		printf("               -p         ---specifying working directory;\n");
		printf("               directory1 ---directory path 1;\n");
		printf("               directory2 ---directory path 2;\n");
		printf("               ...        ---more directory path.\n");
		printf("-------------------------------------------------------------------\n");

		return 100;
	}
	else if (argc == 1)
	{

		printf("-------------------------------------------------------------------\n");
		printf("---||No specifying working directory.||--------------------\n");
		printf("---||using the directory of executable file.||-------------\n");
		printf("-------------------------------------------------------------------\n");

		printf("-------------------------------------------------------------------\n");
		printf("---||The Working Project is running.||---------------------\n");
		printf("-------------------------------------------------------------------\n");

		memset(temp, 0, 100);

		/*start calculation*/
		start = time(NULL);

		run_result = DEM_Calculation(argc, (char*)("."));

		/*consumed time calculation*/
		end = time(NULL);
		result = (int)difftime(end, start);

		//path for windows
		if (win32)
		{
			//file for log output
			strcpy(temp, ".");
			strcat(temp, "\\Consumed time.txt");
		}
		//path for Linux
		else
		{
			//file for log output
			strcpy(temp, ".");
			strcat(temp, "/Consumed time.txt");
		}

		if ((fpch = fopen(temp, "w")) != NULL)
		{
			fprintf(fpch, "Time used for DEM simulation:%3d : %2d : %2d\n", (int)(result / 3600),
				(int)((result % 3600) / 60), (int)((result % 3600) % 60));
			fclose(fpch);
		}

		if (run_result == 0)
		{
			printf("-------------------------------------------------------------------\n");
			printf("--||The Working Project No.   1 is finished.||-------------\n");
			printf("-------------------------------------------------------------------\n");
		}
		else
		{
			printf("-------------------------------------------------------------------\n");
			printf("--||Simulation of Project No.  1 raised an error.|| ------\n");
			printf("-------------------------------------------------------------------\n");
		}
	}

	return 0;
}
