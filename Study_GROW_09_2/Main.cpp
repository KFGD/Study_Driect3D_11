#define POLYRAM_D3D11
#define _CRT_SECURE_NO_WARNINGS
#include "polyram.h"
#include "polyram_d3d11.h"
#include <ctime>
#include <amp.h>
#include <amp_math.h>

#define BUFFER_SIZE	65535
#define LOOPCOUNT	60000

class MyScene : public PRGame
{
public:
	void onInitialize()
	{
		float *a = new float[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			a[i] = i + 1;
		concurrency::array_view<float, 1> gpu_in(BUFFER_SIZE, a);
		concurrency::array_view<float, 1> gpu_out(BUFFER_SIZE);

		clock_t start = clock();
		for (int i = 0; i < LOOPCOUNT; ++i)
		{
			concurrency::parallel_for_each(gpu_out.extent, [=](concurrency::index<1> i)restrict(amp) {
				gpu_out[i] = concurrency::fast_math::sqrt(gpu_in[i]);
			});
		}
		clock_t end = clock();

		delete[] a;

		FILE *fp = fopen("AMP_GPU.txt", "wt");
		fprintf(fp, "C++ AMP GPU Performance : %ds\n", (end - start) / CLOCKS_PER_SEC);
		for (int i = 0; i < BUFFER_SIZE; ++i)
			fprintf(fp, "sqrt(%f) = %f\n", (float)(i + 1), gpu_out[i]);
		fclose(fp);

		float *cpu_in = new float[BUFFER_SIZE];
		for (int i = 0; i < BUFFER_SIZE; ++i)
			cpu_in[i] = i + 1;
		float *cpu_out = new float[BUFFER_SIZE];

		start = clock();
		for (int i = 0; i < LOOPCOUNT; ++i)
			for (int j = 0; j < BUFFER_SIZE; ++j)
				cpu_out[j] = sqrt(cpu_in[j]);
		end = clock();

		fp = fopen("NO_AMP.txt", "wt");
		fprintf(fp, "CPU Performance : %ds\n", (end - start) / CLOCKS_PER_SEC);
		for (int i = 0; i < BUFFER_SIZE; ++i)
			fprintf(fp, "sqrt(%f) = %f\n", (float)(i + 1), cpu_out[i]);
		fclose(fp);

		delete[] cpu_out;
		delete[] cpu_in;

		PostQuitMessage(0);

	}

	void onDestroy()
	{

	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		float clearColor[] = { 0, 0, 0, 1 };
		graphicsContext->immediateContext->ClearRenderTargetView(graphicsContext->renderTargetView, clearColor);
		graphicsContext->immediateContext->ClearDepthStencilView(graphicsContext->depthStencilView, D3D11_CLEAR_DEPTH, 1, 0);

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