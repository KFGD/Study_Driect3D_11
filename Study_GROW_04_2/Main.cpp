#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"

struct MyConstantBuffer { PRMat world, view, proj; };

class MyScene : public PRGame {
public:
	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureSRV;
	ID3D11Buffer* constantBuffer;
	ID3D11SamplerState* samplerState;
	ID3D11RasterizerState* rasterizerState;

	ID3D11BlendState* alphaBlendState;
	ID3D11BlendState* additiveBlendState;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		PRModelGenerator rect(PRModelType_Rectangle, PRModelProperty_Position | PRModelProperty_TexCoord);
		D3D11_BUFFER_DESC vertexBufferDesc = { rect.getDataSize(), D3D11_USAGE_DEFAULT,
			D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
		D3D11_SUBRESOURCE_DATA vertexBufferInput = { rect.getData(), rect.getDataSize() };
		graphicsContext->d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferInput, &vertexBuffer);

		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		PRLoadShader(graphicsContext->d3dDevice, std::string("MyVertexShader.cso"), std::string("MyPixelShader.cso"),
			&vertexShader, &pixelShader, inputElements, _countof(inputElements), &inputLayout);

		texture = PRCreateTexture2D(graphicsContext->d3dDevice, std::string("test.jpg"));
		graphicsContext->d3dDevice->CreateShaderResourceView(texture, nullptr, &textureSRV);

		D3D11_SAMPLER_DESC samplerDesc;
		memset(&samplerDesc, 0, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		graphicsContext->d3dDevice->CreateSamplerState(&samplerDesc, &samplerState);

		constantBuffer = PRCreateConstantBuffer<MyConstantBuffer>(graphicsContext->d3dDevice);

		D3D11_RASTERIZER_DESC rasterizerDesc;
		memset(&rasterizerDesc, 0, sizeof(D3D11_RASTERIZER_DESC));
		rasterizerDesc.CullMode = D3D11_CULL_NONE;
		rasterizerDesc.FillMode = D3D11_FILL_SOLID;
		rasterizerDesc.DepthClipEnable = false;
		graphicsContext->d3dDevice->CreateRasterizerState(&rasterizerDesc, &rasterizerState);

		D3D11_BLEND_DESC blendDesc;
		memset(&blendDesc, 0, sizeof(D3D11_BLEND_DESC));
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		//blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_COLOR;	//Homework
		//blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_COLOR;	//Homework
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		graphicsContext->d3dDevice->CreateBlendState(&blendDesc, &alphaBlendState);

		memset(&blendDesc, 0, sizeof(D3D11_BLEND_DESC));
		blendDesc.RenderTarget[0].BlendEnable = true;
		blendDesc.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
		blendDesc.RenderTarget[0].DestBlend = D3D11_BLEND_ONE;
		blendDesc.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
		blendDesc.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
		blendDesc.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
		graphicsContext->d3dDevice->CreateBlendState(&blendDesc, &additiveBlendState);

}

	void onDestroy()
	{
		additiveBlendState->Release();
		alphaBlendState->Release();

		rasterizerState->Release();
		samplerState->Release();
		constantBuffer->Release();
		textureSRV->Release();
		texture->Release();
		pixelShader->Release();
		vertexShader->Release();
		inputLayout->Release();
		vertexBuffer->Release();
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);
		
		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->OMSetRenderTargets(1, &graphicsContext->renderTargetView, nullptr);
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->OMSetBlendState(alphaBlendState, nullptr, 0xffffffff);
		//graphicsContext->immediateContext->OMSetBlendState(additiveBlendState, nullptr, 0xffffffff);

		unsigned stride = sizeof(PRVec3) + sizeof(PRVec2), offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphicsContext->immediateContext->IASetInputLayout(inputLayout);

		graphicsContext->immediateContext->VSSetShader(vertexShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShader(pixelShader, nullptr, 0);

		graphicsContext->immediateContext->RSSetState(rasterizerState);

		MyConstantBuffer cb;
		PRMat::createTranslate(&PRVec3(-0.25f, 0, 0), &cb.world);
		PRMat::createLookAtLH(&PRVec3(0, 0, -2), &PRVec3(0, 0, 0), &PRVec3(0, 1, 0), &cb.view);
		PRMat::createPerspectiveFieldOfViewLH(PR_PIover4, 1280 / 720.0f, 0.001f, 1000.0f, &cb.proj);
		cb.world = cb.world.transpose();
		cb.view = cb.view.transpose();
		cb.proj = cb.proj.transpose();
		graphicsContext->immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);
		graphicsContext->immediateContext->VSSetConstantBuffers(0, 1, &constantBuffer);
		graphicsContext->immediateContext->PSSetShaderResources(0, 1, &textureSRV);
		graphicsContext->immediateContext->PSSetSamplers(0, 1, &samplerState);

		graphicsContext->immediateContext->Draw(6, 0);

		PRMat::createTranslate(&PRVec3(0.25f, 0, 0), &cb.world);
		cb.world = cb.world.transpose();
		graphicsContext->immediateContext->UpdateSubresource(constantBuffer, 0, nullptr, &cb, sizeof(MyConstantBuffer), 0);

		graphicsContext->immediateContext->Draw(6, 0);

		graphicsContext->dxgiSwapChain->Present(0, 0);
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