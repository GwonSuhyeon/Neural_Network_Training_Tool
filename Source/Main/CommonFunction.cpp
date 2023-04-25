

#include "CommonFunction.h"


bool Errno_Checker( errno_t fopenResult )
{
	switch( fopenResult )
	{
		// case에서는 fopen_s함수에서 에러가 발생한다면 주로 발생 할 것 같다고 예상되는 에러코드들만 확인한다.
	case 0:
	{
		// 에러 발생 안함.
		;
	}
	break;


	case ENOENT:		// No such file or directory
	case EINTR:			// Interrupted function
	case EAGAIN:		// No more processes or not enough memory or maximum nesting level reached
	case ENOMEM:		// Not enough memory
	case ENFILE:		// Too many files open in system
	case EFBIG:			// File too large
	case ENAMETOOLONG:	// Filename too long


	{
		// 주요 에러들은 여기에서 로그 남기기.
		::gLog_ErrorLog.LS_AddLog( _T( "File open fail [ Errno : major error ] - DataPreProcess.cpp" ) );

		return false;
	}


	default:
	{
		// 주요 에러가 아닌 경우에는 여기에서 로그를 남긴다.
		::gLog_ErrorLog.LS_AddLog( _T( "File open fail [ Errno : not major error ] - DataPreProcess.cpp" ) );

		return false;
	}
	break;


	}


	return true;
}