#ifndef __POLYRAM_H__
#define __POLYRAM_H__

/* ==============================================================================================
*
*   libPolyram
*                          Copyright (C) 2015 Daramkun(Jin Jae-yeon)
*
*  -- The MIT License --
*
*  Permission is hereby granted, free of charge, to any person obtaining a copy of this software
*  and associated documentation files (the "Software"), to deal in the Software without
*  restriction, including without limitation the rights to use, copy, modify, merge, publish, 
*  distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the
*  Software is furnished to do so, subject to the following conditions:
*
*  The above copyright notice and this permission notice shall be included in all copies or 
*  substantial portions of the Software.
*
*  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
*  BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
*  NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
*  DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
*  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*
============================================================================================== */

#include <iostream>
#include <exception>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <string>

#if ( defined ( _WINDOWS ) || defined ( _WIN32 ) || defined ( _WIN64 ) || defined ( WIN32 ) || defined ( WIN64 ) )
#	include <Windows.h>
#	include <wincodec.h>
#	include <atlconv.h>
#	pragma comment ( lib, "windowscodecs.lib" )
#	if WINAPI_FAMILY_PARTITION( WINAPI_PARTITION_DESKTOP ) || !defined ( WINAPI_FAMILY_DESKTOP_APP )
#		define PRPlatformMicrosoftWindowsNT		1
#		define PRPlatformMicrosoftWindowsRT		0
#		pragma comment ( lib, "winmm.lib" )
#	elif WINAPI_FAMILY_PARTITION ( WINAPI_FAMILY_PC_APP )
#		define PRPlatformMicrosoftWindowsNT		0
#		define PRPlatformMicrosoftWindowsRT		1
#		include <wrl.h>
#		include <wrl/client.h>
#	endif
#else
#	define PRPlatformMicrosoftWindowsNT			0
#	define PRPlatformMicrosoftWindowsRT			0
#endif
#if defined ( EMSCRIPTEN )
#	include <emscripten/emscripten.h>
#	include <emscripten/html5.h>
#	define PRPlatformWeb						1
#else
#	define PRPlatformWeb						0
#endif
#if defined ( __APPLE__ )
#	include <TargetConditionals.h>
#	define PRPlatformAppleOSX					TARGET_OS_MAC && !( TARGET_OS_IOS || TARGET_OS_SIMULATOR )
#	define PRPlatformAppleiOS					TARGET_OS_IOS || TARGET_OS_SIMULATOR
#	import <Foundation/Foundation.h>
#	include <sys/time.h>
#	if ( PRPlatformAppleOSX )
#		import <Cocoa/Cocoa.h>
#	else
#		import <UIKit/UIKit.h>
#	endif
#else
#	define PRPlatformAppleOSX					0
#	define PRPlatformAppleiOS					0
#endif
#if defined ( __ANDROID__ )
#	include <jni.h>
#	include <sys/time.h>
#	include <android/api-level.h>
#	include <android/native_activity.h>
#	include <android/native_window.h>
#	include <android/input.h>
#	include <android/window.h>
#	include <android/configuration.h>
#	include <android/asset_manager.h>
#	include <android/obb.h>
#	include <android/looper.h>
#	include <android/keycodes.h>
#	include <android/sensor.h>
#	include <android/storage_manager.h>
#	include <android/log.h>
#	include "android_native_app_glue/android_native_app_glue.h"

struct engine {
	struct android_app* app;

	ASensorManager* sensorManager;
	const ASensor* accelerometerSensor;
	ASensorEventQueue* sensorEventQueue;

	int animating;
	int32_t width;
	int32_t height;

	void * state;
};

#	define PRPlatformGoogleAndroid				1
#else
#	define PRPlatformGoogleAndroid				0
#endif
#if ( defined ( __unix__ ) || defined ( __linux__ ) ) && !defined ( __ANDROID__ )
#	include <sys/time.h>
#	include <X11/X.h>
#	include <X11/Xlib.h>
#	define PRPlatformUNIX						1
#else
#	define PRPlatformUNIX						0
#endif
#define PRPlatformMicrosoftWindowsFamily		( PRPlatformMicrosoftWindowsNT || PRPlatformMicrosoftWindowsRT )
#define PRPlatformAppleFamily					( PRPlatformAppleOSX || PRPlatformAppleiOS )
#define PRPlatformUNIXFamily					( PRPlatformUNIX || PRPlatformGoogleAndroid )
#define PRPlatformDesktops						( PRPlatformMicrosoftWindowsNT || PRPlatformAppleOSX || PRPlatformUNIX )
#define PRPlatformMobiles						( PRPlatformMicrosoftWindowsRT || PRPlatformAppleiOS || PRPlatformGoogleAndroid )

