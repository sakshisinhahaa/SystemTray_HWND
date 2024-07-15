#System Tray Application
This project demonstrates how to create a Windows System Tray application using C++ and HWND. The application includes a system tray icon, a right-click context menu, and functionality to show and hide a window.
This also opens a HWND window with menus and submenu when clicked. 

## Features

###System Tray Icon
- Adds an icon to the Windows system tray.
- Provides tooltip text for the system tray icon.
- Loads an icon from a file and displays it in the system tray.

###Tray Icon Interactions

- **Left-Click Action**: Shows the application window which contains menu and submenus and brings it to the foreground.
- **Right-Click Action**: Displays a context menu with options such as help(displays a message box with help information) and quit(Exits the application).

### Window Management
- Shows the main application window when the tray icon is left-clicked.
- Hides the main application window instead of closing it, keeping the application running in the system tray.
- Gracefully exits the application and removes the tray icon when the `Quit` option is selected from the context menu.

This project was created to demonstrate the basics of creating a Windows System Tray application using C++ and the Windows API.

