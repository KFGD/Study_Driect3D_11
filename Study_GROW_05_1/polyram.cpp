#define _CRT_SECURE_NO_WARNINGS
#include "polyram.h"
#include <stdarg.h>
#include <regex>

PRGame::PRGame () { }
PRGame::~PRGame () { }
void PRGame::onInitialize () { }
void PRGame::onDestroy () { }
void PRGame::onUpdate ( double dt ) { }
void PRGame::onDraw ( double dt ) { }
void PRGame::onKeyDown ( PRKey key ) { }
void PRGame::onKeyUp ( PRKey key ) { }
void PRGame::onMouseDown ( PRMButton button, int x, int y ) { }
void PRGame::onMouseUp ( PRMButton button, int x, int y ) { }
void PRGame::onMouseMove ( PRMButton button, int x, int y ) { }
void PRGame::onMouseWheel ( int wheelX, int wheelY ) { }
void PRGame::onTouchDown ( int pid, int x, int y ) { }
void PRGame::onTouchUp ( int pid, int x, int y ) { }
void PRGame::onTouchMove ( int pid, int x, int y ) { }
void PRGame::onActivated () { }
void PRGame::onDeactivated () { }
void PRGame::onResized () { }
void PRGame::onAccelerometer ( float x, float y, float z ) { }

PRVersion::PRVersion ( std::string & versionString ) {
	std::smatch match;
	std::regex versionChecker ( "([0-9]+)[.]*([0-9]*)(.*)" );
	if ( std::regex_match ( versionString, match, versionChecker ) ) {
		major = atoi ( ( *( ++match.begin () ) ).str ().c_str () );
		if ( match.size () > 2 )
			minor = atoi ( ( *( ++++match.begin () ) ).str ().c_str () );
	}
}
PRVersion::PRVersion ( int _major, int _minor ) { major = _major; minor = _minor; }

PRGraphicsContext::~PRGraphicsContext () { }

PRKey keyConv ( int key ) {
#if !PRPlatformMicrosoftWindowsRT
	switch ( key )
#else
	switch ( ( Windows::System::VirtualKey ) key )
#endif
	{
#if PRPlatformMicrosoftWindowsNT
	case VK_UP: return PRKey_Up; case VK_DOWN: return PRKey_Down; case VK_LEFT: return PRKey_Left; case VK_RIGHT: return PRKey_Right;
	case VK_RETURN: return PRKey_Return; case VK_SPACE: return PRKey_Space; case VK_BACK: return PRKey_Backspace;
	case VK_TAB: return PRKey_Tab; case VK_ESCAPE: return PRKey_Escape; case VK_CAPITAL: return PRKey_CapsLock;
	case VK_F1: return PRKey_F1; case VK_F2: return PRKey_F2; case VK_F3: return PRKey_F3; case VK_F4: return PRKey_F4;
	case VK_F5: return PRKey_F5; case VK_F6: return PRKey_F6; case VK_F7: return PRKey_F7; case VK_F8: return PRKey_F8;
	case VK_F9: return PRKey_F9; case VK_F10: return PRKey_F10; case VK_F11: return PRKey_F11; case VK_F12: return PRKey_F12;
	case '0': return PRKey_0; case '1': return PRKey_1; case '2': return PRKey_2; case '3': return PRKey_3; case '4': return PRKey_4;
	case '5': return PRKey_5; case '6': return PRKey_6; case '7': return PRKey_7; case '8': return PRKey_8; case '9': return PRKey_9;
	case 'A': return PRKey_A; case 'B': return PRKey_B; case 'C': return PRKey_C; case 'D': return PRKey_D; case 'E': return PRKey_E;
	case 'F': return PRKey_F; case 'G': return PRKey_G; case 'H': return PRKey_H; case 'I': return PRKey_I; case 'J': return PRKey_J;
	case 'K': return PRKey_K; case 'L': return PRKey_L; case 'M': return PRKey_M; case 'N': return PRKey_N; case 'O': return PRKey_O;
	case 'P': return PRKey_P; case 'Q': return PRKey_Q; case 'R': return PRKey_R; case 'S': return PRKey_S; case 'T': return PRKey_T;
	case 'U': return PRKey_U; case 'V': return PRKey_V; case 'W': return PRKey_W; case 'X': return PRKey_X; case 'Y': return PRKey_Y;
	case 'Z': return PRKey_Z;
	case VK_OEM_3: return PRKey_Grave; case VK_OEM_MINUS: return PRKey_Subtract; case VK_OEM_PLUS: return PRKey_Equals;
	case VK_OEM_5: return PRKey_Backslash; case VK_OEM_4: return PRKey_LeftBracket; case VK_OEM_6: return PRKey_RightBracket;
	case VK_OEM_1: return PRKey_Semicolon; case VK_OEM_7: return PRKey_Quotation;
	case VK_OEM_COMMA: return PRKey_Comma; case VK_OEM_PERIOD: return PRKey_Period; case VK_OEM_2: return PRKey_Slash;
	case VK_INSERT: return PRKey_Insert; case VK_DELETE: return PRKey_Delete; case VK_HOME: return PRKey_Home; case VK_END: return PRKey_End;
	case VK_PRIOR: return PRKey_PageUp; case VK_NEXT: return PRKey_PageDown;
	case VK_CONTROL: return GetKeyState ( VK_LCONTROL ) ? PRKey_LeftCtrl : PRKey_RightCtrl;
	case VK_MENU: return GetKeyState ( VK_LMENU ) ? PRKey_LeftAlt : PRKey_RightAlt;
	case VK_SHIFT: return GetKeyState ( VK_LSHIFT ) ? PRKey_LeftShift : PRKey_RightShift;
	case VK_LWIN: return PRKey_LeftWin; case VK_RWIN: return PRKey_RightWin;
	default: return PRKey_Unknown;
#elif PRPlatformMicrosoftWindowsRT
		using namespace Windows::System;
	case VirtualKey::Left: return PRKey_Left; case VirtualKey::Right: return PRKey_Right;
	case VirtualKey::Up: return PRKey_Up; case VirtualKey::Down: return PRKey_Down;
	case VirtualKey::A: return PRKey_A; case VirtualKey::B: return PRKey_B; case VirtualKey::C: return PRKey_C; case VirtualKey::D: return PRKey_D;
	case VirtualKey::E: return PRKey_E; case VirtualKey::F: return PRKey_F; case VirtualKey::G: return PRKey_G; case VirtualKey::H: return PRKey_H;
	case VirtualKey::I: return PRKey_I; case VirtualKey::J: return PRKey_J; case VirtualKey::K: return PRKey_K; case VirtualKey::L: return PRKey_L;
	case VirtualKey::M: return PRKey_M; case VirtualKey::N: return PRKey_N; case VirtualKey::O: return PRKey_O; case VirtualKey::P: return PRKey_P;
	case VirtualKey::Q: return PRKey_Q; case VirtualKey::R: return PRKey_R; case VirtualKey::S: return PRKey_S; case VirtualKey::T: return PRKey_T;
	case VirtualKey::U: return PRKey_U; case VirtualKey::V: return PRKey_V; case VirtualKey::W: return PRKey_W; case VirtualKey::X: return PRKey_X;
	case VirtualKey::Y: return PRKey_Y; case VirtualKey::Z: return PRKey_Z;
	case VirtualKey::F1: return PRKey_F1; case VirtualKey::F2: return PRKey_F2; case VirtualKey::F3: return PRKey_F3;
	case VirtualKey::F4: return PRKey_F4; case VirtualKey::F5: return PRKey_F5; case VirtualKey::F6: return PRKey_F6;
	case VirtualKey::F7: return PRKey_F7; case VirtualKey::F8: return PRKey_F8; case VirtualKey::F9: return PRKey_F9;
	case VirtualKey::F10: return PRKey_F10; case VirtualKey::F11: return PRKey_F11; case VirtualKey::F12: return PRKey_F12;
	case VirtualKey::Number0: return PRKey_0; case VirtualKey::Number1: return PRKey_1; case VirtualKey::Number2: return PRKey_2;
	case VirtualKey::Number3: return PRKey_3; case VirtualKey::Number4: return PRKey_4; case VirtualKey::Number5: return PRKey_5;
	case VirtualKey::Number6: return PRKey_6; case VirtualKey::Number7: return PRKey_7; case VirtualKey::Number8: return PRKey_8;
	case VirtualKey::Number9: return PRKey_9;
	case VirtualKey::Back: return PRKey_Backspace; case VirtualKey::Enter: return PRKey_Return; case VirtualKey::Tab: return PRKey_Tab;
	case VirtualKey::CapitalLock: return PRKey_CapsLock; case VirtualKey::Escape: return PRKey_Escape; case VirtualKey::Space: return PRKey_Space;
	case VirtualKey::LeftControl: return PRKey_LeftCtrl; case VirtualKey::RightControl: return PRKey_RightCtrl;
	case VirtualKey::LeftMenu: return PRKey_LeftAlt; case VirtualKey::RightMenu: return PRKey_RightAlt;
	case VirtualKey::LeftShift: return PRKey_LeftShift; case VirtualKey::RightShift: return PRKey_RightShift;
	case VirtualKey::LeftWindows: return PRKey_LeftWin; case VirtualKey::RightWindows: return PRKey_RightWin;
	case VirtualKey::Insert: return PRKey_Insert; case VirtualKey::Delete: return PRKey_Delete; case VirtualKey::Home: return PRKey_Home;
	case VirtualKey::End: return PRKey_End; case VirtualKey::PageUp: return PRKey_PageUp; case VirtualKey::PageDown: return PRKey_PageDown;
	default:
		if ( key == 219 ) return PRKey_LeftBracket; if ( key == 221 ) return PRKey_RightBracket;
		if ( key == 220 ) return PRKey_Backslash; if ( key == 191 ) return PRKey_Slash;
		if ( key == 188 ) return PRKey_Comma; if ( key == 190 ) return PRKey_Period;
		if ( key == 189 ) return PRKey_Subtract; if ( key == 187 ) return PRKey_Equals;
		if ( key == 186 ) return PRKey_Semicolon; if ( key == 192 ) return PRKey_Grave;
		if ( key == 222 ) return PRKey_Quotation;
		break;
#elif PRPlatformAppleFamily
	case 0x7E: return PRKey_Up; case 0x7D: return PRKey_Down; case 0x7B: return PRKey_Left; case 0x7C: return PRKey_Right;
	case 0x24: return PRKey_Return; case 0x31: return PRKey_Space; case 0x33: return PRKey_Backspace;
	case 0x30: return PRKey_Tab; case 0x35: return PRKey_Escape;
	case 0x7A: return PRKey_F1; case 0x78: return PRKey_F2; case 0x63: return PRKey_F3; case 0x76: return PRKey_F4;
	case 0x60: return PRKey_F5; case 0x61: return PRKey_F6; case 0x62: return PRKey_F7; case 0x64: return PRKey_F8;
	case 0x65: return PRKey_F9; case 0x6D: return PRKey_F10; case 0x67: return PRKey_F11; case 0x6F: return PRKey_F12;
	case 0x1D: return PRKey_0; case 0x12: return PRKey_1; case 0x13: return PRKey_2; case 0x14: return PRKey_3; case 0x15: return PRKey_4;
	case 0x17: return PRKey_5; case 0x16: return PRKey_6; case 0x1A: return PRKey_7; case 0x1C: return PRKey_8; case 0x19: return PRKey_9;
	case 0x00: return PRKey_A; case 0x0B: return PRKey_B; case 0x08: return PRKey_C; case 0x02: return PRKey_D; case 0x0E: return PRKey_E;
	case 0x03: return PRKey_F; case 0x05: return PRKey_G; case 0x04: return PRKey_H; case 0x22: return PRKey_I; case 0x26: return PRKey_J;
	case 0x28: return PRKey_K; case 0x25: return PRKey_L; case 0x2E: return PRKey_M; case 0x2D: return PRKey_N; case 0x1F: return PRKey_O;
	case 0x23: return PRKey_P; case 0x0C: return PRKey_Q; case 0x0F: return PRKey_R; case 0x01: return PRKey_S; case 0x11: return PRKey_T;
	case 0x20: return PRKey_U; case 0x09: return PRKey_V; case 0x0D: return PRKey_W; case 0x07: return PRKey_X; case 0x10: return PRKey_Y;
	case 0x06: return PRKey_Z;
	case 0x32: return PRKey_Grave; case 0x1B: return PRKey_Subtract; case 0x18: return PRKey_Equals;
	case 0x2A: return PRKey_Backslash; case 0x21: return PRKey_LeftBracket; case 0x1E: return PRKey_RightBracket;
	case 0x29: return PRKey_Semicolon; case 0x27: return PRKey_Quotation;
	case 0x2B: return PRKey_Comma; case 0x2F: return PRKey_Period; case 0x2C: return PRKey_Slash;
	case 0x72: return PRKey_Insert; case 0x75: return PRKey_Delete; case 0x73: return PRKey_Home; case 0x77: return PRKey_End;
	case 0x74: return PRKey_PageUp; case 0x79: return PRKey_PageDown;
	case 0x3B: return PRKey_LeftCtrl; case 0x3E: return PRKey_RightCtrl;
	case 0x3A: return PRKey_LeftAlt; case 0x3D: return PRKey_RightAlt;
	case 0x38: return PRKey_LeftShift; case 0x3C: return PRKey_RightShift;
	case 0x37: return PRKey_LeftWin; case 0x36: return PRKey_RightWin;
	default: return PRKey_Unknown;
#elif PRPlatformUNIX
	case XK_Up: return PRKey_Up; case XK_Down: return PRKey_Down; case XK_Left: return PRKey_Left; case XK_Right: return PRKey_Right;
	case XK_Return: return PRKey_Return; case XK_space: return PRKey_Space; case XK_BackSpace: return PRKey_Backspace;
	case XK_Tab: return PRKey_Tab; case XK_Escape: return PRKey_Escape;
	case XK_F1: return PRKey_F1; case XK_F2: return PRKey_F2; case XK_F3: return PRKey_F3; case XK_F4: return PRKey_F4;
	case XK_F5: return PRKey_F5; case XK_F6: return PRKey_F6; case XK_F7: return PRKey_F7; case XK_F8: return PRKey_F8;
	case XK_F9: return PRKey_F9; case XK_F10: return PRKey_F10; case XK_F11: return PRKey_F11; case XK_F12: return PRKey_F12;
	case XK_0: return PRKey_0; case XK_1: return PRKey_1; case XK_2: return PRKey_2; case XK_3: return PRKey_3; case XK_4: return PRKey_4;
	case XK_5: return PRKey_5; case XK_6: return PRKey_6; case XK_7: return PRKey_7; case XK_8: return PRKey_8; case XK_9: return PRKey_9;
	case XK_A: return PRKey_A; case XK_B: return PRKey_B; case XK_C: return PRKey_C; case XK_D: return PRKey_D; case XK_E: return PRKey_E;
	case XK_F: return PRKey_F; case XK_G: return PRKey_G; case XK_H: return PRKey_H; case XK_I: return PRKey_I; case XK_J: return PRKey_J;
	case XK_K: return PRKey_K; case XK_L: return PRKey_L; case XK_M: return PRKey_M; case XK_N: return PRKey_N; case XK_O: return PRKey_O;
	case XK_P: return PRKey_P; case XK_Q: return PRKey_Q; case XK_R: return PRKey_R; case XK_S: return PRKey_S; case XK_T: return PRKey_T;
	case XK_U: return PRKey_U; case XK_V: return PRKey_V; case XK_W: return PRKey_W; case XK_X: return PRKey_X; case XK_Y: return PRKey_Y;
	case XK_Z: return PRKey_Z;
	case XK_grave: return PRKey_Grave; case XK_minus: return PRKey_Subtract; case XK_equal: return PRKey_Equals;
	case XK_backslash: return PRKey_Backslash; case XK_bracketleft: return PRKey_LeftBracket; case XK_bracketright: return PRKey_RightBracket;
	case XK_semicolon: return PRKey_Semicolon; case XK_apostrophe: return PRKey_Quotation;
	case XK_comma: return PRKey_Comma; case XK_period: return PRKey_Period; case XK_slash: return PRKey_Slash;
	case XK_Insert: return PRKey_Insert; case XK_Delete: return PRKey_Delete; case XK_Home: return PRKey_Home; case XK_End: return PRKey_End;
	case XK_Page_Up: return PRKey_PageUp; case XK_Page_Down: return PRKey_PageDown;
	case XK_Control_L: return PRKey_LeftCtrl; case XK_Control_R: return PRKey_RightCtrl;
	case XK_Alt_L: return PRKey_LeftAlt; case XK_Alt_R: return PRKey_RightAlt;
	case XK_Shift_L: return PRKey_LeftShift; case XK_Shift_R: return PRKey_RightShift;
	case XK_Super_L: return PRKey_LeftWin; case XK_Super_R: return PRKey_RightWin;
	default: PRKey_Unknown;
#elif PRPlatformGoogleAndroid
	case AKEYCODE_DPAD_UP: return PRKey_Up; case AKEYCODE_DPAD_DOWN: return PRKey_Down; case AKEYCODE_DPAD_LEFT: return PRKey_Left; case AKEYCODE_DPAD_RIGHT: return PRKey_Right;
	case AKEYCODE_ENTER: return PRKey_Return; case AKEYCODE_SPACE: return PRKey_Space; case AKEYCODE_BACK: return PRKey_Backspace;
	case AKEYCODE_TAB: return PRKey_Tab; case AKEYCODE_ESCAPE: return PRKey_Escape;
	case AKEYCODE_F1: return PRKey_F1; case AKEYCODE_F2: return PRKey_F2; case AKEYCODE_F3: return PRKey_F3; case AKEYCODE_F4: return PRKey_F4;
	case AKEYCODE_F5: return PRKey_F5; case AKEYCODE_F6: return PRKey_F6; case AKEYCODE_F7: return PRKey_F7; case AKEYCODE_F8: return PRKey_F8;
	case AKEYCODE_F9: return PRKey_F9; case AKEYCODE_F10: return PRKey_F10; case AKEYCODE_F11: return PRKey_F11; case AKEYCODE_F12: return PRKey_F12;
	case AKEYCODE_0: return PRKey_0; case AKEYCODE_1: return PRKey_1; case AKEYCODE_2: return PRKey_2; case AKEYCODE_3: return PRKey_3; case AKEYCODE_4: return PRKey_4;
	case AKEYCODE_5: return PRKey_5; case AKEYCODE_6: return PRKey_6; case AKEYCODE_7: return PRKey_7; case AKEYCODE_8: return PRKey_8; case AKEYCODE_9: return PRKey_9;
	case AKEYCODE_A: return PRKey_A; case AKEYCODE_B: return PRKey_B; case AKEYCODE_C: return PRKey_C; case AKEYCODE_D: return PRKey_D; case AKEYCODE_E: return PRKey_E;
	case AKEYCODE_F: return PRKey_F; case AKEYCODE_G: return PRKey_G; case AKEYCODE_H: return PRKey_H; case AKEYCODE_I: return PRKey_I; case AKEYCODE_J: return PRKey_J;
	case AKEYCODE_K: return PRKey_K; case AKEYCODE_L: return PRKey_L; case AKEYCODE_M: return PRKey_M; case AKEYCODE_N: return PRKey_N; case AKEYCODE_O: return PRKey_O;
	case AKEYCODE_P: return PRKey_P; case AKEYCODE_Q: return PRKey_Q; case AKEYCODE_R: return PRKey_R; case AKEYCODE_S: return PRKey_S; case AKEYCODE_T: return PRKey_T;
	case AKEYCODE_U: return PRKey_U; case AKEYCODE_V: return PRKey_V; case AKEYCODE_W: return PRKey_W; case AKEYCODE_X: return PRKey_X; case AKEYCODE_Y: return PRKey_Y;
	case AKEYCODE_Z: return PRKey_Z;
	case AKEYCODE_GRAVE: return PRKey_Grave; case AKEYCODE_MINUS: return PRKey_Subtract; case AKEYCODE_EQUALS: return PRKey_Equals;
	case AKEYCODE_BACKSLASH: return PRKey_Backslash; case AKEYCODE_LEFT_BRACKET: return PRKey_LeftBracket; case AKEYCODE_RIGHT_BRACKET: return PRKey_RightBracket;
	case AKEYCODE_SEMICOLON: return PRKey_Semicolon; case AKEYCODE_APOSTROPHE: return PRKey_Quotation;
	case AKEYCODE_COMMA: return PRKey_Comma; case AKEYCODE_PERIOD: return PRKey_Period; case AKEYCODE_SLASH: return PRKey_Slash;
	case AKEYCODE_PAGE_UP: return PRKey_PageUp; case AKEYCODE_PAGE_DOWN: return PRKey_PageDown; case AKEYCODE_MOVE_HOME: return PRKey_Home; case AKEYCODE_MOVE_END: return PRKey_End;
	case AKEYCODE_CTRL_LEFT: return PRKey_LeftCtrl; case AKEYCODE_CTRL_RIGHT: return PRKey_RightCtrl;
	case AKEYCODE_ALT_LEFT: return PRKey_LeftAlt; case AKEYCODE_ALT_RIGHT: return PRKey_RightAlt;
	case AKEYCODE_SHIFT_LEFT: return PRKey_LeftShift; case AKEYCODE_SHIFT_RIGHT: return PRKey_RightShift;
	case AKEYCODE_META_LEFT: return PRKey_LeftWin; case AKEYCODE_META_RIGHT: return PRKey_RightWin;
	default: return PRKey_Unknown;
#endif
	}
	return PRKey_Unknown;
}