#if defined ( POLYRAM_D3D9 )
#	if ( !PRPlatformMicrosoftWindowsNT )
#		error Direct3D9 is for Windows NT only in this framework.
#	endif
#	include <d3d9.h>
#	pragma comment ( lib, "d3d9.lib" )
#endif
#if defined ( POLYRAM_D3D11 )
#	if ( !PRPlatformMicrosoftWindowsFamily )
#		error Direct3D11 is for Windows Family only.
#	endif
#	include <d3dcommon.h>
#	include <d3d11.h>
#	include <dxgi.h>
#	if defined ( NTDDI_WIN8)
#		include <d3d11_1.h>
#	endif
#	if defined ( NTDDI_WINBLUE )
#		include <d3d11_2.h>
#		include <dxgi1_2.h>
#	endif
#	if defined ( NTDDI_WIN10 )
#		include <d3d11_3.h>
#		include <dxgi1_3.h>
#	endif
#	pragma comment ( lib, "d3d11.lib" )
#	pragma comment ( lib, "dxgi.lib" )
#	pragma comment ( lib, "dxguid.lib" )
#endif
#if defined ( POLYRAM_D3D12 )
#	if ( !PRPlatformMicrosoftWindowsFamily )
#		error Direct3D12 is for Windows Family only.
#	endif
#	if !defined ( NTDDI_WIN10 )
#		error You cannot build for Direct3D 12 because your build target is not Windows 10 or higher.
#	endif
#	include <d3dcommon.h>
#	include <d3d12.h>
#	include <dxgi.h>
#	include <dxgi1_4.h>
#	pragma comment ( lib, "d3d12.lib" )
#	pragma comment ( lib, "dxgi.lib" )
#	pragma comment ( lib, "dxguid.lib" )
#endif
#if defined ( POLYRAM_OPENGL )
#	if PRPlatformDesktops && !defined ( GLEW_STATIC )
#		define GLEW_STATIC
#		if PRPlatformMicrosoftWindowsNT && defined ( POLYRAM_DLL_MODE )
#			undef GLEW_STATIC
#		endif
#	endif
#	if PRPlatformMicrosoftWindowsNT
#		include <GL/glew.h>
#		include <gl/gl.h>
#		include <gl/glu.h>
#		pragma comment ( lib, "OpenGL32.lib" )
#		pragma comment ( lib, "GLU32.lib" )
#	elif PRPlatformMicrosoftWindowsRT
#		error You cannot use OpenGL in Windows RT.
#	elif PRPlatformAppleOSX
#		include "./GL/glew.h"
#		import <OpenGL/OpenGL.h>
#	elif PRPlatformAppleiOS
#		import <OpenGLES/EAGL.h>
#		import <OpenGLES/EAGLDrawable.h>
#		import <OpenGLES/gltypes.h>
#		import <OpenGLES/ES1/gl.h>
#		import <OpenGLES/ES1/glext.h>
#		import <OpenGLES/ES2/gl.h>
#		import <OpenGLES/ES2/glext.h>
#		import <OpenGLES/ES3/gl.h>
#		import <OpenGLES/ES3/glext.h>
#		import <GLKit/GLKit.h>
#	elif PRPlatformUNIX
#		include <GL/glew.h>
#		include <GL/gl.h>
#		include <GL/glx.h>
#	elif PRPlatformGoogleAndroid
#		include <EGL/egl.h>
#		include <EGL/eglext.h>
#		include <EGL/eglplatform.h>
#		include <GLES2/gl2.h>
#		include <GLES2/gl2ext.h>
#		include <GLES2/gl2platform.h>
#	endif
#endif
#if defined ( POLYRAM_METAL )
#	if PRPlatformAppleFamily
#		import <Metal/Metal.h>
#	else
#		error You cannot use Metal API from this platform.
#	endif
#endif
#if defined ( POLYRAM_VULKAN )
/*
#	include <vulkan/vulkan.h>
#	include <vulkan/vk_sdk_platform.h>
#	if PRPlatformMicrosoftWindowsNT
#		pragma comment ( lib, "vulkan-1.lib" )
#	endif
*/
#endif

#if defined ( POLYRAM_DLL_MODE )
#	if LIBPOLYRAM_EXPORTS
#		define POLYRAMDECLSPEC	__declspec ( dllexport )
#	else
#		define POLYRAMDECLSPEC	__declspec ( dllimport )
#	endif
#else
#	define POLYRAMDECLSPEC
#endif

enum PRKey {
	PRKey_Unknown,
	PRKey_Up, PRKey_Down, PRKey_Left, PRKey_Right,
	PRKey_Return, PRKey_Space, PRKey_Backspace, PRKey_Tab, PRKey_Escape, PRKey_CapsLock,
	PRKey_F1, PRKey_F2, PRKey_F3, PRKey_F4, PRKey_F5, PRKey_F6, PRKey_F7, PRKey_F8, PRKey_F9, PRKey_F10, PRKey_F11, PRKey_F12,
	PRKey_0, PRKey_1, PRKey_2, PRKey_3, PRKey_4, PRKey_5, PRKey_6, PRKey_7, PRKey_8, PRKey_9,
	PRKey_A, PRKey_B, PRKey_C, PRKey_D, PRKey_E, PRKey_F, PRKey_G, PRKey_H, PRKey_I, PRKey_J, PRKey_K, PRKey_L, PRKey_M,
	PRKey_N, PRKey_O, PRKey_P, PRKey_Q, PRKey_R, PRKey_S, PRKey_T, PRKey_U, PRKey_V, PRKey_W, PRKey_X, PRKey_Y, PRKey_Z,
	PRKey_Grave, PRKey_Subtract, PRKey_Equals, PRKey_Backslash, PRKey_LeftBracket, PRKey_RightBracket, PRKey_Semicolon,
	PRKey_Quotation, PRKey_Comma, PRKey_Period, PRKey_Slash,
	PRKey_Insert, PRKey_Delete, PRKey_Home, PRKey_End, PRKey_PageUp, PRKey_PageDown,
	PRKey_LeftCtrl, PRKey_LeftAlt, PRKey_LeftShift, PRKey_LeftWin,
	PRKey_RightCtrl, PRKey_RightAlt, PRKey_RightShift, PRKey_RightWin,
};

