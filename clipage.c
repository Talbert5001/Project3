// Created by Talbert Herndon

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <dirent.h>
#include <sys/stat.h>
#include <time.h>
#include <dirent.h>
#include<fcntl.h>

#define MAX 256

#define MAXSTR 1000
#define MAXLIST 100
#define clear() printf("\33[H\033[J]")

#define PAGE 7
#define PAGE_TABLE 4
#define MEMORY 256

void terminal();
int processCmd(char **parsed);
int stringer(char *str, char **parsed);
int getLine(char *str);
int chatbot(); // starts a chat bot

int main()
{
	char inputString[MAXSTR], *parsedCmd[MAXLIST];
	char *parsedPiped[MAXLIST];

	terminal();

	while (1)
	{
		char cwd[1024];
		getcwd(cwd, sizeof(cwd));
		printf("\nDir:%s", cwd);
		if (getLine(inputString))
			continue;
		stringer(inputString, parsedCmd);
	}
	return 0;
}

int getLine(char *str)
{
	char *buf;
	buf = readline("# ");
	if (strlen(buf) != 0)
	{
		add_history(buf);
		strcpy(str, buf);
		return 0;
	}
	else
	{
		return 1;
	}
}

void terminal()
{
	clear();
	printf("\n ********************************\n");
	printf("Welcome to the Talbert and Chris Terminal");
	char *username = getenv("USER");
	printf("\n\nUSER is: @%s", username);
	sleep(2);
	clear();
}
void parseSpace(char *str, char **parsed)
{
	for (int i = 0; i < MAXLIST; i++)
	{
		parsed[i] = strsep(&str, " ");

		if (parsed[i] == NULL)
		{
			break;
		}
		if (strlen(parsed[i]) == 0)
		{
			i--;
		}
	}
}
int stringer(char *str, char **parsed)
{
	parseSpace(str, parsed);

	if (processCmd(parsed))
	{
		return 0;
	}
}

int ls(void)
{
	struct dirent *de;
	DIR *dr = opendir(".");

	if (dr == NULL)
	{
		printf("could not open current directory");
		return 0;
	}

	while ((de = readdir(dr)) != NULL)
		printf("%s ", de->d_name);

	closedir(dr);
	return 0;
}

int chatbot()
{
	char name;
	printf("Hey! What is your name?\n");
	scanf("%c", &name);
	printf("Oh... I don't talk to people named %c\n\n", name);
	printf("BYE!");
	return 0;
}

int calculator(char *method)
{
	if (method = "add")
	{
		int a, b, sum;
		printf("Enter First Number:");
		scanf("%d", &a);
		printf("Enter Second Number:");
		scanf("%d", &b);
		sum = a + b;
		printf("%d + %d = %d", a, b, sum);
	}
	if (method = "subtract")
	{
		int a, b, sum;

		printf("Enter First Number:");
		scanf("%d", &a);
		printf("Enter Second Number:");
		scanf("%d", &b);
		sum = a - b;
		printf("%d - %d = %d", a, b, sum);
	}
}
int create(char *filename)
{
	FILE *fp;
	fp = fopen(filename, "w");
	printf("%s \n", filename);
}

int delete (char *filename)
{
	if (remove(filename) == 0)
		printf("Deleted successfully");
	else
		printf("Unable to delete the file");

	return 0;
}

int renamefile(char *filenames)
{

	char new_filename[10] = "";

	int ret;
	printf("%s \n", filenames);

	printf("What would you like to rename the file to: ");
	scanf("%s", &new_filename);

	ret = rename(filenames, new_filename);

	if (ret == 0)
	{
		printf("File renamed sucessfully");
	}
	else
	{
		printf("Error: unable to rename file");
	}
	return (0);
}

