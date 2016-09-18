#include <Windows.h>
#include <d3d11.h>
#include <DXGI.h>
#include <cstdio>

//////////////////////////////////////////////////////////////////

// TODO: Global Variables for Direct3D
ID3D11Device* d3dDevice;				//하드웨어의 기능 지원 점검과 자원 할당에 사용되는 인터페이스
ID3D11DeviceContext* immediateContext;	//렌더 대상 설정 및 자원을 그래픽 파이프라인에 바인딩하고 GPU가 수행할 렌더링 명령들을 지시하는 데에 사용되는 인터페이스
IDXGISwapChain* dxgiSwapChain;

//텍스처는 PipeLine으로부터 View를 통해서 Access가 가능함, Render-Target도 텍스처의 일종이기 때문에 역시 View를 이용하여 Access해야 한다
ID3D11RenderTargetView* renderTargetView;	//Render-Target-View

ID3D11VertexShader* vertexShader;
ID3D11InputLayout* inputLayout;
ID3D11PixelShader* pixelShader;
ID3D11Buffer* vertexBuffer;


struct MyVertex{ float x, y, z; };

//fileName의 이름에 맞는 파일을 열고 length에 파일 속 문자의 길이를 할당하고 buffer에 length만큼 메모리를 할당한 후, buffer에 fileName의 내용을 복사
void ReadData(const char* fileName, void** buffer, int* length) {
	FILE* fp = fopen(fileName, "rb");
	fseek(fp, 0, SEEK_END);	//파일을 쓰기/읽기 위한 커서의 위치를 파일의 끝으로 이동
	*length = ftell(fp);	//현재 커서의 위치를 반환(파일의 문자 길이)
	fseek(fp, 0, SEEK_SET);	//파일을 쓰기/읽기 위한 커서의 위치를 파일의 맨앞으로 이동
	*buffer = new char[*length];
	fread(*buffer, *length, 1, fp);
	fclose(fp);
}

//Direct3D 장치 생성
bool InitializeDirect3D(HWND hWnd)
{
	// TODO: Initializing Direct3D
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };		//교환 사슬의 특성들을 설정하기 위한 구조체
	swapChainDesc.BufferCount = 1;						//후면 버퍼의 개수: 1개
	swapChainDesc.BufferDesc = { 1280, 720, { 60, 1}, DXGI_FORMAT_R8G8B8A8_UNORM,
	DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_STRETCHED };		//후면 버퍼의 속성들을 서술하는 개별적인 구조체(버퍼의 너비와 높이, 픽셀 형식 등)
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;				//후면 버퍼의 용도를 서술하는 구조체
	swapChainDesc.OutputWindow = hWnd;											//렌더링 결과를 표시할 창의 핸들
	swapChainDesc.SampleDesc = { 1, 0 };										//다중표본화를 위해 추출한 표본 개수와 품질 수준을 서술하는 구조체
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;						//사슬 교환 효과를 서술하는 구조체(DXGI_SWAP_EFFECT_DISCARD로 설정하면 디스플레이 구동기가 제시하는 가장 효율적인 방법을 설택)
	swapChainDesc.Windowed = true;												//창모드를 원하면 true, 전체화면을 원하면 false

	//Direct3D 장치와 교환 사슬을 생성
	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &dxgiSwapChain, &d3dDevice,
		nullptr, &immediateContext)))
		return false;

	//어떤 용도이든 Direct3D에서 텍스처를 사용하려면 텍스처의 초기화 시점에서 그 텍스처의 자원뷰를 생성해야 한다.
	
	ID3D11Resource* backBuffer;
	//SwapChanin으로부터 Back-Buffer의 포인터 획득(1: 후면 버퍼의 색인, 2: 버퍼의 인터페이스 형식을 지정, 3: 후면 버퍼를 가리키는 포인터)
	dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&backBuffer);

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};	//사용하는데 없음, 렌더대상으로 사용할 자원(후면 버퍼)에 담긴 원소들의 자료 형식을 서술
	//렌더 대상 뷰를 생성하는 메소드(1: 렌더 대상으로 사용할 자원, 2: D3D11_RENDER_TARGET_VIEW_DESC 구조체 혹은 무형식이 아닐경우 nullptr, 3: 생성된 렌더 대상 뷰를 할당할 Render-Target-View의 포인터)
	if (FAILED(d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView)))
		return false;

	backBuffer->Release();	//렌더 대상 뷰를 생성하였음으로 backBuffer를 해제

	//
	//Output-Merger Stage:
	//시각화할 pixel들을 결정하고 pixel color를 블렌디하는 마지막 과정
	//
	
	//OMStage때, 그래픽 파이프라인에 renderTargetView가 가리키는 자원을 바인딩하도록 명령내림
	immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);	//OM Stage때, 하나 이상의 Render-Target과 깊이 혹은 스텐실 버퍼를 바인딩함(1: view의 개수, 2:장치에 바인딩하기 위한 Render-Target을 가리키는 ID3D11RenderTargetView Array Pointer)

	void* vertexShaderData;
	int vertexShaderLength;
	ReadData("MyVertexShader.cso", (void**)&vertexShaderData, &vertexShaderLength);
	
	//vertexShaderData안에 저장된 컴파일된 Shader정보를 기반으로 VertexShader를 생성
	d3dDevice->CreateVertexShader(vertexShaderData, vertexShaderLength, nullptr, &vertexShader);

	//Vertex의 특성(ex.사용용도)을 담은 구조체
	D3D11_INPUT_ELEMENT_DESC inputEelementDescs[] = {
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};//이 Vertex들은 POSITION으로 사용되며 DXGI_FORMAT_R32G32B32_FLOAT이라는 DXGI_FORMAT형식이며 각 Vertex의 Data이다

	//IA Stage(Input-Assembler Stage)에 input-buffer data의 특성을 적용하기 위한 Input-Layer 생성
	//_countof: 정적으로 할당된 배열속 요소의 개수를 계산
	d3dDevice->CreateInputLayout(inputEelementDescs, _countof(inputEelementDescs), vertexShaderData, vertexShaderLength, &inputLayout);
	delete[] vertexShaderData;

	void* pixelShaderData;
	int pixelShaderLength;
	ReadData("MyPixelShader.cso", (void**)&pixelShaderData, &pixelShaderLength);

	//pixelShaderData안에 저장된 컴파일된 Shader정보를 기반으로 PixelShader를 생성
	d3dDevice->CreatePixelShader(pixelShaderData, pixelShaderLength, nullptr, &pixelShader);
	delete[] pixelShaderData;

	MyVertex vertices[] = {
		{-0.5f, -0.5f, +0.0f},
		{+0.0f, +0.5f, +0.0f},
		{+0.5f, -0.5f, +0.0f}
	};
	
	//Buffer Resource의 특성을 기술한 구조체
	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(vertices), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };//(1: Buffer size with bytes, 2: D3D11_USAGE, 3: 파이프라인에 바인딩되는 방식)
	
	//SubResource의 특성을 기술한 구조체
	D3D11_SUBRESOURCE_DATA vertexBufferSubResourceData = { vertices, sizeof(vertices), 0 };	//(1: 생성하기 위한 SubResource에 대한 Pointer)
	
	//Buffer생성(Vertex Buffer, Index Buffer, Shader-Constant Buffer)
	d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferSubResourceData, &vertexBuffer);

	//ViewPort 구조체
	D3D11_VIEWPORT viewport = { 0, };
	viewport.Width = 1280;
	viewport.Height = 720;
	viewport.MaxDepth = 1.0f;
	immediateContext->RSSetViewports(1, &viewport);	//Array of Viewports을 PipeLine의 Raterize-Stage에 바인딩하도록 명령

	return true;
}