enum PRMButton { PRMButton_None = 0, PRMButton_Left = 1, PRMButton_Right = 2, PRMButton_Middle = 4, };

class POLYRAMDECLSPEC PRGame {
public:
	PRGame ();
	virtual ~PRGame ();

	virtual void onInitialize ();
	virtual void onDestroy ();
	virtual void onUpdate ( double dt );
	virtual void onDraw ( double dt );

	virtual void onKeyDown ( PRKey key );
	virtual void onKeyUp ( PRKey key );

	virtual void onMouseDown ( PRMButton button, int x, int y );
	virtual void onMouseUp ( PRMButton button, int x, int y );
	virtual void onMouseMove ( PRMButton button, int x, int y );
	virtual void onMouseWheel ( int wheelX, int wheelY );

	virtual void onTouchDown ( int pid, int x, int y );
	virtual void onTouchUp ( int pid, int x, int y );
	virtual void onTouchMove ( int pid, int x, int y );

	virtual void onActivated ();
	virtual void onDeactivated ();
	virtual void onResized ();

	virtual void onAccelerometer ( float x, float y, float z );
};

enum PRRendererType {
	PRRendererType_Unknown,
	PRRendererType_Direct3D9,
	PRRendererType_Direct3D11,
	PRRendererType_Direct3D12,
	PRRendererType_OpenGL1,
	PRRendererType_OpenGL2,
	PRRendererType_OpenGL3,
	PRRendererType_OpenGL4,
	PRRendererType_OpenGLES1,
	PRRendererType_OpenGLES2,
	PRRendererType_OpenGLES3,
	PRRendererType_WebGL1,
	PRRendererType_Vulkan1,
	PRRendererType_Metal1,
};

struct POLYRAMDECLSPEC PRVersion {
	int major, minor;
	PRVersion ( std::string & versionString );
	PRVersion ( int major, int minor = 0 );
};

class POLYRAMDECLSPEC PRGraphicsContext { public: virtual ~PRGraphicsContext (); };

class POLYRAMDECLSPEC PRApp {
public:
	PRApp ( PRGame * game, PRRendererType rendererType, int width, int height, std::string & title
#if PRPlatformGoogleAndroid
		, struct android_app * state
#endif
	);
	~PRApp ();

public:
	PRGame * getGame ();
	PRGraphicsContext * getGraphicsContext ();
	void setGraphicsContext ( PRGraphicsContext * graphicsContext );
	void getClientSize ( int * width, int * height );

	bool setCursorPosition ( int x, int y );
	bool setCursorVisible ( bool visible );

	void run ();
	void exit ();

public:
	static PRApp * sharedApp ();

private:
	PRGame * m_game;
	PRGraphicsContext * m_graphicsContext;
#if PRPlatformMicrosoftWindowsRT || PRPlatformGoogleAndroid
	PRRendererType m_rendererType;
#endif

public:
#if PRPlatformMicrosoftWindowsNT
	HWND m_hWnd;
#elif PRPlatformMicrosoftWindowsRT
	Windows::UI::Core::CoreWindow^ window;
#elif PRPlatformAppleOSX
	NSWindow * window;
#elif PRPlatformUNIX
	Display * display;
	XVisualInfo * visualInfo;
	Colormap colorMap;
	Window window;
	unsigned width, height;
#elif PRPlatformGoogleAndroid
	struct engine engine;
#endif
};

#if defined ( POLYRAM_D3D9 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D9 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D9 ( PRApp * app );
	~PRGraphicsContext_Direct3D9 ();

public:
	IDirect3DDevice9 * d3dDevice;
};
#endif
#if defined ( POLYRAM_D3D11 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D11 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D11 ( PRApp * app );
	~PRGraphicsContext_Direct3D11 ();

public:
#if PRPlatformMicrosoftWindowsRT
	IDXGISwapChain1* dxgiSwapChain;
#else
	IDXGISwapChain* dxgiSwapChain;