int move()
{
	int ch;
	FILE *fp1, *fp2;
	char source[MAX], target[MAX];

	/* get the source file name from the user */
	printf("Enter your source file name:");
	fgets(source, MAX, stdin);
	source[strlen(source) - 1] = '\0';

	/* get the destination file name from the user */
	printf("Enter your destination file name:");
	fgets(target, MAX, stdin);
	target[strlen(target) - 1] = '\0';

	/* open the source file in read mode */
	fp1 = fopen(source, "r");
	/* open the destination file in write mode */
	fp2 = fopen(target, "w");

	/* error handling */
	if (!fp1)
	{
		printf("Unable to open source file to read!!\n");
		fclose(fp2);
		return 0;
	}

	if (!fp2)
	{
		printf("Unable to open target file to write\n");
		return 0;
	}

	/* copying contents of source file to target file */
	while ((ch = fgetc(fp1)) != EOF)
	{
		fputc(ch, fp2);
	}

	/* closing the opened files */
	fclose(fp1);
	fclose(fp2);

	/* removing the source file */
	remove(source);
	return 0;
}
int page()
{
	char pages[PAGE_TABLE][10];
	char *pageTable[PAGE_TABLE];
	int physicalMemory[MEMORY];
	srand(time(NULL));
	int i, j = 0;

	FILE *fp = fopen("page.txt", "r");

	if (fp == NULL)
	{

		perror("Unable to open file!");
		exit(1);
	}
	while (fgets(pages[i], 10, fp) != NULL)
	{
		pages[i][strlen(pages[i]) - 1] = '\0';
		i++;
	}
	j = i;

	for (i = 0; i < j; ++i)
	{
		printf("\n index[%d] frame[%d]  String:%s \n", i, rand() % (PAGE + 1) + 0, pages[i]);
	}
	printf("\n");
	fclose(fp);
}

