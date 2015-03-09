#pragma once

#include "ExportMacro.h"

#ifdef __cplusplus
extern "C" {
#endif

struct PACK_RESOURCE_SET {};
struct PACK_RESOURCE {};

typedef PACK_RESOURCE_SET* PACK_RESOURCE_SET_HANDLE;
typedef PACK_RESOURCE* PACK_RESOURCE_HANDLE;

#define PROGRESS_MONITOR_BEGIN_TASK			0
#define PROGRESS_MONITOR_WORKED				1
#define PROGRESS_MONITOR_DONE				2
#define PROGRESS_MONITOR_SET_TASK_NAME		3
#define PROGRESS_MONITOR_SET_SUB_TASK_NAME	4

struct ProgressMonitorData 
{
	int type;
	union
	{
		struct _BeginTask 
		{
			LPCTSTR lpszTaskName;
			int totalWork;
		} beginTask;
		struct _Worked
		{
			int work;
		} worked;
		struct _Done 
		{
	
		} done;

		struct _SetTaskName
		{
			LPCTSTR lpszName;
		} setTaskName;

		struct _SetSubTaskName
		{
			LPCTSTR lpszName;
		} setSubTaskName;
	} content;
	DWORD dwParamter;
};
// 在压制package文件的时候的回调函数
// 返回false会中断本次压制
typedef bool (*ProgressMonitorProc)(ProgressMonitorData * pData);

//////////////////////////////////////////////////////////////////////////
// 创建资源集和关闭资源集的操作
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFolder(LPCTSTR lpszFolder);
MABINOGIRESOURCE_API PACK_RESOURCE_SET_HANDLE CreateResourceSetFromFile(LPCTSTR lpszFile);
MABINOGIRESOURCE_API void CloseResourceSet(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

// 从一个文件创建资源
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE CreateResourceFromFile(LPCTSTR lpszFile, LPCTSTR lpszResourceName, size_t version);

// 释放一个资源的引用
MABINOGIRESOURCE_API void CloseResource(PACK_RESOURCE_HANDLE hResource);

//////////////////////////////////////////////////////////////////////////
// 找到指定全名的资源
MABINOGIRESOURCE_API int ResourceSet_FindResourceIndex(PACK_RESOURCE_SET_HANDLE hResourceSet, LPCTSTR lpszName);

// 获得一个资源
MABINOGIRESOURCE_API PACK_RESOURCE_HANDLE ResourceSet_GetResource(PACK_RESOURCE_SET_HANDLE hResourceSet, size_t index);

// 获得资源总数
MABINOGIRESOURCE_API size_t ResourceSet_GetResourceCount(PACK_RESOURCE_SET_HANDLE hResourceSet);
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// 当前实体的全名，为相对路径，如 db/ss.xml
MABINOGIRESOURCE_API int Resource_GetResourceName(PACK_RESOURCE_HANDLE hResource, LPTSTR lpszBuffer, int nBuffer);

// 全名的长度
MABINOGIRESOURCE_API int Resource_GetResourceNameLength(PACK_RESOURCE_HANDLE hResource);

// 返回解压后内容
MABINOGIRESOURCE_API size_t Resource_GetDecompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// 返回解压前内容
MABINOGIRESOURCE_API size_t Resource_GetCompressedContent(PACK_RESOURCE_HANDLE hResource, void* lpBuffer, size_t size);

// 返回压缩后大小
MABINOGIRESOURCE_API size_t Resource_GetCompressedSize(PACK_RESOURCE_HANDLE hResource);

// 返回压缩前的大小
MABINOGIRESOURCE_API size_t Resource_GetDecompressedSize(PACK_RESOURCE_HANDLE hResource);

// 返回版本，数字越大，版本越高
MABINOGIRESOURCE_API size_t Resource_GetVersion(PACK_RESOURCE_HANDLE hResource);

// 返回创建时间
MABINOGIRESOURCE_API FILETIME Resource_GetCreationTime(PACK_RESOURCE_HANDLE hResource);

// 返回最后访问时间
MABINOGIRESOURCE_API FILETIME Resource_GetLastAccessTime(PACK_RESOURCE_HANDLE hResource);

// 返回最后写入时间
MABINOGIRESOURCE_API FILETIME Resource_GetLastWriteTime(PACK_RESOURCE_HANDLE hResource);	
//////////////////////////////////////////////////////////////////////////

// 保存为一个pack文件
MABINOGIRESOURCE_API void PackResources(PACK_RESOURCE_HANDLE * hResourceArray, size_t length, size_t version, LPCTSTR lpszPackFile, ProgressMonitorProc proc, DWORD dwParameter);

#ifdef __cplusplus
}
#endif

