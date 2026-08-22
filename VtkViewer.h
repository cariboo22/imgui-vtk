#pragma once

#include <iostream>
#include <string>
#include <exception>

#include "imgui.h"

#include <unordered_map>
#include <vtkProp.h>
#include <vtkPropCollection.h>
#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCallbackCommand.h>
#include <vtkCommand.h>
#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkOpenGLFramebufferObject.h>
#include <vtkGenericRenderWindowInteractor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkRenderer.h>

// RGB Color in range [0.0, 1.0]
#define DEFAULT_BACKGROUND 0.39, 0.39, 0.39
// Alpha value in range [0.0, 1.0] where 1 = opaque
#define DEFAULT_ALPHA 1

// #define FORWARD_IMGUI_KEYBOARD_TO_VTK 1

#ifdef FORWARD_IMGUI_KEYBOARD_TO_VTK
struct VtkKey {
    const char* keySym;
    const char keyCode;
    const bool printable;
};

static const std::unordered_map<ImGuiKey, VtkKey> imGuiToVtkKey = {
    // Letters
    { ImGuiKey_A, {"a", 'a', true} },
    { ImGuiKey_B, {"b", 'b', true} },
    { ImGuiKey_C, {"c", 'c', true} },
    { ImGuiKey_D, {"d", 'd', true} },
    { ImGuiKey_E, {"e", 'e', true} },
    { ImGuiKey_F, {"f", 'f', true} },
    { ImGuiKey_G, {"g", 'g', true} },
    { ImGuiKey_H, {"h", 'h', true} },
    { ImGuiKey_I, {"i", 'i', true} },
    { ImGuiKey_J, {"j", 'j', true} },
    { ImGuiKey_K, {"k", 'k', true} },
    { ImGuiKey_L, {"l", 'l', true} },
    { ImGuiKey_M, {"m", 'm', true} },
    { ImGuiKey_N, {"n", 'n', true} },
    { ImGuiKey_O, {"o", 'o', true} },
    { ImGuiKey_P, {"p", 'p', true} },
    { ImGuiKey_Q, {"q", 'q', true} },
    { ImGuiKey_R, {"r", 'r', true} },
    { ImGuiKey_S, {"s", 's', true} },
    { ImGuiKey_T, {"t", 't', true} },
    { ImGuiKey_U, {"u", 'u', true} },
    { ImGuiKey_V, {"v", 'v', true} },
    { ImGuiKey_W, {"w", 'w', true} },
    { ImGuiKey_X, {"x", 'x', true} },
    { ImGuiKey_Y, {"y", 'y', true} },
    { ImGuiKey_Z, {"z", 'z', true} },

    // Numbers
    { ImGuiKey_0, {"0", '0', true} },
    { ImGuiKey_1, {"1", '1', true} },
    { ImGuiKey_2, {"2", '2', true} },
    { ImGuiKey_3, {"3", '3', true} },
    { ImGuiKey_4, {"4", '4', true} },
    { ImGuiKey_5, {"5", '5', true} },
    { ImGuiKey_6, {"6", '6', true} },
    { ImGuiKey_7, {"7", '7', true} },
    { ImGuiKey_8, {"8", '8', true} },
    { ImGuiKey_9, {"9", '9', true} },

    // Navigation
    { ImGuiKey_LeftArrow,  {"Left",  0, false} },
    { ImGuiKey_RightArrow, {"Right", 0, false} },
    { ImGuiKey_UpArrow,    {"Up",    0, false} },
    { ImGuiKey_DownArrow,  {"Down",  0, false} },

    { ImGuiKey_Home,     {"Home",     0, false} },
    { ImGuiKey_End,      {"End",      0, false} },
    { ImGuiKey_PageUp,   {"Prior",    0, false} },
    { ImGuiKey_PageDown, {"Next",     0, false} },
    { ImGuiKey_Insert,   {"Insert",   0, false} },
    { ImGuiKey_Delete,   {"Delete",   0, false} },

    // Whitespace
    { ImGuiKey_Space, {"space", ' ', true} },
    { ImGuiKey_Tab,   {"Tab", '\t', true} },
    { ImGuiKey_Enter, {"Return", '\r', true} },

    // Editing
    { ImGuiKey_Backspace, {"BackSpace", '\b', true} },
    { ImGuiKey_Escape,    {"Escape", 27, true} },

    // Function keys
    { ImGuiKey_F1,  {"F1", 0, false} },
    { ImGuiKey_F2,  {"F2", 0, false} },
    { ImGuiKey_F3,  {"F3", 0, false} },
    { ImGuiKey_F4,  {"F4", 0, false} },
    { ImGuiKey_F5,  {"F5", 0, false} },
    { ImGuiKey_F6,  {"F6", 0, false} },
    { ImGuiKey_F7,  {"F7", 0, false} },
    { ImGuiKey_F8,  {"F8", 0, false} },
    { ImGuiKey_F9,  {"F9", 0, false} },
    { ImGuiKey_F10, {"F10", 0, false} },
    { ImGuiKey_F11, {"F11", 0, false} },
    { ImGuiKey_F12, {"F12", 0, false} },
};
#endif

