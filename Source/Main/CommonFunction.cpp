

#include "CommonFunction.h"


bool Errno_Checker( errno_t fopenResult )
{
	switch( fopenResult )
	{
		// case������ fopen_s�Լ����� ������ �߻��Ѵٸ� �ַ� �߻� �� �� ���ٰ� ����Ǵ� �����ڵ�鸸 Ȯ���Ѵ�.
	case 0:
	{
		// ���� �߻� ����.
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
		// �ֿ� �������� ���⿡�� �α� �����.
		::gLog_ErrorLog.LS_AddLog( _T( "File open fail [ Errno : major error ] - DataPreProcess.cpp" ) );

		return false;
	}


	default:
	{
		// �ֿ� ������ �ƴ� ��쿡�� ���⿡�� �α׸� �����.
		::gLog_ErrorLog.LS_AddLog( _T( "File open fail [ Errno : not major error ] - DataPreProcess.cpp" ) );

		return false;
	}
	break;


	}


	return true;
}