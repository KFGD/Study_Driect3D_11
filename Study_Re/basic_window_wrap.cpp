#include <Windows.h>
#include <d3d11.h>
#include <DXGI.h>
#include <cstdio>
#include <cmath>

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

ID3D11Buffer* constantBuffer;
ID3D11RasterizerState* rasterizerState;

ID3D11Texture2D* depthStencilBuffer;
ID3D11DepthStencilView* depthStencilView;
ID3D11DepthStencilState* depthStencilState;	//Homework


struct MyVertex
{
	float x, y, z;
};

struct MyVertexWithColor
{
	float x, y, z;
	float color[4];
};

struct MyConstantBuffer { float world[16], view[16], proj[16]; };

#define cot(x) 1 / tan( x )
void transpose(float v[16])
{
	float temp[16] = { v[0], v[4], v[8], v[12], v[1], v[5], v[9], v[13],
		v[2], v[6], v[10], v[14], v[3], v[7], v[11], v[15] };
	memcpy(v, temp, sizeof(float) * 16);
}


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
	swapChainDesc.BufferDesc = { 1280, 720,{ 60, 1 }, DXGI_FORMAT_R8G8B8A8_UNORM,
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
							//Homework
							//
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	memset(&depthStencilDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));

	//Depth test parameters
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;

	//Stencil test parameters
	depthStencilDesc.StencilEnable = false;
	depthStencilDesc.StencilReadMask = 0xFF;
	depthStencilDesc.StencilWriteMask = 0xFF;

	//Stencil operations if pixel is front-facing
	depthStencilDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_INCR;
	depthStencilDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Stencil operations if pixel is back-facing
	depthStencilDesc.BackFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilDepthFailOp = D3D11_STENCIL_OP_DECR;
	depthStencilDesc.BackFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
	depthStencilDesc.BackFace.StencilFunc = D3D11_COMPARISON_ALWAYS;

	//Create depth stencil state
	if (FAILED(d3dDevice->CreateDepthStencilState(&depthStencilDesc, &depthStencilState))) {
		return false;
	}

	//Bind depth stencil state
	//immediateContext->OMSetDepthStencilState(depthStencilState, 1);


	D3D11_TEXTURE2D_DESC depthStencilBufferDesc = { 0, };
	//memset(&depthStencilBufferDesc, 0, sizeof(D3D11_TEXTURE2D_DESC));
	depthStencilBufferDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilBufferDesc.ArraySize = 1;
	depthStencilBufferDesc.Width = 1280;
	depthStencilBufferDesc.Height = 720;
	depthStencilBufferDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilBufferDesc.MipLevels = 1;
	depthStencilBufferDesc.SampleDesc.Count = 1;
	d3dDevice->CreateTexture2D(&depthStencilBufferDesc, nullptr, &depthStencilBuffer);

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	memset(&depthStencilBufferDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
	depthStencilViewDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	if (FAILED(d3dDevice->CreateDepthStencilView(depthStencilBuffer, &depthStencilViewDesc, &depthStencilView))) {
		return false;
	}

	//
	//Output-Merger Stage:
	//시각화할 pixel들을 결정하고 pixel color를 블렌디하는 마지막 과정
	//

	//OMStage때, 그래픽 파이프라인에 renderTargetView가 가리키는 자원을 바인딩하도록 명령내림
	//immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);	//OM Stage때, 하나 이상의 Render-Target과 깊이 혹은 스텐실 버퍼를 바인딩함(1: view의 개수, 2:장치에 바인딩하기 위한 Render-Target을 가리키는 ID3D11RenderTargetView Array Pointer)
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);	//Homework

	void* vertexShaderData;
	int vertexShaderLength;
	ReadData("MyVertexShader.cso", (void**)&vertexShaderData, &vertexShaderLength);

	//vertexShaderData안에 저장된 컴파일된 Shader정보를 기반으로 VertexShader를 생성
	d3dDevice->CreateVertexShader(vertexShaderData, vertexShaderLength, nullptr, &vertexShader);

	//Homework
	//Vertex의 특성(ex.사용용도)을 담은 구조체
	D3D11_INPUT_ELEMENT_DESC inputEelementDescs[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
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

	//
	//박스 코드
	//

	const float a = 0.1f;

	//Homework
	MyVertexWithColor points[] = {
		{ -a, -a, -a, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -a, +a, -a, 0.0f, 0.0f, 0.0f, 1.0f },
		{ +a, +a, -a, 0.0f, 0.0f, 0.0f, 1.0f },
		{ +a, -a, -a, 0.0f, 0.0f, 0.0f, 1.0f },
		{ -a, -a, +a, 0.0f, 0.0f, 1.0f, 1.0f },
		{ -a, +a, +a, 0.0f, 1.0f, 0.0f, 1.0f },
		{ +a, +a ,+a, 1.0f, 0.0f, 0.0f, 1.0f },
		{ +a, -a, +a, 1.0f, 1.0f, 1.0f, 1.0f }
	};

	//Homework
	MyVertexWithColor vertices[] = {
		//front
		points[0], points[1], points[2],
		points[0], points[2], points[3],
		//back
		points[4], points[6], points[5],
		points[4], points[7], points[6],
		//left
		points[4], points[5], points[1],
		points[4], points[1], points[0],
		//right
		points[3], points[2], points[6],
		points[3], points[6], points[7],
		//top
		points[1], points[5], points[6],
		points[1], points[6], points[2],
		//bottom
		points[4], points[0], points[3],
		points[4], points[3], points[7]
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

	D3D11_BUFFER_DESC constantBufferDesc = { sizeof(MyConstantBuffer), D3D11_USAGE_DEFAULT,
		D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0 };
	d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &constantBuffer);

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
	rasterizerDesc.FillMode = D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_NONE;
	rasterizerDesc.FrontCounterClockwise = false;
	d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

	return true;
}

