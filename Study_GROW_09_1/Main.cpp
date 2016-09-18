#define POLYRAM_D3D11
#define _CRT_SECURE_NO_WARNINGS
#include "polyram.h"
#include "polyram_d3d11.h"
#include <ctime>

class MyScene : public PRGame
{
public:
	ID3D11Buffer *buffer1, *buffer2;
	ID3D11ShaderResourceView *textureSRV;
	ID3D11UnorderedAccessView *textureUAV;
	ID3D11ComputeShader *computeShader;

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

#define BUFFER_SIZE		65535

		D3D11_BUFFER_DESC bufferDesc = { 0, };
		bufferDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_UNORDERED_ACCESS;
		bufferDesc.Usage = D3D11_USAGE_DEFAULT;
		bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_READ | D3D11_CPU_ACCESS_WRITE;
		bufferDesc.ByteWidth = sizeof(float) * BUFFER_SIZE;
		bufferDesc.StructureByteStride = sizeof(float);
		bufferDesc.MiscFlags = D3D11_RESOURCE_MISC_BUFFER_STRUCTURED;
		graphicsContext->d3dDevice->CreateBuffer(&bufferDesc, nullptr, &buffer2);
		float *ti = new float[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			ti[i] = i + 1;
		D3D11_SUBRESOURCE_DATA initialData = { ti, BUFFER_SIZE * sizeof(float), 0 };
		graphicsContext->d3dDevice->CreateBuffer(&bufferDesc, &initialData, &buffer1);
		delete[] ti;

		D3D11_SHADER_RESOURCE_VIEW_DESC srvDesc;
		memset(&srvDesc, 0, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
		srvDesc.Buffer.NumElements = 1;
		srvDesc.Buffer.ElementWidth = BUFFER_SIZE;
		srvDesc.ViewDimension = D3D11_SRV_DIMENSION_BUFFER;
		graphicsContext->d3dDevice->CreateShaderResourceView(buffer1, &srvDesc, &textureSRV);

		D3D11_UNORDERED_ACCESS_VIEW_DESC uavDesc;
		memset(&uavDesc, 0, sizeof(D3D11_UNORDERED_ACCESS_VIEW_DESC));
		uavDesc.Buffer.NumElements = BUFFER_SIZE;
		uavDesc.ViewDimension = D3D11_UAV_DIMENSION_BUFFER;
		uavDesc.Buffer.Flags =
			graphicsContext->d3dDevice->CreateUnorderedAccessView(buffer2, &uavDesc, &textureUAV);

		computeShader = PRLoadComputeShader(graphicsContext->d3dDevice, std::string("MyComputeShader.cso"));

		graphicsContext->immediateContext->CSSetShader(computeShader, nullptr, 0);
		graphicsContext->immediateContext->CSSetShaderResources(0, 1, &textureSRV);
		graphicsContext->immediateContext->CSSetUnorderedAccessViews(0, 1, &textureUAV, nullptr);

#define LOOPCOUNT	60000
		
		clock_t begin = clock();
		for (int i = 0; i < LOOPCOUNT; ++i)
			graphicsContext->immediateContext->Dispatch(BUFFER_SIZE, 1, 1);
		clock_t end = clock();

		FILE *fp = fopen("GPU_Proceed.txt", "wt");
		fprintf(fp, "Compute Shader Running time: %ds\n", (end - begin) / CLOCKS_PER_SEC);
		D3D11_MAPPED_SUBRESOURCE mappedResource;
		graphicsContext->immediateContext->Map(buffer2, 0, D3D11_MAP_READ, 0, &mappedResource);
		float *b = (float*)mappedResource.pData;

		for (int i = 0; i < BUFFER_SIZE; ++i)
			fprintf(fp, "sqrt(%f) = %f\n", (float)(i + 1), b[i]);

		graphicsContext->immediateContext->Unmap(buffer2, 0);
		fclose(fp);

		//////////////////////////////////////////////

		float *cputest = new float[BUFFER_SIZE], *cputest2 = new float[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			cputest[i] = i + 1;

		begin = clock();
		for (int i = 0; i < LOOPCOUNT; ++i)
		{
//#pragma omp parallel for
			for (int j = 0; j < BUFFER_SIZE; ++j)
				cputest2[j] = sqrt(cputest[j]);
		}
		end = clock();

		fp = fopen("CPU_Proceed.txt", "wt");
		fprintf(fp, "CPU Running time: %ds\n", (end - begin) / CLOCKS_PER_SEC);

		for (int i = 0; i < BUFFER_SIZE; ++i)
			fprintf(fp, "sqrt(%f) = %f\n", (float)(i + 1), cputest2[i]);

		delete[] cputest2;
		delete[] cputest;

		fclose(fp);

		PostQuitMessage(0);
	}

	void onDestroy()
	{
		computeShader->Release();
		textureUAV->Release();
		textureSRV->Release();
		buffer2->Release();
		buffer1->Release();
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

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