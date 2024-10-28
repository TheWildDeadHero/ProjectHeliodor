from tkinter import *
from tkinter.messagebox import *
from tkinter.colorchooser import askcolor
from tkinter.filedialog import LoadFileDialog, SaveFileDialog, SaveAs
from tkinter import ttk
#from ImageOps import *
from enum import StrEnum



class _PaintToolState(StrEnum):
    NONE            = "NONE"
    PEN             = "PEN"
    BRUSH           = "BRUSH"
    ERASER          = "ERASER"
    LINE            = "LINE"
    RECTANGLE       = "RECTANGLE"
    CIRCLE          = "CIRCLE"
    TRIANGLE        = "TRIANGLE"
    STAR            = "STAR"
    PIXEL_SEL       = "PIXEL SELECT"
    AREA_SEL        = "AREA SELECT"
    PAINT_BUCKET    = "PAINT BUCKET"
    REPLACE         = "COLOR REPLACE"

class _PaintFrame(Frame):

    _DEFAULT_BRUSH_SIZE     = 1.0
    _DEFAULT_LEFT_COLOR     = 'black'
    _DEFAULT_RIGHT_COLOR    = 'red'

    def __init__(self, master):

        super().__init__(master)

        self._master                        = master

        # GUI
        self._toolbar_frame                 = Frame(self._master)
        self._animation_frame               = Frame(self._master)
        self._layer_frame                   = Frame(self._master)
        self._canvas_main_frame             = Frame(self._master)

        self._canvas_frames                 = []

        self._toolbar_pane                  = PanedWindow(self._master, orient = VERTICAL)
        self._animation_pane                = PanedWindow(self._master, orient = VERTICAL)
        self._layer_pane                    = PanedWindow(self._master, orient = HORIZONTAL)

        self._paint_toolbar                 = LabelFrame(self._master, text = "Tools")
        self._layer_toolbar                 = LabelFrame(self._master, text = "Layers")
        self._animation_toolbar             = LabelFrame(self._master, text = "Animation")

        self._canvas_notebook               = ttk.Notebook(self._master)

        self._toolbar_buttons               = \
        {
            _PaintToolState.PEN:            Button(self._master, text = "Pen",              command = self._draw_pen),
            _PaintToolState.BRUSH:          Button(self._master, text = "Brush",            command = self._draw_brush),
            _PaintToolState.ERASER:         Button(self._master, text = "Eraser",           command = self._erase),
            _PaintToolState.LINE:           Button(self._master, text = "Line",             command = self._draw_line),
            _PaintToolState.RECTANGLE:      Button(self._master, text = "Rectangle",        command = self._draw_rectangle),
            _PaintToolState.CIRCLE:         Button(self._master, text = "Circle",           command = self._draw_circle),
            _PaintToolState.TRIANGLE:       Button(self._master, text = "Triangle",         command = self._draw_triangle),
            _PaintToolState.STAR:           Button(self._master, text = "Star",             command = self._draw_star),
            _PaintToolState.PIXEL_SEL:      Button(self._master, text = "Select",           command = self._select_pixels),
            _PaintToolState.AREA_SEL:       Button(self._master, text = "Mask",             command = self._select_area),
            _PaintToolState.PAINT_BUCKET:   Button(self._master, text = "Paint Bucket",     command = self._flood),
            _PaintToolState.REPLACE:        Button(self._master, text = "Replace Color",    command = self._replace_color)
        }

        self._save_button                   = Button(self._master, text = "Save",       command = self._save_func)
        self._open_button                   = Button(self._master, text = "Load",       command = self._open_func)

        self._left_color_picker_button      = Button(self._master, text = "Left Color Picker",  command = self._pick_left_color)
        self._right_color_picker_button     = Button(self._master, text = "Right Color Picker", command = self._pick_right_color)

        self._brush_size_slider             = Scale(self._master, from_ = 1, to = 128, orient = HORIZONTAL, label = "Brush Size")
        self._zoom_slider                   = Scale(self._master, from_ = 100, to = 800, orient = HORIZONTAL, label = "Zoom", tickinterval = 100)

        # Menu Bar
        self._menu                          = Menu(self._master)

        self._file_submenu                  = Menu(self._menu, tearoff = 0)
        self._edit_submenu                  = Menu(self._menu, tearoff = 0)
        self._select_submenu                = Menu(self._menu, tearoff = 0)
        self._view_submenu                  = Menu(self._menu, tearoff = 0)
        self._tools_submenu                 = Menu(self._menu, tearoff = 0)
        self._window_submenu                = Menu(self._menu, tearoff = 0)
        self._help_submenu                  = Menu(self._menu, tearoff = 0)

        # Canvas

        self._canvases                      = []
        self._canvas                        = None
        self._image                         = None

        # Dialogs

        #self._save                          = SaveFileDialog(self)
        #self._open                          = LoadFileDialog(self)

        # App state

        self._history                       = [[]]

        self._filename                      = []
        self._path                          = []

        self._x: int                        = None
        self._y: int                        = None
        self._last_drawn_object_id          = None

        self._left_color                    = self._DEFAULT_LEFT_COLOR
        self._right_color                   = self._DEFAULT_RIGHT_COLOR

        self._smooth                        = False

        self._tool_state: _PaintToolState   = _PaintToolState.NONE

        self._setup_menu_bar()
        self._setup_gui()
        self._setup_canvas(64, 64)

    def _setup_menu_bar(self) -> None:
        self._menu.add_cascade(label = "File",   menu = self._file_submenu) 
        self._menu.add_cascade(label = "Edit",   menu = self._edit_submenu)
        self._menu.add_cascade(label = "Select", menu = self._select_submenu)
        self._menu.add_cascade(label = "View",   menu = self._view_submenu)
        self._menu.add_cascade(label = "Tools",  menu = self._tools_submenu)
        self._menu.add_cascade(label = "Window", menu = self._window_submenu)
        self._menu.add_cascade(label = "Help",   menu = self._help_submenu)

        # File
        self._file_submenu.add_command(label = "New File",            command = self._dummy)
        self._file_submenu.add_separator()
        self._file_submenu.add_command(label = "Open...",             command = self._dummy)
        self._file_submenu.add_separator()
        self._file_submenu.add_command(label = "Save",                command = self._save_func)
        self._file_submenu.add_command(label = "Save As...",          command = self._dummy)
        self._file_submenu.add_separator()
        self._file_submenu.add_command(label = "Exit",                command = self.master.destroy)

        # Edit
        self._edit_submenu.add_command(label = "Undo",                command = self._dummy)
        self._edit_submenu.add_command(label = "Redo",                command = self._dummy)
        self._edit_submenu.add_separator()
        self._edit_submenu.add_command(label = "Cut",                 command = self._dummy)
        self._edit_submenu.add_command(label = "Copy",                command = self._dummy)
        self._edit_submenu.add_command(label = "Paste",               command = self._dummy)
        self._edit_submenu.add_command(label = "Delete",              command = self._dummy)
        self._edit_submenu.add_separator()
        self._edit_submenu.add_command(label = "Resize...",           command = self._dummy)
        self._edit_submenu.add_command(label = "Resize Canvas...",    command = self._dummy)

        # Select
        self._select_submenu.add_command(label = "Select All Pixels", command = self._dummy)
        self._select_submenu.add_command(label = "Select Pixels",     command = self._dummy)
        self._select_submenu.add_separator()
        self._select_submenu.add_command(label = "Select Area",       command = self._dummy)

        # View
        self._view_submenu.add_command(label = "Zoom In",             command = self._dummy)
        self._view_submenu.add_command(label = "Zoom Out",            command = self._dummy)
        self._view_submenu.add_command(label = "Zoom...",             command = self._dummy)

        # Tools
        self._tools_submenu.add_command(label = "Pen",                command = self._draw_pen)
        self._tools_submenu.add_command(label = "Brush",              command = self._draw_brush)
        self._tools_submenu.add_command(label = "Eraser",             command = self._erase)
        self._tools_submenu.add_command(label = "Paint Bucket",       command = self._flood)
        self._tools_submenu.add_separator()
        self._tools_submenu.add_command(label = "Line",               command = self._draw_line)
        self._tools_submenu.add_command(label = "Circle",             command = self._draw_circle)
        self._tools_submenu.add_command(label = "Rectangle",          command = self._draw_rectangle)
        self._tools_submenu.add_command(label = "Triangle",           command = self._draw_triangle)
        self._tools_submenu.add_command(label = "Star",               command = self._draw_star)
        self._tools_submenu.add_separator()
        self._tools_submenu.add_command(label = "Color...",           command = self._pick_left_color)

        # Window
        self._window_submenu.add_command(label = "Maximize",          command = self._dummy)
        self._window_submenu.add_command(label = "Minimize",          command = self._dummy)

        # Help
        self._help_submenu.add_command(label = "About...",            command = self._show_about)

        self.master.configure(menu = self._menu)

    def _setup_gui(self) -> None:
        self._toolbar_buttons[_PaintToolState.PEN].grid(row = 0, column = 0)
        self._toolbar_buttons[_PaintToolState.BRUSH].grid(row = 0, column = 1)
        self._toolbar_buttons[_PaintToolState.LINE].grid(row = 0, column = 2)
        self._toolbar_buttons[_PaintToolState.CIRCLE].grid(row = 0, column = 3)
        self._toolbar_buttons[_PaintToolState.RECTANGLE].grid(row = 0, column = 4)
        self._toolbar_buttons[_PaintToolState.ERASER].grid(row = 0, column = 5)

        self._left_color_picker_button.grid(row = 1, column = 0)
        self._right_color_picker_button.grid(row = 1, column = 1)

        self._brush_size_slider.grid(row = 3, column = 0)

    def _setup_canvas(self, width: int, height: int, bg: str = 'white') -> None:
        #self._canvases.append(Canvas(self, borderwidth = 2, bg = bg, height = height, width = width))

        self._canvas = Canvas(self._master, borderwidth = 2, bg = bg, height = height, width = width)
        self._canvas.grid(row = 2, column = 0)

    def _destroy_canvas(self, which: int) -> None:
        #self._canvases[which].destroy
        None

    def _setup_draw(self, smooth: bool = False) -> None:
        self._reset_draw(None, True)

        self._smooth = smooth

        self._canvas.bind('<B1-Motion>', self._left_draw)
        self._canvas.bind('<B2-Motion>', self._right_draw)

        self._canvas.bind('<ButtonRelease-1>', self._reset_draw)
        self._canvas.bind('<ButtonRelease-2>', self._reset_draw)

    def _reset_draw(self, event, unbind: bool = False):

        if unbind:
            self._canvas.unbind('<Button-1>')
            self._canvas.unbind('<Button-2>')

            self._canvas.unbind('<B1-Motion>')
            self._canvas.unbind('<B2-Motion>')

            self._canvas.unbind('<ButtonRelease-1>')
            self._canvas.unbind('<ButtonRelease-2>')

        self._x, self._y = None, None

        self._last_drawn_object_id = None

    def _on_tool_select(self, tool_state: _PaintToolState) -> None:

        for name, button in self._toolbar_buttons.items():

            if name == tool_state:
                button.config(relief=SUNKEN)
            else:
                button.config(relief=RAISED)

        if tool_state != _PaintToolState.NONE:
            self._tool_state = tool_state

    def _save_func(self) -> None:
        #self._save.go()
        with open("Test.ps", 'w+') as file:
            file.write(self._canvas.postscript())
            file.flush()
        ...

    def _save_as_func(self) -> None:
        #self._save.go()
        ...

    def _open_func(self) -> None:
        #self._open.go()
        ...

    def _set_canvas_size(self, width: int, height: int) -> None:
        self._canvas.config(width = width, height = height)

    def _show_about(self) -> None:
        showinfo("About", "Copyright 2024 William Smith")

    def _pick_left_color(self) -> None:
        self._left_color = askcolor(color = self._left_color)[1]

    def _pick_right_color(self) -> None:
        self._right_color = askcolor(color = self._right_color)[1]

    def _draw_pen(self) -> None:
        self._on_tool_select(_PaintToolState.PEN)
        self._setup_draw()

    def _draw_brush(self) -> None:
        self._on_tool_select(_PaintToolState.BRUSH)
        self._setup_draw(True)

    def _erase(self) -> None:
        self._on_tool_select(_PaintToolState.ERASER)
        self._setup_draw()

    def _draw_line(self) -> None:
        self._on_tool_select(_PaintToolState.LINE)
        self._setup_draw()

    def _draw_rectangle(self) -> None:
        self._on_tool_select(_PaintToolState.RECTANGLE)
        self._setup_draw()

    def _draw_circle(self) -> None:
        self._on_tool_select(_PaintToolState.CIRCLE)
        self._setup_draw()

    def _draw_triangle(self) -> None:
        self._on_tool_select(_PaintToolState.TRIANGLE)
        self._setup_draw()

    def _draw_star(self) -> None:
        self._on_tool_select(_PaintToolState.STAR)
        self._setup_draw()

    def _flood(self) -> None:
        self._on_tool_select(_PaintToolState.PAINT_BUCKET)

    def _replace_color(self) -> None:
        self._on_tool_select(_PaintToolState.REPLACE)

    def _select_pixels(self) -> None:
        self._on_tool_select(_PaintToolState.PIXEL_SEL)

    def _select_area(self) -> None:
        self._on_tool_select(_PaintToolState.AREA_SEL)

    def _left_draw(self, event) -> None:
        self._draw(event, self._left_color)

    def _right_draw(self, event) -> None:
        self._draw(event, self._right_color)

    def _draw(self, event, color: str) -> None:

        width = self._brush_size_slider.get()
        
        if self._tool_state == _PaintToolState.ERASER:
            color = 'white'
        
        if self._tool_state in (_PaintToolState.BRUSH, _PaintToolState.PEN, _PaintToolState.ERASER):

            if self._x and self._y:
                self._canvas.create_line(self._x, self._y,
                                         event.x, event.y,
                                         width = width,
                                         fill = color,
                                         smooth = self._smooth,
                                         capstyle = ROUND,
                                         splinesteps = 128)

            self._x = event.x
            self._y = event.y
        
        else:

            if not self._x and not self._y:
                self._x = event.x
                self._y = event.y

            if self._last_drawn_object_id is not None:
                self._canvas.delete(self._last_drawn_object_id)

            if self._tool_state == _PaintToolState.LINE:
                self._last_drawn_object_id = self._canvas.create_line(self._x, self._y,
                                                                      event.x, event.y,
                                                                      width = width,
                                                                      fill = color,
                                                                      smooth = self._smooth,
                                                                      capstyle = ROUND,
                                                                      splinesteps = 128)

            elif self._tool_state == _PaintToolState.CIRCLE:
                self._last_drawn_object_id = self._canvas.create_oval(self._x, self._y,
                                                                      event.x, event.y,
                                                                      width = width,
                                                                      outline = self._left_color,
                                                                      fill = self._right_color)
            
            elif self._tool_state == _PaintToolState.RECTANGLE:
                self._last_drawn_object_id = self._canvas.create_rectangle(self._x, self._y,
                                                                           event.x, event.y,
                                                                           width = width,
                                                                           outline = self._left_color,
                                                                           fill = self._right_color)
    
    def _dummy(self, dummy1: None, dummy2: None, dummy3: None, dummy4: None, dummy5: None, dummy6: None, dummy7: None) -> None:
        pass

if __name__ == '__main__':
    from sys import platform

    if platform in ("win32", "cygwin"):
        style = ttk.Style()
        style.theme_use('classic')

    root = Tk()
    root.title("PyPaint")

    paint_app = _PaintFrame(root)
    paint_app.mainloop()
