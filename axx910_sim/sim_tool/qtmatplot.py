from PyQt5 import QtCore, QtGui, QtWidgets
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5 import NavigationToolbar2QT as NavigationToolbar
import matplotlib.pyplot as plt


from matplotlib.figure import Figure

class MplCanvas(FigureCanvas):

    def __init__(self):
        self.fig, self.ax = plt.subplots()
        self.ax.format_coord = format_coord
        #self.ax.format_coord = format_coord_ELE



        FigureCanvas.__init__(self, self.fig)
        # FigureCanvas.setSizePolicy(self, QtGui.QSizePolicy.Expanding, QtGui.QSizePolicy.Expanding)
        FigureCanvas.updateGeometry(self)


class MatplotWidget(QtWidgets.QWidget):

    def __init__(self, parent = None):
        QtWidgets.QWidget.__init__(self, parent)
        self.canvas = MplCanvas()
        self.naviToolbar = NavigationToolbar(self.canvas, self)
        #self.vbl = QtGui.QGridLayout()
        self.vbl = QtWidgets.QGridLayout()
        self.vbl.addWidget(self.canvas, 0, 0, 1, 1)
        self.vbl.addWidget(self.naviToolbar)
        self.setLayout(self.vbl)



def format_coord(x, y):
    if (x > 0) and (y > 0):
        col = int(x + 0.5)
        row = int(y + 0.5)
    elif (x > 0) and (y < 0):
        col = int(x + 0.5)
        row = int(y - 0.5)
    elif (x < 0) and (y > 0):
        col = int(x - 0.5)
        row = int(y + 0.5)
    elif (x < 0) and (y < 0):
        col = int(x - 0.5)
        row = int(y - 0.5)

    #col = int(x)
    #row = int(y)

    # return 'x=%1d, y=%1d' % (col, row)
    return 'Y=%1d, X=%1d' % (row, col)

def format_coord_ELE(x, y):
    col = int(x + 0.5)
    row = int(y + 0.5)
    return 'Ele=%1d, Azi=%1d' % (row, col)