PRApp * g_sharedApp;

#if PRPlatformMicrosoftWindowsNT
int g_MouseButton;
#elif PRPlatformMicrosoftWindowsRT
namespace polyram {
	ref class PRWinRTFramework sealed : public Windows::ApplicationModel::Core::IFrameworkView {
	private:
		PRRendererType rendererType;

		bool m_windowClosed;
		bool m_windowVisible;

	internal:
		PRWinRTFramework ( PRRendererType rendererType ) {
			this->rendererType = rendererType;

			m_windowClosed = false;
			m_windowVisible = false;
		}

	public:
		virtual void Initialize ( Windows::ApplicationModel::Core::CoreApplicationView ^ appView ) {
			using namespace Windows::Foundation;
			using namespace Windows::ApplicationModel::Core;
			using namespace Windows::ApplicationModel::Activation;
			appView->Activated += ref new TypedEventHandler<CoreApplicationView^, IActivatedEventArgs^> ( this, &PRWinRTFramework::OnActivated );
		}

		virtual void SetWindow ( Windows::UI::Core::CoreWindow ^ window ) {
			PRApp::sharedApp ()->window = window;

			using namespace Windows::Foundation;
			using namespace Windows::UI::Core;
			window->VisibilityChanged += ref new TypedEventHandler<CoreWindow^, VisibilityChangedEventArgs^> ( this, &PRWinRTFramework::OnVisibilityChanged );
			window->Closed += ref new TypedEventHandler<CoreWindow^, CoreWindowEventArgs^> ( this, &PRWinRTFramework::OnWindowClosed );
			window->SizeChanged += ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^> ( this, &PRWinRTFramework::OnResized );
			window->KeyDown += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^> ( this, &PRWinRTFramework::OnKeyDown );
			window->KeyUp += ref new TypedEventHandler<CoreWindow^, KeyEventArgs^> ( this, &PRWinRTFramework::OnKeyUp );
			window->PointerPressed += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerPressed );
			window->PointerReleased += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerReleased );
			window->PointerMoved += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerMoved );
			window->PointerWheelChanged += ref new TypedEventHandler<CoreWindow^, PointerEventArgs^> ( this, &PRWinRTFramework::OnPointerWheel );
		}

		virtual void Load ( Platform::String ^ entryPoint ) { }

		virtual void Run () {
			switch ( rendererType ) {
			case PRRendererType_Direct3D11:
				PRApp::sharedApp ()->setGraphicsContext ( new PRGraphicsContext_Direct3D11 ( PRApp::sharedApp () ) );
				break;
			case PRRendererType_Direct3D12:
				PRApp::sharedApp ()->setGraphicsContext ( new PRGraphicsContext_Direct3D12 ( PRApp::sharedApp () ) );
				break;
			default:
				throw std::runtime_error ( "Cannot use this renderer version in this platform." );
			}

			PRApp::sharedApp ()->getGame ()->onInitialize ();

			double elapsedTime, lastTime = PRCurrentSec (), currentTime, calcFps = 0;
			while ( !m_windowClosed ) {
				if ( m_windowVisible ) {
					elapsedTime = ( currentTime = PRCurrentSec () ) - lastTime;
					lastTime = currentTime;

					if ( PRApp::sharedApp ()->getGame () != nullptr ) {
						PRApp::sharedApp ()->getGame ()->onUpdate ( elapsedTime );
						PRApp::sharedApp ()->getGame ()->onDraw ( elapsedTime );
					}
				}

				PRApp::sharedApp ()->window->Dispatcher->ProcessEvents ( Windows::UI::Core::CoreProcessEventsOption::ProcessAllIfPresent );
			}
		}

		virtual void Uninitialize () { auto game = PRApp::sharedApp ()->getGame (); if ( game ) game->onDestroy (); }

	private:
		void OnActivated ( Windows::ApplicationModel::Core::CoreApplicationView^ CoreAppView, Windows::ApplicationModel::Activation::IActivatedEventArgs^ Args ) {
			Windows::UI::Core::CoreWindow^ window = Windows::UI::Core::CoreWindow::GetForCurrentThread ();
			window->Activate ();
			m_windowClosed = false;
		}

	private:
		void OnVisibilityChanged ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::VisibilityChangedEventArgs^ e ) { m_windowVisible = true; }
		void OnWindowClosed ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::CoreWindowEventArgs^ e ) { m_windowClosed = true; }
		void OnResized ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ e )
		{
			if ( PRApp::sharedApp ()->getGame () ) PRApp::sharedApp ()->getGame ()->onResized ();
		}
		void OnKeyDown ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onKeyDown ( keyConv ( ( int ) e->VirtualKey ) );
		}
		void OnKeyUp ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::KeyEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onKeyUp ( keyConv ( ( int ) e->VirtualKey ) );
		}
		void OnPointerPressed ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () ) {
				int mouseButton;
				if ( e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMButton_Left;
				else if ( e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMButton_Right;
				else if ( e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMButton_Middle;
				PRApp::sharedApp ()->getGame ()->onMouseDown ( ( PRMButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}
		void OnPointerReleased ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () ) {
				int mouseButton;
				if ( !e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMButton_Left;
				else if ( !e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMButton_Right;
				else if ( !e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMButton_Middle;
				PRApp::sharedApp ()->getGame ()->onMouseUp ( ( PRMButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}
		void OnPointerMoved ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () ) {
				int mouseButton = PRMButton_None;
				if ( e->CurrentPoint->Properties->IsLeftButtonPressed ) mouseButton |= PRMButton_Left;
				else if ( e->CurrentPoint->Properties->IsRightButtonPressed ) mouseButton |= PRMButton_Right;
				else if ( e->CurrentPoint->Properties->IsMiddleButtonPressed ) mouseButton |= PRMButton_Middle;
				PRApp::sharedApp ()->getGame ()->onMouseMove ( ( PRMButton ) mouseButton,
					( int ) e->CurrentPoint->Position.X, ( int ) e->CurrentPoint->Position.Y );
			}
		}

		void OnPointerWheel ( Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::PointerEventArgs^ e ) {
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseWheel ( 0, e->CurrentPoint->Properties->MouseWheelDelta );
		}
	};

	ref class PRWinRTFrameworkView sealed : public Windows::ApplicationModel::Core::IFrameworkViewSource {
	private: PRRendererType rendererType;
	internal: PRWinRTFrameworkView ( PRRendererType rendererType ) { this->rendererType = rendererType; }
	public: virtual Windows::ApplicationModel::Core::IFrameworkView^ CreateView () { return ref new PRWinRTFramework ( rendererType ); }
	};
}
#elif PRPlatformAppleOSX
#define WINDOW_STYLE NSMiniaturizableWindowMask | NSClosableWindowMask | NSTitledWindowMask
int g_MouseButton;
int g_MouseX, g_MouseY;
#elif PRPlatformUNIX
int g_MouseButton;
int g_MouseX, g_MouseY;
#endif

PRApp::PRApp ( PRGame * game, PRRendererType rendererType, int width, int height, std::string & title
#if PRPlatformGoogleAndroid
	, struct android_app * state
#endif
) : m_game ( game ), m_graphicsContext ( nullptr ) {
	g_sharedApp = this;
#if PRPlatformMicrosoftWindowsNT
	WNDCLASS wndClass = { 0, };
	wndClass.style = CS_HREDRAW | CS_VREDRAW;
	wndClass.hInstance = GetModuleHandle ( nullptr );
	wndClass.hIcon = LoadIcon ( nullptr, IDI_APPLICATION );
	wndClass.hCursor = LoadCursor ( nullptr, IDC_ARROW );
	wndClass.lpfnWndProc = static_cast<WNDPROC> ( [] ( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam ) -> LRESULT {
		switch ( uMsg ) {
		case WM_KEYDOWN:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onKeyDown ( keyConv ( ( int ) wParam ) );
			break;
		case WM_KEYUP:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onKeyUp ( keyConv ( ( int ) wParam ) );
			break;

		case WM_LBUTTONDOWN:
			g_MouseButton |= PRMButton_Left;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Left, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_RBUTTONDOWN:
			g_MouseButton |= PRMButton_Right;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Right, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MBUTTONDOWN:
			g_MouseButton |= PRMButton_Middle;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Middle, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_LBUTTONUP:
			g_MouseButton &= PRMButton_Left;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Left, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_RBUTTONUP:
			g_MouseButton &= PRMButton_Right;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Right, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MBUTTONUP:
			g_MouseButton &= PRMButton_Middle;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Middle, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MOUSEMOVE:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseMove ( ( PRMButton ) g_MouseButton, LOWORD ( lParam ), HIWORD ( lParam ) );
			break;
		case WM_MOUSEWHEEL:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseWheel ( 0, ( int ) GET_WHEEL_DELTA_WPARAM ( wParam ) / WHEEL_DELTA );
			break;
		case WM_MOUSEHWHEEL:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseWheel ( ( int ) GET_WHEEL_DELTA_WPARAM ( wParam ) / WHEEL_DELTA, 0 );
			break;

		case WM_ACTIVATE:
			if ( PRApp::sharedApp ()->getGame () ) {
				if ( wParam != WA_INACTIVE ) PRApp::sharedApp ()->getGame ()->onActivated ();
				else PRApp::sharedApp ()->getGame ()->onDeactivated ();
			}
			break;
		case WM_SIZE:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onResized ();
			break;
		default: return DefWindowProc ( hWnd, uMsg, wParam, lParam );
		}
		return 0;
	} );
	wndClass.lpszClassName = TEXT ( "libPolyram" );
	if ( RegisterClass ( &wndClass ) == 0 )
		throw std::runtime_error ( "Failed register window class." );

	RECT adjust = { 0, 0, width, height };
	AdjustWindowRect ( &adjust, WS_OVERLAPPEDWINDOW, FALSE );
	int _width = adjust.right - adjust.left, _height = adjust.bottom - adjust.top;
	int x = GetSystemMetrics ( SM_CXSCREEN ) / 2 - _width / 2, y = GetSystemMetrics ( SM_CYSCREEN ) / 2 - _height / 2;

	USES_CONVERSION;

	m_hWnd = CreateWindow ( TEXT ( "libPolyram" ), A2W ( title.c_str () ),
		WS_OVERLAPPEDWINDOW, x, y, _width, _height, nullptr, nullptr, wndClass.hInstance, nullptr );
	if ( m_hWnd == 0 )
		throw std::runtime_error ( "Failed create window." );

	switch ( rendererType ) {
	//case PRRendererType_Direct3D9: m_graphicsContext = new PRGraphicsContext_Direct3D9 ( this ); break;
	case PRRendererType_Direct3D11: m_graphicsContext = new PRGraphicsContext_Direct3D11 ( this ); break;
	//case PRRendererType_Direct3D12: m_graphicsContext = new PRGraphicsContext_Direct3D12 ( this ); break;
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	//case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	//case PRRendererType_Vulkan1: m_graphicsContext = new PRGraphicsContext_Vulkan ( this ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformMicrosoftWindowsRT
	m_rendererType = rendererType;
#elif PRPlatformAppleOSX
	window = [ [ NSWindow alloc ] initWithContentRect:CGRectMake ( 0, 0, width, height ) styleMask : WINDOW_STYLE backing : NSBackingStoreBuffered defer : NO ];
	if ( window == nil )
		throw std::runtime_error ( "Failed create NSWindow." );
	window.title = [ NSString stringWithUTF8String : title ];
	[window center];
	[window makeKeyAndOrderFront : window];

	NSView * view = window.contentView;
	if ( view == nil )
		throw std::runtime_error ( "Failed to retrieve content view for window." );

	NSView * renegaderView = [ [ NSView alloc ] initWithFrame:CGRectMake ( 0, 0, width, height ) ];
	if ( renegaderView == nil )
		throw std::runtime_error ( "Failed create NSView." );
	window.contentView = renegaderView;
	view = nil;

	[window makeKeyWindow];

	switch ( rendererType ) {
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	case PRRendererType_Metal: m_graphicsContext = new PRGraphicsContext_Metal ( this ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformUNIX
	display = XOpenDisplay ( nullptr );
	if ( display == nullptr )
		throw std::runtime_error ( "Cannot connect to X server." );

	Window root = DefaultRootWindow ( display );

	GLint attr [] = {
		GLX_RGBA, GLX_DEPTH_SIZE, 16, GLX_STENCIL_SIZE, 8, GLX_DOUBLEBUFFER, true, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
		GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR, None
	};
	visualInfo = glXChooseVisual ( display, 0, attr );
	if ( visualInfo == nullptr )
		throw std::runtime_error ( "No appropriate visual found." );

	colorMap = XCreateColormap ( display, root, visualInfo->visual, AllocNone );

	XSetWindowAttributes setWindowAttr = { 0, };
	setWindowAttr.colormap = colorMap;
	setWindowAttr.background_pixmap = None;
	setWindowAttr.border_pixel = 0;
	setWindowAttr.event_mask = KeyPressMask | KeyReleaseMask | ButtonPressMask | ButtonReleaseMask | ButtonMotionMask;

	window = XCreateWindow ( display, root, 0, 0, this->width = width, this->height = height, 0, visualInfo->depth, InputOutput,
		visualInfo->visual, CWColormap | CWEventMask, &setWindowAttr );
	if ( !window )
		throw std::runtime_error ( "Failed create window." );

	Atom wmDelete = XInternAtom ( display, "WM_DELETE_WINDOW", true );
	XSetWMProtocols ( display, window, &wmDelete, 1 );

	XStoreName ( display, window, "libPolyram" );
	XMapWindow ( display, window );

	switch ( rendererType ) {
	case PRRendererType_OpenGL1:
	case PRRendererType_OpenGL2:
	case PRRendererType_OpenGL3:
	case PRRendererType_OpenGL4: m_graphicsContext = new PRGraphicsContext_OpenGL ( this, rendererType ); break;
	default: throw std::runtime_error ( "Illegal Graphics Renderer." );
	}
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	m_rendererType = rendererType;
	memset ( &this->engine, 0, sizeof ( this->engine ) );
	state->userData = &engine;
	state->onAppCmd = [] ( struct android_app* app, int32_t cmd ) {
		struct engine* engine = ( struct engine* )app->userData;
		switch ( cmd ) {
		case APP_CMD_SAVE_STATE:
			break;
		case APP_CMD_INIT_WINDOW:
			if ( engine->app->window != nullptr )
			{
				switch ( PRApp::sharedApp ()->m_rendererType ) {
				case PRRendererType_OpenGLES1:
				case PRRendererType_OpenGLES2:
				case PRRendererType_OpenGLES3:
					PRApp::sharedApp ()->m_graphicsContext =
						new PRGraphicsContext_OpenGL ( PRApp::sharedApp (), PRApp::sharedApp ()->m_rendererType );
					break;
				default: throw std::runtime_error ( "Illegal Graphics Renderer." );
				}
			}
			break;
		case APP_CMD_TERM_WINDOW:
			SAFE_DELETE ( PRApp::sharedApp ()->m_graphicsContext );
			break;
		case APP_CMD_GAINED_FOCUS:
			if ( PRApp::sharedApp ()->engine.accelerometerSensor != nullptr ) {
				ASensorEventQueue_enableSensor ( PRApp::sharedApp ()->engine.sensorEventQueue,
					PRApp::sharedApp ()->engine.accelerometerSensor );
				ASensorEventQueue_setEventRate ( PRApp::sharedApp ()->engine.sensorEventQueue,
					PRApp::sharedApp ()->engine.accelerometerSensor, ( 1000L / 60 ) * 1000 );
			}
			break;
		}
	};
	state->onInputEvent = [] ( struct android_app* app, AInputEvent* event ) -> int32_t {
		PRGame * scene = PRApp::sharedApp ()->getGame ();
		switch ( AInputEvent_getType ( event ) ) {
		case AINPUT_EVENT_TYPE_KEY:
			if ( scene ) {
				int32_t action = AKeyEvent_getAction ( event );
				int32_t keyCode = AKeyEvent_getKeyCode ( event );
				if ( action == AKEY_EVENT_ACTION_DOWN )
					scene->onKeyDown ( keyConv ( keyCode ) );
				else if ( action == AKEY_EVENT_ACTION_UP )
					scene->onKeyUp ( keyConv ( keyCode ) );
			}
			else return 0;
			return 1;
		case AINPUT_EVENT_TYPE_MOTION:
			if ( scene ) {
				int32_t action = AMotionEvent_getAction ( event );
				int32_t maskedAction = action & AMOTION_EVENT_ACTION_MASK;
				int32_t pind = ( action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK ) >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
				int32_t pid = AMotionEvent_getPointerId ( event, pind );

				switch ( maskedAction ) {
				case AMOTION_EVENT_ACTION_DOWN:
					scene->onTouchDown ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_POINTER_DOWN:
					scene->onTouchDown ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_UP:
					scene->onTouchUp ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_POINTER_UP:
					scene->onTouchUp ( pid, AMotionEvent_getX ( event, pind ), AMotionEvent_getY ( event, pind ) );
					break;
				case AMOTION_EVENT_ACTION_MOVE:
					for ( int i = 0; i < AMotionEvent_getPointerCount ( event ); ++i ) {
						int32_t pid = AMotionEvent_getPointerId ( event, i );
						scene->onTouchMove ( pid, AMotionEvent_getX ( event, i ), AMotionEvent_getY ( event, i ) );
					}
					break;
				}
			}
			return 1;
		}
		return 0;
	};
	this->engine.app = state;

	this->engine.sensorManager = ASensorManager_getInstance ();
	this->engine.accelerometerSensor = ASensorManager_getDefaultSensor ( engine.sensorManager, ASENSOR_TYPE_ACCELEROMETER );
	this->engine.sensorEventQueue = ASensorManager_createEventQueue ( engine.sensorManager, state->looper, LOOPER_ID_USER, NULL, NULL );

	if ( state->savedState != NULL )
		engine.state = state->savedState;
#elif PRPlatformWeb

#endif
}

PRApp::~PRApp () {
	SAFE_DELETE ( m_graphicsContext );
#if PRPlatformMicrosoftWindowsNT
	DestroyWindow ( m_hWnd );
#elif PRPlatformMicrosoftWindowsRT

#elif PRPlatformAppleOSX
	window = nil;
#elif PRPlatformUNIX
	XDestroyWindow ( display, window );
	XFreeColormap ( display, colorMap );
	XCloseDisplay ( display );
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
}

PRGame * PRApp::getGame () { return m_game; }
PRGraphicsContext * PRApp::getGraphicsContext () { return m_graphicsContext; }
void PRApp::setGraphicsContext ( PRGraphicsContext * graphicsContext ) { m_graphicsContext = graphicsContext; }

void PRApp::getClientSize ( int * width, int * height ) {
#if PRPlatformMicrosoftWindowsNT
	RECT rect;
	GetClientRect ( m_hWnd, &rect );
	if ( width ) *width = rect.right - rect.left;
	if ( height ) *height = rect.bottom - rect.top;
#elif PRPlatformMicrosoftWindowsRT
	if ( width ) *width = ( unsigned ) window->Bounds.Width;
	if ( height ) *height = ( unsigned ) window->Bounds.Height;
#elif PRPlatformAppleOSX
	if ( width ) *width = window.contentView.frame.size.width;
	if ( height ) *height = window.contentView.frame.size.height;
#elif PRPlatformUNIX
	if ( width ) *width = this->width;
	if ( height ) *height = this->height;
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	if ( width ) *width = engine.width;
	if ( height ) *height = engine.height;
#elif PRPlatformWeb

#endif
}

bool PRApp::setCursorPosition ( int x, int y ) {
#if PRPlatformMicrosoftWindowsNT
	POINT pos;
	ClientToScreen ( m_hWnd, &pos );
	SetCursorPos ( pos.x, pos.y );
	return true;
#elif PRPlatformMicrosoftWindowsRT

#elif PRPlatformAppleOSX
	CGDirectDisplayID displayID = ( CGDirectDisplayID ) [ [ [ [ NSScreen mainScreen ] deviceDescription ] objectForKey:@"NSScreenNumber"] intValue ];
	CGDisplayMoveCursorToPoint ( displayID, [ window convertRectToScreen : CGRectMake ( x, y, 0, 0 ) ].origin );
	return true;
#elif PRPlatformUNIX
	XMoveWindow ( display, window, x, y );
	XFlush ( display );
	return true;
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
	return false;
}

bool PRApp::setCursorVisible ( bool visible )
{
#if PRPlatformMicrosoftWindowsNT
	ShowCursor ( visible );
	return true;
#elif PRPlatformMicrosoftWindowsRT
	window->PointerCursor = visible ? ref new Windows::UI::Core::CoreCursor ( Windows::UI::Core::CoreCursorType::Arrow, 1 ) : nullptr;
	return true;
#elif PRPlatformAppleOSX
	if ( !visible ) [ NSCursor hide ];
	else [ NSCursor unhide ];
	return true;
#elif PRPlatformUNIX

#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid

#elif PRPlatformWeb

#endif
	return false;
}

void PRApp::run () {
#if !PRPlatformMicrosoftWindowsRT
	double elapsedTime, lastTime = PRCurrentSec (), currentTime;
#endif

#if PRPlatformMicrosoftWindowsNT
	ShowWindow ( m_hWnd, SW_SHOW );
	UpdateWindow ( m_hWnd );

	if ( m_game ) m_game->onInitialize ();

	MSG msg;
	while ( IsWindow ( m_hWnd ) ) {
		if ( PeekMessage ( &msg, NULL, 0, 0, PM_NOREMOVE ) ) {
			if ( !GetMessage ( &msg, NULL, 0, 0 ) )break;
			TranslateMessage ( &msg );
			DispatchMessage ( &msg );
		}
		else {
			elapsedTime = ( currentTime = PRCurrentSec () ) - lastTime;
			lastTime = currentTime;

			if ( m_game != nullptr ) {
				m_game->onUpdate ( elapsedTime );
				m_game->onDraw ( elapsedTime );
			}

			Sleep ( 1 );
		}
	}
#elif PRPlatformMicrosoftWindowsRT
	Windows::ApplicationModel::Core::CoreApplication::Run ( ref new polyram::PRWinRTFrameworkView ( m_rendererType ) );
#elif PRPlatformAppleOSX
	window.isVisible = visible;

	if ( m_game ) m_game->onInitialize ();

	while ( window.isVisible ) {
		NSEvent * event = [ [ NSApplication sharedApp ] nextEventMatchingMask:NSAnyEventMask untilDate : nil inMode : NSDefaultRunLoopMode dequeue : YES ];
		switch ( event.type ) {
		case NSKeyDown:
			if ( LqLauncher::getInstance ()->getGame () )
				LqLauncher::getInstance ()->getGame ()->onKeyDown ( keyConv ( ( int ) event.keyCode ) );
			break;
		case NSKeyUp:
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onKeyUp ( keyConv ( ( int ) event.keyCode ) );
			break;

		case NSLeftMouseDown:
			g_MouseButton |= PRMButton_Left;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Left, g_MouseX, g_MouseY );
			break;
		case NSLeftMouseUp:
			g_MouseButton &= PRMButton_Left;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Left, g_MouseX, g_MouseY );
			break;
		case NSRightMouseDown:
			g_MouseButton |= PRMButton_Right;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Right, g_MouseX, g_MouseY );
			break;
		case NSRightMouseUp:
			g_MouseButton &= PRMButton_Right;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Right, g_MouseX, g_MouseY );
			break;
		case NSOtherMouseDown:
			g_MouseButton |= PRMButton_Middle;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseDown ( PRMButton_Middle, g_MouseX, g_MouseY );
			break;
		case NSOtherMouseUp:
			g_MouseButton &= PRMButton_Middle;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseUp ( PRMButton_Middle, g_MouseX, g_MouseY );
			break;

		case NSMouseMoved:
			g_MouseX = ( int ) event.locationInWindow.x; g_MouseY = ( int ) event.locationInWindow.y;
			if ( PRApp::sharedApp ()->getGame () )
				PRApp::sharedApp ()->getGame ()->onMouseMove ( ( PRMButton ) g_MouseButton, g_MouseX, g_MouseY );
			break;

		default: break;
		}
		[ [ NSApplication sharedApp ] sendEvent:event ];

		elapsedTime = ( currentTime = PRCurrentSec () ) - lastTime;
		lastTime = currentTime;

		if ( m_game != nullptr ) {
			m_game->onUpdate ( elapsedTime );
			m_game->onDraw ( elapsedTime );
		}
	}
#elif PRPlatformUNIX
	if ( m_game ) m_game->onInitialize ();

	XEvent xev;
	bool loopflag = true;
	while ( loopflag ) {
		if ( XPending ( display ) ) {
			XNextEvent ( display, &xev );

			switch ( xev.type ) {
			case KeyPress:
				if ( PRApp::sharedApp ()->getGame () )
					PRApp::sharedApp ()->getGame ()->onKeyDown ( keyConv ( xev.xkey.keycode ) );
				break;
			case KeyRelease:
				if ( PRApp::sharedApp ()->getGame () )
					PRApp::sharedApp ()->getGame ()->onKeyUp ( keyConv ( xev.xkey.keycode ) );
				break;

			case ButtonPress:
				PRMButton button;
				switch ( xev.xbutton.window ) {
				case Button1: button = PRMButton_Left; break;
				case Button2: button = PRMButton_Right; break;
				case Button3: button = PRMButton_Middle; break;
				}

				g_MouseButton |= button;
				if ( PRApp::sharedApp ()->getGame () )
					PRApp::sharedApp ()->getGame ()->onMouseDown ( button, g_MouseX, g_MouseY );
				break;
			case ButtonRelease: {
				PRMButton button;
				switch ( xev.xbutton.window ) {
				case Button1: button = PRMButton_Left; break;
				case Button2: button = PRMButton_Right; break;
				case Button3: button = PRMButton_Middle; break;
				}

				g_MouseButton |= button;
				if ( PRApp::sharedApp ()->getGame () )
					PRApp::sharedApp ()->getGame ()->onMouseUp ( button, g_MouseX, g_MouseY );
			}
								break;
			case MotionNotify:
				g_MouseX = xev.xmotion.x; g_MouseY = xev.xmotion.x;
				if ( PRApp::sharedApp ()->getGame () )
					PRApp::sharedApp ()->getGame ()->onMouseMove ( ( PRMButton ) g_MouseButton, g_MouseX, g_MouseY );
				break;

			case ClientMessage: loopflag = false; break;
			}
		}

		elapsedTime = ( currentTime = PRCurrentSec () ) - lastTime;
		lastTime = currentTime;

		if ( m_game != nullptr ) {
			m_game->onUpdate ( elapsedTime );
			m_game->onDraw ( elapsedTime );
		}
	}
#elif PRPlatformAppleiOS

#elif PRPlatformGoogleAndroid
	engine.animating = 1;
	while ( 1 ) {
		int ident;
		int events;
		struct android_poll_source* source;

		while ( ( ident = ALooper_pollAll ( engine.animating ? 0 : -1, NULL, &events, ( void** ) &source ) ) >= 0 ) {
			if ( source != nullptr )
				source->process ( this->engine.app, source );

			if ( ident == LOOPER_ID_USER ) {
				if ( engine.accelerometerSensor != nullptr ) {
					ASensorEvent event;
					while ( ASensorEventQueue_getEvents ( engine.sensorEventQueue, &event, 1 ) > 0 )
						if ( m_game ) m_game->onAccelerometer ( event.acceleration.x, event.acceleration.y, event.acceleration.z );
				}
			}

			if ( this->engine.app->destroyRequested != 0 ) {
				if ( m_game ) m_game->onDestroy ();
				SAFE_DELETE ( this->m_graphicsContext );
				return;
			}
		}

		if ( engine.animating ) {
			elapsedTime = ( currentTime = PRCurrentSec () ) - lastTime;
			lastTime = currentTime;

			if ( m_game != nullptr ) {
				m_game->onUpdate ( elapsedTime );
				if ( this->m_graphicsContext == nullptr || ( ( PRGraphicsContext_OpenGL* ) this->m_graphicsContext )->display == nullptr )
					continue;
				m_game->onDraw ( elapsedTime );
			}
		}
	}
#elif PRPlatformWeb

#endif
	if ( m_game ) m_game->onDestroy ();
}

void PRApp::exit () {
#if PRPlatformMicrosoftWindowsNT
	PostQuitMessage ( 0 );
#elif PRPlatformMicrosoftWindowsRT
	this->window->Close ();
#elif PRPlatformAppleOSX
	if ( window.isVisible )
		[window orderOut:window];
#elif PRPlatformAppleiOS

#elif PRPlatformUNIX
	XEvent xev;
	xev.type = ClientMessage;
	XSendEvent ( display, window, false, 0, &xev );
#elif PRPlatformGoogleAndroid
	ANativeActivity_finish ( engine.app->activity );
#endif
}

PRApp * PRApp::sharedApp () { return g_sharedApp; }

#if POLYRAM_D3D9
PRGraphicsContext_Direct3D9::PRGraphicsContext_Direct3D9 ( PRApp * app ) {
	IDirect3D9 * d3d;
	if ( !( d3d = Direct3DCreate9 ( D3D_SDK_VERSION ) ) )
		throw std::runtime_error ( "Failed create Direct3D." );

	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

	D3DPRESENT_PARAMETERS pp = { 0, };
	pp.BackBufferWidth = windowWidth;
	pp.BackBufferHeight = windowHeight;
	pp.BackBufferCount = 1;
	pp.BackBufferFormat = D3DFMT_A8R8G8B8;
	pp.EnableAutoDepthStencil = true;
	pp.AutoDepthStencilFormat = D3DFMT_D24S8;
	pp.hDeviceWindow = app->m_hWnd;
	pp.Windowed = true;
	pp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	pp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

	D3DCAPS9 caps;
	d3d->GetDeviceCaps ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &caps );
	if ( FAILED ( d3d->CreateDevice ( D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, app->m_hWnd,
		caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT ? D3DCREATE_HARDWARE_VERTEXPROCESSING : D3DCREATE_SOFTWARE_VERTEXPROCESSING, &pp, &d3dDevice ) ) ) {
		d3dDevice = nullptr;
		d3d->Release ();
		d3d = nullptr;
		throw std::runtime_error ( "Failed create Direct3D Device." );
	}
}

PRGraphicsContext_Direct3D9::~PRGraphicsContext_Direct3D9 () {
	IDirect3D9 * d3dFactory = nullptr;
	if ( d3dDevice ) d3dDevice->GetDirect3D ( &d3dFactory );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( d3dFactory );
}
#endif

#if POLYRAM_D3D11
PRGraphicsContext_Direct3D11::PRGraphicsContext_Direct3D11 ( PRApp * app ) {
	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

	auto flag = D3D11_CREATE_DEVICE_BGRA_SUPPORT |
#if defined ( _DEBUG )
		D3D11_CREATE_DEVICE_DEBUG;
#else
		0;
#endif

#if PRPlatformMicrosoftWindowsNT
	DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };
	swapChainDesc.BufferDesc.Width = windowWidth;
	swapChainDesc.BufferDesc.Height = windowHeight;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = app->m_hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Windowed = true;
	swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D_FEATURE_LEVEL featureLevel;
	if ( FAILED ( D3D11CreateDeviceAndSwapChain ( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, flag,
		nullptr, 0, D3D11_SDK_VERSION, &swapChainDesc, &dxgiSwapChain, &d3dDevice, &featureLevel, &immediateContext ) ) )
		throw std::runtime_error ( "Failed create Direct3D device and Swap Chain." );
#elif PRPlatformMicrosoftWindowsRT
	D3D_FEATURE_LEVEL featureLevel;
	if ( FAILED ( D3D11CreateDevice ( nullptr, D3D_DRIVER_TYPE_HARDWARE, 0, flag, nullptr, 0, D3D11_SDK_VERSION,
		&d3dDevice, &featureLevel, &immediateContext ) ) )
		throw std::runtime_error ( "Failed create Direct3D device." );

	IDXGIDevice2 * dxgiDevice;
	d3dDevice->QueryInterface<IDXGIDevice2> ( &dxgiDevice );

	IDXGIAdapter * dxgiAdapter;
	if ( FAILED ( dxgiDevice->GetAdapter ( &dxgiAdapter ) ) )
		throw std::runtime_error ( "Cannot get IDXGIFactory." );

	IDXGIFactory2 * dxgiFactory;
	if ( FAILED ( dxgiAdapter->GetParent ( __uuidof ( IDXGIFactory2 ), ( void** ) &dxgiFactory ) ) )
		throw std::runtime_error ( "Cannot get IDXGIFactory." );

	DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0, };
	swapChainDesc.Width = windowWidth;
	swapChainDesc.Height = windowHeight;
	swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
	swapChainDesc.BufferCount = 2;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_BACK_BUFFER;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
	swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
	swapChainDesc.Stereo = false;

	if ( FAILED ( dxgiFactory->CreateSwapChainForCoreWindow ( d3dDevice, reinterpret_cast< IUnknown* >( app->window ),
		&swapChainDesc, nullptr, &dxgiSwapChain ) ) )
		throw std::runtime_error ( "Failed create DXGI Swap chain." );

	dxgiDevice->SetMaximumFrameLatency ( 1 );
#endif

	ID3D11Texture2D * backBuffer;
	if ( FAILED ( dxgiSwapChain->GetBuffer ( 0, __uuidof ( ID3D11Texture2D ), ( void ** ) &backBuffer ) ) )
		throw std::runtime_error ( "Failed get buffer from Swap Chain." );

	if ( FAILED ( d3dDevice->CreateRenderTargetView ( backBuffer, nullptr, &renderTargetView ) ) )
		throw std::runtime_error ( "Failed create Render target view." );

	D3D11_TEXTURE2D_DESC descBack;
	backBuffer->GetDesc ( &descBack );
	D3D11_TEXTURE2D_DESC descDepth;
	descDepth.Width = descBack.Width;
	descDepth.Height = descBack.Height;
	descDepth.MipLevels = 1;
	descDepth.ArraySize = 1;
	descDepth.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	descDepth.SampleDesc.Count = 1;
	descDepth.SampleDesc.Quality = 0;
	descDepth.Usage = D3D11_USAGE_DEFAULT;
	descDepth.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	descDepth.CPUAccessFlags = 0;
	descDepth.MiscFlags = 0;
	if ( FAILED ( d3dDevice->CreateTexture2D ( &descDepth, NULL, &depthStencilBuffer ) ) )
		throw std::runtime_error ( "Failed create Depth-stencil buffer." );

	if ( FAILED ( d3dDevice->CreateDepthStencilView ( depthStencilBuffer, nullptr, &depthStencilView ) ) )
		throw std::runtime_error ( "Failed create Depth-stencil view." );

	immediateContext->OMSetRenderTargets ( 1, &renderTargetView, depthStencilView );
	backBuffer->Release ();

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = ( float ) windowWidth;
	viewport.Height = ( float ) windowHeight;
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	immediateContext->RSSetViewports ( 1, &viewport );
}

PRGraphicsContext_Direct3D11::~PRGraphicsContext_Direct3D11 () {
	SAFE_RELEASE ( depthStencilView );
	SAFE_RELEASE ( depthStencilBuffer );
	SAFE_RELEASE ( renderTargetView );
	SAFE_RELEASE ( immediateContext );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( dxgiSwapChain );
}
#endif

#if POLYRAM_D3D12
PRGraphicsContext_Direct3D12::PRGraphicsContext_Direct3D12 ( PRApp * app ) {
	int windowWidth, windowHeight;
	app->getClientSize ( &windowWidth, &windowHeight );

#ifdef _DEBUG
	if ( SUCCEEDED ( D3D12GetDebugInterface ( IID_PPV_ARGS ( &debugLayer ) ) ) )
		debugLayer->EnableDebugLayer ();
#endif
	{
		IDXGIFactory2 * dxgiFactory;
		if ( FAILED ( CreateDXGIFactory2 ( 0, __uuidof ( IDXGIFactory2 ), ( void** ) &dxgiFactory ) ) )
			throw std::runtime_error ( "Failed create DXGI factory." );

		IDXGIAdapter1 * dxgiAdapter;
		if ( FAILED ( dxgiFactory->EnumAdapters1 ( 0, &dxgiAdapter ) ) )
			throw std::runtime_error ( "Failed enumeration DXGI Adapters." );

		if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_12_0, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
			if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_11_0, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
				if ( FAILED ( D3D12CreateDevice ( dxgiAdapter, D3D_FEATURE_LEVEL_9_3, __uuidof ( ID3D12Device ), ( void** ) &d3dDevice ) ) )
					throw std::runtime_error ( "Failed create Device." );

		dxgiAdapter->Release ();
		dxgiFactory->Release ();

		D3D12_COMMAND_QUEUE_DESC commandQueueDesc = { };
		commandQueueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
		commandQueueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		commandQueueDesc.NodeMask = 0;
		commandQueueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		if ( FAILED ( d3dDevice->CreateCommandQueue ( &commandQueueDesc, __uuidof ( ID3D12CommandQueue ), ( void** ) &commandQueue ) ) )
			throw std::runtime_error ( "Failed create Command queue." );

#if PRPlatformMicrosoftWindowsNT
		DXGI_SWAP_CHAIN_DESC swapChainDesc = { 0, };
		swapChainDesc.BufferDesc.Width = windowWidth;
		swapChainDesc.BufferDesc.Height = windowHeight;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.OutputWindow = app->m_hWnd;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
		swapChainDesc.Windowed = true;
		IDXGISwapChain * dxgiSwapChain;
		if ( FAILED ( dxgiFactory->CreateSwapChain ( commandQueue, &swapChainDesc, &dxgiSwapChain ) ) )
			throw std::runtime_error ( "Failed create Swap Chain." );
		if ( FAILED ( dxgiSwapChain->QueryInterface ( __uuidof ( IDXGISwapChain3 ), ( void** ) &this->dxgiSwapChain ) ) )
			throw std::runtime_error ( "Cannot query interface from IDXGISwapChain to IDXGISwapChain3." );
#elif PRPlatformMicrosoftWindowsRT
		DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0, };
		swapChainDesc.Width = windowWidth;
		swapChainDesc.Height = windowHeight;
		swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
		swapChainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapChainDesc.BufferCount = 2;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
		swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapChainDesc.Stereo = false;

		IDXGISwapChain1 * dxgiSwapChain;
		if ( FAILED ( dxgiFactory->CreateSwapChainForCoreWindow ( commandQueue, reinterpret_cast< IUnknown* >( app->window ),
			&swapChainDesc, nullptr, &dxgiSwapChain ) ) )
			throw std::runtime_error ( "Failed create DXGI Swap chain." );
		if ( FAILED ( dxgiSwapChain->QueryInterface ( __uuidof ( IDXGISwapChain3 ), ( void** ) &this->dxgiSwapChain ) ) )
			throw std::runtime_error ( "Cannot query interface from IDXGISwapChain to IDXGISwapChain3." );
#endif

		dxgiFactory->Release ();

		D3D12_DESCRIPTOR_HEAP_DESC descHeapDesc;
		descHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		descHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		descHeapDesc.NumDescriptors = 2;
		descHeapDesc.NodeMask = 0;
		if ( FAILED ( d3dDevice->CreateDescriptorHeap ( &descHeapDesc, __uuidof ( ID3D12DescriptorHeap ), ( void** ) &descriptorHeap ) ) )
			throw std::runtime_error ( "Failed create Descriptor Heap." );
		descriptorHandleIncrementSize = d3dDevice->GetDescriptorHandleIncrementSize ( D3D12_DESCRIPTOR_HEAP_TYPE_RTV );

		D3D12_CPU_DESCRIPTOR_HANDLE descriptorHandle = descriptorHeap->GetCPUDescriptorHandleForHeapStart ();
		for ( UINT n = 0; n < 2; n++ )
		{
			if ( FAILED ( dxgiSwapChain->GetBuffer ( n, __uuidof ( ID3D12Resource ), ( void** ) &renderTargets [ n ] ) ) )
				throw std::runtime_error ( "Failed create Render Target View." );
			d3dDevice->CreateRenderTargetView ( renderTargets [ n ], nullptr, descriptorHandle );
			descriptorHandle.ptr += descriptorHandleIncrementSize;
		}

		if ( FAILED ( d3dDevice->CreateCommandAllocator ( D3D12_COMMAND_LIST_TYPE_DIRECT, __uuidof ( ID3D12CommandAllocator ), ( void** ) &commandAllocator ) ) )
			throw std::runtime_error ( "Failed create Command Allocator." );
	}

	{
		ID3DBlob * signature;
		ID3DBlob * error;
		D3D12_ROOT_SIGNATURE_DESC rootSignatureDesc;
		rootSignatureDesc.NumParameters = 0;
		rootSignatureDesc.pParameters = nullptr;
		rootSignatureDesc.NumStaticSamplers = 0;
		rootSignatureDesc.pStaticSamplers = nullptr;
		rootSignatureDesc.Flags = D3D12_ROOT_SIGNATURE_FLAG_ALLOW_INPUT_ASSEMBLER_INPUT_LAYOUT;
		if ( FAILED ( D3D12SerializeRootSignature ( &rootSignatureDesc, D3D_ROOT_SIGNATURE_VERSION_1, &signature, &error ) ) )
			throw std::runtime_error ( "Failed serialize Root Signature." );
		if ( FAILED ( d3dDevice->CreateRootSignature ( 0, signature->GetBufferPointer (), signature->GetBufferSize (),
			__uuidof ( ID3D12RootSignature ), ( void** ) &rootSignature ) ) )
			throw std::runtime_error ( "Failed create Root Signature." );
		signature->Release ();
		if ( error ) error->Release ();
	}

	{
		if ( FAILED ( d3dDevice->CreateFence ( 0, D3D12_FENCE_FLAG_NONE, __uuidof ( ID3D12Fence ), ( void** ) &fence ) ) )
			throw std::runtime_error ( "Failed create Fence." );
		fenceValue = 1;

		fenceEvent = CreateEventEx ( nullptr, FALSE, FALSE, EVENT_ALL_ACCESS );
		if ( fenceEvent == nullptr )
		{
			throw std::runtime_error ( "Cannot create Event. check GetLastError ()." );
		}

		Synchronization ();
	}
}

