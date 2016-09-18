#include <Windows.h>
#include <d3d11.h>
#include <DXGI.h>
#include <cstdio>
#include <cmath>

//////////////////////////////////////////////////////////////////

// TODO: Global Variables for Direct3D
ID3D11Device* d3dDevice;				//�ϵ������ ��� ���� ���˰� �ڿ� �Ҵ翡 ���Ǵ� �������̽�
ID3D11DeviceContext* immediateContext;	//���� ��� ���� �� �ڿ��� �׷��� ���������ο� ���ε��ϰ� GPU�� ������ ������ ��ɵ��� �����ϴ� ���� ���Ǵ� �������̽�
IDXGISwapChain* dxgiSwapChain;

//�ؽ�ó�� PipeLine���κ��� View�� ���ؼ� Access�� ������, Render-Target�� �ؽ�ó�� �����̱� ������ ���� View�� �̿��Ͽ� Access�ؾ� �Ѵ�
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


//fileName�� �̸��� �´� ������ ���� length�� ���� �� ������ ���̸� �Ҵ��ϰ� buffer�� length��ŭ �޸𸮸� �Ҵ��� ��, buffer�� fileName�� ������ ����
void ReadData(const char* fileName, void** buffer, int* length) {
	FILE* fp = fopen(fileName, "rb");
	fseek(fp, 0, SEEK_END);	//������ ����/�б� ���� Ŀ���� ��ġ�� ������ ������ �̵�
	*length = ftell(fp);	//���� Ŀ���� ��ġ�� ��ȯ(������ ���� ����)
	fseek(fp, 0, SEEK_SET);	//������ ����/�б� ���� Ŀ���� ��ġ�� ������ �Ǿ����� �̵�
	*buffer = new char[*length];
	fread(*buffer, *length, 1, fp);
	fclose(fp);
}

