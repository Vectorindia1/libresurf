// engine/cef/cef_app.cpp

#include "cef_app.h"

#include "include/cef_command_line.h"
#include "include/wrapper/cef_helpers.h"

namespace libresurf {

LibreSurfApp::LibreSurfApp() = default;

void LibreSurfApp::OnContextInitialized() {
    CEF_REQUIRE_UI_THREAD();
    // Browser window creation happens here after CEF is ready.
    // The MainWindow will be created by the platform-specific entry point.
}

void LibreSurfApp::OnBeforeCommandLineProcessing(const CefString& process_type,
                                                  CefRefPtr<CefCommandLine> command_line) {
    // Disable features that could leak information or reduce security.
    command_line->AppendSwitch("disable-background-networking");
    command_line->AppendSwitch("disable-client-side-phishing-detection");
    command_line->AppendSwitch("disable-default-apps");
    command_line->AppendSwitch("disable-extensions");  // until extension system is ready
    command_line->AppendSwitch("disable-sync");
    command_line->AppendSwitch("no-first-run");
    command_line->AppendSwitch("no-default-browser-check");
    command_line->AppendSwitch("disable-translate");
    command_line->AppendSwitch("disable-features=AutofillServerCommunication");

    // Enable hardware acceleration (can be disabled by user preference)
    // command_line->AppendSwitch("disable-gpu");  // uncomment for software rendering
}

}  // namespace libresurf
