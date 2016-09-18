#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"
#include <vector>
#include <thread>
#include <atomic>
#pragma comment(lib, "winmm.lib")

struct MyConstantBuffer { PRMat world, view, proj; PRVec4 col; };

class MyScene : public PRGame
{
public:
	ID3D11Buffer* sphereVB;
	int sphereVBSize;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer* vertexCB;
	ID3D11RasterizerState* rasterizerState;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		PRModelGenerator sphere(PRModelType_Sphere, PRModelProperty_Position);
		sphereVB = PRCreateVertexBuffer(graphicsContext->d3dDevice, sphere.getData(), sphere.getDataSize());
		sphereVBSize = sphere.getDataSize() / sizeof(PRVec3);

		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		PRLoadShader(graphicsContext->d3dDevice, std::string("MyVertexShader.cso"), std::string("MyPixelShader.cso"),
			&vertexShader, &pixelShader, inputElements, _countof(inputElements), &inputLayout);

		vertexCB = PRCreateConstantBuffer<MyConstantBuffer>(graphicsContext->d3dDevice, true);

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
		sphereVB->Release();
	}

	void onDraw(double dt)
	{
		static int count = 0;
		count += 8;

		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		std::atomic<unsigned> drawCount = 0;

		ID3D11CommandList* commandLists[8] = { 0, };
		/*std::thread independentThread([&]()
		{*/
#pragma omp parallel for num_threads(8)
			for (int i = 0; i < 8; ++i)
			{
				srand(timeGetTime());

				ID3D11DeviceContext* deferredContext;
				graphicsContext->d3dDevice->CreateDeferredContext(0, &deferredContext);

				deferredContext->OMSetRenderTargets(1, &graphicsContext->renderTargetView, graphicsContext->depthStencilView);

				D3D11_VIEWPORT viewport = { 0, };
				viewport.Width = 1280;
				viewport.Height = 720;
				viewport.MaxDepth = 1;
				deferredContext->RSSetViewports(1, &viewport);

				deferredContext->VSSetShader(vertexShader, nullptr, 0);
				deferredContext->PSSetShader(pixelShader, nullptr, 0);

				deferredContext->VSSetConstantBuffers(0, 1, &vertexCB);

				deferredContext->RSSetState(rasterizerState);

				unsigned stride = sizeof(PRVec3), offset = 0;
				deferredContext->IASetVertexBuffers(0, 1, &sphereVB, &stride, &offset);
				deferredContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
				deferredContext->IASetInputLayout(inputLayout);

				for (int j = 0; j </*2000*/count / 8; ++j)
				{
					D3D11_MAPPED_SUBRESOURCE mappedResource;
					deferredContext->Map(vertexCB, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
					MyConstantBuffer* cb = (MyConstantBuffer*)mappedResource.pData;
					PRVec3 translate((rand() % 100 - 50), (rand() % 100 - 50), (rand() % 100 - 50));
					PRMat::createTranslate(&translate, &cb->world);
					PRMat::createLookAtLH(&PRVec3(0, 100, 100), &PRVec3(0, 0, 0), &PRVec3(0, 1, 0), &cb->view);
					PRMat::createPerspectiveFieldOfViewLH(PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb->proj);
					cb->col = PRVec4((rand() % 255) / 255.f, (rand() % 255) / 255.f, (rand() % 255) / 255.f, 1);
					deferredContext->Unmap(vertexCB, 0);
					deferredContext->VSSetConstantBuffers(0, 1, &vertexCB);

					deferredContext->Draw(sphereVBSize, 0);

					++drawCount;

				}

				ID3D11CommandList* commandList;
				deferredContext->FinishCommandList(false, &commandList);
				commandLists[i] = commandList;

				deferredContext->Release();

			}
		/*});
		independentThread.join();*/

		for (int i = 0; i < 8; ++i)
			graphicsContext->immediateContext->ExecuteCommandList(commandLists[i], false);

		graphicsContext->dxgiSwapChain->Present(1, 0);

		for (int i = 0; i < 8; ++i)
			commandLists[i]->Release();

		//PRLog("Drawn Count: %d", drawCount);
	}

	void onUpdate(double dt)
	{
		static double total = 0;
		static int fr = 0;
		total += dt;
		++fr;
		if (total >= 1) {
			--total;
			PRLog("FPS: %lf", fr + (fr*total));
			fr = 0;
		}
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
	catch (std::exception& ex) {
		PRLog(ex.what());
	}
}