class VtkViewerError : public std::runtime_error {
public:
	explicit VtkViewerError(const std::string& message) throw() : std::runtime_error(message) {}
	~VtkViewerError() = default;
public:
	virtual char const* what() const throw() {
		return exception::what();
	}
};

class VtkViewer {
private:
	static void isCurrentCallbackFn(vtkObject* caller, long unsigned int eventId, void* clientData, void* callData);
	void processEvents();
private:
	vtkSmartPointer<vtkGenericOpenGLRenderWindow> renderWindow;
	vtkSmartPointer<vtkGenericRenderWindowInteractor> interactor;
	vtkSmartPointer<vtkInteractorStyleTrackballCamera> interactorStyle;
	vtkSmartPointer<vtkRenderer> renderer;
private:
	unsigned int viewportWidth, viewportHeight;
	unsigned int tex;
	bool firstRender;
public:
	VtkViewer();
	VtkViewer(const VtkViewer& vtkViewer);
	VtkViewer(VtkViewer&& vtkViewer) noexcept;
	~VtkViewer();

	VtkViewer& operator=(const VtkViewer& vtkViewer);
private:
	IMGUI_IMPL_API void init();
public:
	IMGUI_IMPL_API void render();
	IMGUI_IMPL_API void render(const ImVec2 size);
	IMGUI_IMPL_API void addActor(const vtkSmartPointer<vtkProp>& actor);
	IMGUI_IMPL_API void addActors(const vtkSmartPointer<vtkPropCollection>& actors);
	IMGUI_IMPL_API void removeActor(const vtkSmartPointer<vtkProp>& actor);
	void setViewportSize(const ImVec2 newSize);
public:
	static inline int NoScrollFlags(){
		return ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoScrollWithMouse;
	}
public:
	inline void setRenderWindow(const vtkSmartPointer<vtkGenericOpenGLRenderWindow>& renderWindow) {
		this->renderWindow = renderWindow;
	}

	inline void setInteractor(const vtkSmartPointer<vtkGenericRenderWindowInteractor>& interactor) {
		this->interactor = interactor;
	}

	inline void setInteractorStyle(const vtkSmartPointer<vtkInteractorStyleTrackballCamera>& interactorStyle) {
		this->interactorStyle = interactorStyle;
	}

	inline void setRenderer(const vtkSmartPointer<vtkRenderer>& renderer) {
		this->renderer = renderer;
	}
public:
	inline vtkSmartPointer<vtkGenericOpenGLRenderWindow>& getRenderWindow() {
		return renderWindow;
	}

	inline vtkSmartPointer<vtkGenericRenderWindowInteractor>& getInteractor() {
		return interactor;
	}

	inline vtkSmartPointer<vtkInteractorStyleTrackballCamera>& getInteractorStyle() {
		return interactorStyle;
	}

	inline vtkSmartPointer<vtkRenderer>& getRenderer() {
		return renderer;
	}
public:

	inline unsigned int getViewportWidth() const {
		return viewportWidth;
	}

	inline unsigned int getViewportHeight() const {
		return viewportHeight;
	}

	inline unsigned int getTexture() const {
		return tex;
	}
};
