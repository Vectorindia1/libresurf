// platform/linux/main_linux.cpp
// Linux application entry point for LibreSurf.
//
// Initializes GTK and CEF, runs the CEF message loop, and creates the main browser window.

#include <gtk/gtk.h>
#include <iostream>

#include "include/cef_app.h"
#include "include/cef_command_line.h"
#include "engine/cef/cef_app.h"
#include "engine/cef/cef_client.h"

int main(int argc, char* argv[]) {
    // 1. Initialize CEF command line.
    CefMainArgs main_args(argc, argv);
    CefRefPtr<CefCommandLine> command_line = CefCommandLine::CreateCommandLine();
    command_line->InitFromArgv(argc, argv);

    // 2. Create the LibreSurf CEF Application.
    CefRefPtr<libresurf::LibreSurfApp> app(new libresurf::LibreSurfApp);

    // 3. Execute the secondary process, if any.
    // CEF launches multiple processes. If this is a child process (e.g. renderer),
    // ExecuteProcess will run it and return the exit code. If this is the main process,
    // it returns -1 and we continue.
    int exit_code = CefExecuteProcess(main_args, app, nullptr);
    if (exit_code >= 0) {
        return exit_code;
    }

    // 4. Initialize GTK. (Required for Linux GUI).
    gtk_init(&argc, &argv);

    // 5. Initialize CEF in the main browser process.
    CefSettings settings;
    settings.no_sandbox = true; // TODO: configure the sandbox for production
    settings.command_line_args_disabled = true;

    if (!CefInitialize(main_args, settings, app.get(), nullptr)) {
        std::cerr << "Failed to initialize CEF!" << std::endl;
        return 1;
    }

    // 6. Create the main GTK window.
    GtkWidget* window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "LibreSurf");
    gtk_window_set_default_size(GTK_WINDOW(window), 1200, 800);
    g_signal_connect(window, "destroy", G_CALLBACK(+[](GtkWidget*, gpointer) {
        CefQuitMessageLoop();
    }), nullptr);

    // 7. Create the browser within the window.
    // In a full implementation, we embed the CEF view inside a GTK container.
    // For now, we create a basic browser window using CEF's default window info.
    CefWindowInfo window_info;
    window_info.SetAsChild(gtk_widget_get_window(window), {0, 0, 1200, 800});
    
    CefBrowserSettings browser_settings;
    CefRefPtr<libresurf::LibreSurfClient> client(new libresurf::LibreSurfClient());
    
    // Initial page load (New Tab Page logic would normally go here).
    CefBrowserHost::CreateBrowser(window_info, client, "https://example.com", 
                                  browser_settings, nullptr, nullptr);

    gtk_widget_show_all(window);

    // 8. Run the CEF message loop.
    CefRunMessageLoop();

    // 9. Shutdown CEF.
    CefShutdown();
    
    return 0;
}
