class IDispatcher
{
public:
	IDispatcher();
	~IDispatcher();

	// 
	// It's virtual to prevent you from "forgetting" to handle Windows messages.
	// 
	virtual LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) = 0;
};
