#define POLYRAM_D3D11
#include "polyram.h"
#include "polyram_d3d11.h"
#include <d2d1.h>
#pragma comment( lib, "d2d1.lib")
#include <dwrite.h>
#pragma comment(lib, "dwrite.lib")

struct MyConstantBuffer { PRMat world, view, proj; PRVec4 pointLightPos; };

class MyScene : public PRGame
{
public:
	ID2D1Factory *d2dFactory;
	ID2D1RenderTarget *d2dRenderTarget;

	ID2D1SolidColorBrush *d2dMagentaBrush;
	ID2D1GradientStopCollection *d2dGradientStopCollection;
	ID2D1LinearGradientBrush *d2dGradientBrush;
	ID2D1Bitmap *d2dBitmap1, *d2dBitmap2;

	ID3D11Texture2D *d3dTexture;

	IDWriteFactory *dwFactory;
	IDWriteTextFormat *dwTextFormat, *dwTextFormatBoldItalic;

	//Homework
	ID3D11Buffer *bunnyVB;
	int bunnyVBSize;
	ID3D11InputLayout *inputLayout;
	ID3D11VertexShader *vertexShader;
	ID3D11PixelShader *pixelShader;
	ID3D11Buffer *vertexCB;
	ID3D11RasterizerState *rasterizerState;
	//~Homework

public:
	void onInitialize()
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		//Homework
		PRModelGenerator sphere(std::string("bunny.obj"));
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

		//~Homework

		D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &d2dFactory);

		float dpiX, dpiY;
		d2dFactory->GetDesktopDpi(&dpiX, &dpiY);

		IDXGISurface *surface;
		graphicsContext->dxgiSwapChain->GetBuffer(0, __uuidof(IDXGISurface), (void**)&surface);

		D2D1_RENDER_TARGET_PROPERTIES renderTargetProperty;
		memset(&renderTargetProperty, 0, sizeof(D2D1_RENDER_TARGET_PROPERTIES));
		renderTargetProperty.type = D2D1_RENDER_TARGET_TYPE_DEFAULT;
		renderTargetProperty.usage = D2D1_RENDER_TARGET_USAGE_NONE;
		renderTargetProperty.pixelFormat = { DXGI_FORMAT_UNKNOWN, D2D1_ALPHA_MODE_PREMULTIPLIED };
		renderTargetProperty.dpiX = dpiX;
		renderTargetProperty.dpiY = dpiY;
		d2dFactory->CreateDxgiSurfaceRenderTarget(surface, renderTargetProperty, &d2dRenderTarget);

		surface->Release();

		d2dRenderTarget->CreateSolidColorBrush(D2D1::ColorF(1, 0, 1, 1), &d2dMagentaBrush);

		D2D1_GRADIENT_STOP gradientStops[] = {
			D2D1::GradientStop(0.0f, D2D1::ColorF(1, 0, 1, 1)),
			D2D1::GradientStop(0.5f, D2D1::ColorF(0, 1, 0, 1)),
			D2D1::GradientStop(1.0f, D2D1::ColorF(1, 1, 0, 1)),
		};
		d2dRenderTarget->CreateGradientStopCollection(gradientStops, _countof(gradientStops), &d2dGradientStopCollection);
		d2dRenderTarget->CreateLinearGradientBrush(
			D2D1::LinearGradientBrushProperties(D2D1::Point2F(50, 0), D2D1::Point2F(50, 100)),
			d2dGradientStopCollection, &d2dGradientBrush
		);

		void *buffer;
		unsigned width, height;
		PRGetImageData(std::string("Test1.jpg"), &buffer, &width, &height);
		D2D1_BITMAP_PROPERTIES bitmapProp1;
		bitmapProp1.dpiX = dpiX;
		bitmapProp1.dpiY = dpiY;
		bitmapProp1.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
		d2dRenderTarget->CreateBitmap(D2D1::SizeU(width, height), buffer, width * 4, &bitmapProp1, &d2dBitmap1);
		delete[] buffer;

		d3dTexture = PRCreateTexture2D(graphicsContext->d3dDevice, std::string("Test2.jpg"));
		IDXGISurface *dxgiSurface;
		d3dTexture->QueryInterface(__uuidof(IDXGISurface), (void**)&dxgiSurface);
		D2D1_BITMAP_PROPERTIES bitmapProp2;
		bitmapProp2.dpiX = dpiX;
		bitmapProp2.dpiY = dpiY;
		bitmapProp2.pixelFormat = D2D1::PixelFormat(DXGI_FORMAT_R8G8B8A8_UNORM, D2D1_ALPHA_MODE_PREMULTIPLIED);
		d2dRenderTarget->CreateSharedBitmap(__uuidof(IDXGISurface), dxgiSurface, &bitmapProp2, &d2dBitmap2);
		dxgiSurface->Release();

		DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, __uuidof(IDWriteFactory), (IUnknown**)&dwFactory);
		dwFactory->CreateTextFormat(L"NanumGothic", NULL, DWRITE_FONT_WEIGHT_NORMAL, DWRITE_FONT_STYLE_NORMAL,
			DWRITE_FONT_STRETCH_NORMAL, 24.0f * (dpiX / 72.0f), L"en-US", &dwTextFormat);
		dwFactory->CreateTextFormat(L"NanumGothic", NULL, DWRITE_FONT_WEIGHT_EXTRA_BOLD, DWRITE_FONT_STYLE_ITALIC,
			DWRITE_FONT_STRETCH_NORMAL, 24.0f * (dpiX / 72.0f), L"en-US", &dwTextFormatBoldItalic);
	}

	void onDestroy()
	{


		dwTextFormat->Release();
		dwFactory->Release();

		d3dTexture->Release();

		d2dBitmap2->Release();
		d2dBitmap1->Release();

		d2dGradientBrush->Release();
		d2dGradientStopCollection->Release();
		d2dMagentaBrush->Release();

		d2dRenderTarget->Release();
		d2dFactory->Release();

		//Homework

		rasterizerState->Release();
		vertexCB->Release();
		pixelShader->Release();
		vertexShader->Release();
		inputLayout->Release();
		bunnyVB->Release();

		//~Homework
	}

	void onDraw(double dt)
	{
		GETGRAPHICSCONTEXT(PRGraphicsContext_Direct3D11);

		//Homework

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

		//~Homework

		d2dRenderTarget->BeginDraw();

		//d2dRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));	//Homework

		d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		d2dRenderTarget->DrawLine(D2D1::Point2F(100, 100), D2D1::Point2F(200, 200), d2dMagentaBrush);

		d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Translation(300, 100));
		d2dRenderTarget->FillRectangle(D2D1::RectF(0, 0, 100, 100), d2dGradientBrush);


		d2dRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		d2dRenderTarget->DrawBitmap(d2dBitmap1, D2D1::RectF(500, 100, 600, 200), 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 500, 500));
		d2dRenderTarget->DrawBitmap(d2dBitmap2, D2D1::RectF(700, 100, 800, 200), 1.0f,
			D2D1_BITMAP_INTERPOLATION_MODE_LINEAR, D2D1::RectF(0, 0, 500, 500));

		d2dRenderTarget->DrawTextW(TEXT("Hello, world!"), 13,
			dwTextFormat, D2D1::RectF(10, 10, 300, 100), d2dMagentaBrush);
		d2dRenderTarget->DrawTextW(TEXT("Hello, world"), 13,
			dwTextFormatBoldItalic, D2D1::RectF(10, 60, 300, 100), d2dMagentaBrush);

		d2dRenderTarget->EndDraw();

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