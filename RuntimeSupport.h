class RuntimeSupport
{
	HINSTANCE appInstance = nullptr;
	unsigned long refcount = 0L;

	OSVERSIONINFO version = { 0 };

	TCHAR *ControlPath = nullptr;
	TCHAR WinDir[MAX_PATH];
	
	void AddRef();
	void Release();

	void SupportMessage();

public:
	HINSTANCE instance();

	void startUp(HINSTANCE instance);
	void release();
	void OpenDisplaySettings();

	RuntimeSupport();
	RuntimeSupport(RuntimeSupport& reference);
	
	~RuntimeSupport();
};
