import wx

from dataclasses import dataclass

STATIC_WINDOW_STYLE: int = wx.MINIMIZE_BOX|wx.SYSTEM_MENU|wx.CAPTION|wx.CLOSE_BOX|wx.CLIP_CHILDREN


class GameEditor(wx.Frame):
    """
    Game Editor screen.
    """

    def __init__(self, parent, title):
        wx.Frame.__init__(self, parent, title=title, style=STATIC_WINDOW_STYLE)
        
        # File menu
        file_menu: wx.Menu = wx.Menu()
        menu_item_save: wx.MenuItem = file_menu.Append(wx.ID_SAVE, "&Save", "Saves your level")
        file_menu.AppendSeparator()
        menu_item_exit: wx.MenuItem = file_menu.Append(wx.ID_EXIT, "&Close", "Quit this application")

        # Menu bar
        menu_bar: wx.MenuBar = wx.MenuBar()
        menu_bar.Append(file_menu, "&File")
        self.SetMenuBar(menu_bar)
        
        # Events
        self.Bind(wx.EVT_MENU, self.on_exit, menu_item_exit)

        # Level metadata
        label_width = wx.StaticText(self, label="Width:")
        grid_width = wx.TextCtrl(self, value='35')
        label_height = wx.StaticText(self, label="Height:")
        grid_height = wx.TextCtrl(self, value='35')
        label_layer = wx.StaticText(self, label="Layer:")
        grid_layer = wx.TextCtrl(self, value='1')

        # Layout
        metadata_sizer: wx.BoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(grid_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(grid_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_layer, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(grid_layer, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        
        frame_sizer: wx.BoxSizer = wx.BoxSizer(orient=wx.VERTICAL)
        frame_sizer.AddSpacer(10)
        frame_sizer.Add(metadata_sizer, 0, 0, 0, 10)
        frame_sizer.AddSpacer(10)

        self.SetSizer(frame_sizer)
        self.Sizer.Fit(self)
        self.Layout()

        # Show frame
        self.Show(True)

    def on_exit(self, e):
        self.Close()


def editor():
    app = wx.App(False)
    frame = GameEditor(None, "World Designer")
    app.MainLoop()

    