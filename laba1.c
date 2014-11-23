#include <stdio.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
int main()
{
char name[64];
struct stat buff;

printf("Введите имя файла свойства которого хотите посмотреть:\n");
scanf("%s",name);
printf("\nВы ввели:\t%s\n",name);

int fd=open(name,O_RDONLY,0400);
if(fd<0)printf("\nОшибка открытия файла\n");
else
{
	printf("Файл успешно открылся, это дескриптор fd=%d\n",fd);
	
	//int a=fstat(fd,buff);
	int a=stat(name,buff);
	if(a==0)
	{
		//printf("Идентификатор файловой системы %ld\n",buff.t_dev);
		printf("Номер индексного дескриптора: %ld\n", (long) buff.st_ino);
		printf("Тип файла и флаги доступа: %lo (octal)\n", (unsigned long) buff.st_mode);
		printf("Значение счетчика жестких ссылок: %ld\n", (long) buff.st_nlink);
		printf("Идентификатор пользоватея: UID=%ld\n",(long)buff.st_uid);
		printf("Идентификатор группы: GID=%ld\n", (long)buff.st_gid);
		printf("Общий размер в байтах: %lld bytes\n",(long long) buff.st_size);
		printf("Размер блока ввода вывода: %ld bytes\n", (long) buff.st_blksize);
		printf("Количество выделенных блоков: %lld\n",(long long) buff.st_blocks);
		printf("Время последнего доступа: %s", ctime(&buff.st_atime));
		printf("Время последней модификации: %s", ctime(&buff.st_mtime));
		printf("Время последнего изменения: %s", ctime(&buff.st_ctime));
		printf("\n\n");
	}
	close(fd);
}
return 0;
}