#if defined ( POLYRAM_D3D12 )
#include <dxgidebug.h>
#endif

PRGraphicsContext_Direct3D12::~PRGraphicsContext_Direct3D12 () {
	Synchronization ();
	CloseHandle ( fenceEvent );
	SAFE_RELEASE ( fence );
	SAFE_RELEASE ( rootSignature );
	SAFE_RELEASE ( commandAllocator );
	for ( int i = 0; i < 2; ++i )
	{
		auto rt = renderTargets [ i ];
		SAFE_RELEASE ( rt );
	}
	SAFE_RELEASE ( descriptorHeap );
	SAFE_RELEASE ( commandQueue );
	SAFE_RELEASE ( d3dDevice );
	SAFE_RELEASE ( dxgiSwapChain );
#if defined ( _DEBUG )
	SAFE_RELEASE ( debugLayer );
	IDXGIDebug1* pDebug = nullptr;
	if ( SUCCEEDED ( DXGIGetDebugInterface1 ( 0, IID_PPV_ARGS ( &pDebug ) ) ) ) {
		pDebug->ReportLiveObjects ( DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_SUMMARY );
		pDebug->Release ();
	}
#endif
}

void PRGraphicsContext_Direct3D12::Synchronization () {
	const UINT64 myFence = fenceValue;
	if ( FAILED ( commandQueue->Signal ( fence, myFence ) ) )
		throw std::runtime_error ( "Command Queue Signal failed." );
	fenceValue++;

	if ( fence->GetCompletedValue () < myFence )
	{
		if ( FAILED ( fence->SetEventOnCompletion ( myFence, fenceEvent ) ) )
			throw std::runtime_error ( "Cannot set Event on completion." );
		WaitForSingleObject ( fenceEvent, INFINITE );
	}

	frameIndex = dxgiSwapChain->GetCurrentBackBufferIndex ();
}
#endif

