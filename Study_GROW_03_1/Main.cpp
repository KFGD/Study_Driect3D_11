#define POLYRAM_D3D11
#include "polyram.h"

class MyScene : public PRGame {
public:
	ID3D11Buffer* vertexBuffer;
	ID3D11InputLayout* inputLayout;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	ID3D11Texture2D* texture;
	ID3D11ShaderResourceView* textureSRV;

	ID3D11SamplerState* samplerState;

	//Homework
	//ID3D11Buffer* constantPixelBuffer;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		PRModelGenerator rect(PRModelType_Rectangle, PRModelProperty_Position | PRModelProperty_TexCoord);
		D3D11_BUFFER_DESC vertexBufferDesc = { rect.getDataSize(), D3D11_USAGE_DEFAULT,
			D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
		D3D11_SUBRESOURCE_DATA vertexBufferInput = { rect.getData(), rect.getDataSize() };
		graphicsContext->d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferInput, &vertexBuffer);

		void* shaderData;
		unsigned shaderDataLength;
		PRGetRawData(std::string("MyVertexShader.cso"), &shaderData, &shaderDataLength);
		graphicsContext->d3dDevice->CreateVertexShader(shaderData, shaderDataLength, nullptr, &vertexShader);
		D3D11_INPUT_ELEMENT_DESC inputElements[] = {
			{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
			{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
		};
		graphicsContext->d3dDevice->CreateInputLayout(inputElements, _countof(inputElements),
			shaderData, shaderDataLength, &inputLayout);
		SAFE_DELETE(shaderData);

		PRGetRawData(std::string("MyPixelShader.cso"), &shaderData, &shaderDataLength);
		graphicsContext->d3dDevice->CreatePixelShader(shaderData, shaderDataLength, nullptr, &pixelShader);
		SAFE_DELETE(shaderData);

		void* textureData;
		unsigned textureWidth, textureHeight;
		PRGetImageData(std::string("test.jpg"), &textureData, &textureWidth, &textureHeight);
		D3D11_TEXTURE2D_DESC textureDesc = { 0, };
		textureDesc.ArraySize = 1;
		textureDesc.Width = textureWidth;
		textureDesc.Height = textureHeight;
		textureDesc.MipLevels = 1;
		textureDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		textureDesc.SampleDesc.Count = 1;
		//textureDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		textureDesc.Usage = D3D11_USAGE_DEFAULT;
		textureDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

		D3D11_SUBRESOURCE_DATA textureInput = {
			textureData,
			textureWidth * sizeof(int),
			textureWidth * textureHeight * sizeof(int)
		};
		graphicsContext->d3dDevice->CreateTexture2D(&textureDesc, &textureInput, &texture);

		graphicsContext->d3dDevice->CreateShaderResourceView(texture, nullptr, &textureSRV);

		delete[] textureData;

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

		//Homework
		/*D3D11_BUFFER_DESC constantPixelBufferDesc = { sizeof(float) * 4 , D3D11_USAGE_DEFAULT,
			D3D11_BIND_CONSTANT_BUFFER, 0, 0, 0 };
		graphicsContext->d3dDevice->CreateBuffer(&constantPixelBufferDesc, nullptr, &constantPixelBuffer);*/
	}

	void onDestroy()
	{
		samplerState->Release();
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
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

		graphicsContext->immediateContext->VSSetShader(vertexShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShader(pixelShader, nullptr, 0);
		graphicsContext->immediateContext->PSSetShaderResources(0, 1, &textureSRV);
		graphicsContext->immediateContext->PSSetSamplers(0, 1, &samplerState);

		unsigned stride = sizeof(PRVec3) + sizeof(PRVec2), offset = 0;
		graphicsContext->immediateContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
		graphicsContext->immediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		graphicsContext->immediateContext->IASetInputLayout(inputLayout);

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