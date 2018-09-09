#include <CMAPI.h>
#include <stdlib.h>
#include <stdarg.h>

// Обработчики для Bento. На базе стандартных функций C

static void CM_VARARGS error_handler(CMErrorNbr err,...)
{
	va_list ap;
	va_start(ap,err);
	printf("Ошибка #(%d)\n",err);
	va_end(ap);

	exit(err);
}

static CMPtr CM_FIXEDARGS alloc_handler(CMSize size,CMRefCon ref)
{
	return malloc(size);
}

static void CM_FIXEDARGS free_handler(CMPtr ptr,CMRefCon ref)
{
	if (ptr) free(ptr);
}

struct SessionOps
{
	MallocProto allocHandler;
	FreeProto freeHandler;
	ErrorProto errorHandler;
};

#define SessionOps_offset(x)   (size_t)(void *)&(((struct SessionOps *)NULL)->x)

static struct 
{
	const char *name;
	size_t offset;
} session_table[]={
	{CMAllocOpType,SessionOps_offset(allocHandler)},
	{CMFreeOpType,SessionOps_offset(freeHandler)},
	{CMErrorOpType,SessionOps_offset(errorHandler)}
};

static struct SessionOps sops={alloc_handler,free_handler,error_handler};

// Метаобработчик для Bento

CMHandlerAddr CM_FIXEDARGS ODBentoSessionHandler(CMType pv,CMconst_CMGlobalName name)
{
	int i=0;

	while (i < (sizeof(session_table)/sizeof(session_table[0])))
	{
		if (!strcmp(session_table[i].name,name))
		{
			return *((CMHandlerAddr *)(((char *)&sops)+session_table[i].offset));
		}

		i++;
	}

	return NULL;
}

void main()
{
  // Инициализируем сессию
  
  // Тестово выделяем память
  CMAlloc();
  
  // Высвобождаем память
  CMFree();
  
  // Завершаемся с сообщением, что все ОК
  CMError();
  
  // Завершаем сессию Bento
}