#if POLYRAM_OPENGL

#if PRPlatformMicrosoftWindowsNT
#include "wglext.h"
#elif PRPlatformUNIX
#include <cstdarg>
#include "glxext.h"
typedef GLXContext ( *GLXCREATECONTEXTATTRIBSARBPROC ) ( Display*, GLXFBConfig, GLXContext, Bool, const int * );
bool isExtensionSupported ( const char * extList, const char * e ) {
	const char *s, *t, *w = strchr ( e, ' ' );
	if ( w || *e == '\0' ) return false;
	for ( s = extList; ; ) {
		if ( !( w = strstr ( s, e ) ) ) break;
		t = w + strlen ( e );
		if ( ( w == s || *( w - 1 ) == ' ' ) && ( *t == ' ' || *t == '\0' ) )
			return true;
		s = t;
	}
	return false;
}
#endif

PRGraphicsContext_OpenGL::PRGraphicsContext_OpenGL ( PRApp * app, PRRendererType rendererType ) {
#if PRPlatformMicrosoftWindowsNT
	hDC = GetDC ( app->m_hWnd );

	PIXELFORMATDESCRIPTOR pixelFormatDescriptor =
	{
		sizeof ( PIXELFORMATDESCRIPTOR ), 1,
		PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA, 32,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0,
		24, 8,
		0, PFD_MAIN_PLANE, 0, 0, 0, 0,
	};
	int pixelFormat = ChoosePixelFormat ( hDC, &pixelFormatDescriptor );
	if ( !SetPixelFormat ( hDC, pixelFormat, &pixelFormatDescriptor ) )
		throw std::runtime_error ( "Failed SetPixelFormat in OpenGL initialize." );

	glContext = wglCreateContext ( hDC );
	if ( glContext == 0 )
		throw std::runtime_error ( "Failed wglCreateContext in OpenGL initialize." );
	if ( !wglMakeCurrent ( hDC, glContext ) )
		throw std::runtime_error ( "Failed wglMakeCurrent." );

	if ( rendererType > PRRendererType_OpenGL1 ) {
		PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = ( PFNWGLCREATECONTEXTATTRIBSARBPROC ) wglGetProcAddress ( "wglCreateContextAttribsARB" );
		if ( wglCreateContextAttribsARB ) {
			int attribs [] = {
				WGL_CONTEXT_MAJOR_VERSION_ARB, ( rendererType - PRRendererType_OpenGL1 ) + 1,
				WGL_CONTEXT_MINOR_VERSION_ARB, 5,
				0
			};
			HGLRC temp = nullptr;
			while ( attribs [ 3 ] > 0 ) {
				if ( temp != nullptr ) {
					if ( attribs [ 1 ] <= 2 ) break;
					PRVersion version ( std::string ( ( const char * ) glGetString ( GL_VERSION ) ) );
					if ( version.major == attribs [ 1 ] && version.minor == attribs [ 3 ] )
						break;
				}

				temp = wglCreateContextAttribsARB ( hDC, 0, attribs );
				if ( temp == nullptr ) { --attribs [ 3 ]; continue; }
				wglDeleteContext ( glContext );
				glContext = temp;
				if ( !wglMakeCurrent ( hDC, glContext ) ) throw std::runtime_error ( "Failed wglMakeCurrent." );
			}

			if ( temp == nullptr )
				throw std::runtime_error ( "Failed create new attribs context." );
		}
	}
#elif PRPlatformAppleOSX
	auto profile = NSOpenGLProfileVersionLegacy;
	if ( rendererType == PRRendererType_OpenGL3 )
		profile = NSOpenGLProfileVersion3_2Core;
	else if ( rendererType == PRRendererType_OpenGL4 )
		profile = NSOpenGLProfileVersion4_1Core;

	NSOpenGLPixelFormatAttribute attr [] = {
		NSOpenGLPFAOpenGLProfile, profile, NSOpenGLPFAAccelerated, NSOpenGLPFADoubleBuffer,
		NSOpenGLPFADepthSize, rendererInfo.depthBufferSize, NSOpenGLPFAStencilSize, rendererInfo.stencilBufferSize, 0
	};

	NSOpenGLPixelFormat * pixelFormat = [ [ NSOpenGLPixelFormat alloc ] initWithAttributes:attr ];
	if ( pixelFormat == nil )
		throw PRException ( "Failed create NSOpenGLPixelFormat." );

	glContext = [ [ NSOpenGLContext alloc ] initWithFormat:pixelFormat shareContext : nil ];
	if ( glContext == nil )
		throw PRException ( "Failed create NSOpenGLContext." );
	glContext.view = app->window.contentView;

	[glContext makeCurrentContext];
#elif PRPlatformAppleiOS
	EAGLRenderingAPI api;
	switch ( rendererType ) {
	case PRRendererType_OpenGLES1: api = kEAGLRenderingAPIOpenGLES1; break;
	case PRRendererType_OpenGLES2: api = kEAGLRenderingAPIOpenGLES2; break;
	case PRRendererType_OpenGLES3: api = kEAGLRenderingAPIOpenGLES3; break;
	default: throw std::runtime_error ( "Invaild OpenGL ES version." );
	}
	glContext = [ [ EAGLContext alloc ] initWithAPI:api ];

	GLKView * view = ( GLKView* ) wnd->window.rootViewController.view;
	view.context = glContext;

	view.drawableDepthFormat = GLKViewDrawableDepthFormat24;
	view.drawableStencilFormat = GLKViewDrawableStencilFormat8;
#elif PRPlatformUNIX
	const char * glxExts = glXQueryExtensionsString ( app->display, DefaultScreen ( app->display ) );
	GLXCREATECONTEXTATTRIBSARBPROC glXCreateContextAttribsARB = ( GLXCREATECONTEXTATTRIBSARBPROC ) glXGetProcAddressARB ( ( const GLubyte * ) "glXCreateContextAttribsARB" );

	if ( !isExtensionSupported ( glxExts, "GLX_ARB_create_context" ) || glXCreateContextAttribsARB == nullptr ) {
		glContext = glXCreateContext ( app->display, app->visualInfo, nullptr, true );
	}
	else {
		GLint visualAttr [] = {
			GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_STENCIL_SIZE, 8, GLX_DOUBLEBUFFER, true, GLX_DRAWABLE_TYPE, GLX_WINDOW_BIT,
			GLX_X_VISUAL_TYPE, GLX_TRUE_COLOR, None
		};
		GLint contextAttribs [] = {
			GLX_CONTEXT_MAJOR_VERSION_ARB, ( rendererType - PRRendererType_OpenGL1 ) + 1,
			GLX_CONTEXT_MINOR_VERSION_ARB, 0,
			GLX_CONTEXT_PROFILE_MASK_ARB, GLX_CONTEXT_CORE_PROFILE_BIT_ARB,
			None,
		};

		int nelements;
		GLXFBConfig * config = glXChooseFBConfig ( app->display, DefaultScreen ( app->display ), visualAttr, &nelements );
		if ( nelements == 0 )
			throw std::runtime_error ( "FBConfig's count is zero." );

		glContext = glXCreateContextAttribsARB ( app->display, config [ 0 ], nullptr, true, contextAttribs );
	}

	if ( glContext == nullptr )
		throw std::runtime_error ( "Failed create OpenGL context." );

	if ( !glXMakeCurrent ( app->display, app->window, glContext ) )
		throw std::runtime_error ( "Failed make current." );
#elif PRPlatformGoogleAndroid
	const EGLint attribs [] = {
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE
	};
	EGLint w, h, format;
	EGLint numConfigs;
	EGLConfig config;

	display = eglGetDisplay ( EGL_DEFAULT_DISPLAY );

	eglInitialize ( display, 0, 0 );

	eglChooseConfig ( display, attribs, &config, 1, &numConfigs );
	eglGetConfigAttrib ( display, config, EGL_NATIVE_VISUAL_ID, &format );

	ANativeWindow_setBuffersGeometry ( PRApp::sharedApp ()->engine.app->window, 0, 0, format );

	surface = eglCreateWindowSurface ( display, config, PRApp::sharedApp ()->engine.app->window, NULL );
	EGLint createAttribs [] = { EGL_CONTEXT_CLIENT_VERSION, ( rendererType - PRRendererType_OpenGLES1 ) + 1, EGL_NONE };
	context = eglCreateContext ( display, config, NULL, createAttribs );

	if ( eglMakeCurrent ( display, surface, surface, context ) == EGL_FALSE )
		throw std::runtime_error ( "Unable to eglMakeCurrent" );

	eglQuerySurface ( display, surface, EGL_WIDTH, &w );
	eglQuerySurface ( display, surface, EGL_HEIGHT, &h );

	PRApp::sharedApp ()->engine.width = w;
	PRApp::sharedApp ()->engine.height = h;
#endif
	GLenum errorCode = glGetError ();
	if ( errorCode != GL_NO_ERROR )
		throw std::runtime_error ( "OpenGL Error." );

#if PRPlatformDesktops
	PRLog ( "OGL ERR: %d", glGetError () );
	glewExperimental = GL_TRUE;
	GLenum glewError = glewInit ();
	if ( glewError != GLEW_OK )
		throw std::runtime_error ( ( const char* ) glewGetErrorString ( glewError ) );
	PRLog ( "OGL ERR in GLEW: %d", glGetError () );
#endif

	glClearColor ( 0, 0, 0, 1 );
#if PRPlatformDesktops
	glClearDepth ( 1 );
#else
	glClearDepthf ( 1 );
#endif
	glClearStencil ( 0 );
	glClear ( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
	PRLog ( "OGL ERR: %d", glGetError () );
}

PRGraphicsContext_OpenGL::~PRGraphicsContext_OpenGL () {
#if PRPlatformMicrosoftWindowsNT
	wglDeleteContext ( glContext );
#elif PRPlatformAppleOSX
	glContext = nil;
#elif PRPlatformAppleiOS

#elif PRPlatformUNIX
	PRApp * app = PRApp::sharedApp ();
	glXMakeCurrent ( app->display, 0, 0 );
	glXDestroyContext ( app->display, glContext );
#elif PRPlatformGoogleAndroid
	if ( display != EGL_NO_DISPLAY ) {
		eglMakeCurrent ( display, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT );
		if ( context != EGL_NO_CONTEXT ) {
			eglDestroyContext ( display, context );
		}
		if ( surface != EGL_NO_SURFACE ) {
			eglDestroySurface ( display, surface );
		}
		eglTerminate ( display );
	}
	PRApp::sharedApp ()->engine.animating = 0;
	display = EGL_NO_DISPLAY;
	context = EGL_NO_CONTEXT;
	surface = EGL_NO_SURFACE;
#endif
}

void PRGraphicsContext_OpenGL::makeCurrent () {
#if PRPlatformMicrosoftWindowsNT
	wglMakeCurrent ( hDC, glContext );
#elif PRPlatformAppleOSX
	[ glContext makeCurrentContext ];
#elif PRPlatformAppleiOS
	[ EAGLContext setCurrentContext : glContext ];
#elif PRPlatformUNIX
	PRApp * app = PRApp::sharedApp ();
	glXMakeCurrent ( app->display, app->window, glContext );
#elif PRPlatformGoogleAndroid
	eglMakeCurrent ( display, surface, surface, context );
#endif
}

void PRGraphicsContext_OpenGL::swapBuffers () {
	glFlush ();
#if PRPlatformMicrosoftWindowsNT
	SwapBuffers ( hDC );
#elif PRPlatformAppleOSX
	[ glContext flushBuffer ];
#elif PRPlatformAppleiOS
	[ glContext presentRenderbuffer : 0 ];
#elif PRPlatformUNIX
	PRApp * app = PRApp::sharedApp ();
	glXSwapBuffers ( app->display, app->window );
#elif PRPlatformGoogleAndroid
	eglSwapBuffers ( display, surface );
#endif
}
#endif

#if POLYRAM_METAL
PRGraphicsContext_Metal::PRGraphicsContext_Metal ( PRApp * app ) {
	device = MTLCreateSystemDefaultDevice ();
	commandQueue = [ device newCommandQueue ];
	library = [ device newDefaultLibrary ];
	commandBuffer = [ commandQueue commandBuffer ];
}

PRGraphicsContext_Metal::~PRGraphicsContext_Metal () {
	commandBuffer = nil;
	library = nil;
	commandQueue = nil;
	device = nil;
}
#endif

#if defined ( POLYRAM_VULKAN )
/*PRGraphicsContext_Vulkan::PRGraphicsContext_Vulkan ( PRApp * app ) {
	VkApplicationInfo applicationInfo;
	VkInstanceCreateInfo instanceInfo;

	applicationInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	applicationInfo.pNext = nullptr;
	applicationInfo.pApplicationName = "libPolyram";
	applicationInfo.pEngineName = "libPolyram";
	applicationInfo.engineVersion = 1;
	applicationInfo.apiVersion = VK_API_VERSION;

	instanceInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	instanceInfo.pNext = nullptr;
	instanceInfo.flags = 0;
	instanceInfo.pApplicationInfo = &applicationInfo;
	instanceInfo.enabledLayerCount = 0;
	instanceInfo.ppEnabledLayerNames = nullptr;
	instanceInfo.enabledExtensionCount = 0;
	instanceInfo.ppEnabledExtensionNames = nullptr;

	VkResult result = vkCreateInstance ( &instanceInfo, nullptr, &instance );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed to create Vulkan instance." );

	uint32_t deviceCount = 0;
	result = vkEnumeratePhysicalDevices ( instance, &deviceCount, nullptr );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed to query the number of physical devices present." );

	if ( deviceCount == 0 )
		throw std::runtime_error ( "Couldn't detect any device present with Vulkan support." );

	std::vector<VkPhysicalDevice> physicalDevices ( deviceCount );
	result = vkEnumeratePhysicalDevices ( instance, &deviceCount, &physicalDevices [ 0 ] );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Faied to enumerate physical devices presen." );

	VkDeviceCreateInfo deviceInfo;
	deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	deviceInfo.pNext = nullptr;
	deviceInfo.flags = 0;
	deviceInfo.enabledLayerCount = 0;
	deviceInfo.ppEnabledLayerNames = nullptr;
	deviceInfo.enabledExtensionCount = 0;
	deviceInfo.ppEnabledExtensionNames = nullptr;
	deviceInfo.pEnabledFeatures = nullptr;

	float queuePriorities [] = { 1.0f };
	VkDeviceQueueCreateInfo deviceQueueInfo;
	deviceQueueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	deviceQueueInfo.pNext = nullptr;
	deviceQueueInfo.flags = 0;
	deviceQueueInfo.queueFamilyIndex = 0;
	deviceQueueInfo.queueCount = 1;
	deviceQueueInfo.pQueuePriorities = queuePriorities;

	deviceInfo.queueCreateInfoCount = 1;
	deviceInfo.pQueueCreateInfos = &deviceQueueInfo;

	result = vkCreateDevice ( physicalDevices [ 0 ], &deviceInfo, nullptr, &device );
	if ( result != VK_SUCCESS )
		throw std::runtime_error ( "Failed creating logical device." );

	vkGetDeviceQueue ( device, 0, 0, &queue );
}

PRGraphicsContext_Vulkan::~PRGraphicsContext_Vulkan ()
{
	if ( device != VK_NULL_HANDLE )
	{
		vkDeviceWaitIdle ( device );
		vkDestroyDevice ( device, nullptr );
	}
	if ( instance != VK_NULL_HANDLE )
		vkDestroyInstance ( instance, nullptr );
}*/
#endif

#define COPIEDMETHOD0(x,y) x temp; y ( &temp ); return temp;
#define COPIEDMETHOD1(x,y,z) x temp; y ( z, &temp ); return temp;
#define COPIEDMETHOD2(x,y,z,w) x temp; y ( z, w, &temp ); return temp;

PRVec2::PRVec2 () : x ( 0 ), y ( 0 ) { }
PRVec2::PRVec2 ( float v ) : x ( v ), y ( v ) { }
PRVec2::PRVec2 ( float x, float y ) : x ( x ), y ( y ) { }

void PRVec2::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVec2::length ( float * result ) { length ( this, result ); }
void PRVec2::normalize ( PRVec2 * result ) { normalize ( this, result ); }

float PRVec2::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVec2::length () { float temp; length ( this, &temp ); return temp; }
PRVec2 PRVec2::normalize () { PRVec2 temp; normalize ( this, &temp ); return temp; }

void PRVec2::lengthSquared ( const PRVec2 * v, float * result ) { *result = v->x * v->x + v->y * v->y; }
void PRVec2::length ( const PRVec2 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVec2::normalize ( const PRVec2 * v, PRVec2 * result ) { float len; length ( v, &len ); divide ( v, len, result ); }

float PRVec2::lengthSquared ( const PRVec2 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVec2::length ( const PRVec2 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVec2 PRVec2::normalize ( const PRVec2 & v ) { PRVec2 temp; normalize ( &v, &temp ); return temp; }

void PRVec2::add ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
}
void PRVec2::subtract ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
}
void PRVec2::negate ( const PRVec2 * v1, PRVec2 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
}
void PRVec2::multiply ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
}
void PRVec2::multiply ( const PRVec2 * v1, float v2, PRVec2 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
}
void PRVec2::multiply ( float v1, const PRVec2 * v2, PRVec2 * result ) { multiply ( v2, v1, result ); }
void PRVec2::divide ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
}
void PRVec2::divide ( const PRVec2 * v1, float v2, PRVec2 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
}
void PRVec2::dot ( const PRVec2 * v1, const PRVec2 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y );
}
void PRVec2::dot ( const PRVec2 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 );
}
void PRVec2::cross ( const PRVec2 * v1, const PRVec2 * v2, PRVec2 * result ) {
	result->x = v1->x * v2->y;
	result->y = v1->y * v2->x;
}

