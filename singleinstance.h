// 
// This code is slightly modified from MS KB article Q243953. Thanks MS!
// 
class CLimitSingleInstance
{
protected:
	DWORD  m_dwLastError;
	HANDLE m_hMutex;

public:
	CLimitSingleInstance(const TCHAR *strMutexName)
	{
		m_hMutex = CreateMutex(nullptr, FALSE, strMutexName);
		m_dwLastError = GetLastError();
	}

	~CLimitSingleInstance()
	{
		if (m_hMutex)
		{
			CloseHandle(m_hMutex);
			m_hMutex = nullptr;
		}
	}

	BOOL IsAnotherInstanceRunning()
	{
		return (ERROR_ALREADY_EXISTS == m_dwLastError);
	}
};