#endif
	ID3D11Device* d3dDevice;
	ID3D11DeviceContext* immediateContext;
	ID3D11RenderTargetView* renderTargetView;
	ID3D11DepthStencilView* depthStencilView;
	ID3D11Texture2D* depthStencilBuffer;
};
#endif
#if defined ( POLYRAM_D3D12 )
class POLYRAMDECLSPEC PRGraphicsContext_Direct3D12 : public PRGraphicsContext {
public:
	PRGraphicsContext_Direct3D12 ( PRApp * app );
	~PRGraphicsContext_Direct3D12 ();

public:
	void Synchronization ();

public:
#ifdef _DEBUG
	ID3D12Debug * debugLayer;
#else
	void * d3d12_debugLayer_dummy;
#endif
	IDXGISwapChain3* dxgiSwapChain;
	ID3D12Device* d3dDevice;
	ID3D12CommandQueue* commandQueue;
	ID3D12DescriptorHeap* descriptorHeap;
	unsigned descriptorHandleIncrementSize;
	ID3D12Resource* renderTargets [ 2 ];
	unsigned frameIndex;
	ID3D12CommandAllocator* commandAllocator;
	ID3D12RootSignature* rootSignature;
	ID3D12Fence* fence;
	HANDLE fenceEvent;
	unsigned fenceValue;
};
#endif
#if defined ( POLYRAM_OPENGL )
class POLYRAMDECLSPEC PRGraphicsContext_OpenGL : public PRGraphicsContext {
public:
	PRGraphicsContext_OpenGL ( PRApp * app, PRRendererType rendererType );
	~PRGraphicsContext_OpenGL ();

public:
	void makeCurrent ();
	void swapBuffers ();

public:
#if PRPlatformMicrosoftWindowsNT
	HDC hDC;
	HGLRC glContext;
#elif PRPlatformAppleOSX
	NSOpenGLContext * glContext;
#elif PRPlatformAppleiOS
	EAGLContext * glContext;
#elif PRPlatformUNIX
	GLXContext glContext;
#elif PRPlatformGoogleAndroid
	EGLDisplay display;
	EGLSurface surface;
	EGLContext context;
#endif
};
#endif
#if defined ( POLYRAM_METAL )
class POLYRAMDECLSPEC PRGraphicsContext_Metal : public PRGraphicsContext {
public:
	PRGraphicsContext_Metal ( PRApp * app );
	~PRGraphicsContext_Metal ();

public:
	id<MTLDevice> device;
	id<MTLLibrary> library;
	id<MTLCommandQueue> commandQueue;
	id<MTLCommandBuffer> commandBuffer;
};
#endif
#if defined ( POLYRAM_VULKAN )
/*class PRGraphicsContext_Vulkan : public PRGraphicsContext {
public:
	PRGraphicsContext_Vulkan ( PRApp * app );
	~PRGraphicsContext_Vulkan ();

public:
	VkInstance instance;
	VkDevice device;
	VkQueue queue;

	VkSwapchainKHR swapChain;
};*/
#endif

#define GETGRAPHICSCONTEXT(x) auto graphicsContext = static_cast<x*> ( PRApp::sharedApp ()->getGraphicsContext () )

struct PRVec2;
struct PRVec3;
struct PRVec4;
struct PRQuat;
struct PRMat;

struct POLYRAMDECLSPEC PRVec2 {
public:
	float x, y;

public:
	PRVec2 ();
	PRVec2 ( float v );
	PRVec2 ( float x, float y );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVec2 * result );

	float lengthSquared ();
	float length ();
	PRVec2 normalize ();

public:
	static void lengthSquared ( const PRVec2 * v, float * result );
	static void length ( const PRVec2 * v, float * result );
	static void normalize ( const PRVec2 * v, PRVec2 * result );

	static float lengthSquared ( const PRVec2 & v );
	static float length ( const PRVec2 & v );
	static PRVec2 normalize ( const PRVec2 & v );

public:
	static void add ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result );
	static void subtract ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result );
	static void negate ( const PRVec2 * v1, PRVec2 * result );
	static void multiply ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result );
	static void multiply ( const PRVec2 * v1, float v2, PRVec2 * result );
	static void multiply ( float v1, const PRVec2 * v2, PRVec2 * result );
	static void divide ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result );
	static void divide ( const PRVec2 * v1, float v2, PRVec2 * result );

	static void dot ( const PRVec2 * v1, const PRVec2 * v2, float * result );
	static void dot ( const PRVec2 * v1, float v2, float * result );
	static void cross ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result );

	static PRVec2 add ( const PRVec2 & v1, const PRVec2 & v2 );
	static PRVec2 subtract ( const PRVec2 & v1, const PRVec2 & v2 );
	static PRVec2 negate ( const PRVec2 & v1 );
	static PRVec2 multiply ( const PRVec2 & v1, const PRVec2 & v2 );
	static PRVec2 multiply ( const PRVec2 & v1, float v2 );
	static PRVec2 multiply ( float v1, const PRVec2 & v2 );
	static PRVec2 divide ( const PRVec2 & v1, const PRVec2 & v2 );
	static PRVec2 divide ( const PRVec2 & v1, float v2 );

	static float dot ( const PRVec2 & v1, const PRVec2 & v2 );
	static float dot ( const PRVec2 & v1, float v2 );
	static PRVec2 cross ( const PRVec2 & v1, const PRVec2 & v2 );

public:
	static void transform ( const PRVec2 * pos, const PRMat * mat, PRVec2 * result );
	static void transformNormal ( const PRVec2 * nor, const PRMat * mat, PRVec2 * result );

	static PRVec2 transform ( const PRVec2 & pos, const PRMat & mat );
	static PRVec2 transformNormal ( const PRVec2 & nor, const PRMat & mat );
};

POLYRAMDECLSPEC PRVec2 operator+ ( const PRVec2 & v1, const PRVec2 & v2 );
POLYRAMDECLSPEC PRVec2 operator- ( const PRVec2 & v1, const PRVec2 & v2 );
POLYRAMDECLSPEC PRVec2 operator- ( const PRVec2 & v1 );
POLYRAMDECLSPEC PRVec2 operator* ( const PRVec2 & v1, const PRVec2 & v2 );
POLYRAMDECLSPEC PRVec2 operator* ( const PRVec2 & v1, float v2 );
POLYRAMDECLSPEC PRVec2 operator* ( float v1, const PRVec2 & v2 );
POLYRAMDECLSPEC PRVec2 operator/ ( const PRVec2 & v1, const PRVec2 & v2 );
POLYRAMDECLSPEC PRVec2 operator/ ( const PRVec2 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVec2 & v1, const PRVec2 & v2 );