//Direct3D 장치 해제
void UninitializeDirect3D()
{
	// TODO: Uninitializing Direct3D
	vertexBuffer->Release();

	inputLayout->Release();
	pixelShader->Release();
	vertexShader->Release();

	renderTargetView->Release();

	immediateContext->Release();
	d3dDevice->Release();
	dxgiSwapChain->Release();
}

void Loop()
{
	// TODO: Rendering
	//float clearColor[] = { 1, 0, 1, 1 };			//보라색
	float clearColor[] = { 101/255.0f, 156/255.0f, 239/255.0f, 1 };	//하늘색
	immediateContext->ClearRenderTargetView(renderTargetView, clearColor);	//Render-Target을 clearColor색으로 지움

	immediateContext->VSSetShader(vertexShader, nullptr, 0);	//vertexShader를 장치에 세팅
	immediateContext->PSSetShader(pixelShader, nullptr, 0);		//pixelShader를 장치에 세팅

	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	immediateContext->IASetInputLayout(inputLayout);		//inputLyaer를 장치에 세팅
	UINT stride = sizeof(MyVertex), offset = 0;
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//VertexBuffer들을 장치에 세팅

	immediateContext->Draw(3, 0);

	dxgiSwapChain->Present(0, 0);
}

//////////////////////////////////////////////////////////////////

#pragma region Precode
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE: PostQuitMessage(0); break;
	default: return DefWindowProc(hWnd, uMsg, wParam, lParam);
	}
	return 0;
}

HWND InitializeWindow(int width = 1280, int height = 720)
{
	WNDCLASS wndClass = { CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, nullptr,
		LoadIcon(nullptr, IDI_APPLICATION), LoadCursor(nullptr, IDC_ARROW),
		nullptr, nullptr, TEXT("Win32AppWindow") };
	if (RegisterClass(&wndClass) == 0)
		return 0;

	RECT rect = { 0, 0, width, height };
	AdjustWindowRect(&rect, WS_OVERLAPPEDWINDOW, false);
	int w = rect.right - rect.left, h = rect.bottom - rect.top;
	int x = GetSystemMetrics(SM_CXSCREEN) / 2 - w / 2, y = GetSystemMetrics(SM_CYSCREEN) / 2 - h / 2;

	return CreateWindow(TEXT("Win32AppWindow"), TEXT("Application"), WS_OVERLAPPEDWINDOW,
		x, y, w, h, nullptr, nullptr, GetModuleHandle(nullptr), nullptr);
}

void RunWindow(HWND hWnd)
{
	ShowWindow(hWnd, SW_SHOW);
	UpdateWindow(hWnd);

	MSG msg;
	while (true)
	{
		if (PeekMessage(&msg, nullptr, 0, 0, PM_NOREMOVE))
		{
			if (!GetMessage(&msg, nullptr, 0, 0))
				return;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			Loop();
			Sleep(1);
		}
	}
}

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	HWND hWnd = InitializeWindow();
	if (hWnd == nullptr) return -1;
	if (!InitializeDirect3D(hWnd)) return -2;

	RunWindow(hWnd);

	UninitializeDirect3D();

	return 0;
}
#pragma endregion