PRVec2 PRVec2::add ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, add, &v1, &v2 ); }
PRVec2 PRVec2::subtract ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, subtract, &v1, &v2 ); }
PRVec2 PRVec2::negate ( const PRVec2 & v1 ) { COPIEDMETHOD1 ( PRVec2, negate, &v1 ); }
PRVec2 PRVec2::multiply ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, multiply, &v1, &v2 ); }
PRVec2 PRVec2::multiply ( const PRVec2 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec2, multiply, &v1, v2 ); }
PRVec2 PRVec2::multiply ( float v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, multiply, v1, &v2 ); }
PRVec2 PRVec2::divide ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, divide, &v1, &v2 ); }
PRVec2 PRVec2::divide ( const PRVec2 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec2, divide, &v1, v2 ); }
float PRVec2::dot ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVec2::dot ( const PRVec2 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }
PRVec2 PRVec2::cross ( const PRVec2 & v1, const PRVec2 & v2 ) { COPIEDMETHOD2 ( PRVec2, cross, &v1, &v2 ); }

void PRVec2::transform ( const PRVec2 * pos, const PRMat * mat, PRVec2 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
}
void PRVec2::transformNormal ( const PRVec2 * nor, const PRMat * mat, PRVec2 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 );
}

PRVec2 PRVec2::transform ( const PRVec2 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec2, transform, &pos, &mat ); }
PRVec2 PRVec2::transformNormal ( const PRVec2 & nor, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec2, transformNormal, &nor, &mat ); }

PRVec2 operator+ ( const PRVec2 & v1, const PRVec2 & v2 ) { return PRVec2::add ( v1, v2 ); }
PRVec2 operator- ( const PRVec2 & v1, const PRVec2 & v2 ) { return PRVec2::subtract ( v1, v2 ); }
PRVec2 operator- ( const PRVec2 & v1 ) { return PRVec2::negate ( v1 ); }
PRVec2 operator* ( const PRVec2 & v1, const PRVec2 & v2 ) { return PRVec2::multiply ( v1, v2 ); }
PRVec2 operator* ( const PRVec2 & v1, float v2 ) { return PRVec2::multiply ( v1, v2 ); }
PRVec2 operator* ( float v1, const PRVec2 & v2 ) { return PRVec2::multiply ( v1, v2 ); }
PRVec2 operator/ ( const PRVec2 & v1, const PRVec2 & v2 ) { return PRVec2::divide ( v1, v2 ); }
PRVec2 operator/ ( const PRVec2 & v1, float v2 ) { return PRVec2::divide ( v1, v2 ); }
bool operator== ( const PRVec2 & v1, const PRVec2 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y );
}

PRVec3::PRVec3 () : x ( 0 ), y ( 0 ), z ( 0 ) { }
PRVec3::PRVec3 ( float v ) : x ( v ), y ( v ), z ( v ) { }
PRVec3::PRVec3 ( float x, float y, float z ) : x ( x ), y ( y ), z ( z ) { }
PRVec3::PRVec3 ( const PRVec2 & v, float z ) : x ( v.x ), y ( v.y ), z ( z ) { }

void PRVec3::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVec3::length ( float * result ) { length ( this, result ); }
void PRVec3::normalize ( PRVec3 * result ) { normalize ( this, result ); }

float PRVec3::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVec3::length () { float temp; length ( this, &temp ); return temp; }
PRVec3 PRVec3::normalize () { PRVec3 temp; normalize ( this, &temp ); return temp; }

void PRVec3::lengthSquared ( const PRVec3 * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z; }
void PRVec3::length ( const PRVec3 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVec3::normalize ( const PRVec3 * v, PRVec3 * result )
{
	float len; length ( v, &len );
	divide ( v, len, result );
}

float PRVec3::lengthSquared ( const PRVec3 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVec3::length ( const PRVec3 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVec3 PRVec3::normalize ( const PRVec3 & v ) { PRVec3 temp; normalize ( &v, &temp ); return temp; }

void PRVec3::add ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
}
void PRVec3::subtract ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
}
void PRVec3::negate ( const PRVec3 * v1, PRVec3 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
}
void PRVec3::multiply ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
}
void PRVec3::multiply ( const PRVec3 * v1, float v2, PRVec3 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
}
void PRVec3::multiply ( float v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
}
void PRVec3::divide ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
}
void PRVec3::divide ( const PRVec3 * v1, float v2, PRVec3 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
}
void PRVec3::dot ( const PRVec3 * v1, const PRVec3 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z );
}
void PRVec3::dot ( const PRVec3 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 );
}
void PRVec3::cross ( const PRVec3 * v1, const PRVec3 * v2, PRVec3 * result ) {
	result->x = v1->y * v2->z - v1->z * v2->y;
	result->y = v1->z * v2->x - v1->x * v2->z;
	result->z = v1->x * v2->y - v1->y * v2->x;
}

PRVec3 PRVec3::add ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, add, &v1, &v2 ); }
PRVec3 PRVec3::subtract ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, subtract, &v1, &v2 ); }
PRVec3 PRVec3::negate ( const PRVec3 & v1 ) { COPIEDMETHOD1 ( PRVec3, negate, &v1 ); }
PRVec3 PRVec3::multiply ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, multiply, &v1, &v2 ); }
PRVec3 PRVec3::multiply ( const PRVec3 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec3, multiply, &v1, v2 ); }
PRVec3 PRVec3::multiply ( float v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, multiply, v1, &v2 ); }
PRVec3 PRVec3::divide ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, divide, &v1, &v2 ); }
PRVec3 PRVec3::divide ( const PRVec3 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec3, divide, &v1, v2 ); }
float PRVec3::dot ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVec3::dot ( const PRVec3 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }
PRVec3 PRVec3::cross ( const PRVec3 & v1, const PRVec3 & v2 ) { COPIEDMETHOD2 ( PRVec3, cross, &v1, &v2 ); }

void PRVec3::transform ( const PRVec2 * pos, const PRMat * mat, PRVec3 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + mat->_43;
}
void PRVec3::transform ( const PRVec3 * pos, const PRMat * mat, PRVec3 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + mat->_43;
}
void PRVec3::transform ( const PRVec3 * pos, const PRQuat * q, PRVec3 * result ) {
	float x = 2 * ( q->y * pos->z - q->z * pos->y ), y = 2 * ( q->z * pos->x - q->x * pos->z ),
		z = 2 * ( q->x * pos->y - q->y * pos->x );
	result->x = pos->x + x * q->w + ( q->y * z - q->z * y );
	result->y = pos->y + y * q->w + ( q->z * x - q->x * z );
	result->z = pos->z + z * q->w + ( q->x * y - q->y * x );
}
void PRVec3::transformNormal ( const PRVec2 * nor, const PRMat * mat, PRVec3 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 );
	result->z = ( nor->x * mat->_13 ) + ( nor->y * mat->_23 );
}
void PRVec3::transformNormal ( const PRVec3 * nor, const PRMat * mat, PRVec3 * result ) {
	result->x = ( nor->x * mat->_11 ) + ( nor->y * mat->_21 ) + ( nor->z * mat->_31 );
	result->y = ( nor->x * mat->_12 ) + ( nor->y * mat->_22 ) + ( nor->z * mat->_32 );
	result->z = ( nor->x * mat->_13 ) + ( nor->y * mat->_23 ) + ( nor->z * mat->_33 );
}

PRVec3 PRVec3::transform ( const PRVec3 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec3, transform, &pos, &mat ); }
PRVec3 PRVec3::transform ( const PRVec2 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec3, transform, &pos, &mat ); }
PRVec3 PRVec3::transform ( const PRVec3 & pos, const PRQuat & q ) { COPIEDMETHOD2 ( PRVec3, transform, &pos, &q ); }
PRVec3 PRVec3::transformNormal ( const PRVec2 & nor, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec3, transformNormal, &nor, &mat ); }
PRVec3 PRVec3::transformNormal ( const PRVec3 & nor, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec3, transformNormal, &nor, &mat ); }

PRVec3 operator+ ( const PRVec3 & v1, const PRVec3 & v2 ) { return PRVec3::add ( v1, v2 ); }
PRVec3 operator- ( const PRVec3 & v1, const PRVec3 & v2 ) { return PRVec3::subtract ( v1, v2 ); }
PRVec3 operator- ( const PRVec3 & v1 ) { return PRVec3::negate ( v1 ); }
PRVec3 operator* ( const PRVec3 & v1, const PRVec3 & v2 ) { return PRVec3::multiply ( v1, v2 ); }
PRVec3 operator* ( const PRVec3 & v1, float v2 ) { return PRVec3::multiply ( v1, v2 ); }
PRVec3 operator* ( float v1, const PRVec3 & v2 ) { return PRVec3::multiply ( v1, v2 ); }
PRVec3 operator/ ( const PRVec3 & v1, const PRVec3 & v2 ) { return PRVec3::divide ( v1, v2 ); }
PRVec3 operator/ ( const PRVec3 & v1, float v2 ) { return PRVec3::divide ( v1, v2 ); }
bool operator== ( const PRVec3 & v1, const PRVec3 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z );
}

PRVec4::PRVec4 () : x ( 0 ), y ( 0 ), z ( 0 ), w ( 0 ) { }
PRVec4::PRVec4 ( float v ) : x ( v ), y ( v ), z ( v ), w ( 0 ) { }
PRVec4::PRVec4 ( float x, float y, float z, float w ) : x ( x ), y ( y ), z ( z ), w ( w ) { }
PRVec4::PRVec4 ( const PRVec2 & v, float z, float w ) : x ( v.x ), y ( v.y ), z ( z ), w ( w ) { }
PRVec4::PRVec4 ( const PRVec3 & v, float w ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( w ) { }
PRVec4::PRVec4 ( const PRQuat & v ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( v.w ) { }

void PRVec4::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRVec4::length ( float * result ) { length ( this, result ); }
void PRVec4::normalize ( PRVec4 * result ) { normalize ( this, result ); }

float PRVec4::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRVec4::length () { float temp; length ( this, &temp ); return temp; }
PRVec4 PRVec4::normalize () { PRVec4 temp; normalize ( this, &temp ); return temp; }

void PRVec4::lengthSquared ( const PRVec4 * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w; }
void PRVec4::length ( const PRVec4 * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRVec4::normalize ( const PRVec4 * v, PRVec4 * result ) {
	float len; length ( v, &len );
	divide ( v, len, result );
}

float PRVec4::lengthSquared ( const PRVec4 & v ) { float temp; lengthSquared ( &v, &temp ); return temp; }
float PRVec4::length ( const PRVec4 & v ) { float temp; length ( &v, &temp ); return temp; }
PRVec4 PRVec4::normalize ( const PRVec4 & v ) { PRVec4 temp; normalize ( &v, &temp ); return temp; }

void PRVec4::add ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	result->w = v1->w + v2->w;
}
void PRVec4::subtract ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	result->z = v1->w - v2->w;
}
void PRVec4::negate ( const PRVec4 * v1, PRVec4 * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
	result->w = -v1->w;
}
void PRVec4::multiply ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
	result->z = v1->w * v2->w;
}
void PRVec4::multiply ( const PRVec4 * v1, float v2, PRVec4 * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
	result->z = v1->w * v2;
}
void PRVec4::multiply ( float v1, const PRVec4 * v2, PRVec4 * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
	result->z = v1 * v2->w;
}
void PRVec4::divide ( const PRVec4 * v1, const PRVec4 * v2, PRVec4 * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
	result->z = v1->w / v2->w;
}
void PRVec4::divide ( const PRVec4 * v1, float v2, PRVec4 * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
	result->z = v1->w / v2;
}
void PRVec4::dot ( const PRVec4 * v1, const PRVec4 * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z ) + ( v1->w * v2->w );
}
void PRVec4::dot ( const PRVec4 * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 ) + ( v1->w * v2 );
}

PRVec4 PRVec4::add ( const PRVec4 & v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( PRVec4, add, &v1, &v2 ); }
PRVec4 PRVec4::subtract ( const PRVec4 & v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( PRVec4, subtract, &v1, &v2 ); }
PRVec4 PRVec4::negate ( const PRVec4 & v1 ) { COPIEDMETHOD1 ( PRVec4, negate, &v1 ); }
PRVec4 PRVec4::multiply ( const PRVec4 & v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( PRVec4, multiply, &v1, &v2 ); }
PRVec4 PRVec4::multiply ( const PRVec4 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec4, multiply, &v1, v2 ); }
PRVec4 PRVec4::multiply ( float v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( PRVec4, multiply, v1, &v2 ); }
PRVec4 PRVec4::divide ( const PRVec4 & v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( PRVec4, divide, &v1, &v2 ); }
PRVec4 PRVec4::divide ( const PRVec4 & v1, float v2 ) { COPIEDMETHOD2 ( PRVec4, divide, &v1, v2 ); }
float PRVec4::dot ( const PRVec4 & v1, const PRVec4 & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRVec4::dot ( const PRVec4 & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }

void PRVec4::transform ( const PRVec2 * pos, const PRMat * mat, PRVec4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + mat->_43;
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + mat->_44;
}
void PRVec4::transform ( const PRVec3 * pos, const PRMat * mat, PRVec4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + mat->_41;
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + mat->_42;
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + mat->_43;
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + ( pos->z * mat->_34 ) + mat->_44;
}
void PRVec4::transform ( const PRVec4 * pos, const PRMat * mat, PRVec4 * result ) {
	result->x = ( pos->x * mat->_11 ) + ( pos->y * mat->_21 ) + ( pos->z * mat->_31 ) + ( pos->w * mat->_41 );
	result->y = ( pos->x * mat->_12 ) + ( pos->y * mat->_22 ) + ( pos->z * mat->_32 ) + ( pos->w * mat->_42 );
	result->z = ( pos->x * mat->_13 ) + ( pos->y * mat->_23 ) + ( pos->z * mat->_33 ) + ( pos->w * mat->_43 );
	result->w = ( pos->x * mat->_14 ) + ( pos->y * mat->_24 ) + ( pos->z * mat->_34 ) + ( pos->w * mat->_44 );
}
PRVec4 PRVec4::transform ( const PRVec2 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec4, transform, &pos, &mat ); }
PRVec4 PRVec4::transform ( const PRVec3 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec4, transform, &pos, &mat ); }
PRVec4 PRVec4::transform ( const PRVec4 & pos, const PRMat & mat ) { COPIEDMETHOD2 ( PRVec4, transform, &pos, &mat ); }

PRVec4 operator+ ( const PRVec4 & v1, const PRVec4 & v2 ) { return PRVec4::add ( v1, v2 ); }
PRVec4 operator- ( const PRVec4 & v1, const PRVec4 & v2 ) { return PRVec4::subtract ( v1, v2 ); }
PRVec4 operator- ( const PRVec4 & v1 ) { return PRVec4::negate ( v1 ); }
PRVec4 operator* ( const PRVec4 & v1, const PRVec4 & v2 ) { return PRVec4::multiply ( v1, v2 ); }
PRVec4 operator* ( const PRVec4 & v1, float v2 ) { return PRVec4::multiply ( v1, v2 ); }
PRVec4 operator* ( float v1, const PRVec4 & v2 ) { return PRVec4::multiply ( v1, v2 ); }
PRVec4 operator/ ( const PRVec4 & v1, const PRVec4 & v2 ) { return PRVec4::divide ( v1, v2 ); }
PRVec4 operator/ ( const PRVec4 & v1, float v2 ) { return PRVec4::divide ( v1, v2 ); }
bool operator== ( const PRVec4 & v1, const PRVec4 & v2 )
{
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z ) && PRIsEquals ( v1.w, v2.w );
}

