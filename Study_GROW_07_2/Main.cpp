#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"

struct MyConstantBuffer { PRMat world, view, proj; PRVec4 pointLightPos; };

class MyScene : public PRGame
{
public:
	ID3D11Buffer *bunnyVB;
	int bunnyVBSize;
	ID3D11InputLayout *inputLayout;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
	ID3D11Buffer *vertexCB;
	ID3D11RasterizerState *rasterizerState;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		PRModelGenerator sphere(std::string("Cube.obj"));
		bunnyVB = PRCreateVertexBuffer(graphicsContext->d3dDevice, sphere.getData(), sphere.getDataSize());
		bunnyVBSize = sphere.getDataSize() / (sizeof(PRVec3) * 2);

		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		};
		PRLoadShader(graphicsContext->d3dDevice, std::string("MyVertexShader.cso"), std::string("MyPixelShader.cso"),
			&vertexShader, &pixelShader, inputElements, _countof(inputElements), &inputLayout);

		vertexCB = PRCreateConstantBuffer<MyConstantBuffer>(graphicsContext->d3dDevice);

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.DepthClipEnable = false;
		graphicsContext->d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);
	}

	void onDestroy()
	{
		rasterizerState->Release();
		vertexCB->Release();
		pixelShader->Release();
		vertexShader->Release();
		inputLayout->Release();
		bunnyVB->Release();
	}

	void onDraw(double dt)
	{
		static int count = 8;
		count += 8;

		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->VSSetShader(vertexShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShader(pixelShader, nullptr, 0);

		graphicsContext->immediateContext->VSSetConstantBuffers(0, 1, &vertexCB);

		graphicsContext->immediateContext->RSSetState(rasterizerState);

		unsigned stride = sizeof(PRVec3) * 2, offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &bunnyVB, &stride, &offset);
		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphicsContext->immediateContext->IASetInputLayout(inputLayout);

		MyConstantBuffer cb;
		static float rot = 0;
		rot += dt;
		PRMat::createRotationY(rot, &cb.world);
		PRMat::createLookAtLH(&PRVec3(5, 5, 5), &PRVec3(0, 0, 0), &PRVec3(0, 1, 0), &cb.view);
		PRMat::createPerspectiveFieldOfViewLH(PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb.proj);
		cb.pointLightPos = PRVec4(5, 5, 5);
		graphicsContext->immediateContext->UpdateSubresource(vertexCB, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);

		graphicsContext->immediateContext->Draw(bunnyVBSize, 0);

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