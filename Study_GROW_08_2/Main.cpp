#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"

class MyScene : public PRGame
{
	ID3D11Buffer *vertexBuffer;
	int vertexCount;
	ID3D11InputLayout *inputLayout;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
	ID3D11GeometryShader *geometryShader;
	ID3D11Buffer *constantBuffer;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		struct { PRVec3 p; PRVec4 c; } vertices[] = {
			{ { -0.45f, +0.45f, 0 },{ 1, 0, 0, 1 } },
			{ { +0.45f, +0.45f, 0 },{ 0, 1, 0, 1 } },
			{ { +0.45f, -0.45f, 0 },{ 0, 0, 1, 1 } },
			{ { -0.45f, -0.45f, 0 },{ 1, 1, 0, 1 } },
		};
		vertexBuffer = PRCreateVertexBuffer(graphicsContext->d3dDevice, vertices, sizeof(vertices));
		vertexCount = _countof(vertices);

		D3D11_INPUT_ELEMENT_DESC inputElements[]{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		PRLoadShader(graphicsContext->d3dDevice, std::string("MyVertexShader.cso"), std::string("MyPixelShader.cso"),
			&vertexShader, &pixelShader, inputElements, _countof(inputElements), &inputLayout);
		geometryShader = PRLoadGeometryShader(graphicsContext->d3dDevice, std::string("MyGeometryShader.cso"));
	}

	void onDestroy()
	{
		inputLayout->Release();
		geometryShader->Release();
		pixelShader->Release();
		vertexShader->Release();
		vertexBuffer->Release();
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->VSSetShader(vertexShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShader(pixelShader, nullptr, 0);
		graphicsContext->immediateContext->GSSetShader(geometryShader, nullptr, 0);

		unsigned stride = sizeof(PRVec3) + sizeof(PRVec4), offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);
		graphicsContext->immediateContext->IASetInputLayout(inputLayout);

		graphicsContext->immediateContext->Draw(vertexCount, 0);

		graphicsContext->dxgiSwapChain->Present(1, 0);
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME(MAIN_FUNC_ARGS)
{
	try {
		MyScene scene;
		std::string title("Test");
		PRApp app(&scene, PRRendererType_Direct3D11, 1280, 720, title);
		app.run();
	}
	catch (std::exception &ex) {
		PRLog(ex.what());
	}
}