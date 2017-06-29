// 
// very basic for now (rv)
// 
class NotifyIcon: public IDispatcher
{
	NOTIFYICONDATA data = { 0 };
	HINSTANCE instance = nullptr;

public:
		LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

		NotifyIcon(HINSTANCE hInstance);
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