PRQuat::PRQuat () : x ( 0 ), y ( 0 ), z ( 0 ), w ( 1 ) { }
PRQuat::PRQuat ( float v ) : x ( v ), y ( v ), z ( v ), w ( v ) { }
PRQuat::PRQuat ( float x, float y, float z, float w ) : x ( x ), y ( y ), z ( z ), w ( w ) {  }
PRQuat::PRQuat ( const PRVec2 & v, float z, float w ) : x ( v.x ), y ( v.y ), z ( z ), w ( w ) { }
PRQuat::PRQuat ( const PRVec3 & v, float w ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( w ) { }
PRQuat::PRQuat ( const PRVec4 & v ) : x ( v.x ), y ( v.y ), z ( v.z ), w ( v.w ) { }
PRQuat::PRQuat ( float yaw, float pitch, float roll ) {
	float halfRoll = roll * 0.5f, halfPitch = pitch * 0.5f, halfYaw = yaw * 0.5f;
	
	float sinRoll = sin ( halfRoll ), cosRoll = cos ( halfRoll );
	float sinPitch = sin ( halfPitch ), cosPitch = cos ( halfPitch );
	float sinYaw = sin ( halfYaw ), cosYaw = cos ( halfYaw );
	
	x = ( cosYaw * sinPitch * cosRoll ) + ( sinYaw * cosPitch * sinRoll );
	y = ( sinYaw * cosPitch * cosRoll ) - ( cosYaw * sinPitch * sinRoll );
	z = ( cosYaw * cosPitch * sinRoll ) - ( sinYaw * sinPitch * cosRoll );
	w = ( cosYaw * cosPitch * cosRoll ) + ( sinYaw * sinPitch * sinRoll );
}
PRQuat::PRQuat ( const PRMat & m ) {
	float num8 = ( m._11 + m._22 ) + m._33;
	if ( num8 > 0.0f ) {
		float num = sqrtf ( num8 + 1.0f );
		num = 0.5f / num;
		x = ( m._23 - m._32 ) * num; y = ( m._31 - m._13 ) * num;
		z = ( m._12 - m._21 ) * num; w = num * 0.5f;
	}
	else if ( ( m._11 >= m._22 ) && ( m._11 >= m._33 ) ) {
		float num7 = sqrtf ( ( ( 1.0f + m._11 ) - m._22 ) - m._33 );
		float num4 = 0.5f / num7;
		x = 0.5f * num7; y = ( m._12 + m._21 ) * num4;
		z = ( m._13 + m._31 ) * num4; w = ( m._23 - m._32 ) * num4;
	}
	else if ( m._22 > m._33 ) {
		float num6 = sqrtf ( ( ( 1.0f + m._22 ) - m._11 ) - m._33 );
		float num3 = 0.5f / num6;
		x = ( m._21 + m._12 ) * num3; y = 0.5f * num6;
		z = ( m._32 + m._23 ) * num3; w = ( m._31 - m._13 ) * num3;
	}
	else {
		float num5 = sqrtf ( ( ( 1.0f + m._33 ) - m._11 ) - m._22 );
		float num2 = 0.5f / num5;
		x = ( m._31 + m._13 ) * num2; y = ( m._32 + m._23 ) * num2;
		z = 0.5f * num5; w = ( m._12 - m._21 ) * num2;
	}
}

void PRQuat::lengthSquared ( float * result ) { lengthSquared ( this, result ); }
void PRQuat::length ( float * result ) { length ( this, result ); }
void PRQuat::normalize ( PRQuat * result ) { normalize ( this, result ); }
void PRQuat::invert ( PRQuat * result ) { invert ( this, result ); }

float PRQuat::lengthSquared () { float temp; lengthSquared ( this, &temp ); return temp; }
float PRQuat::length () { float temp; length ( this, &temp ); return temp; }
PRQuat PRQuat::normalize () { PRQuat temp; normalize ( this, &temp ); return temp; }
PRQuat PRQuat::invert () { PRQuat temp; invert ( this, &temp ); return temp; }

void PRQuat::lengthSquared ( const PRQuat * v, float * result ) { *result = v->x * v->x + v->y * v->y + v->z * v->z + v->w * v->w; }
void PRQuat::length ( const PRQuat * v, float * result ) { float ls; lengthSquared ( v, &ls ); *result = sqrtf ( ls ); }
void PRQuat::normalize ( const PRQuat * v, PRQuat * result ) {
	float len; length ( v, &len );
	result->x = v->x / len;
	result->y = v->y / len;
	result->z = v->z / len;
	result->w = v->w / len;
}
void PRQuat::invert ( const PRQuat * v, PRQuat * result ) {
	float len; length ( v, &len );
	result->x = -v->x / len;
	result->y = -v->y / len;
	result->z = -v->z / len;
	result->w = v->w / len;
}

float PRQuat::lengthSquared ( const PRQuat & v ) { COPIEDMETHOD1 ( float, lengthSquared, &v ); }
float PRQuat::length ( const PRQuat & v ) { COPIEDMETHOD1 ( float, length, &v ); }
PRQuat PRQuat::normalize ( const PRQuat & v ) { COPIEDMETHOD1 ( PRQuat, normalize, &v ); }
PRQuat PRQuat::invert ( const PRQuat & v ) { COPIEDMETHOD1 ( PRQuat, invert, &v ); }

void PRQuat::add ( const PRQuat * v1, const PRQuat * v2, PRQuat * result ) {
	result->x = v1->x + v2->x;
	result->y = v1->y + v2->y;
	result->z = v1->z + v2->z;
	result->w = v1->w + v2->w;
}
void PRQuat::subtract ( const PRQuat * v1, const PRQuat * v2, PRQuat * result ) {
	result->x = v1->x - v2->x;
	result->y = v1->y - v2->y;
	result->z = v1->z - v2->z;
	result->z = v1->w - v2->w;
}
void PRQuat::negate ( const PRQuat * v1, PRQuat * result ) {
	result->x = -v1->x;
	result->y = -v1->y;
	result->z = -v1->z;
	result->w = -v1->w;
}
void PRQuat::multiply ( const PRQuat * v1, const PRQuat * v2, PRQuat * result ) {
	result->x = v1->x * v2->x;
	result->y = v1->y * v2->y;
	result->z = v1->z * v2->z;
	result->z = v1->w * v2->w;
}
void PRQuat::multiply ( const PRQuat * v1, float v2, PRQuat * result ) {
	result->x = v1->x * v2;
	result->y = v1->y * v2;
	result->z = v1->z * v2;
	result->z = v1->w * v2;
}
void PRQuat::multiply ( float v1, const PRQuat * v2, PRQuat * result ) {
	result->x = v1 * v2->x;
	result->y = v1 * v2->y;
	result->z = v1 * v2->z;
	result->z = v1 * v2->w;
}
void PRQuat::divide ( const PRQuat * v1, const PRQuat * v2, PRQuat * result ) {
	result->x = v1->x / v2->x;
	result->y = v1->y / v2->y;
	result->z = v1->z / v2->z;
	result->z = v1->w / v2->w;
}
void PRQuat::divide ( const PRQuat * v1, float v2, PRQuat * result ) {
	result->x = v1->x / v2;
	result->y = v1->y / v2;
	result->z = v1->z / v2;
	result->z = v1->w / v2;
}
void PRQuat::dot ( const PRQuat * v1, const PRQuat * v2, float * result ) {
	*result = ( v1->x * v2->x ) + ( v1->y * v2->y ) + ( v1->z * v2->z ) + ( v1->w * v2->w );
}
void PRQuat::dot ( const PRQuat * v1, float v2, float * result ) {
	*result = ( v1->x * v2 ) + ( v1->y * v2 ) + ( v1->z * v2 ) + ( v1->w * v2 );
}
PRQuat PRQuat::add ( const PRQuat & v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( PRQuat, add, &v1, &v2 ); }
PRQuat PRQuat::subtract ( const PRQuat & v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( PRQuat, subtract, &v1, &v2 ); }
PRQuat PRQuat::negate ( const PRQuat & v1 ) { COPIEDMETHOD1 ( PRQuat, negate, &v1 ); }
PRQuat PRQuat::multiply ( const PRQuat & v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( PRQuat, multiply, &v1, &v2 ); }
PRQuat PRQuat::multiply ( const PRQuat & v1, float v2 ) { COPIEDMETHOD2 ( PRQuat, multiply, &v1, v2 ); }
PRQuat PRQuat::multiply ( float v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( PRQuat, multiply, v1, &v2 ); }
PRQuat PRQuat::divide ( const PRQuat & v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( PRQuat, divide, &v1, &v2 ); }
PRQuat PRQuat::divide ( const PRQuat & v1, float v2 ) { COPIEDMETHOD2 ( PRQuat, divide, &v1, v2 ); }
float PRQuat::dot ( const PRQuat & v1, const PRQuat & v2 ) { COPIEDMETHOD2 ( float, dot, &v1, &v2 ); }
float PRQuat::dot ( const PRQuat & v1, float v2 ) { COPIEDMETHOD2 ( float, dot, &v1, v2 ); }

PRQuat operator+ ( const PRQuat & v1, const PRQuat & v2 ) { return PRQuat::add ( v1, v2 ); }
PRQuat operator- ( const PRQuat & v1, const PRQuat & v2 ) { return PRQuat::subtract ( v1, v2 ); }
PRQuat operator- ( const PRQuat & v1 ) { return PRQuat::negate ( v1 ); }
PRQuat operator* ( const PRQuat & v1, const PRQuat & v2 ) { return PRQuat::multiply ( v1, v2 ); }
PRQuat operator* ( const PRQuat & v1, float v2 ) { return PRQuat::multiply ( v1, v2 ); }
PRQuat operator* ( float v1, const PRQuat & v2 ) { return PRQuat::multiply ( v1, v2 ); }
PRQuat operator/ ( const PRQuat & v1, const PRQuat & v2 ) { return PRQuat::divide ( v1, v2 ); }
PRQuat operator/ ( const PRQuat & v1, float v2 ) { return PRQuat::divide ( v1, v2 ); }
bool operator== ( const PRQuat & v1, const PRQuat & v2 ) {
	return PRIsEquals ( v1.x, v2.x ) && PRIsEquals ( v1.y, v2.y ) && PRIsEquals ( v1.z, v2.z ) && PRIsEquals ( v1.w, v2.w );
}

PRMat::PRMat () : _11 ( 1 ), _12 ( 0 ), _13 ( 0 ), _14 ( 0 ), _21 ( 0 ), _22 ( 1 ), _23 ( 0 ), _24 ( 0 ),
_31 ( 0 ), _32 ( 0 ), _33 ( 1 ), _34 ( 0 ), _41 ( 0 ), _42 ( 0 ), _43 ( 0 ), _44 ( 1 ) { }
PRMat::PRMat ( float v ) : _11 ( v ), _12 ( v ), _13 ( v ), _14 ( v ), _21 ( v ), _22 ( v ), _23 ( v ), _24 ( v ),
_31 ( v ), _32 ( v ), _33 ( v ), _34 ( v ), _41 ( v ), _42 ( v ), _43 ( v ), _44 ( v ) { }
PRMat::PRMat ( float _11, float _12, float _13, float _14, float _21, float _22, float _23, float _24,
	float _31, float _32, float _33, float _34, float _41, float _42, float _43, float _44 )
	: _11 ( _11 ), _12 ( _12 ), _13 ( _13 ), _14 ( _14 ), _21 ( _21 ), _22 ( _22 ), _23 ( _23 ), _24 ( _24 ),
	_31 ( _31 ), _32 ( _32 ), _33 ( _33 ), _34 ( _34 ), _41 ( _41 ), _42 ( _42 ), _43 ( _43 ), _44 ( _44 ) { }
PRMat::PRMat ( PRVec4 & c1, PRVec4 & c2, PRVec4 & c3, PRVec4 & c4 )
	: _11 ( c1.x ), _12 ( c1.y ), _13 ( c1.z ), _14 ( c1.w ), _21 ( c2.x ), _22 ( c2.y ), _23 ( c2.z ), _24 ( c2.w ),
	_31 ( c3.x ), _32 ( c3.y ), _33 ( c3.z ), _34 ( c3.w ), _41 ( c4.x ), _42 ( c4.y ), _43 ( c4.z ), _44 ( c4.w ) { }
PRMat::PRMat ( PRQuat & q ) {
	float n9 = q.x * q.x, n8 = q.y * q.y, n7 = q.z * q.z, n6 = q.x * q.y;
	float n5 = q.z * q.w, n4 = q.z * q.x, n3 = q.y * q.w, n2 = q.y * q.z;
	float n1 = q.x * q.w;
	_11 = 1.0f - ( 2.0f * ( n8 + n7 ) ); _12 = 2.0f * ( n6 + n5 ); _13 = 2.0f * ( n4 - n3 ); _14 = 0;
	_21 = 2.0f * ( n6 - n5 ); _22 = 1.0f - ( 2.0f * ( n7 + n9 ) ); _23 = 2.0f * ( n2 + n1 ); _24 = 0;
	_31 = 2.0f * ( n4 + n3 ); _32 = 2.0f * ( n2 - n1 ); _33 = 1.0f - ( 2.0f * ( n8 + n9 ) ); _34 = 0;
	_41 = 0; _42 = 0; _43 = 0; _44 = 1;
}

void PRMat::invert ( PRMat * result ) { PRMat::invert ( this, result ); }
void PRMat::transpose ( PRMat * result ) { PRMat::transpose ( this, result ); }
void PRMat::determinant ( float * result ) { PRMat::determinant ( this, result ); }

PRMat PRMat::invert () { PRMat temp; invert ( &temp ); return temp; }
PRMat PRMat::transpose () { PRMat temp; transpose ( &temp ); return temp; }
float PRMat::determinant () { float temp; determinant ( &temp ); return temp; }

void PRMat::invert ( const PRMat * m, PRMat * result ) {
	float n1 = m->_11, n2 = m->_12, n3 = m->_13, n4 = m->_14, n5 = m->_21, n6 = m->_22, n7 = m->_23, n8 = m->_24;
	float n9 = m->_31, n10 = m->_32, n11 = m->_33, n12 = m->_34, n13 = m->_41, n14 = m->_42, n15 = m->_43, n16 = m->_44;
	float n17 = n11 * n16 - n12 * n15, n18 = n10 * n16 - n12 * n14, n19 = n10 * n15 - n11 * n14;
	float n20 = n9 * n16 - n12 * n13, n21 = n9 * n15 - n11 * n13, n22 = n9 * n14 - n10 * n13;
	float n23 = n6 * n17 - n7 * n18 + n8 * n19, n24 = -( n5 * n17 - n7 * n20 + n8 * n21 );
	float n25 = n5 * n18 - n6 * n20 + n8 * n22, n26 = -( n5 * n19 - n6 * n21 + n7 * n22 );
	float n27 = 1.0f / ( n1 * n23 + n2 * n24 + n3 * n25 + n4 * n26 );
	result->_11 = n23 * n27; result->_21 = n24 * n27; result->_31 = n25 * n27; result->_41 = n26 * n27;
	result->_12 = -( n2 * n17 - n3 * n18 + n4 * n19 ) * n27;
	result->_22 = ( n1 * n17 - n3 * n20 + n4 * n21 ) * n27;
	result->_32 = -( n1 * n18 - n2 * n20 + n4 * n22 ) * n27;
	result->_42 = ( n1 * n19 - n2 * n21 + n3 * n22 ) * n27;
	float n28 = n7 * n16 - n8 * n15, n29 = n6 * n16 - n8 * n14, n30 = n6 * n15 - n7 * n14;
	float n31 = n5 * n16 - n8 * n13, n32 = n5 * n15 - n7 * n13, n33 = n5 * n14 - n6 * n13;
	result->_13 = ( n2 * n28 - n3 * n29 + n4 * n30 ) * n27;
	result->_23 = -( n1 * n28 - n3 * n31 + n4 * n32 ) * n27;
	result->_33 = ( n1 * n29 - n2 * n31 + n4 * n33 ) * n27;
	result->_43 = -( n1 * n30 - n2 * n32 + n3 * n33 ) * n27;
	float n34 = n7 * n12 - n8 * n11, n35 = n6 * n12 - n8 * n10, n36 = n6 * n11 - n7 * n10;
	float n37 = n5 * n12 - n8 * n9, n38 = n5 * n11 - n7 * n9, n39 = n5 * n10 - n6 * n9;
	result->_14 = -( n2 * n34 - n3 * n35 + n4 * n36 ) * n27;
	result->_24 = ( n1 * n34 - n3 * n37 + n4 * n38 ) * n27;
	result->_34 = -( n1 * n35 - n2 * n37 + n4 * n39 ) * n27;
	result->_44 = ( n1 * n36 - n2 * n38 + n3 * n39 ) * n27;
}
void PRMat::transpose ( const PRMat * m, PRMat * result ) {
	result->_11 = m->_11; result->_12 = m->_21; result->_13 = m->_31; result->_14 = m->_41;
	result->_21 = m->_12; result->_22 = m->_22; result->_23 = m->_32; result->_24 = m->_42;
	result->_31 = m->_13; result->_32 = m->_23; result->_33 = m->_33; result->_34 = m->_43;
	result->_41 = m->_14; result->_42 = m->_24; result->_43 = m->_34; result->_44 = m->_44;
}
void PRMat::determinant ( const PRMat * m, float * result ) {
	float n22 = m->_11, n21 = m->_12, n20 = m->_13, n19 = m->_14, n12 = m->_21, n11 = m->_22, n10 = m->_23, n9 = m->_24;
	float n8 = m->_31, n7 = m->_32, n6 = m->_33, n5 = m->_34, n4 = m->_41, n3 = m->_42, n2 = m->_43, n1 = m->_44;
	float n18 = ( n6 * n1 ) - ( n5 * n2 ), n17 = ( n7 * n1 ) - ( n5 * n3 );
	float n16 = ( n7 * n2 ) - ( n6 * n3 ), n15 = ( n8 * n1 ) - ( n5 * n4 );
	float n14 = ( n8 * n2 ) - ( n6 * n4 ), n13 = ( n8 * n3 ) - ( n7 * n4 );
	*result = ( ( ( ( n22 * ( ( ( n11 * n18 ) - ( n10 * n17 ) ) + ( n9 * n16 ) ) ) -
		( n21 * ( ( ( n12 * n18 ) - ( n10 * n15 ) ) + ( n9 * n14 ) ) ) ) +
		( n20 * ( ( ( n12 * n17 ) - ( n11 * n15 ) ) + ( n9 * n13 ) ) ) ) -
		( n19 * ( ( ( n12 * n16 ) - ( n11 * n14 ) ) + ( n10 * n13 ) ) ) );
}
PRMat PRMat::invert ( const PRMat & m ) { COPIEDMETHOD1 ( PRMat, invert, &m ); }
PRMat PRMat::transpose ( const PRMat & m ) { COPIEDMETHOD1 ( PRMat, transpose, &m ); }
float PRMat::determinant ( const PRMat & m ) { COPIEDMETHOD1 ( float, determinant, &m ); }

void PRMat::add ( const PRMat * v1, const PRMat * v2, PRMat * result ) {
	result->_11 = v1->_11 + v2->_11; result->_12 = v1->_12 + v2->_12; result->_13 = v1->_13 + v2->_13; result->_14 = v1->_14 + v2->_14;
	result->_21 = v1->_21 + v2->_21; result->_22 = v1->_22 + v2->_22; result->_23 = v1->_23 + v2->_23; result->_24 = v1->_24 + v2->_24;
	result->_31 = v1->_31 + v2->_31; result->_32 = v1->_32 + v2->_32; result->_33 = v1->_33 + v2->_33; result->_34 = v1->_34 + v2->_34;
	result->_41 = v1->_41 + v2->_41; result->_42 = v1->_42 + v2->_42; result->_43 = v1->_43 + v2->_43; result->_44 = v1->_44 + v2->_44;
}
void PRMat::subtract ( const PRMat * v1, const PRMat * v2, PRMat * result ) {
	result->_11 = v1->_11 - v2->_11; result->_12 = v1->_12 - v2->_12; result->_13 = v1->_13 - v2->_13; result->_14 = v1->_14 - v2->_14;
	result->_21 = v1->_21 - v2->_21; result->_22 = v1->_22 - v2->_22; result->_23 = v1->_23 - v2->_23; result->_24 = v1->_24 - v2->_24;
	result->_31 = v1->_31 - v2->_31; result->_32 = v1->_32 - v2->_32; result->_33 = v1->_33 - v2->_33; result->_34 = v1->_34 - v2->_34;
	result->_41 = v1->_41 - v2->_41; result->_42 = v1->_42 - v2->_42; result->_43 = v1->_43 - v2->_43; result->_44 = v1->_44 - v2->_44;
}
void PRMat::negate ( const PRMat * v1, PRMat * result ) {
	result->_11 = -v1->_11; result->_12 = -v1->_12; result->_13 = -v1->_13; result->_14 = -v1->_14;
	result->_21 = -v1->_21; result->_22 = -v1->_22; result->_23 = -v1->_23; result->_24 = -v1->_24;
	result->_31 = -v1->_31; result->_32 = -v1->_32; result->_33 = -v1->_33; result->_34 = -v1->_34;
	result->_41 = -v1->_41; result->_42 = -v1->_42; result->_43 = -v1->_43; result->_44 = -v1->_44;
}
void PRMat::multiply ( const PRMat * v1, const PRMat * v2, PRMat * result ) {
	result->_11 = ( ( ( v1->_11 * v2->_11 ) + ( v1->_12 * v2->_21 ) ) + ( v1->_13 * v2->_31 ) ) + ( v1->_14 * v2->_41 );
	result->_12 = ( ( ( v1->_11 * v2->_12 ) + ( v1->_12 * v2->_22 ) ) + ( v1->_13 * v2->_32 ) ) + ( v1->_14 * v2->_42 );
	result->_13 = ( ( ( v1->_11 * v2->_13 ) + ( v1->_12 * v2->_23 ) ) + ( v1->_13 * v2->_33 ) ) + ( v1->_14 * v2->_43 );
	result->_14 = ( ( ( v1->_11 * v2->_14 ) + ( v1->_12 * v2->_24 ) ) + ( v1->_13 * v2->_34 ) ) + ( v1->_14 * v2->_44 );
	result->_21 = ( ( ( v1->_21 * v2->_11 ) + ( v1->_22 * v2->_21 ) ) + ( v1->_23 * v2->_31 ) ) + ( v1->_24 * v2->_41 );
	result->_22 = ( ( ( v1->_21 * v2->_12 ) + ( v1->_22 * v2->_22 ) ) + ( v1->_23 * v2->_32 ) ) + ( v1->_24 * v2->_42 );
	result->_23 = ( ( ( v1->_21 * v2->_13 ) + ( v1->_22 * v2->_23 ) ) + ( v1->_23 * v2->_33 ) ) + ( v1->_24 * v2->_43 );
	result->_24 = ( ( ( v1->_21 * v2->_14 ) + ( v1->_22 * v2->_24 ) ) + ( v1->_23 * v2->_34 ) ) + ( v1->_24 * v2->_44 );
	result->_31 = ( ( ( v1->_31 * v2->_11 ) + ( v1->_32 * v2->_21 ) ) + ( v1->_33 * v2->_31 ) ) + ( v1->_34 * v2->_41 );
	result->_32 = ( ( ( v1->_31 * v2->_12 ) + ( v1->_32 * v2->_22 ) ) + ( v1->_33 * v2->_32 ) ) + ( v1->_34 * v2->_42 );
	result->_33 = ( ( ( v1->_31 * v2->_13 ) + ( v1->_32 * v2->_23 ) ) + ( v1->_33 * v2->_33 ) ) + ( v1->_34 * v2->_43 );
	result->_34 = ( ( ( v1->_31 * v2->_14 ) + ( v1->_32 * v2->_24 ) ) + ( v1->_33 * v2->_34 ) ) + ( v1->_34 * v2->_44 );
	result->_41 = ( ( ( v1->_41 * v2->_11 ) + ( v1->_42 * v2->_21 ) ) + ( v1->_43 * v2->_31 ) ) + ( v1->_44 * v2->_41 );
	result->_42 = ( ( ( v1->_41 * v2->_12 ) + ( v1->_42 * v2->_22 ) ) + ( v1->_43 * v2->_32 ) ) + ( v1->_44 * v2->_42 );
	result->_43 = ( ( ( v1->_41 * v2->_13 ) + ( v1->_42 * v2->_23 ) ) + ( v1->_43 * v2->_33 ) ) + ( v1->_44 * v2->_43 );
	result->_44 = ( ( ( v1->_41 * v2->_14 ) + ( v1->_42 * v2->_24 ) ) + ( v1->_43 * v2->_34 ) ) + ( v1->_44 * v2->_44 );
}
void PRMat::multiply ( const PRMat * v1, float v2, PRMat * result ) {
	result->_11 = v1->_11 * v2; result->_12 = v1->_12 * v2; result->_13 = v1->_13 * v2; result->_14 = v1->_14 * v2;
	result->_21 = v1->_21 * v2; result->_22 = v1->_22 * v2; result->_23 = v1->_23 * v2; result->_24 = v1->_24 * v2;
	result->_31 = v1->_31 * v2; result->_32 = v1->_32 * v2; result->_33 = v1->_33 * v2; result->_34 = v1->_34 * v2;
	result->_41 = v1->_41 * v2; result->_42 = v1->_42 * v2; result->_43 = v1->_43 * v2; result->_44 = v1->_44 * v2;
}
void PRMat::multiply ( float v1, const PRMat * v2, PRMat * result ) {
	result->_11 = v2->_11 * v1; result->_12 = v2->_12 * v1; result->_13 = v2->_13 * v1; result->_14 = v2->_14 * v1;
	result->_21 = v2->_21 * v1; result->_22 = v2->_22 * v1; result->_23 = v2->_23 * v1; result->_24 = v2->_24 * v1;
	result->_31 = v2->_31 * v1; result->_32 = v2->_32 * v1; result->_33 = v2->_33 * v1; result->_34 = v2->_34 * v1;
	result->_41 = v2->_41 * v1; result->_42 = v2->_42 * v1; result->_43 = v2->_43 * v1; result->_44 = v2->_44 * v1;
}
void PRMat::divide ( const PRMat * v1, const PRMat * v2, PRMat * result ) {
	result->_11 = v1->_11 / v2->_11; result->_12 = v1->_12 / v2->_12; result->_13 = v1->_13 / v2->_13; result->_14 = v1->_14 / v2->_14;
	result->_21 = v1->_21 / v2->_21; result->_22 = v1->_22 / v2->_22; result->_23 = v1->_23 / v2->_23; result->_24 = v1->_24 / v2->_24;
	result->_31 = v1->_31 / v2->_31; result->_32 = v1->_32 / v2->_32; result->_33 = v1->_33 / v2->_33; result->_34 = v1->_34 / v2->_34;
	result->_41 = v1->_41 / v2->_41; result->_42 = v1->_42 / v2->_42; result->_43 = v1->_43 / v2->_43; result->_44 = v1->_44 / v2->_44;
}
void PRMat::divide ( const PRMat * v1, float v2, PRMat * result ) {
	result->_11 = v1->_11 / v2; result->_12 = v1->_12 / v2; result->_13 = v1->_13 / v2; result->_14 = v1->_14 / v2;
	result->_21 = v1->_21 / v2; result->_22 = v1->_22 / v2; result->_23 = v1->_23 / v2; result->_24 = v1->_24 / v2;
	result->_31 = v1->_31 / v2; result->_32 = v1->_32 / v2; result->_33 = v1->_33 / v2; result->_34 = v1->_34 / v2;
	result->_41 = v1->_41 / v2; result->_42 = v1->_42 / v2; result->_43 = v1->_43 / v2; result->_44 = v1->_44 / v2;
}

PRMat PRMat::add ( const PRMat & v1, const PRMat & v2 ) { COPIEDMETHOD2 ( PRMat, add, &v1, &v2 ); }
PRMat PRMat::subtract ( const PRMat & v1, const PRMat & v2 ) { COPIEDMETHOD2 ( PRMat, subtract, &v1, &v2 ); }
PRMat PRMat::negate ( const PRMat & v1 ) { COPIEDMETHOD1 ( PRMat, negate, &v1 ); }
PRMat PRMat::multiply ( const PRMat & v1, const PRMat & v2 ) { COPIEDMETHOD2 ( PRMat, multiply, &v1, &v2 ); }
PRMat PRMat::multiply ( const PRMat & v1, float v2 ) { COPIEDMETHOD2 ( PRMat, multiply, &v1, v2 ); }
PRMat PRMat::multiply ( float v1, const PRMat & v2 ) { COPIEDMETHOD2 ( PRMat, multiply, v1, &v2 ); }
PRMat PRMat::divide ( const PRMat & v1, const PRMat & v2 ) { COPIEDMETHOD2 ( PRMat, divide, &v1, &v2 ); }
PRMat PRMat::divide ( const PRMat & v1, float v2 ) { COPIEDMETHOD2 ( PRMat, divide, &v1, v2 ); }

void PRMat::createTranslate ( const PRVec3 * v, PRMat * result ) {
	*result = PRMat (
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		v->x, v->y, v->z, 1
	);
}
void PRMat::createScale ( const PRVec3 * v, PRMat * result ) {
	*result = PRMat (
		v->x, 0, 0, 0,
		0, v->y, 0, 0,
		0, 0, v->z, 0,
		0, 0, 0, 1
	);
}
void PRMat::createRotationX ( float r, PRMat * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMat (
		1, 0, 0, 0,
		0, v1, v2, 0,
		0, -v2, v1, 0,
		0, 0, 0, 1
	);
}
void PRMat::createRotationY ( float r, PRMat * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMat (
		v1, 0, -v2, 0,
		0, 1, 0, 0,
		v2, 0, v1, 0,
		0, 0, 0, 1
	);
}
void PRMat::createRotationZ ( float r, PRMat * result ) {
	float v1 = cosf ( r ), v2 = sinf ( r );
	*result = PRMat (
		v1, v2, 0, 0,
		-v2, v1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}
PRMat PRMat::createTranslate ( const PRVec3 & v ) {
	COPIEDMETHOD1 ( PRMat, createTranslate, &v );
}
PRMat PRMat::createScale ( const PRVec3 & v ) {
	COPIEDMETHOD1 ( PRMat, createScale, &v );
}
PRMat PRMat::createRotationX ( float r ) {
	COPIEDMETHOD1 ( PRMat, createRotationX, r );
}
PRMat PRMat::createRotationY ( float r ) {
	COPIEDMETHOD1 ( PRMat, createRotationY, r );
}
PRMat PRMat::createRotationZ ( float r ) {
	COPIEDMETHOD1 ( PRMat, createRotationZ, r );
}
void PRMat::createLookAtLH ( const PRVec3 * position, const PRVec3 * target, const PRVec3 * upVector, PRMat * result ) {
	PRVec3 zaxis;
	PRVec3::subtract ( target, position, &zaxis );
	zaxis.normalize ( &zaxis );
	PRVec3 xaxis;
	PRVec3::cross ( upVector, &zaxis, &xaxis );
	xaxis.normalize ( &xaxis );
	PRVec3 yaxis;
	PRVec3::cross ( &zaxis, &xaxis, &yaxis );
	*result = PRMat (
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-PRVec3::dot ( xaxis, *position ), -PRVec3::dot ( yaxis, *position ), -PRVec3::dot ( zaxis, *position ), 1 );
}
void PRMat::createLookAtRH ( const PRVec3 * position, const PRVec3 * target, const PRVec3 * upVector, PRMat * result ) {
	PRVec3 zaxis;
	PRVec3::subtract ( position, target, &zaxis );
	zaxis.normalize ( &zaxis );
	PRVec3 xaxis;
	PRVec3::cross ( upVector, &zaxis, &xaxis );
	xaxis.normalize ( &xaxis );
	PRVec3 yaxis;
	PRVec3::cross ( &zaxis, &xaxis, &yaxis );
	*result = PRMat (
		xaxis.x, yaxis.x, zaxis.x, 0,
		xaxis.y, yaxis.y, zaxis.y, 0,
		xaxis.z, yaxis.z, zaxis.z, 0,
		-PRVec3::dot ( xaxis, *position ), -PRVec3::dot ( yaxis, *position ), -PRVec3::dot ( zaxis, *position ), 1 );
}
PRMat PRMat::createLookAtLH ( const PRVec3 & position, const PRVec3 & target, const PRVec3 & upVector ) {
	PRMat temp;
	createLookAtLH ( &position, &target, &upVector, &temp );
	return temp;
}
PRMat PRMat::createLookAtRH ( const PRVec3 & position, const PRVec3 & target, const PRVec3 & upVector ) {
	PRMat temp;
	createLookAtRH ( &position, &target, &upVector, &temp );
	return temp;
}
void PRMat::createOrthographicLH ( float w, float h, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / ( zf - zn ), 0,
		0, 0, zn / ( zn - zf ), 1
	);
}
void PRMat::createOrthographicRH ( float w, float h, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 / w, 0, 0, 0,
		0, 2 / h, 0, 0,
		0, 0, 1 / ( zn - zf ), 0,
		0, 0, zn / ( zn - zf ), 1
	);
}
void PRMat::createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 / ( r - l ), 0, 0, 0,
		0, 2 / ( t - b ), 0, 0,
		0, 0, 1 / ( zf - zn ), 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), zn / ( zn - zf ), 1
	);
}
void PRMat::createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 / ( r - l ), 0, 0, 0,
		0, 2 / ( t - b ), 0, 0,
		0, 0, 1 / ( zn - zf ), 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), zn / ( zn - zf ), 1
	);
}
void PRMat::createPerspectiveLH ( float w, float h, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 * zn / w, 0, 0, 0,
		0, 2 * zn / h, 0, 0,
		0, 0, zf / ( zf - zn ), 1,
		0, 0, zn * zf / ( zf - zn ), 0
	);
}
void PRMat::createPerspectiveRH ( float w, float h, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 * zn / w, 0, 0, 0,
		0, 2 * zn / h, 0, 0,
		0, 0, zf / ( zn - zf ), 1,
		0, 0, zn * zf / ( zn - zf ), 0
	);
}
void PRMat::createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 * zn / ( r - l ), 0, 0, 0,
		0, 2 * zn / ( t - b ), 0, 0,
		( l + r ) / ( l - r ), ( t + b ) / ( b - t ), zf / ( zf - zn ), 1,
		0, 0, zn * zf / ( zf - zn ), 1 );
}
void PRMat::createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf, PRMat * result ) {
	*result = PRMat (
		2 * zn / ( r - l ), 0, 0, 0,
		0, 2 * zn / ( t - b ), 0, 0,
		( l + r ) / ( l - r ), ( t + b ) / ( t - b ), zf / ( zn - zf ), 1,
		0, 0, zn * zf / ( zn - zf ), 1 );
}
void PRMat::createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf, PRMat * result ) {
	float ys = 1 / tanf ( fov * 0.5f ), xs = ys / aspect;
	*result = PRMat (
		xs, 0, 0, 0,
		0, ys, 0, 0,
		0, 0, zf / ( zf - zn ), 1,
		0, 0, ( -zn * zf ) / ( zf - zn ), 0
	);
}
void PRMat::createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf, PRMat * result ) {
	float ys = 1 / tanf ( fov * 0.5f ), xs = ys / aspect;
	*result = PRMat (
		xs, 0, 0, 0,
		0, ys, 0, 0,
		0, 0, zf / ( zn - zf ), -1,
		0, 0, ( zn * zf ) / ( zn - zf ), 0
	);
}
PRMat PRMat::createOrthographicLH ( float w, float h, float zn, float zf ) {
	PRMat temp;
	createOrthographicLH ( w, h, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createOrthographicRH ( float w, float h, float zn, float zf ) {
	PRMat temp;
	createOrthographicRH ( w, h, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createOrthographicOffCenterLH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMat temp;
	createOrthographicOffCenterLH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createOrthographicOffCenterRH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMat temp;
	createOrthographicOffCenterRH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveLH ( float w, float h, float zn, float zf ) {
	PRMat temp;
	createPerspectiveLH ( w, h, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveRH ( float w, float h, float zn, float zf ) {
	PRMat temp;
	createPerspectiveRH ( w, h, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveOffCenterLH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMat temp;
	createPerspectiveOffCenterLH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveOffCenterRH ( float l, float r, float b, float t, float zn, float zf ) {
	PRMat temp;
	createPerspectiveOffCenterRH ( l, r, b, t, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveFieldOfViewLH ( float fov, float aspect, float zn, float zf ) {
	PRMat temp;
	createPerspectiveFieldOfViewLH ( fov, aspect, zn, zf, &temp );
	return temp;
}
PRMat PRMat::createPerspectiveFieldOfViewRH ( float fov, float aspect, float zn, float zf ) {
	PRMat temp;
	createPerspectiveFieldOfViewRH ( fov, aspect, zn, zf, &temp );
	return temp;
}
void PRMat::createBillboard ( const PRVec3 * objPos, const PRVec3 * camPos, const PRVec3 * camUpVec,
	const PRVec3 * camForwardVec, PRMat * result ) {
	PRVec3 vector, vector2, vector3;
	vector = *objPos - *camPos;
	float num = vector.lengthSquared ();
	if ( num < 0.0001f ) vector = -*camForwardVec;
	else vector = vector * ( 1.0f / sqrtf ( num ) );

	PRVec3::cross ( camUpVec, &vector, &vector3 );
	vector3 = vector3.normalize ();
	PRVec3::cross ( &vector, &vector3, &vector2 );
	*result = PRMat (
		vector3.x, vector3.y, vector3.z, 0,
		vector2.x, vector2.y, vector2.z, 0,
		vector.x, vector.y, vector.z, 0,
		objPos->x, objPos->y, objPos->z, 1
	);
}

PRMat operator+ ( const PRMat & v1, const PRMat & v2 ) { return PRMat::add ( v1, v2 ); }
PRMat operator- ( const PRMat & v1, const PRMat & v2 ) { return PRMat::subtract ( v1, v2 ); }
PRMat operator- ( const PRMat & v1 ) { return PRMat::negate ( v1 ); }
PRMat operator* ( const PRMat & v1, const PRMat & v2 ) { return PRMat::multiply ( v1, v2 ); }
PRMat operator* ( const PRMat & v1, float v2 ) { return PRMat::multiply ( v1, v2 ); }
PRMat operator* ( float v1, const PRMat & v2 ) { return PRMat::multiply ( v1, v2 ); }
PRMat operator/ ( const PRMat & v1, const PRMat & v2 ) { return PRMat::divide ( v1, v2 ); }
PRMat operator/ ( const PRMat & v1, float v2 ) { return PRMat::divide ( v1, v2 ); }
bool operator== ( const PRMat & v1, const PRMat & v2 ) {
	return PRIsEquals ( v1._11, v2._11 ) && PRIsEquals ( v1._12, v2._12 ) && PRIsEquals ( v1._13, v2._13 ) && PRIsEquals ( v1._14, v2._14 ) &&
		PRIsEquals ( v1._21, v2._21 ) && PRIsEquals ( v1._22, v2._22 ) && PRIsEquals ( v1._23, v2._23 ) && PRIsEquals ( v1._24, v2._24 ) &&
		PRIsEquals ( v1._31, v2._31 ) && PRIsEquals ( v1._32, v2._32 ) && PRIsEquals ( v1._33, v2._33 ) && PRIsEquals ( v1._34, v2._34 ) &&
		PRIsEquals ( v1._41, v2._41 ) && PRIsEquals ( v1._42, v2._42 ) && PRIsEquals ( v1._43, v2._43 ) && PRIsEquals ( v1._44, v2._44 );
}

#if PRPlatformUNIX
#	include <SOIL/SOIL.h>
#elif PRPlatformGoogleAndroid
#	include "stb_image/stb_image_aug.h"
#endif

FILE* PR_openFile ( std::string & filename, const char * openmode ) {
#if PRPlatformAppleFamily
	CFBundleRef mainBundle = CFBundleGetMainBundle ();
	CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL ( mainBundle );
	char path [ 4096 ];
	if ( !CFURLGetFileSystemRepresentation ( resourceURL, true, ( UInt8 * ) path, 4096 ) )
		throw std::runtime_error ( "Cannot get resource directory path." );
	CFRelease ( resourceURL );

	chdir ( path );
#endif

#if PRPlatformMicrosoftWindowsRT
	USES_CONVERSION;
#endif

	char fullpath [ 4096 ] = { 0, };
#if PRPlatformMicrosoftWindowsRT
	strcat_s ( fullpath, 4096, W2A ( Windows::ApplicationModel::Package::Current->InstalledLocation->Path->Data () ) );
	strcat_s ( fullpath, 4096, "\\" );
#endif
	strcat ( fullpath, filename.c_str () );

	FILE * fp = fopen ( fullpath, openmode );
	return fp;
}

bool PRGetImageData ( std::string & filename, void ** buffer, unsigned * width, unsigned * height )
{
#if PRPlatformAppleFamily
	CFBundleRef mainBundle = CFBundleGetMainBundle ();
	CFURLRef resourceURL = CFBundleCopyResourcesDirectoryURL ( mainBundle );
	char path [ 4096 ];
	if ( !CFURLGetFileSystemRepresentation ( resourceURL, true, ( UInt8 * ) path, 4096 ) )
		throw std::runtime_error ( "Cannot get resource directory path." );
	CFRelease ( resourceURL );

	chdir ( path );
#endif

#if PRPlatformUNIX
	*buffer = SOIL_load_image ( filename.c_str (), ( int* ) width, ( int* ) height, nullptr, 4 );
	if ( *buffer == nullptr )
		return false;
#elif !PRPlatformMicrosoftWindowsFamily
	*buffer = stbi_load ( filename.c_str (), ( int* ) width, ( int* ) height, 0, 4 );
	if ( *buffer == nullptr )
		return false;
#else
	USES_CONVERSION;

	IWICImagingFactory * factory;
	IWICBitmapDecoder * decoder;
	IWICBitmapFrameDecode * frameDecode;
	IWICFormatConverter * formatConverter;

	char fullpath [ 4096 ] = { 0, };
#if PRPlatformMicrosoftWindowsRT
	strcat_s ( fullpath, 4096, W2A ( Windows::ApplicationModel::Package::Current->InstalledLocation->Path->Data () ) );
	strcat_s ( fullpath, 4096, "\\Assets\\" );
#endif
	strcat_s ( fullpath, 4096, filename.c_str () );

	if ( FAILED ( CoCreateInstance ( CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_IWICImagingFactory, ( void** ) &factory ) ) )
		return false;

	if ( FAILED ( factory->CreateDecoderFromFilename ( A2W ( fullpath ), nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand, &decoder ) ) )
		return false;

	decoder->GetFrame ( 0, &frameDecode );
	frameDecode->GetSize ( width, height );

	factory->CreateFormatConverter ( &formatConverter );
	if ( FAILED ( formatConverter->Initialize ( frameDecode, GUID_WICPixelFormat32bppRGBA, WICBitmapDitherTypeNone, nullptr, 0, WICBitmapPaletteTypeCustom ) ) )
		return false;

	*buffer = new int [ *width * *height ];
	formatConverter->CopyPixels ( nullptr, sizeof ( int ) * *width, sizeof ( int ) * *width * *height, ( BYTE* ) *buffer );

	formatConverter->Release ();
	frameDecode->Release ();
	decoder->Release ();
	factory->Release ();
#endif

	return true;
}

POLYRAMDECLSPEC bool PRGetRawData ( std::string & filename, void ** buffer, unsigned * size )
{
	FILE * fp = PR_openFile ( filename, "rb" );
	if ( fp == nullptr ) return false;

	fseek ( fp, 0, SEEK_END );
	*size = ( unsigned ) ftell ( fp );
	fseek ( fp, 0, SEEK_SET );

	*buffer = new char [ *size ];
	fread ( *buffer, *size, 1, fp );

	fclose ( fp );

	return true;
}

struct vertex { PRVec3 p; PRVec2 t; PRVec4 d; };
struct polygonTriangle { vertex v1, v2, v3; };
struct polygonLine { vertex v1, v2; };

void generateCube ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );
void generateRect ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );
void generateSphere ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );
void generateCircle ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );
void generateGrid ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );
void generateGuide ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length );

PRModelGenerator::PRModelGenerator ( PRModelType modelType, PRModelProperty properties, PRModelEncircling circling,
	PRModelTexCoord tcs, const PRVec3 * scale ) {
	switch ( modelType ) {
	case PRModelType_Box:		generateCube ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Rectangle:	generateRect ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Sphere:	generateSphere ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Circle:	generateCircle ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Grid:		generateGrid ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	case PRModelType_Guide:		generateGuide ( properties, circling, tcs, scale, &m_data, &m_dataSize ); break;
	}
	m_properties = properties;
}

PRModelGenerator::PRModelGenerator ( std::string & filename, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale ) {
	if ( filename.substr ( filename.size () - 3, 3 ).compare ( "obj" ) != 0 )
		throw std::runtime_error ( "This object can read Wavefront's OBJ file only." );

	FILE * fp = PR_openFile ( filename, "rt" );

	// Original Source from "http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading"
	std::vector<unsigned> vIndices, uvIndices, nIndices;
	std::vector<PRVec3> tempVertices;
	std::vector<PRVec2> tempUVs;
	std::vector<PRVec3> tempNormals;

	char lineHeader [ 128 ];
	char stupidBuffer [ 1024 ];

	PRModelProperty prop = PRModelProperty_Position;

	unsigned i1 = 0, i2 = 1, i3 = 2;
	if ( circling == PRModelEncircling_LeftHand ) { i1 = 1; i2 = 0; i3 = 2; }

	while ( 1 ) {
		int res = fscanf ( fp, "%s", lineHeader );
		if ( res == EOF ) break;

		if ( strcmp ( lineHeader, "v" ) == 0 ) {
			PRVec3 vertex;
			fscanf ( fp, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z );
			tempVertices.push_back ( vertex );
		} else if ( strcmp ( lineHeader, "vt" ) == 0 ) {
			PRVec2 uv;
			fscanf ( fp, "%f %f\n", &uv.x, &uv.y );
			tempUVs.push_back ( uv );
			prop |= PRModelProperty_TexCoord;
		} else if ( strcmp ( lineHeader, "vn" ) == 0 ) {
			PRVec3 normal;
			fscanf ( fp, "%f %f %f\n", &normal.x, &normal.y, &normal.z );
			tempNormals.push_back ( normal );
			prop |= PRModelProperty_Normal;
		} else if ( strcmp ( lineHeader, "f" ) == 0 ) {
			//std::string vertex1, vertex2, vertex3;
			unsigned vi [ 3 ] = { 0, }, uvi [ 3 ] = { 0, }, ni [ 3 ] = { 0, };
			if ( prop == ( PRModelProperty_Position | PRModelProperty_Normal | PRModelProperty_TexCoord ) ) {
				int matches = fscanf ( fp, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vi [ 0 ], &uvi [ 0 ], &ni [ 0 ],
					&vi [ 1 ], &uvi [ 1 ], &ni [ 1 ], &vi [ 2 ], &uvi [ 2 ], &ni [ 2 ] );
				if ( matches != 9 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == ( PRModelProperty_Position | PRModelProperty_Normal ) ) {
				int matches = fscanf ( fp, "%d//%d %d//%d %d//%d\n", &vi [ 0 ], &ni [ 0 ],
					&vi [ 1 ], &ni [ 1 ], &vi [ 2 ], &ni [ 2 ] );
				if ( matches != 6 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == ( PRModelProperty_Position | PRModelProperty_TexCoord ) ) {
				int matches = fscanf ( fp, "%d/%d %d/%d %d/%d\n", &vi [ 0 ], &uvi [ 0 ],
					&vi [ 1 ], &uvi [ 1 ], &vi [ 2 ], &uvi [ 2 ] );
				if ( matches != 6 )
					throw std::runtime_error ( "File format is invalid." );
			} else if ( prop == PRModelProperty_Position ) {
				int matches = fscanf ( fp, "%d %d %d\n", &vi [ 0 ], &vi [ 1 ], &vi [ 2 ] );
				if ( matches != 3 )
					throw std::runtime_error ( "File format is invalid." );
			}

			vIndices.push_back ( vi [ i1 ] ); vIndices.push_back ( vi [ i2 ] ); vIndices.push_back ( vi [ i3 ] );

			if ( prop & PRModelProperty_TexCoord ) {
				uvIndices.push_back ( uvi [ i1 ] ); uvIndices.push_back ( uvi [ i2 ] ); uvIndices.push_back ( uvi [ i3 ] );
			}
			if ( prop & PRModelProperty_Normal ) {
				nIndices.push_back ( ni [ i1 ] ); nIndices.push_back ( ni [ i2 ] ); nIndices.push_back ( ni [ i3 ] );
			}
		} else fgets ( stupidBuffer, 1024, fp );
	}

	size_t vertexIndicesSize = vIndices.size ();
	unsigned stride = sizeof ( float ) * 3;
	if ( prop & PRModelProperty_Normal ) stride += sizeof ( float ) * 3;
	if ( prop & PRModelProperty_TexCoord ) stride += sizeof ( float ) * 2;

	float * vv = new float [ vertexIndicesSize * ( stride / sizeof ( float ) ) ];
	m_data = vv;
	m_dataSize = vertexIndicesSize * stride;
	unsigned count = 0;
	for ( unsigned i = 0; i < vertexIndicesSize; ++i ) {
		unsigned vertexIndex = vIndices [ i ];
		PRVec3 vertex = tempVertices [ vertexIndex - 1 ];
		if ( scale != nullptr ) vertex = vertex * *scale;
		vv [ count++ ] = vertex.x; vv [ count++ ] = vertex.y; vv [ count++ ] = vertex.z;

		if ( prop & PRModelProperty_Normal ) {
			unsigned normalIndex = nIndices [ i ];
			PRVec3 normal = tempNormals [ normalIndex - 1 ];
			vv [ count++ ] = normal.x; vv [ count++ ] = normal.y; vv [ count++ ] = normal.z;
		}

		if ( prop & PRModelProperty_TexCoord ) {
			unsigned uvIndex = uvIndices [ i ];
			PRVec2 uv = tempUVs [ uvIndex - 1 ];
			vv [ count++ ] = uv.x; vv [ count++ ] = ( tcs == PRModelTexCoord_UV ? uv.y : ( 1 - uv.y ) );
		}
	}

	m_properties = prop;
}

PRModelProperty PRModelGenerator::getProperties () const { return m_properties; }
const void* PRModelGenerator::getData () const { return m_data; }
unsigned PRModelGenerator::getDataSize () const { return m_dataSize; }

PRModelGenerator::~PRModelGenerator () { SAFE_DELETE_ARRAY ( m_data ); }

void generateTriangleModel ( void * data, unsigned dataSize, PRModelProperty properties, PRModelEncircling circling,
	PRModelTexCoord tcs, const PRVec3 * scale, void** result, unsigned * length ) {
	polygonTriangle *vertices = ( polygonTriangle* ) data;

	std::vector<float> vv;
	for ( unsigned i = 0; i < dataSize / sizeof ( polygonTriangle ); ++i ) {
		PRVec3 norm = 
			circling == PRModelEncircling_RightHand ?
				PRCalcNormal ( vertices->v1.p, vertices->v2.p, vertices->v3.p ) :
				PRCalcNormal ( vertices->v2.p, vertices->v1.p, vertices->v3.p );
		vertex v1 = ( circling == PRModelEncircling_RightHand ? vertices->v1 : vertices->v2 );
		vertex v2 = ( circling == PRModelEncircling_RightHand ? vertices->v2 : vertices->v1 );
		vertex v3 = vertices->v3;

		PRVec3 p1 = v1.p;
		if ( scale != nullptr ) p1 = p1 * *scale;
		vv.push_back ( p1.x ); vv.push_back ( p1.y ); vv.push_back ( p1.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( v1.t.x ); vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - v1.t.y : v1.t.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( v1.d.x ); vv.push_back ( v1.d.y ); vv.push_back ( v1.d.z ); vv.push_back ( v1.d.w );
		}

		PRVec3 p2 = v2.p;
		if ( scale != nullptr ) p2 = p2 * *scale;
		vv.push_back ( p2.x ); vv.push_back ( p2.y ); vv.push_back ( p2.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( v2.t.x ); vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - v2.t.y : v2.t.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( v2.d.x ); vv.push_back ( v2.d.y ); vv.push_back ( v2.d.z ); vv.push_back ( v2.d.w );
		}

		PRVec3 p3 = v3.p;
		if ( scale != nullptr ) p3 = p3 * *scale;
		vv.push_back ( p3.x ); vv.push_back ( p3.y ); vv.push_back ( p3.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( v3.t.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - v3.t.y : v3.t.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( v3.d.x ); vv.push_back ( v3.d.y ); vv.push_back ( v3.d.z ); vv.push_back ( v3.d.w );
		}

		++vertices;
	}

	*result = new float [ vv.size () ];
	*length = ( unsigned ) vv.size () * sizeof ( float );
	memcpy ( *result, &vv [ 0 ], *length );
}

void generateLineModel ( void * data, unsigned dataSize, PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs,
	const PRVec3 * scale, void** result, unsigned * length ) {
	polygonLine *vertices = ( polygonLine* ) data;

	std::vector<float> vv;
	for ( unsigned i = 0; i < dataSize / sizeof ( polygonLine ); ++i ) {
		PRVec3 norm = vertices->v2.p - vertices->v1.p;

		PRVec3 p1 = vertices->v1.p;
		if ( scale != nullptr ) p1 = p1 * *scale;
		vv.push_back ( p1.x ); vv.push_back ( p1.y ); vv.push_back ( p1.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v1.t.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v1.t.y : vertices->v1.t.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v1.d.x );
			vv.push_back ( vertices->v1.d.y );
			vv.push_back ( vertices->v1.d.z );
			vv.push_back ( vertices->v1.d.w );
		}

		PRVec3 p2 = vertices->v2.p;
		if ( scale != nullptr ) p2 = p2 * *scale;
		vv.push_back ( p2.x ); vv.push_back ( p2.y ); vv.push_back ( p2.z );

		if ( properties & PRModelProperty_Normal ) {
			vv.push_back ( norm.x ); vv.push_back ( norm.y ); vv.push_back ( norm.z );
		}

		if ( properties & PRModelProperty_TexCoord ) {
			vv.push_back ( vertices->v2.t.x );
			vv.push_back ( tcs == PRModelTexCoord_ST ? 1 - vertices->v2.t.y : vertices->v2.t.y );
		}

		if ( properties & PRModelProperty_Diffuse ) {
			vv.push_back ( vertices->v2.d.x );
			vv.push_back ( vertices->v2.d.y );
			vv.push_back ( vertices->v2.d.z );
			vv.push_back ( vertices->v2.d.w );
		}

		++vertices;
	}

	*result = new float [ vv.size () ];
	*length = ( unsigned ) vv.size () * sizeof ( float );
	memcpy ( *result, &vv [ 0 ], *length );
}

void generateCube ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length ) {
	vertex cube [] = {
		{ { -0.5f, -0.5f, -0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },

		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },

		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },

		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, -0.5f }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, +0.5f }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, +0.5f }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, +0.5f, -0.5f }, { 0, 1 }, { 1, 1, 1, 1 } }
	};
	generateTriangleModel ( cube, sizeof ( cube ), properties, circling, tcs, scale, result, length );
}