int sched()
{
	int a = 0;
	// printf("Please run execute wanted files in scheduler seperated by semicolon \n");
	// printf("./(filename) ; ./(filename) ; ... \n");
	// printf("Process 0: Ready");
	srand(time(NULL));
	while (a < 5)
	{

		printf("Process [%d]: Ready \n", a);
		printf("Process [%d]: Wait \n", a);
		printf("Process [%d]: Running \n", a);
		if (a == 1)
		{
			printf("\n hellowrold \n");
		}
		if (a == 3)
		{
			int i;
			for (i = 0; i < 10; i++)
			{
				printf("\n %d seconds \n", i);
			}
		}
		if (a == 5)
		{
			ls();
		}
		if (a == 4)
		{
			time_t t = time(NULL);
			struct tm tm = *localtime(&t);
			printf("\n now: %d-%02d-%02d %02d:%02d:%02d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		}
		printf("\n %d miliseconds to run \n", rand() % (200 + 1 - 50) + 50);

		a++;
	}
	// execv("./helloworld",NULL);

	return 0;
}

int createDir(char *filename)
{
	mkdir(filename, S_IRWXU);

	return 0;
}
int cat(char *filename)
{
	FILE *ptr;
	char ch;

	// Opening file in reading mode
	ptr = fopen(filename, "r");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}

	printf("content of this file are \n");

	// Printing what is written in file
	// character by character using loop.
	do
	{
		ch = fgetc(ptr);
		printf("%c", ch);

		// Checking if character is not EOF.
		// If it is EOF stop eading.
	} while (ch != EOF);

	// Closing the file
	fclose(ptr);
	return 0;
}

int copy(){
   char ch, source_file[20], target_file[20];
   FILE *source, *target;
 
   printf("Enter name of file to copy\n");
   gets(source_file);
 
   source = fopen(source_file, "r");
 
   if( source == NULL )
   {
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   printf("Enter name of target file or new file\n");
   gets(target_file);
 
   target = fopen(target_file, "w");
 
   if( target == NULL )
   {
      fclose(source);
      printf("Press any key to exit...\n");
      exit(EXIT_FAILURE);
   }
 
   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
 
   printf("File copied successfully.\n");
 
   fclose(source);
   fclose(target);
 
   return 0;
}

int stats(char *filename) {

	struct stat sb;

	if (stat(filename, &sb) != -1){
		printf("%s is %ld bytes long.\n",filename,sb.st_size);

	}
	

}

void searchInDirectory(char *dirname){
    DIR *dir;
    struct dirent *dirp;
    dir=opendir(dirname);
    chdir(dirname);
    while((dirp=readdir(dir))!=NULL){
        if(dirp->d_type==4){
            if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0){
                continue;
            }
            printf("%s %s\n", "FOLDER", dirp->d_name);
            searchInDirectory(dirp->d_name);
        }
        else{
            printf("%s %s\n", "FILE", dirp->d_name);
        }
    }
    chdir("..");
    closedir(dir);
}

int processCmd(char **parsed)
{
	int numCmds = 18; // number of default commands
	int switchCmd = 0;
	char *cmds[numCmds];
	cmds[0] = "help"; // associated strings are used to call commands
	cmds[1] = "cd";
	cmds[2] = "exit";
	cmds[3] = "ls";
	cmds[4] = "bot";
	cmds[5] = "add";
	cmds[6] = "page";
	cmds[7] = "subtract";
	cmds[8] = "scheduler";
	cmds[9] = "create";
	cmds[10] = "rename";
	cmds[11] = "rm";
	cmds[12] = "mv";
	cmds[13] = "mkdir";
	cmds[14] = "cat";
	cmds[15] = "copy";
	cmds[16]= "stats";
	cmds[17] = "find";
	for (int i = 0; i < numCmds; i++)
	{
		if (strcmp(parsed[0], cmds[i]) == 0)
		{
			switchCmd = i + 1;
			break;
		}
	}
	switch (switchCmd)
	{		// use cases
	case 1: // help command
		printf("HELP\n");
		printf("cd - change directory\n");
		printf("ls - get list of files in directory\n");
		printf("exit - leaves cmd\n");
		printf("bot - starts a small chat bot\n");
		printf("add - adds two numbers\n");
		printf("page(filename) - pages a  your file\n");
		printf("subtract - subtracts two numbers \n");
		printf("scheduler (filename); (filename);...; - schedules first come first server \n");
		printf("create (filename) \n");
		printf("rename (old filename)\n");
		printf("rm (filename) \n");
		printf("mv \n");
		printf("mkdir (directory name) \n");
		printf("cat(filename) - prints out what is in a file \n");
		printf("copy - copy file \n");
		printf("stats (filename) - gets the metadata of a file \n");
		printf("find - scan a directory to find files \n");
		return 1;
	case 2: // cd command
		chdir(parsed[1]);
		return 1;
	case 3: // exit command
		printf("\nClosing\n\n");
		exit(0);
	case 4: // list files
		ls();
		return 1;
	case 5: // chat bot command
		printf("\nSTRATING CHAT BOT\n");
		chatbot();
		return 1;
	case 6: // starts calculator
		printf("STARTING CALCULATOR\n");
		calculator("add");
		return 1;
	case 7: // page
		printf("Creating Virtual Memory, Page Table");
		page(parsed[1]);
		return 1;
	case 8:
		printf("\n STARING CALCULATOR\n");
		calculator("subtract");
		return 1;
	case 9:
		printf("\n First come, First Serve\n");
		sched();
		return 1;
	case 10:
		printf("creating file \n");
		create(parsed[1]);
		return 1;
	case 11:
		renamefile(parsed[1]);
		return 1;
	case 12:
		delete (parsed[1]);
		return 1;
	case 13:
		move();
		return 1;
	case 14:
		createDir(parsed[1]);
		return 1;
	case 15:
		cat(parsed[1]);
		return 1;
	case 16:
		copy();
		return 1;
	case 17:
		stats(parsed[1]);
		return 1;
	case 18:
		searchInDirectory(".");
		return 1;
	default:
		break;
	}
	return 0;
}