//Direct3D 장치 해제
void UninitializeDirect3D()
{
	// TODO: Uninitializing Direct3D
	depthStencilView->Release();
	depthStencilBuffer->Release();

	rasterizerState->Release();

	vertexBuffer->Release();

	inputLayout->Release();
	pixelShader->Release();
	vertexShader->Release();

	renderTargetView->Release();

	depthStencilState->Release();	//Homework

	immediateContext->Release();
	d3dDevice->Release();
	dxgiSwapChain->Release();
}

void Loop()
{
	// TODO: Rendering
	float clearColor[] = { 101 / 255.0f, 156 / 255.0f, 239 / 255.0f, 1 };	//하늘색
	immediateContext->ClearRenderTargetView(renderTargetView, clearColor);	//Render-Target을 clearColor색으로 지움
	immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	immediateContext->RSSetState(rasterizerState);

	MyConstantBuffer constantBufferData = { 0, };
	static float angle = 0;
	angle += 0.001f;
	float world[16] = { cos(angle), 0, -sin(angle), 0, 0, 1, 0, 0, sin(angle), 0, cos(angle), 0, 0, 0, 0, 1 };
	transpose(world);
	float view[16] = { 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1 };
	transpose(view);
	float yScale = cot((3.141592f / 4) / 2);
	float xScale = yScale / (1280 / 720.0f);
	float zn = 0.001f, zf = 1000.0f;
	float proj[16] = { xScale, 0, 0, 0, 0, yScale, 0, 0, 0, 0, zf / (zf - zn), 1, 0, 0, -zn * zf / (zf - zn), 1 };
	transpose(proj);
	memcpy(constantBufferData.world, world, sizeof(float) * 16);
	memcpy(constantBufferData.view, view, sizeof(float) * 16);
	memcpy(constantBufferData.proj, proj, sizeof(float) * 16);
	immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &constantBufferData,
		sizeof(constantBufferData), 0);	//memcpy: cpu->cpu updateSubrsource: cpu->gpu

	immediateContext->VSSetShader(vertexShader, nullptr, 0);	//vertexShader를 장치에 세팅
	immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	immediateContext->PSSetShader(pixelShader, nullptr, 0);		//pixelShader를 장치에 세팅


	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	immediateContext->IASetInputLayout(inputLayout);		//inputLyaer를 장치에 세팅
															//UINT stride = sizeof(MyVertex), offset = 0;			//수정
	UINT stride = sizeof(MyVertexWithColor), offset = 0;	//Homework
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//VertexBuffer들을 장치에 세팅

	immediateContext->Draw(36, 0);	//수정
									//Draw에서 앞서 세팅한 값을 가지고 그래픽 파이프라인을 따라 그리기 시작

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