struct POLYRAMDECLSPEC PRVec3 {
public:
	float x, y, z;

public:
	PRVec3 ();
	PRVec3 ( float v );
	PRVec3 ( float x, float y, float z );
	PRVec3 ( const PRVec2 & v, float z );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVec3 * result );

	float lengthSquared ();
	float length ();
	PRVec3 normalize ();

public:
	static void lengthSquared ( const PRVec3 * v, float * result );
	static void length ( const PRVec3 * v, float * result );
	static void normalize ( const PRVec3 * v, PRVec3 * result );

	static float lengthSquared ( const PRVec3 & v );
	static float length ( const PRVec3 & v );
	static PRVec3 normalize ( const PRVec3 & v );

public:
	static void add ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result );
	static void subtract ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result );
	static void negate ( const PRVec3 * v1, PRVec3 * result );
	static void multiply ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result );
	static void multiply ( const PRVec3 * v1, float v2, PRVec3 * result );
	static void multiply ( float v1, const PRVec3 * v2, PRVec3 * result );
	static void divide ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result );
	static void divide ( const PRVec3 * v1, float v2, PRVec3 * result );

	static void dot ( const PRVec3 * v1, const PRVec3 * v2, float * result );
	static void dot ( const PRVec3 * v1, float v2, float * result );
	static void cross ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result );

	static PRVec3 add ( const PRVec3 & v1, const PRVec3 & v2 );
	static PRVec3 subtract ( const PRVec3 & v1, const PRVec3 & v2 );
	static PRVec3 negate ( const PRVec3 & v1 );
	static PRVec3 multiply ( const PRVec3 & v1, const PRVec3 & v2 );
	static PRVec3 multiply ( const PRVec3 & v1, float v2 );
	static PRVec3 multiply ( float v1, const PRVec3 & v2 );
	static PRVec3 divide ( const PRVec3 & v1, const PRVec3 & v2 );
	static PRVec3 divide ( const PRVec3 & v1, float v2 );

	static float dot ( const PRVec3 & v1, const PRVec3 & v2 );
	static float dot ( const PRVec3 & v1, float v2 );
	static PRVec3 cross ( const PRVec3 & v1, const PRVec3 & v2 );

public:
	static void transform ( const PRVec2 * pos, const PRMat * mat, PRVec3 * result );
	static void transform ( const PRVec3 * pos, const PRMat * mat, PRVec3 * result );
	static void transform ( const PRVec3 * pos, const PRQuat * q, PRVec3 * result );
	static void transformNormal ( const PRVec2 * nor, const PRMat * mat, PRVec3 * result );
	static void transformNormal ( const PRVec3 * nor, const PRMat * mat, PRVec3 * result );

	static PRVec3 transform ( const PRVec2 & pos, const PRMat & mat );
	static PRVec3 transform ( const PRVec3 & pos, const PRMat & mat );
	static PRVec3 transform ( const PRVec3 & pos, const PRQuat & q );
	static PRVec3 transformNormal ( const PRVec2 & nor, const PRMat & mat );
	static PRVec3 transformNormal ( const PRVec3 & nor, const PRMat & mat );
};

POLYRAMDECLSPEC PRVec3 operator+ ( const PRVec3 & v1, const PRVec3 & v2 );
POLYRAMDECLSPEC PRVec3 operator- ( const PRVec3 & v1, const PRVec3 & v2 );
POLYRAMDECLSPEC PRVec3 operator- ( const PRVec3 & v1 );
POLYRAMDECLSPEC PRVec3 operator* ( const PRVec3 & v1, const PRVec3 & v2 );
POLYRAMDECLSPEC PRVec3 operator* ( const PRVec3 & v1, float v2 );
POLYRAMDECLSPEC PRVec3 operator* ( float v1, const PRVec3 & v2 );
POLYRAMDECLSPEC PRVec3 operator/ ( const PRVec3 & v1, const PRVec3 & v2 );
POLYRAMDECLSPEC PRVec3 operator/ ( const PRVec3 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVec3 & v1, const PRVec3 & v2 );

struct POLYRAMDECLSPEC PRVec4 {
public:
	float x, y, z, w;

public:
	PRVec4 ();
	PRVec4 ( float v );
	PRVec4 ( float x, float y, float z, float w );
	PRVec4 ( const PRVec2 & v, float z, float w );
	PRVec4 ( const PRVec3 & v, float w );
	PRVec4 ( const PRQuat & q );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRVec4 * result );

	float lengthSquared ();
	float length ();
	PRVec4 normalize ();

public:
	static void lengthSquared ( const PRVec4 * v, float * result );
	static void length ( const PRVec4 * v, float * result );
	static void normalize ( const PRVec4 * v, PRVec4 * result );

	static float lengthSquared ( const PRVec4 & v );
	static float length ( const PRVec4 & v );
	static PRVec4 normalize ( const PRVec4 & v );

