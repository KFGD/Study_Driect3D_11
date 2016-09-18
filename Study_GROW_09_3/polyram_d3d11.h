#ifndef __POLYRAM_D3D11_H__
#define __POLYRAM_D3D11_H__

#include "polyram.h"

#ifdef POLYRAM_D3D11

ID3D11Texture2D* PRCreateTexture2D(ID3D11Device * d3dDevice, DXGI_FORMAT format, unsigned width, unsigned height,
	UINT userBindFlags = 0) {
	UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
	if (userBindFlags != 0)
		bindFlags |= userBindFlags;
	else if (format == DXGI_FORMAT_D16_UNORM || format == DXGI_FORMAT_D24_UNORM_S8_UINT ||
		format == DXGI_FORMAT_D32_FLOAT || format == DXGI_FORMAT_D32_FLOAT_S8X24_UINT)
		bindFlags |= D3D11_BIND_DEPTH_STENCIL;
	else
		bindFlags |= D3D11_BIND_RENDER_TARGET;

	D3D11_TEXTURE2D_DESC desc = { 0, };
	desc.ArraySize = 1;
	desc.BindFlags = bindFlags;
	desc.Format = format;
	desc.Width = width;
	desc.Height = height;
	desc.Usage = D3D11_USAGE_DEFAULT;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;

	ID3D11Texture2D * texture2D = nullptr;
	d3dDevice->CreateTexture2D(&desc, nullptr, &texture2D);

	return texture2D;
}

ID3D11Texture2D* PRCreateTexture2D(ID3D11Device * d3dDevice, std::string & filename) {
	void * data;
	unsigned width, height;
	if (!PRGetImageData(filename, &data, &width, &height))
		return nullptr;

	D3D11_TEXTURE2D_DESC desc = { 0, };
	desc.ArraySize = 1;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	//desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA subresData = { data, width * sizeof(int), width * height * sizeof(int) };

	ID3D11Texture2D * texture2D = nullptr;
	d3dDevice->CreateTexture2D(&desc, &subresData, &texture2D);

	delete[] data;

	return texture2D;
}

bool PRLoadShader(ID3D11Device * d3dDevice, std::string & vertexShaderFilename, std::string & pixelShaderFilename,
	ID3D11VertexShader ** vertexShader, ID3D11PixelShader ** pixelShader,
	const D3D11_INPUT_ELEMENT_DESC * inputElements = nullptr, int inputElementSize = 0, ID3D11InputLayout ** inputLayout = nullptr) {
	void * data;
	unsigned dataSize;

	PRGetRawData(vertexShaderFilename, &data, &dataSize);
	if (FAILED(d3dDevice->CreateVertexShader(data, dataSize, nullptr, vertexShader))) {
		delete[] data;
		return false;
	}

	if (inputElements != nullptr) {
		if (FAILED(d3dDevice->CreateInputLayout(inputElements, inputElementSize, data, dataSize, inputLayout))) {
			(*vertexShader)->Release();
			delete[] data;
			return false;
		}
	}

	delete[] data;

	PRGetRawData(pixelShaderFilename, &data, &dataSize);
	if (FAILED(d3dDevice->CreatePixelShader(data, dataSize, nullptr, pixelShader))) {
		delete[] data;
		return false;
	}

	delete[] data;

	return true;
}

ID3D11VertexShader* PRLoadVertexShader(ID3D11Device * d3dDevice, std::string & shaderFilename)
{
	void * data;
	unsigned dataSize;

	ID3D11VertexShader* vertexShader;
	PRGetRawData(shaderFilename, &data, &dataSize);
	d3dDevice->CreateVertexShader(data, dataSize, nullptr, &vertexShader);
	delete[] data;

	return vertexShader;
}
ID3D11PixelShader* PRLoadPixelShader(ID3D11Device * d3dDevice, std::string & shaderFilename)
{
	void * data;
	unsigned dataSize;

	ID3D11PixelShader* pixelShader;
	PRGetRawData(shaderFilename, &data, &dataSize);
	d3dDevice->CreatePixelShader(data, dataSize, nullptr, &pixelShader);
	delete[] data;

	return pixelShader;
}
ID3D11GeometryShader* PRLoadGeometryShader(ID3D11Device * d3dDevice, std::string & shaderFilename)
{
	void * data;
	unsigned dataSize;

	ID3D11GeometryShader* geometryShader;
	PRGetRawData(shaderFilename, &data, &dataSize);
	d3dDevice->CreateGeometryShader(data, dataSize, nullptr, &geometryShader);
	delete[] data;

	return geometryShader;
}
ID3D11ComputeShader* PRLoadComputeShader(ID3D11Device * d3dDevice, std::string & shaderFilename)
{
	void * data;
	unsigned dataSize;

	ID3D11ComputeShader* computeShader;
	PRGetRawData(shaderFilename, &data, &dataSize);
	d3dDevice->CreateComputeShader(data, dataSize, nullptr, &computeShader);
	delete[] data;

	return computeShader;
}

