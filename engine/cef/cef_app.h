// engine/cef/cef_app.h
// LibreSurf CEF application entry point.
//
// Implements CefApp and CefBrowserProcessHandler. This is the first CEF object
// created in the main process. It configures the CEF settings and registers
// scheme handlers.

#pragma once

#include "include/cef_app.h"
#include "include/cef_browser_process_handler.h"

namespace libresurf {

class LibreSurfApp : public CefApp, public CefBrowserProcessHandler {
public:
    LibreSurfApp();

    // CefApp
    CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler() override { return this; }

    // CefBrowserProcessHandler
    void OnContextInitialized() override;
    void OnBeforeCommandLineProcessing(const CefString& process_type,
                                       CefRefPtr<CefCommandLine> command_line) override;

private:
    IMPLEMENT_REFCOUNTING(LibreSurfApp);
};

}  // namespace libresurf
