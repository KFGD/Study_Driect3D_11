#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"
#include "Camera3D.h"
#include<Xinput.h>

#pragma comment(lib, "XInput.lib")

struct MyConstantBuffer { PRMat world, view, proj; };

class MyScene : public PRGame {
public:
	ID3D11Buffer *sphereVB, *rectVB;
	int sphereVBSize, rectVBSize;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Buffer *vertexCB, *pixelCB;
	ID3D11DepthStencilState *standardDSS, *stencilDSS1, *stencilDSS2;
	ID3D11RasterizerState *rasterizerState;

	Camera3D camera;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);


		camera.setPos(PRVec3(-1, 0, 2));

		PRModelGenerator sphere(PRModelType_Sphere, PRModelProperty_Position);
		sphereVB = PRCreateVertexBuffer(graphicsContext->d3dDevice, sphere.getData(), sphere.getDataSize());
		sphereVBSize = sphere.getDataSize() / sizeof(PRVec3);

		PRModelGenerator rect(PRModelType_Rectangle, PRModelProperty_Position);
		rectVB = PRCreateVertexBuffer(graphicsContext->d3dDevice, rect.getData(), rect.getDataSize());
		rectVBSize = rect.getDataSize() / sizeof(PRVec3);

		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};

		PRLoadShader(graphicsContext->d3dDevice, std::string("MyVertexShader.cso"), std::string("MyPixelShader.cso"),
			&vertexShader, &pixelShader, inputElements, _countof(inputElements), &inputLayout);

		vertexCB = PRCreateConstantBuffer<MyConstantBuffer>(graphicsContext->d3dDevice);
		pixelCB = PRCreateConstantBuffer<PRVec4>(graphicsContext->d3dDevice);

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.DepthClipEnable = false;
		graphicsContext->d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

		D3D11_DEPTH_STENCIL_DESC dsDesc = { 0, };
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		graphicsContext->d3dDevice->CreateDepthStencilState(&dsDesc, &standardDSS);

		memset(&dsDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsDesc.DepthEnable = true;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = true;
		dsDesc.StencilReadMask = 0xffffffff;
		dsDesc.StencilWriteMask = 0xffffffff;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_ALWAYS;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_REPLACE;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		memcpy(&dsDesc.BackFace, &dsDesc.FrontFace, sizeof(D3D11_DEPTH_STENCILOP_DESC));
		graphicsContext->d3dDevice->CreateDepthStencilState(&dsDesc, &stencilDSS1);

		memset(&dsDesc, 0, sizeof(D3D11_DEPTH_STENCIL_DESC));
		dsDesc.DepthEnable = false;
		dsDesc.DepthFunc = D3D11_COMPARISON_LESS_EQUAL;
		dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
		dsDesc.StencilEnable = true;
		dsDesc.StencilReadMask = 0xffffffff;
		dsDesc.StencilWriteMask = 0xffffffff;
		dsDesc.FrontFace.StencilFunc = D3D11_COMPARISON_EQUAL;
		dsDesc.FrontFace.StencilPassOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilFailOp = D3D11_STENCIL_OP_KEEP;
		dsDesc.FrontFace.StencilDepthFailOp = D3D11_STENCIL_OP_KEEP;
		memcpy(&dsDesc.BackFace, &dsDesc.FrontFace, sizeof(D3D11_DEPTH_STENCILOP_DESC));
		graphicsContext->d3dDevice->CreateDepthStencilState(&dsDesc, &stencilDSS2);
		
}

	void onDestroy()
	{
		stencilDSS2->Release();
		stencilDSS1->Release();
		standardDSS->Release();
		rasterizerState->Release();
		pixelCB->Release();
		vertexCB->Release();
		pixelShader->Release();
		vertexShader->Release();
		inputLayout->Release();
		sphereVB->Release();
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);
		
		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->VSSetShader(vertexShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShader(pixelShader, nullptr, 0);

		graphicsContext->immediateContext->RSSetState(rasterizerState);

		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphicsContext->immediateContext->IASetInputLayout(inputLayout);

		MyConstantBuffer cb;
		PRMat::createTranslate(&PRVec3(-0.5f, 0, 0), &cb.world);
		//PRMat::createLookAtLH(&PRVec3(-2, 2, -2), &PRVec3(0, 0, 0), &PRVec3(0, 1, 0), &cb.view);
		camera.getMatrix(&cb.view);
		PRMat::createPerspectiveFieldOfViewLH(PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb.proj);
		graphicsContext->immediateContext->UpdateSubresource(vertexCB, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
		graphicsContext->immediateContext->VSSetConstantBuffers(0, 1, &vertexCB);
		graphicsContext->immediateContext->UpdateSubresource(pixelCB, 0, nullptr, &PRVec4(1, 0, 1, 1), sizeof(PRVec4), 0);
		graphicsContext->immediateContext->PSSetConstantBuffers(0, 1, &pixelCB);

		unsigned stride = sizeof(PRVec3), offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &sphereVB, &stride, &offset);

		graphicsContext->immediateContext->OMSetDepthStencilState(standardDSS, 0x1);
		graphicsContext->immediateContext->Draw(sphereVBSize, 0);

		PRMat::createRotationY(PRToRadian(90), &cb.world);
		graphicsContext->immediateContext->UpdateSubresource(vertexCB, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
		graphicsContext->immediateContext->UpdateSubresource(pixelCB, 0, nullptr, &PRVec4(0.7f, 0.7f, 0.7f, 1), sizeof(PRVec4), 0);

		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &rectVB, &stride, &offset);

		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_STENCIL, 1, 0);
		graphicsContext->immediateContext->OMSetDepthStencilState(stencilDSS1, 0x1);
		graphicsContext->immediateContext->Draw(rectVBSize, 0);

		PRMat::createTranslate(&PRVec3(0.5f, 0, 0), &cb.world);
		graphicsContext->immediateContext->UpdateSubresource(vertexCB, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
		graphicsContext->immediateContext->UpdateSubresource(pixelCB, 0, nullptr, &PRVec4(1, 1, 1, 1), sizeof(PRVec4), 0);

		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &sphereVB, &stride, &offset);
		graphicsContext->immediateContext->OMSetDepthStencilState(stencilDSS2, 0x1);
		graphicsContext->immediateContext->Draw(sphereVBSize, 0);

		graphicsContext->dxgiSwapChain->Present(0, 0);
	}

	void onUpdate(double dt)
	{
		XINPUT_STATE xinputState;
		if (ERROR_SUCCESS == XInputGetState(0, &xinputState))
		{

			static int jumpState = -1;

			float lX = xinputState.Gamepad.sThumbLX / 32767.f;
			float lY = xinputState.Gamepad.sThumbLY / 32767.f;
			lX = (abs(lX) < 0.5f ? 0 : lX) * dt;
			lY = (abs(lY) < 0.5f ? 0 : lY) * dt;

			camera.walk(-lY);
			camera.strafe(-lX);

			float rX = xinputState.Gamepad.sThumbRX / 32767.f;
			float rY = xinputState.Gamepad.sThumbRY / 32767.f;
			rX = (abs(rX) < 0.5f ? 0 : rX) * dt;
			rY = (abs(rY) < 0.5f ? 0 : rY) * dt;

			camera.setYaw(rX);
			camera.setPitch(rY);

			//Homework
			if (xinputState.Gamepad.wButtons & 0x1000)
			{
				float posY = camera.getPos().y;
				
				//Jump는 y값이 0이하일때만 가능
				if (posY <= 0.0f)
				{
					jumpState = 1;
				}
			}

			//Jump상태이면 0.001씩 상승
			if (jumpState == 1)
			{
				camera.fly(0.001f);
			}
			else if (jumpState == 0)
			{
				camera.fly(-0.001f);
			}

			//Jump가 최대 위치에 도달시, jumpState를 0으로 바꿈
			if (jumpState == 1 && camera.getPos().y >= 0.5f)
			{
				jumpState = 0;
			}
			else if (jumpState == 0 && camera.getPos().y <= 0.0f)
			{
				jumpState = -1;
			}

		}
	}
};

MAIN_FUNC_ATTR
MAIN_FUNC_RTTP MAIN_FUNC_NAME (MAIN_FUNC_ARGS)
{
	try {
		MyScene scene;
		std::string title("TEST");
		PRApp app(&scene, PRRendererType_Direct3D11, 1200, 720, title);
		app.run();
	}
	catch (std::exception& ex) {
		PRLog(ex.what());
	}
}