public:
	static void add ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result );
	static void subtract ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result );
	static void negate ( const PRVec4 * v1, PRVec4 * result );
	static void multiply ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result );
	static void multiply ( const PRVec4 * v1, float v2, PRVec4 * result );
	static void multiply ( float v1, const PRVec4 * v2, PRVec4 * result );
	static void divide ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result );
	static void divide ( const PRVec4 * v1, float v2, PRVec4 * result );

	static void dot ( const PRVec4 * v1, const PRVec4 * v2, float * result );
	static void dot ( const PRVec4 * v1, float v2, float * result );

	static PRVec4 add ( const PRVec4 & v1, const PRVec4 & v2 );
	static PRVec4 subtract ( const PRVec4 & v1, const PRVec4 & v2 );
	static PRVec4 negate ( const PRVec4 & v1 );
	static PRVec4 multiply ( const PRVec4 & v1, const PRVec4 & v2 );
	static PRVec4 multiply ( const PRVec4 & v1, float v2 );
	static PRVec4 multiply ( float v1, const PRVec4 & v2 );
	static PRVec4 divide ( const PRVec4 & v1, const PRVec4 & v2 );
	static PRVec4 divide ( const PRVec4 & v1, float v2 );

	static float dot ( const PRVec4 & v1, const PRVec4 & v2 );
	static float dot ( const PRVec4 & v1, float v2 );

public:
	static void transform ( const PRVec2 * pos, const PRMat * mat, PRVec4 * result );
	static void transform ( const PRVec3 * pos, const PRMat * mat, PRVec4 * result );
	static void transform ( const PRVec4 * pos, const PRMat * mat, PRVec4 * result );

	static PRVec4 transform ( const PRVec2 & pos, const PRMat & mat );
	static PRVec4 transform ( const PRVec3 & pos, const PRMat & mat );
	static PRVec4 transform ( const PRVec4 & pos, const PRMat & mat );
};

POLYRAMDECLSPEC PRVec4 operator+ ( const PRVec4 & v1, const PRVec4 & v2 );
POLYRAMDECLSPEC PRVec4 operator- ( const PRVec4 & v1, const PRVec4 & v2 );
POLYRAMDECLSPEC PRVec4 operator- ( const PRVec4 & v1 );
POLYRAMDECLSPEC PRVec4 operator* ( const PRVec4 & v1, const PRVec4 & v2 );
POLYRAMDECLSPEC PRVec4 operator* ( const PRVec4 & v1, float v2 );
POLYRAMDECLSPEC PRVec4 operator* ( float v1, const PRVec4 & v2 );
POLYRAMDECLSPEC PRVec4 operator/ ( const PRVec4 & v1, const PRVec4 & v2 );
POLYRAMDECLSPEC PRVec4 operator/ ( const PRVec4 & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRVec4 & v1, const PRVec4 & v2 );

struct POLYRAMDECLSPEC PRQuat {
public:
	float x, y, z, w;

public:
	PRQuat ();
	PRQuat ( float v );
	PRQuat ( float x, float y, float z, float w );
	PRQuat ( const PRVec2 & v, float z, float w );
	PRQuat ( const PRVec3 & v, float w );
	PRQuat ( const PRVec4 & v );
	PRQuat ( float yaw, float pitch, float roll );
	PRQuat ( const PRMat & m );

public:
	void lengthSquared ( float * result );
	void length ( float * result );
	void normalize ( PRQuat * result );
	void invert ( PRQuat * result );

	float lengthSquared ();
	float length ();
	PRQuat normalize ();
	PRQuat invert ();

public:
	static void lengthSquared ( const PRQuat * v, float * result );
	static void length ( const PRQuat * v, float * result );
	static void normalize ( const PRQuat * v, PRQuat * result );
	static void invert ( const PRQuat * v, PRQuat * result );

	static float lengthSquared ( const PRQuat & v );
	static float length ( const PRQuat & v );
	static PRQuat normalize ( const PRQuat & v );
	static PRQuat invert ( const PRQuat & v );

public:
	static void add ( const PRQuat * v1, const PRQuat * v2, PRQuat * result );
	static void subtract ( const PRQuat * v1, const PRQuat * v2, PRQuat * result );
	static void negate ( const PRQuat * v1, PRQuat * result );
	static void multiply ( const PRQuat * v1, const PRQuat * v2, PRQuat * result );
	static void multiply ( const PRQuat * v1, float v2, PRQuat * result );
	static void multiply ( float v1, const PRQuat * v2, PRQuat * result );
	static void divide ( const PRQuat * v1, const PRQuat * v2, PRQuat * result );
	static void divide ( const PRQuat * v1, float v2, PRQuat * result );

	static void dot ( const PRQuat * v1, const PRQuat * v2, float * result );
	static void dot ( const PRQuat * v1, float v2, float * result );

	static PRQuat add ( const PRQuat & v1, const PRQuat & v2 );
	static PRQuat subtract ( const PRQuat & v1, const PRQuat & v2 );
	static PRQuat negate ( const PRQuat & v1 );
	static PRQuat multiply ( const PRQuat & v1, const PRQuat & v2 );
	static PRQuat multiply ( const PRQuat & v1, float v2 );
	static PRQuat multiply ( float v1, const PRQuat & v2 );
	static PRQuat divide ( const PRQuat & v1, const PRQuat & v2 );
	static PRQuat divide ( const PRQuat & v1, float v2 );

	static float dot ( const PRQuat & v1, const PRQuat & v2 );
	static float dot ( const PRQuat & v1, float v2 );
};

