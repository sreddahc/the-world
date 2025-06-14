import sys
import tkinter as tk

from time import sleep


def editor():
    # Check if running Linux and if so Load X11
    if (sys.platform == "linux") or (sys.platform == "linux2"):
        import ctypes
        ctypes.CDLL('libX11.so').XInitThreads()
    
    # Create the main window
    window = tk.Tk()
    window.title("Hello, World!")

    # Create a label widget
    label = tk.Label(window, text="Hello, World!")
    label.pack()

    # Start the Tkinter event loop
    window.mainloop()