//Direct3D ��ġ ����
bool InitializeDirect3D(HWND hWnd)
{
	// TODO: Initializing Direct3D
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };		//��ȯ �罽�� Ư������ �����ϱ� ���� ����ü
	swapChainDesc.BufferCount = 1;						//�ĸ� ������ ����: 1��
	swapChainDesc.BufferDesc = { 1280, 720,{ 60, 1 }, DXGI_FORMAT_R8G8B8A8_UNORM,
		DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED, DXGI_MODE_SCALING_STRETCHED };		//�ĸ� ������ �Ӽ����� �����ϴ� �������� ����ü(������ �ʺ�� ����, �ȼ� ���� ��)
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;				//�ĸ� ������ �뵵�� �����ϴ� ����ü
	swapChainDesc.OutputWindow = hWnd;											//������ ����� ǥ���� â�� �ڵ�
	swapChainDesc.SampleDesc = { 1, 0 };										//����ǥ��ȭ�� ���� ������ ǥ�� ������ ǰ�� ������ �����ϴ� ����ü
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;						//�罽 ��ȯ ȿ���� �����ϴ� ����ü(DXGI_SWAP_EFFECT_DISCARD�� �����ϸ� ���÷��� �����Ⱑ �����ϴ� ���� ȿ������ ����� ����)
	swapChainDesc.Windowed = true;												//â��带 ���ϸ� true, ��üȭ���� ���ϸ� false

																				//Direct3D ��ġ�� ��ȯ �罽�� ����
	if (FAILED(D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, 0,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &dxgiSwapChain, &d3dDevice,
		nullptr, &immediateContext)))
		return false;

	//� �뵵�̵� Direct3D���� �ؽ�ó�� ����Ϸ��� �ؽ�ó�� �ʱ�ȭ �������� �� �ؽ�ó�� �ڿ��並 �����ؾ� �Ѵ�.

	ID3D11Resource* backBuffer;
	//SwapChanin���κ��� Back-Buffer�� ������ ȹ��(1: �ĸ� ������ ����, 2: ������ �������̽� ������ ����, 3: �ĸ� ���۸� ����Ű�� ������)
	dxgiSwapChain->GetBuffer(0, __uuidof(ID3D11Resource), (void**)&backBuffer);

	D3D11_RENDER_TARGET_VIEW_DESC renderTargetViewDesc = {};	//����ϴµ� ����, ����������� ����� �ڿ�(�ĸ� ����)�� ��� ���ҵ��� �ڷ� ������ ����
																//���� ��� �並 �����ϴ� �޼ҵ�(1: ���� ������� ����� �ڿ�, 2: D3D11_RENDER_TARGET_VIEW_DESC ����ü Ȥ�� �������� �ƴҰ�� nullptr, 3: ������ ���� ��� �並 �Ҵ��� Render-Target-View�� ������)
	if (FAILED(d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &renderTargetView)))
		return false;

	backBuffer->Release();	//���� ��� �並 �����Ͽ������� backBuffer�� ����

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
	//�ð�ȭ�� pixel���� �����ϰ� pixel color�� �����ϴ� ������ ����
	//

	//OMStage��, �׷��� ���������ο� renderTargetView�� ����Ű�� �ڿ��� ���ε��ϵ��� ��ɳ���
	//immediateContext->OMSetRenderTargets(1, &renderTargetView, nullptr);	//OM Stage��, �ϳ� �̻��� Render-Target�� ���� Ȥ�� ���ٽ� ���۸� ���ε���(1: view�� ����, 2:��ġ�� ���ε��ϱ� ���� Render-Target�� ����Ű�� ID3D11RenderTargetView Array Pointer)
	immediateContext->OMSetRenderTargets(1, &renderTargetView, depthStencilView);	//Homework

	void* vertexShaderData;
	int vertexShaderLength;
	ReadData("MyVertexShader.cso", (void**)&vertexShaderData, &vertexShaderLength);

	//vertexShaderData�ȿ� ����� �����ϵ� Shader������ ������� VertexShader�� ����
	d3dDevice->CreateVertexShader(vertexShaderData, vertexShaderLength, nullptr, &vertexShader);

	//Homework
	//Vertex�� Ư��(ex.���뵵)�� ���� ����ü
	D3D11_INPUT_ELEMENT_DESC inputEelementDescs[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};//�� Vertex���� POSITION���� ���Ǹ� DXGI_FORMAT_R32G32B32_FLOAT�̶�� DXGI_FORMAT�����̸� �� Vertex�� Data�̴�

	  //IA Stage(Input-Assembler Stage)�� input-buffer data�� Ư���� �����ϱ� ���� Input-Layer ����
	  //_countof: �������� �Ҵ�� �迭�� ����� ������ ���
	d3dDevice->CreateInputLayout(inputEelementDescs, _countof(inputEelementDescs), vertexShaderData, vertexShaderLength, &inputLayout);
	delete[] vertexShaderData;

	void* pixelShaderData;
	int pixelShaderLength;
	ReadData("MyPixelShader.cso", (void**)&pixelShaderData, &pixelShaderLength);

	//pixelShaderData�ȿ� ����� �����ϵ� Shader������ ������� PixelShader�� ����
	d3dDevice->CreatePixelShader(pixelShaderData, pixelShaderLength, nullptr, &pixelShader);
	delete[] pixelShaderData;

	//
	//�ڽ� �ڵ�
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

	//Buffer Resource�� Ư���� ����� ����ü
	D3D11_BUFFER_DESC vertexBufferDesc = { sizeof(vertices), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };//(1: Buffer size with bytes, 2: D3D11_USAGE, 3: ���������ο� ���ε��Ǵ� ���)

																													  //SubResource�� Ư���� ����� ����ü
	D3D11_SUBRESOURCE_DATA vertexBufferSubResourceData = { vertices, sizeof(vertices), 0 };	//(1: �����ϱ� ���� SubResource�� ���� Pointer)

																							//Buffer����(Vertex Buffer, Index Buffer, Shader-Constant Buffer)
	d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferSubResourceData, &vertexBuffer);

	//ViewPort ����ü
	D3D11_VIEWPORT viewport = { 0, };
	viewport.Width = 1280;
	viewport.Height = 720;
	viewport.MaxDepth = 1.0f;
	immediateContext->RSSetViewports(1, &viewport);	//Array of Viewports�� PipeLine�� Raterize-Stage�� ���ε��ϵ��� ���

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

//Direct3D ��ġ ����
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
	float clearColor[] = { 101 / 255.0f, 156 / 255.0f, 239 / 255.0f, 1 };	//�ϴû�
	immediateContext->ClearRenderTargetView(renderTargetView, clearColor);	//Render-Target�� clearColor������ ����
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

	immediateContext->VSSetShader(vertexShader, nullptr, 0);	//vertexShader�� ��ġ�� ����
	immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
	immediateContext->PSSetShader(pixelShader, nullptr, 0);		//pixelShader�� ��ġ�� ����


	immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	immediateContext->IASetInputLayout(inputLayout);		//inputLyaer�� ��ġ�� ����
															//UINT stride = sizeof(MyVertex), offset = 0;			//����
	UINT stride = sizeof(MyVertexWithColor), offset = 0;	//Homework
	immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);	//VertexBuffer���� ��ġ�� ����

	immediateContext->Draw(36, 0);	//����
									//Draw���� �ռ� ������ ���� ������ �׷��� ������������ ���� �׸��� ����

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