POLYRAMDECLSPEC PRQuat operator+ ( const PRQuat & v1, const PRQuat & v2 );
POLYRAMDECLSPEC PRQuat operator- ( const PRQuat & v1, const PRQuat & v2 );
POLYRAMDECLSPEC PRQuat operator- ( const PRQuat & v1 );
POLYRAMDECLSPEC PRQuat operator* ( const PRQuat & v1, const PRQuat & v2 );
POLYRAMDECLSPEC PRQuat operator* ( const PRQuat & v1, float v2 );
POLYRAMDECLSPEC PRQuat operator* ( float v1, const PRQuat & v2 );
POLYRAMDECLSPEC PRQuat operator/ ( const PRQuat & v1, const PRQuat & v2 );
POLYRAMDECLSPEC PRQuat operator/ ( const PRQuat & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRQuat & v1, const PRQuat & v2 );

struct POLYRAMDECLSPEC PRMat {
public:
	float _11, _12, _13, _14,
		_21, _22, _23, _24,
		_31, _32, _33, _34,
		_41, _42, _43, _44;

public:
	PRMat ();
	PRMat ( float v );
	PRMat ( float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24,
		float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44 );
	PRMat ( PRVec4 & c1, PRVec4 & c2, PRVec4 & c3, PRVec4 & c4 );
	PRMat ( PRQuat & q );

public:
	void invert ( PRMat * result );
	void transpose ( PRMat * result );
	void determinant ( float * result );

	PRMat invert ();
	PRMat transpose ();
	float determinant ();

public:
	static void invert ( const PRMat * m, PRMat * result );
	static PRMat invert ( const PRMat & m );
	static void transpose ( const PRMat * m, PRMat * result );
	static PRMat transpose ( const PRMat & m );
	static void determinant ( const PRMat * m, float * result );
	static float determinant ( const PRMat & m );

public:
	static void add ( const PRMat * v1, const PRMat * v2, PRMat * result );
	static void subtract ( const PRMat * v1, const PRMat * v2, PRMat * result );
	static void negate ( const PRMat * v1, PRMat * result );
	static void multiply ( const PRMat * v1, const PRMat * v2, PRMat * result );
	static void multiply ( const PRMat * v1, float v2, PRMat * result );
	static void multiply ( float v1, const PRMat * v2, PRMat * result );
	static void divide ( const PRMat * v1, const PRMat * v2, PRMat * result );
	static void divide ( const PRMat * v1, float v2, PRMat * result );

	static PRMat add ( const PRMat & v1, const PRMat & v2 );
	static PRMat subtract ( const PRMat & v1, const PRMat & v2 );
	static PRMat negate ( const PRMat & v1 );
	static PRMat multiply ( const PRMat & v1, const PRMat & v2 );
	static PRMat multiply ( const PRMat & v1, float v2 );
	static PRMat multiply ( float v1, const PRMat & v2 );
	static PRMat divide ( const PRMat & v1, const PRMat & v2 );
	static PRMat divide ( const PRMat & v1, float v2 );

public:
	static void createTranslate ( const PRVec3 * v, PRMat * result );
	static void createScale ( const PRVec3 * v, PRMat * result );
	static void createRotationX ( float r, PRMat * result );
	static void createRotationY ( float r, PRMat * result );
	static void createRotationZ ( float r, PRMat * result );

	static PRMat createTranslate ( const PRVec3 & v );
	static PRMat createScale ( const PRVec3 & v );
	static PRMat createRotationX ( float r );
	static PRMat createRotationY ( float r );
	static PRMat createRotationZ ( float r );

public:
	static void createLookAtLH ( const PRVec3 * position, const PRVec3 * target, const PRVec3 * upVector, PRMat * result );
	static void createLookAtRH ( const PRVec3 * position, const PRVec3 * target, const PRVec3 * upVector, PRMat * result );

	static PRMat createLookAtLH ( const PRVec3 & position, const PRVec3 & target, const PRVec3 & upVector );
	static PRMat createLookAtRH ( const PRVec3 & position, const PRVec3 & target, const PRVec3 & upVector );

public:
	static void createOrthographicLH ( float w, float h, float zn, float zf, PRMat * result );
	static void createOrthographicRH ( float w, float h, float zn, float zf, PRMat * result );
	static void createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMat * result );
	static void createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMat * result );
	static void createPerspectiveLH ( float w, float h, float zn, float zf, PRMat * result );
	static void createPerspectiveRH ( float w, float h, float zn, float zf, PRMat * result );
	static void createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMat * result );
	static void createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMat * result );
	static void createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf, PRMat * result );
	static void createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf, PRMat * result );

	static PRMat createOrthographicLH ( float w, float h, float zn, float zf );
	static PRMat createOrthographicRH ( float w, float h, float zn, float zf );
	static PRMat createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf );
	static PRMat createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf );
	static PRMat createPerspectiveLH ( float w, float h, float zn, float zf );
	static PRMat createPerspectiveRH ( float w, float h, float zn, float zf );
	static PRMat createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf );
	static PRMat createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf );
	static PRMat createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf );
	static PRMat createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf );

public:
	static void createBillboard ( const PRVec3 * objPos, const PRVec3 * camPos, const PRVec3 * camUpVec,
		const PRVec3 * camForwardVec, PRMat * result );
};