ID3D11Buffer* PRCreateVertexBuffer(ID3D11Device * d3dDevice, const void * data, unsigned dataSize) {
	D3D11_BUFFER_DESC vertexBufferDesc = { dataSize, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { data, dataSize };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferInput, &buffer);

	return buffer;
}

ID3D11Buffer* PRCreateVertexBuffer(ID3D11Device * d3dDevice, const PRModelGenerator * gen) {
	D3D11_BUFFER_DESC vertexBufferDesc = { gen->getDataSize(), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { gen->getData(), gen->getDataSize() };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferInput, &buffer);

	return buffer;
}

ID3D11Buffer* PRCreateIndexBuffer(ID3D11Device * d3dDevice, const void * data, unsigned dataSize) {
	D3D11_BUFFER_DESC vertexBufferDesc = { dataSize, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { data, dataSize };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer(&vertexBufferDesc, &vertexBufferInput, &buffer);

	return buffer;
}

template<typename T>
ID3D11Buffer* PRCreateConstantBuffer(ID3D11Device * d3dDevice, bool allowDeferred = false) {
	D3D11_BUFFER_DESC desc = { 0, };
	desc.ByteWidth = sizeof(T);
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if (allowDeferred)
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer(&desc, nullptr, &buffer);

	return buffer;
}

ID3D11Buffer* PRCreateVertexBufferFor2D(ID3D11Device * d3dDevice, unsigned width, unsigned height) {
	struct { PRVec3 pos; PRVec2 tex; } vertices[] = {
		{ { 0, (float)height, 0 },{ 0, 1 } },
		{ { (float)width, (float)height, 0 },{ 1, 1 } },
		{ { 0, 0, 0 },{ 0, 0 } },
		{ { 0, 0, 0 },{ 0, 0 } },
		{ { (float)width, (float)height, 0 },{ 1, 1 } },
		{ { (float)width, 0, 0 },{ 1, 0 } },
	};
	return PRCreateVertexBuffer(d3dDevice, vertices, sizeof(vertices));
}

#if !PRPlatformMicrosoftWindowsRT
#include <d3dcompiler.h>
#pragma comment ( lib, "d3dcompiler.lib" )
bool PRCreateShadersFor2D(ID3D11Device * d3dDevice, ID3D11VertexShader ** vertexShader, ID3D11PixelShader ** pixelShader,
	ID3D11InputLayout ** inputLayout) {

	const char * shaderText = SHADERT(
#pragma pack_matrix(row_major)\n

		struct VERTEX_IN {
		float3 position : POSITION;
		float2 texcoord : TEXCOORD;
	};

	struct PIXEL_IN {
		float4 position : SV_POSITION;
		float2 texcoord : TEXCOOORD;
	};

	cbuffer WorldProjection{
		float4x4 world : WORLD;
	float4x4 proj : PROJECTION;
	};

	PIXEL_IN vs_main(VERTEX_IN input) {
		PIXEL_IN ret;
		ret.position = float4(input.position, 1);
		ret.position = mul(ret.position, world);
		ret.position = mul(ret.position, proj);
		ret.texcoord = input.texcoord;
		return ret;
	}

	Texture2D texture_input;
	SamplerState sampler_input;

	float4 ps_main(PIXEL_IN input) : SV_TARGET{
		return texture_input.Sample(sampler_input, input.texcoord);
	}
	);

	ID3DBlob * compiledVertexShader, *compiledPixelShader, *errorMsg;
	D3DCompile(shaderText, strlen(shaderText), nullptr, nullptr, nullptr, "vs_main", "vs_5_0", 0, 0, &compiledVertexShader, &errorMsg);
	D3DCompile(shaderText, strlen(shaderText), nullptr, nullptr, nullptr, "ps_main", "ps_5_0", 0, 0, &compiledPixelShader, nullptr);

	D3D11_INPUT_ELEMENT_DESC inputElements[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	if (FAILED(d3dDevice->CreateVertexShader(compiledVertexShader->GetBufferPointer(), compiledVertexShader->GetBufferSize(),
		nullptr, vertexShader))) {
		compiledPixelShader->Release();
		compiledVertexShader->Release();
		return false;
	}

	if (inputElements != nullptr) {
		if (FAILED(d3dDevice->CreateInputLayout(inputElements, _countof(inputElements),
			compiledVertexShader->GetBufferPointer(), compiledVertexShader->GetBufferSize(), inputLayout))) {
			(*vertexShader)->Release();
			compiledPixelShader->Release();
			compiledVertexShader->Release();
			return false;
		}
	}

	compiledVertexShader->Release();

	if (FAILED(d3dDevice->CreatePixelShader(compiledPixelShader->GetBufferPointer(), compiledPixelShader->GetBufferSize(),
		nullptr, pixelShader))) {
		(*vertexShader)->Release();
		(*inputLayout)->Release();
		compiledPixelShader->Release();
		return false;
	}

	compiledPixelShader->Release();

	return true;
}
#endif

class PRDraw2DUtility
{
private:
	ID3D11Buffer * vertexBuffer;
	ID3D11Buffer * constantBuffer;

	ID3D11VertexShader * vertexShader;
	ID3D11PixelShader * pixelShader;
	ID3D11InputLayout * inputLayout;

	ID3D11SamplerState * samplerState;

	unsigned width, height;

	struct WorldProjection { PRMat world, proj; };

public:
	PRDraw2DUtility(ID3D11Device * d3dDevice, bool allowDeferredContext = false) {
		PRCreateShadersFor2D(d3dDevice, &vertexShader, &pixelShader, &inputLayout);
		vertexBuffer = PRCreateVertexBufferFor2D(d3dDevice, 1, 1);
		constantBuffer = PRCreateConstantBuffer<WorldProjection>(d3dDevice, allowDeferredContext);

		D3D11_SAMPLER_DESC samplerDesc;
		memset(&samplerDesc, 0, sizeof(D3D11_SAMPLER_DESC));
		samplerDesc.AddressU = samplerDesc.AddressV = samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
		samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		samplerDesc.MinLOD = -FLT_MAX;
		samplerDesc.MaxLOD = FLT_MAX;
		samplerDesc.MaxAnisotropy = 1;
		samplerDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
		d3dDevice->CreateSamplerState(&samplerDesc, &samplerState);
	}

	~PRDraw2DUtility() {
		SAFE_RELEASE(samplerState);

		SAFE_RELEASE(inputLayout);
		SAFE_RELEASE(pixelShader);
		SAFE_RELEASE(vertexShader);

		SAFE_RELEASE(constantBuffer);
		SAFE_RELEASE(vertexBuffer);
	}

public:
	void SetResolution(unsigned width, unsigned height) { this->width = width; this->height = height; }

	void Ready(ID3D11DeviceContext * deviceContext, ID3D11PixelShader * customPixelShader = nullptr) {
		deviceContext->VSSetShader(vertexShader, nullptr, 0);
		deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
		deviceContext->PSSetShader(customPixelShader ? customPixelShader : pixelShader, nullptr, 0);
		deviceContext->PSSetSamplers(0, 1, &samplerState);

		deviceContext->IASetInputLayout(inputLayout);
		deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
		unsigned stride = sizeof(PRVec3) + sizeof(PRVec2), offset = 0;
		deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	}

	void Draw(ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView * srv, PRMat & world) {
		WorldProjection wp;
		PRMat::createScale(&PRVec3(width, height, 1), &wp.world);
		PRMat::multiply(&wp.world, &world, &wp.world);
		PRMat::createOrthographicOffCenterLH(0, width, height, 0, 0.001f, 1000.0f, &wp.proj);
		deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &wp, sizeof(WorldProjection), 0);

		deviceContext->PSSetShaderResources(0, 1, &srv);

		deviceContext->Draw(6, 0);
	}

	void Draw(ID3D11DeviceContext * deviceContext, ID3D11ShaderResourceView ** srv, unsigned count, PRMat & world) {
		WorldProjection wp;
		PRMat::createScale(&PRVec3(width, height, 1), &wp.world);
		PRMat::multiply(&wp.world, &world, &wp.world);
		PRMat::createOrthographicOffCenterLH(0, width, height, 0, 0.001f, 1000.0f, &wp.proj);
		deviceContext->UpdateSubresource(constantBuffer, 0, nullptr, &wp, sizeof(WorldProjection), 0);

		deviceContext->PSSetShaderResources(0, count, srv);

		deviceContext->Draw(6, 0);
	}

	void Done(ID3D11DeviceContext * deviceContext) {
		ID3D11Buffer * cbuff = nullptr;
		ID3D11SamplerState * ss = nullptr;
		ID3D11ShaderResourceView * srv[] = { nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr, nullptr };
		deviceContext->VSSetConstantBuffers(0, 1, &cbuff);
		deviceContext->PSSetSamplers(0, 1, &ss);
		deviceContext->PSSetShaderResources(0, 8, srv);
	}
};

#endif

#endif