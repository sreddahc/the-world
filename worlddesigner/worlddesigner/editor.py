import wx

from dataclasses import dataclass, field
from typing import Any, Dict, List, Optional


STATIC_WINDOW_STYLE: int = wx.MINIMIZE_BOX|wx.SYSTEM_MENU|wx.CAPTION|wx.CLOSE_BOX|wx.CLIP_CHILDREN


@dataclass
class Grid():
    """
    Create a grid
    """
    grid: Optional[List[List[Any]]] = None

    def __init__(self, grid: Optional[List[List[Any]]] = None):
        try:
            if grid is not None:
                self.grid = grid

                if not isinstance(self.grid, List):
                    self.grid = None
                    raise ValueError(f"VALUE ERROR: Bad value {grid}. Expected type is: List[List[Any]]")

                if len(self.grid) == 0:
                    self.grid = None
                    raise ValueError(f"VALUE ERROR: Bad value {grid}. Expected type is: List[List[Any]]")
                
                if not isinstance(self.grid[0], List):
                    self.grid = None
                    raise ValueError(f"VALUE ERROR: Bad value {grid}. Expected type is: List[List[Any]]")
        
        except Exception as e:
            print(e)

    def generate_empty(width: Optional[int] = None, height: Optional[int] = None):
        """
        Generate an empty Grid.
        """
        grid: Optional[List[List[Any]]] = None

        try:
            if width is None or height is None:
                raise ValueError("Missing width or height")
            
            grid = []
            for row in range(height):
                grid.append([])
                for column in range(width):
                    grid[row].append(None)

        except Exception as e:
            print(e)

        return Grid(grid)

    def height(self) -> int:
        """
        Returns the height of the Grid object.
        """
        if self.grid is None:
            return 0
        
        return len(self.grid)

    def width(self) -> int:
        """
        Returns the width of the Grid object.
        """
        if self.grid is None:
            return 0
        
        return len(self.grid[0])

    def to_list(self) -> List[List[Any]]:
        """
        Converts the Grid object into a list object.
        """
        if self.grid == None:
            return [[]]

        return self.grid
    
    def set_value(self, row: int, column: int, value: Any):
        """
        Sets the value of an entry in the Grid to value.
        """

        try:
            if not isinstance(row, int):
                raise ValueError(f"VALUE ERROR: row value type {type(row)} is not of expected type int")
            if not isinstance(column, int):
                raise ValueError(f"VALUE ERROR: column value type {type(column)} is not of expected type int")
            if row < 0:
                raise IndexError(f"INDEX ERROR: Cannot have a negative row value")
            if column < 0:
                raise IndexError(f"INDEX ERROR: Cannot have a negative column value")
            if row >= self.height():
                raise IndexError(f"INDEX ERROR: Cannot have a row value greater than the height of the Grid")
            if column >= self.width():
                raise IndexError(f"INDEX ERROR: Cannot have a column value greater than the width of the Grid")
            self.grid[row][column] = value
        except Exception as e:
            print(e)

    def get_value(self, row: int, column: int) -> Any:
        """
        Gets the  value of a Grid object at a given set of row, column coordinates.
        """
        try:
            if not isinstance(row, int):
                raise ValueError(f"VALUE ERROR: row value type {type(row)} is not of expected type int")
            if not isinstance(column, int):
                raise ValueError(f"VALUE ERROR: column value type {type(column)} is not of expected type int")
            if row < 0:
                raise IndexError(f"INDEX ERROR: Cannot have a negative row value")
            if column < 0:
                raise IndexError(f"INDEX ERROR: Cannot have a negative column value")
            if row >= self.height():
                raise IndexError(f"INDEX ERROR: Cannot have a row value greater than the height of the Grid")
            if column >= self.width():
                raise IndexError(f"INDEX ERROR: Cannot have a column value greater than the width of the Grid")
            if self.grid is None:
                return []
            return self.grid[row][column]
        except Exception as e:
            print(e)
        return None


@dataclass
class GameEditor(wx.Frame):
    """
    Game Editor screen.
    """
    grid_width: int = 35
    grid_height: int = 20
    cell_width: int = 35
    cell_height: int = 35
    layer_data: Dict[int, Grid] = field(default_factory=lambda: {})
    layer_sizer: Dict[int, wx.GridBagSizer] = field(default_factory=lambda: {})

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
        label_grid_width = wx.StaticText(self, label="Grid Width:")
        text_grid_width = wx.TextCtrl(self, value=str(self.grid_width))
        label_grid_height = wx.StaticText(self, label="Grid Height:")
        text_cell_height = wx.TextCtrl(self, value=str(self.grid_height))
        label_cell_width = wx.StaticText(self, label="Cell Width (px):")
        text_cell_width = wx.TextCtrl(self, value=str(self.grid_width))
        label_cell_height = wx.StaticText(self, label="Cell Height (px):")
        text_grid_height = wx.TextCtrl(self, value=str(self.grid_height))
        label_layer = wx.StaticText(self, label="Layer:")
        text_layer = wx.TextCtrl(self, value='1')

        # Layout
        metadata_sizer: wx.BoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_grid_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(text_grid_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_grid_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(text_grid_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_cell_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(text_cell_width, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_cell_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(text_cell_height, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(label_layer, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        metadata_sizer.Add(text_layer, 0, wx.LEFT | wx.ALIGN_CENTRE_VERTICAL, 0, 0)
        metadata_sizer.AddSpacer(10)
        
        # Add grid
        self.generate_grid(1)
        grid_sizer: wx.BoxSizer = wx.BoxSizer(orient=wx.HORIZONTAL)
        grid_sizer.AddSpacer(10)
        grid_sizer.Add(self.layer_sizer[1])
        grid_sizer.AddSpacer(10)
        

        frame_sizer: wx.BoxSizer = wx.BoxSizer(orient=wx.VERTICAL)
        frame_sizer.AddSpacer(10)
        frame_sizer.Add(metadata_sizer, 0, 0, 0, 10)
        frame_sizer.AddSpacer(10)
        frame_sizer.Add(grid_sizer, 0, 0, 0, 10)
        frame_sizer.AddSpacer(10)

        self.SetSizer(frame_sizer)
        self.Sizer.Fit(self)
        self.Layout()

        # Show frame
        self.Show(True)

    def on_exit(self, e):
        self.Close()

    def generate_grid(self, layer: int):
        """
        Generates a grid that can be edited on a layer
        """

        if not hasattr(self, "layer_data"):
            self.layer_data = {}

        if not hasattr(self, "layer_sizer"):
            self.layer_sizer = {}

        self.layer_data[layer] = Grid.generate_empty(self.grid_width, self.grid_height)
        self.layer_sizer[layer] = wx.GridSizer(cols=self.grid_width, gap = wx.Size(2,2))

        for row in range(self.layer_data[layer].height()):
            for column in range(self.layer_data[layer].width()):
                if self.layer_data[layer].get_value(row, column) is None:
                    temp_panel: wx.Panel = wx.Panel(self, size=wx.Size(50, 50))
                    temp_panel.SetBackgroundColour("White")
                    self.layer_sizer[layer].Add(temp_panel)


def editor():
    app = wx.App(False)
    frame = GameEditor(None, "World Designer")
    app.MainLoop()