void generateRect ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length )
{
	vertex rect [] = {
		{ { -0.5f, +0.5f, 0 }, { 0, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, 0 }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, 0 }, { 1, 0 }, { 1, 1, 1, 1 } },
		{ { -0.5f, -0.5f, 0 }, { 0, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, -0.5f, 0 }, { 1, 1 }, { 1, 1, 1, 1 } },
		{ { +0.5f, +0.5f, 0 }, { 1, 0 }, { 1, 1, 1, 1 } },
	};
	generateTriangleModel ( rect, sizeof ( rect ), properties, circling, tcs, scale, result, length );
}

void generateSphere ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length ) {
	// Source from "http://stackoverflow.com/questions/5988686/creating-a-3d-sphere-in-opengl-using-visual-c"

	const unsigned rings = scale == nullptr ? 40 : ( unsigned ) scale->x * 40;
	const unsigned sectors = scale == nullptr ? 40 : ( unsigned ) scale->y * 40;

	float const R = 1.0f / ( float ) ( rings - 1 );
	float const S = 1.0f / ( float ) ( sectors - 1 );
	unsigned r, s;

	std::vector<PRVec3> vertices;
	std::vector<PRVec2> texcoords;
	std::vector<unsigned> indices;

	for ( r = 0; r < rings; r++ ) {
		for ( s = 0; s < sectors; s++ ) {
			float const y = sin ( -PR_PIover2 + PR_PI * r * R );
			float const x = cos ( 2 * PR_PI * s * S ) * sin ( PR_PI * r * R );
			float const z = sin ( 2 * PR_PI * s * S ) * sin ( PR_PI * r * R );
			vertices.push_back ( PRVec3 ( x, y, z ) * 0.5f );
			texcoords.push_back ( PRVec2 ( s * S, r * R ) );
		}
	}

	for ( r = 0; r < rings - 1; r++ ) {
		for ( s = 0; s < sectors - 1; s++ ) {
			int curRow = r * sectors;
			int nextRow = ( r + 1 ) * sectors;

			indices.push_back ( curRow + s );
			indices.push_back ( nextRow + s );
			indices.push_back ( nextRow + ( s + 1 ) );

			indices.push_back ( curRow + s );
			indices.push_back ( nextRow + ( s + 1 ) );
			indices.push_back ( curRow + ( s + 1 ) );
		}
	}

	std::vector<vertex> sphere;
	sphere.resize ( indices.size () );
	int j = 0;
	for ( auto i = indices.begin (); i != indices.end (); ++i ) {
		vertex vtx;
		vtx.p = vertices [ *i ];
		vtx.t = texcoords [ *i ];
		vtx.d = PRVec4 ( 1, 1, 1, 1 );
		sphere [ j++ ] = vtx;
	}

	float * temp = new float [ sphere.size () * sizeof ( vertex ) ];
	unsigned templen = ( unsigned ) ( sizeof ( vertex ) * sphere.size () );
	memcpy ( temp, &sphere [ 0 ], templen );

	generateTriangleModel ( temp, templen, properties, circling, tcs, scale, result, length );

	delete [] temp;
}