POLYRAMDECLSPEC PRMat operator+ ( const PRMat & v1, const PRMat & v2 );
POLYRAMDECLSPEC PRMat operator- ( const PRMat & v1, const PRMat & v2 );
POLYRAMDECLSPEC PRMat operator- ( const PRMat & v1 );
POLYRAMDECLSPEC PRMat operator* ( const PRMat & v1, const PRMat & v2 );
POLYRAMDECLSPEC PRMat operator* ( const PRMat & v1, float v2 );
POLYRAMDECLSPEC PRMat operator* ( float v1, const PRMat & v2 );
POLYRAMDECLSPEC PRMat operator/ ( const PRMat & v1, const PRMat & v2 );
POLYRAMDECLSPEC PRMat operator/ ( const PRMat & v1, float v2 );
POLYRAMDECLSPEC bool operator== ( const PRMat & v1, const PRMat & v2 );

POLYRAMDECLSPEC bool PRGetImageData ( std::string & filename, void** buffer, unsigned * width, unsigned * height );
POLYRAMDECLSPEC bool PRGetRawData ( std::string & filename, void** buffer, unsigned * size );

enum PRModelType { PRModelType_Box, PRModelType_Rectangle, PRModelType_Sphere, PRModelType_Circle, PRModelType_Grid, PRModelType_Guide, };

enum {
	PRModelProperty_Position = 0,
	PRModelProperty_Normal = 1 << 0,
	PRModelProperty_TexCoord = 1 << 1,
	PRModelProperty_Diffuse = 1 << 2,
};
typedef int PRModelProperty;

enum PRModelEncircling { PRModelEncircling_LeftHand, PRModelEncircling_RightHand };

enum PRModelTexCoord { PRModelTexCoord_UV, PRModelTexCoord_ST };

class POLYRAMDECLSPEC PRModelGenerator {
public:
	PRModelGenerator ( PRModelType modelType, PRModelProperty properties, PRModelEncircling circling = PRModelEncircling_LeftHand,
		PRModelTexCoord tcs = PRModelTexCoord_UV, const PRVec3 * scale = nullptr );
	// This constructor only support OBJ file format with XYZ, Normal, UV and Triangle faces format.
	PRModelGenerator ( std::string & filename, PRModelEncircling circling = PRModelEncircling_LeftHand,
		PRModelTexCoord tcs = PRModelTexCoord_UV, const PRVec3 * scale = nullptr );
	~PRModelGenerator ();

public:
	PRModelProperty getProperties () const;
	const void* getData () const;
	unsigned getDataSize () const;

private:
	PRModelProperty m_properties;
	void * m_data;
	unsigned m_dataSize;
};

#define SAFE_RELEASE(x)			if ( x ) x->Release (); x = nullptr;
#define SAFE_DELETE(x)			if ( x ) delete x; x = nullptr;
#define SAFE_DELETE_ARRAY(x)	if ( x ) delete [] ( char * ) x; x = nullptr;

#define PR_Epsilon				1.19209290E-07F
#define PR_NaN					NAN;
#define PR_PositiveInfinite		HUGE_VALF
#define PR_NegativeInfinite		-HUGE_VALF
#define PR_PI					3.1415926536f
#define PR_PIover2				1.5707963268f
#define PR_PIover4				0.7853981634f
#define PR_2PI					6.2831853072f
#define PR_E					2.7182818285f
#define PR_Log10E				0.4342944819f
#define PR_Log2E				1.4426950409f

#define PRMin( x, y )			( ( x > y ) ? y : x )
#define PRMax( x, y )			( ( x > y ) ? x : y )
#define PRPow2( x )				( x * x )
#define PRPow3( x )				( x * x * x )
#define PRToDegree( x )			( x * 180 / PR_PI )
#define PRToRadian( x )			( x * PR_PI / 180 )

#define PRIsEquals( v1, v2 )	( ( v1 == v2 ) ? ( true ) : ( fabs ( v1 - v2 ) < PR_Epsilon ) )
POLYRAMDECLSPEC PRVec3 PRCalcNormal ( const PRVec3 & v1, const PRVec3 & v2, const PRVec3 & v3 );

POLYRAMDECLSPEC double PRCurrentSec ();
POLYRAMDECLSPEC void PRLog ( const char * format, ... );

#if PRPlatformMicrosoftWindowsNT
#	define MAIN_FUNC_ATTR 
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME WINAPI WinMain
#	define MAIN_FUNC_ARGS HINSTANCE, HINSTANCE, LPSTR lpszCmdLine, int
#elif PRPlatformMicrosoftWindowsRT
#	define MAIN_FUNC_ATTR [Platform::MTAThread]
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME main
#	define MAIN_FUNC_ARGS Platform::Array<Platform::String^>^ args
#elif PRPlatformAppleFamily || PRPlatformUNIX
#	define MAIN_FUNC_ATTR 
#	define MAIN_FUNC_RTTP int
#	define MAIN_FUNC_NAME main
#	define MAIN_FUNC_ARGS int argc, char ** argv
#elif PRPlatformGoogleAndroid
#	define MAIN_FUNC_ATTR
#	define MAIN_FUNC_RTTP void
#	define MAIN_FUNC_NAME android_main
#	define MAIN_FUNC_ARGS struct android_app* state
#endif

#endif