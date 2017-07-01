// 
// very basic for now (rv)
// 
class NotifyIcon: public IDispatcher
{
	NOTIFYICONDATA data = { 0 };
	RuntimeSupport& support;

public:
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		NotifyIcon(RuntimeSupport& instance);
		~NotifyIcon();

		BOOL Add(HWND hWnd);
		BOOL Modify();
		BOOL Delete();
		BOOL SetFocus();
		BOOL SetVersion();
		void SetData(NOTIFYICONDATA d);
		NOTIFYICONDATA GetData();
		void ShowContextMenu(HWND hWnd);
};