void generateCircle ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length ) {
	unsigned sectors = scale == nullptr ? 40 : ( unsigned ) PRMax ( scale->x, scale->y ) * 40;

	std::vector<vertex> vertices;
	for ( float r = 0; r <= PR_2PI; r += ( PR_2PI / sectors ) ) {
		vertex vtx;

		vtx.p = PRVec3 ( 0, 0, 0 );
		vtx.t = PRVec2 ( 0.5f, 0.5f );
		vtx.d = PRVec4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );

		vtx.p = PRVec3 ( cos ( r ), sin ( r ), 0 ) * 0.5f;
		vtx.t = PRVec2 ( vtx.p.x + 0.5f, vtx.p.y + 0.5f );
		vtx.d = PRVec4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );

		vtx.p = PRVec3 ( cos ( r + ( PR_2PI / sectors ) ), sin ( r + ( PR_2PI / sectors ) ), 0 ) * 0.5f;
		vtx.t = PRVec2 ( vtx.p.x + 0.5f, vtx.p.y + 0.5f );
		vtx.d = PRVec4 ( 1, 1, 1, 1 );
		vertices.push_back ( vtx );
	}

	float * temp = new float [ vertices.size () * sizeof ( vertex ) ];
	unsigned templen = ( unsigned ) ( sizeof ( vertex ) * vertices.size () );
	memcpy ( temp, &vertices [ 0 ], templen );

	generateTriangleModel ( temp, templen, properties, circling, tcs, scale, result, length );

	delete [] temp;
}

void generateGrid ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length ) {
	polygonLine vertices [ 202 ];
	unsigned index = 0;
	for ( unsigned z = 0; z <= 100; ++z ) {
		vertices [ index ].v1.p = PRVec3 ( -50, 0, ( float ) z - 50 );
		vertices [ index ].v1.t = PRVec2 ( 0, 0 );
		vertices [ index ].v1.d = PRVec4 ( 1, 1, 1, 1 );
		vertices [ index ].v2.p = PRVec3 ( 50, 0, ( float ) z - 50 );
		vertices [ index ].v2.t = PRVec2 ( 1, 0 );
		vertices [ index ].v2.d = PRVec4 ( 1, 1, 1, 1 );
		++index;
	}
	for ( unsigned x = 0; x <= 100; ++x ) {
		vertices [ index ].v1.p = PRVec3 ( ( float ) x - 50, 0, -50 );
		vertices [ index ].v1.t = PRVec2 ( 0, 0 );
		vertices [ index ].v1.d = PRVec4 ( 1, 1, 1, 1 );
		vertices [ index ].v2.p = PRVec3 ( ( float ) x - 50, 0, 50 );
		vertices [ index ].v2.t = PRVec2 ( 0, 1 );
		vertices [ index ].v2.d = PRVec4 ( 1, 1, 1, 1 );
		++index;
	}
	generateLineModel ( vertices, sizeof ( vertices ), properties, circling, tcs, scale, result, length );
}

void generateGuide ( PRModelProperty properties, PRModelEncircling circling, PRModelTexCoord tcs, const PRVec3 * scale,
	void** result, unsigned * length ) {
	polygonLine vertices [ 3 ] = {
		{ { { 0, 0, 0 }, { 0, 0 }, { 1, 0, 0, 1 } }, { { 1, 0, 0 }, { 1, 0 }, { 1, 0, 0, 1 } } },
		{ { { 0, 0, 0 }, { 0, 0 }, { 0, 1, 0, 1 } }, { { 0, 1, 0 }, { 1, 0 }, { 0, 1, 0, 1 } } },
		{ { { 0, 0, 0 }, { 0, 0 }, { 0, 0, 1, 1 } }, { { 0, 0, 1 }, { 0, 1 }, { 0, 0, 1, 1 } } },
	};
	generateLineModel ( vertices, sizeof ( vertices ), properties, circling, tcs, scale, result, length );
}

PRVec3 PRCalcNormal ( const PRVec3 & v1, const PRVec3 & v2, const PRVec3 & v3 ) {
	PRVec3 temp1 = v2 - v1, temp2 = v3 - v1;
	return PRVec3::cross ( temp1, temp2 ).normalize ();
}

double PRCurrentSec () {
#if PRPlatformMicrosoftWindowsNT || PRPlatformMicrosoftWindowsRT
	LARGE_INTEGER performanceFrequency, getTime;
	QueryPerformanceFrequency ( &performanceFrequency );
	QueryPerformanceCounter ( &getTime );
	return ( getTime.QuadPart / ( double ) performanceFrequency.QuadPart );
#elif PRPlatformAppleFamily || PRPlatformUNIXFamily
	timeval tv;
	gettimeofday ( &tv, nullptr );
	return ( tv.tv_sec * 1000 + tv.tv_usec / 1000 ) / 1000.0;
#endif
}

void PRLog ( const char * format, ... ) {
	va_list vl;
	va_start ( vl, format );
	char text [ 1024 ];
	vsprintf ( text, format, vl );
	va_end ( vl );

#if PRPlatformGoogleAndroid
	__android_log_print ( ANDROID_LOG_INFO, "libPolyram", text );
#else
	size_t len = strlen ( text );
	text [ len ] = '\n';
	text [ len + 1 ] = '\0';
#	if PRPlatformMicrosoftWindowsFamily
	OutputDebugStringA ( text );
#	else
	fprintf ( stderr, text );
#	endif
#endif
}