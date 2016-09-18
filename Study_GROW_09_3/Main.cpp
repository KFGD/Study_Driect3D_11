#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"

struct MyConstantBuffer { PRMat world, view, proj; };
struct Lights { PRVec4 lightPos[8]; };

enum RenderTargetIndex {
	RenderTargetIndex_Color,
	RenderTargetIndex_Position,
	RenderTargetIndex_Normal,
	RenderTargetIndex_Depth,
};

class MyScene : public PRGame
{
public:
	PRDraw2DUtility *draw2DUtil;
	ID3D11RasterizerState *rasterizerState;

	ID3D11Texture2D *renderTargetBuffers[4];
	ID3D11RenderTargetView *renderTargetViews[3];
	ID3D11DepthStencilView *depthStencilView;
	ID3D11ShaderResourceView *shaderResourceViews[4];

	ID3D11Buffer *bunny;
	unsigned bunnyVertexCount;
	ID3D11VertexShader *bunnyVertexShader;
	ID3D11PixelShader *bunnyPixelShader;
	ID3D11InputLayout *bunnyInputLayout;
	ID3D11Buffer *bunnyConstantBuffer;

	ID3D11PixelShader *deferredRenderingPixelShader;
	ID3D11Buffer *deferredRenderingLightsConstantBuffer;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);
		draw2DUtil = new PRDraw2DUtility(graphicsContext->d3dDevice);

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		graphicsContext->d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

		PRModelGenerator bunnyModelGen(std::string("bunny.obj"));
		bunny = PRCreateVertexBuffer(graphicsContext->d3dDevice, &bunnyModelGen);
		bunnyVertexCount = bunnyModelGen.getDataSize() / (sizeof(PRVec3) * 2);

		D3D11_INPUT_ELEMENT_DESC inputElements[] = 
		{
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}, 
			{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		PRLoadShader(graphicsContext->d3dDevice, std::string("BunnyVS.cso"), std::string("BunnyPS.cso"),
			&bunnyVertexShader, &bunnyPixelShader, inputElements, _countof(inputElements), &bunnyInputLayout);

		bunnyConstantBuffer = PRCreateConstantBuffer<MyConstantBuffer>(graphicsContext->d3dDevice);

		for (int i = 0; i < 3; ++i)
		{
			renderTargetBuffers[i] = PRCreateTexture2D(graphicsContext->d3dDevice,
				DXGI_FORMAT_R32G32B32A32_FLOAT,
				1280, 720);
			graphicsContext->d3dDevice->CreateRenderTargetView(renderTargetBuffers[i],
				nullptr, &renderTargetViews[i]);
			graphicsContext->d3dDevice->CreateShaderResourceView(renderTargetBuffers[i],
				nullptr, &shaderResourceViews[i]);
		}
		renderTargetBuffers[RenderTargetIndex_Depth] = PRCreateTexture2D(graphicsContext->d3dDevice,
			DXGI_FORMAT_R24G8_TYPELESS, 1280, 720, D3D11_BIND_DEPTH_STENCIL);

		D3D11_DEPTH_STENCIL_VIEW_DESC dsvDesc;
		memset(&dsvDesc, 0, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));
		dsvDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
		dsvDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		graphicsContext->d3dDevice->CreateDepthStencilView(renderTargetBuffers[RenderTargetIndex_Depth],
			&dsvDesc, &depthStencilView);

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvDesc.Format = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
		srvDesc.Texture2D.MipLevels = 1;
		HRESULT result = graphicsContext->d3dDevice->CreateShaderResourceView(renderTargetBuffers[RenderTargetIndex_Depth],
			&srvDesc, &shaderResourceViews[RenderTargetIndex_Depth]);

		deferredRenderingPixelShader = PRLoadPixelShader(graphicsContext->d3dDevice, std::string("DeferredPS.cso"));
		deferredRenderingLightsConstantBuffer = PRCreateConstantBuffer<Lights>(graphicsContext->d3dDevice);
	}

	void onDestroy()
	{
		deferredRenderingLightsConstantBuffer->Release();
		deferredRenderingPixelShader->Release();

		shaderResourceViews[RenderTargetIndex_Depth]->Release();
		depthStencilView->Release();
		renderTargetBuffers[RenderTargetIndex_Depth]->Release();
		for (int i = 0; i < 3; ++i)
		{
			shaderResourceViews[i]->Release();
			renderTargetViews[i]->Release();
			renderTargetBuffers[i]->Release();
		}

		bunnyConstantBuffer->Release();
		bunnyInputLayout->Release();
		bunnyPixelShader->Release();
		bunnyVertexShader->Release();
		bunny->Release();

		rasterizerState->Release();
		SAFE_DELETE(draw2DUtil);
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->OMSetRenderTargets(3, renderTargetViews, depthStencilView);
		for (int i = 0; i < 3; ++i)
			graphicsContext->immediateContext->ClearRenderTargetView(renderTargetViews[i], clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->RSSetState(rasterizerState);

		MyConstantBuffer cb;
		static float rot = 0;
		rot += dt;
		cb.view = PRMat::createLookAtLH(PRVec3(4, 16, -16), PRVec3(0, 0, 0), PRVec3(0, 1, 0));
		cb.proj = PRMat::createPerspectiveFieldOfViewLH(PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f);

		graphicsContext->immediateContext->VSSetShader(bunnyVertexShader, nullptr, 0);
		graphicsContext->immediateContext->VSSetConstantBuffers(0, 1, &bunnyConstantBuffer);
		graphicsContext->immediateContext->PSSetShader(bunnyPixelShader, nullptr, 0);

		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphicsContext->immediateContext->IASetInputLayout(bunnyInputLayout);
		unsigned stride = sizeof(PRVec3) * 2, offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &bunny, &stride, &offset);

		cb.world = PRMat::createRotationY(rot);
		graphicsContext->immediateContext->UpdateSubresource(bunnyConstantBuffer, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
		graphicsContext->immediateContext->Draw(bunnyVertexCount, 0);

		PRVec3 bunnyPositions[] = {
			{0, 0, 4}, {0, 0, -4}, {4, 0, 0}, {-4, 0, 0},
			{-4, 0, -4}, {-4, 0, 4}, {4, 0, -4}, {4, 0, 4},
			{0, 0, 8}, {0, 0, -8}, {8, 0, 0}, {-8, 0, 0},
			{-8, 0, -8}, {-8, 0, 8}, {8, 0, -8}, {8, 0, 8},
			{-4, 0, -8}, {-4, 0, 8}, {4, 0, -8}, {4, 0, 8},
			{-8, 0, -4}, {-8, 0, 4}, {8, 0, -4}, {8, 0, 4},
		};

		for (PRVec3 pos : bunnyPositions)
		{
			cb.world = PRMat::createTranslate(pos);
			graphicsContext->immediateContext->UpdateSubresource(bunnyConstantBuffer, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
			graphicsContext->immediateContext->Draw(bunnyVertexCount, 0);
		}

		graphicsContext->immediateContext->OMSetRenderTargets(1, &graphicsContext->renderTargetView, nullptr);
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);

		draw2DUtil->SetResolution(1280, 720);
		draw2DUtil->Ready(graphicsContext->immediateContext, deferredRenderingPixelShader);
		Lights lights = { 0, };
		lights.lightPos[0] = PRVec4(3, 3, 0, 2);
		lights.lightPos[1] = PRVec4(3, 3, 0, 1);
		lights.lightPos[2] = PRVec4(0, 3, -3, 1);
		lights.lightPos[3] = PRVec4(0, sin(rot) * 5 + 5, 0, 5);
		graphicsContext->immediateContext->UpdateSubresource(deferredRenderingLightsConstantBuffer, 0, nullptr, &lights, sizeof(Lights), 0);
		graphicsContext->immediateContext->PSSetConstantBuffers(0, 1, &deferredRenderingLightsConstantBuffer);
		draw2DUtil->Draw(graphicsContext->immediateContext, shaderResourceViews, _countof(shaderResourceViews), PRMat());
		draw2DUtil->Done(graphicsContext->immediateContext);

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
	int a = 5;
	const int b = 3;
	const int* c;
	c = &b;
	c = &a;

	int* const d = &a;
	*d = 5;

	const int* const e = &a;
	e = &b;
	*e = 3;
}