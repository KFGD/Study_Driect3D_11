#ifndef __POLYRAM_D3D11_H__
#define __POLYRAM_D3D11_H__

#include "polyram.h"

ID3D11Texture2D* PRCreateTexture2D ( ID3D11Device * d3dDevice, DXGI_FORMAT format, unsigned width, unsigned height ) {
	UINT bindFlags = D3D11_BIND_SHADER_RESOURCE;
	if ( format == DXGI_FORMAT_D16_UNORM || format == DXGI_FORMAT_D24_UNORM_S8_UINT ||
		format == DXGI_FORMAT_D32_FLOAT || format == DXGI_FORMAT_D32_FLOAT_S8X24_UINT )
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
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.MipLevels = 1;
	desc.SampleDesc.Count = 1;
	
	ID3D11Texture2D * texture2D = nullptr;
	d3dDevice->CreateTexture2D ( &desc, nullptr, &texture2D );
	
	return texture2D;
}

ID3D11Texture2D* PRCreateTexture2D ( ID3D11Device * d3dDevice, std::string & filename ) {
	void * data;
	unsigned width, height;
	if ( !PRGetImageData ( filename, &data, &width, &height ) )
		return nullptr;

	D3D11_TEXTURE2D_DESC desc = { 0, };
	desc.ArraySize = 1;
	desc.Width = width;
	desc.Height = height;
	desc.MipLevels = 1;
	desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	desc.SampleDesc.Count = 1;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;

	D3D11_SUBRESOURCE_DATA subresData = { data, width * sizeof ( int ), width * height * sizeof ( int ) };

	ID3D11Texture2D * texture2D = nullptr;
	d3dDevice->CreateTexture2D ( &desc, &subresData, &texture2D );

	delete [] data;

	return texture2D;
}

bool PRLoadShader ( ID3D11Device * d3dDevice, std::string & vertexShaderFilename, std::string & pixelShaderFilename,
	ID3D11VertexShader ** vertexShader, ID3D11PixelShader ** pixelShader,
	const D3D11_INPUT_ELEMENT_DESC * inputElements = nullptr, int inputElementSize = 0, ID3D11InputLayout ** inputLayout = nullptr ) {
	void * data;
	unsigned dataSize;

	PRGetRawData ( vertexShaderFilename, &data, &dataSize );
	if ( FAILED ( d3dDevice->CreateVertexShader ( data, dataSize, nullptr, vertexShader ) ) ) {
		delete [] data;
		return false;
	}

	if ( inputElements != nullptr ) {
		if ( FAILED ( d3dDevice->CreateInputLayout ( inputElements, inputElementSize, data, dataSize, inputLayout ) ) ) {
			( *vertexShader )->Release ();
			delete [] data;
			return false;
		}
	}

	delete [] data;

	PRGetRawData ( pixelShaderFilename, &data, &dataSize );
	if ( FAILED ( d3dDevice->CreatePixelShader ( data, dataSize, nullptr, pixelShader ) ) ) {
		delete [] data;
		return false;
	}

	delete [] data;

	return true;
}

ID3D11VertexShader* PRLoadVertexShader ( ID3D11Device * d3dDevice, std::string & shaderFilename )
{
	void * data;
	unsigned dataSize;

	ID3D11VertexShader* vertexShader;
	PRGetRawData ( shaderFilename, &data, &dataSize );
	d3dDevice->CreateVertexShader ( data, dataSize, nullptr, &vertexShader );
	delete [] data;
	
	return vertexShader;
}
ID3D11PixelShader* PRLoadPixelShader ( ID3D11Device * d3dDevice, std::string & shaderFilename )
{
	void * data;
	unsigned dataSize;

	ID3D11PixelShader* pixelShader;
	PRGetRawData ( shaderFilename, &data, &dataSize );
	d3dDevice->CreatePixelShader ( data, dataSize, nullptr, &pixelShader );
	delete [] data;

	return pixelShader;
}
ID3D11GeometryShader* PRLoadGeometryShader ( ID3D11Device * d3dDevice, std::string & shaderFilename )
{
	void * data;
	unsigned dataSize;

	ID3D11GeometryShader* geometryShader;
	PRGetRawData ( shaderFilename, &data, &dataSize );
	d3dDevice->CreateGeometryShader ( data, dataSize, nullptr, &geometryShader );
	delete [] data;

	return geometryShader;
}
ID3D11ComputeShader* PRLoadComputeShader ( ID3D11Device * d3dDevice, std::string & shaderFilename )
{
	void * data;
	unsigned dataSize;

	ID3D11ComputeShader* computeShader;
	PRGetRawData ( shaderFilename, &data, &dataSize );
	d3dDevice->CreateComputeShader ( data, dataSize, nullptr, &computeShader );
	delete [] data;

	return computeShader;
}

ID3D11Buffer* PRCreateVertexBuffer ( ID3D11Device * d3dDevice, const void * data, unsigned dataSize ) {
	D3D11_BUFFER_DESC vertexBufferDesc = { dataSize, D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { data, dataSize };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer ( &vertexBufferDesc, &vertexBufferInput, &buffer );
	
	return buffer;
}

ID3D11Buffer* PRCreateVertexBuffer ( ID3D11Device * d3dDevice, const PRModelGenerator * gen ) {
	D3D11_BUFFER_DESC vertexBufferDesc = { gen->getDataSize (), D3D11_USAGE_DEFAULT, D3D11_BIND_VERTEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { gen->getData (), gen->getDataSize () };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer ( &vertexBufferDesc, &vertexBufferInput, &buffer );

	return buffer;
}

ID3D11Buffer* PRCreateIndexBuffer ( ID3D11Device * d3dDevice, const void * data, unsigned dataSize ) {
	D3D11_BUFFER_DESC vertexBufferDesc = { dataSize, D3D11_USAGE_DEFAULT, D3D11_BIND_INDEX_BUFFER, 0, 0, 0 };
	D3D11_SUBRESOURCE_DATA vertexBufferInput = { data, dataSize };

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer ( &vertexBufferDesc, &vertexBufferInput, &buffer );

	return buffer;
}

template<typename T>
ID3D11Buffer* PRCreateConstantBuffer ( ID3D11Device * d3dDevice, bool allowDeferred = false ) {
	D3D11_BUFFER_DESC desc = { 0, };
	desc.ByteWidth = sizeof ( T );
	desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	if ( allowDeferred )
	{
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	}

	ID3D11Buffer * buffer;
	d3dDevice->CreateBuffer ( &desc, nullptr, &buffer );

	return buffer;
}

#endif