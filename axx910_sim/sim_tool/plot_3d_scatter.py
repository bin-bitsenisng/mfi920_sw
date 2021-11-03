from pyqtgraph.Qt import QtCore, QtGui
import pyqtgraph as pg

import pyqtgraph.opengl as gl
import numpy as np
import OpenGL.GL as ogl
from pyqtgraph.Transform3D import Transform3D



class CanIter(object):

    def __init__(self):
        self.a = 0

    def __iter__(self):
        'Returns itself as an iterator object'
        return self

    def __next__(self):
        self.data = data


class CustomTextItem(gl.GLGraphicsItem.GLGraphicsItem):
    def __init__(self, X, Y, Z, text):
        gl.GLGraphicsItem.GLGraphicsItem.__init__(self)
        self.text = text
        self.X = X
        self.Y = Y
        self.Z = Z

    def setGLViewWidget(self, GLViewWidget):
        self.GLViewWidget = GLViewWidget

    def setText(self, text):
        self.text = text
        self.update()

    def setX(self, X):
        self.X = X
        self.update()

    def setY(self, Y):
        self.Y = Y
        self.update()

    def setZ(self, Z):
        self.Z = Z
        self.update()

    def paint(self):
        self.GLViewWidget.qglColor(QtCore.Qt.gray)
        self.GLViewWidget.renderText(self.X, self.Y, self.Z, self.text)

class Custom3DAxis(gl.GLAxisItem):
    """Class defined to extend 'gl.GLAxisItem'."""
    def __init__(self, parent, color=(0,0,0,.6)):
        gl.GLAxisItem.__init__(self)
        self.parent = parent
        self.c = color

    def add_labels(self):
        """Adds axes labels."""
        x,y,z = self.size()
        #X label
        self.xLabel = CustomTextItem(X=x/2, Y=-y/20, Z=-z/20, text="X")
        self.xLabel.setGLViewWidget(self.parent)
        self.parent.addItem(self.xLabel)
        #Y label
        self.yLabel = CustomTextItem(X=-x/20, Y=y/2, Z=-z/20, text="Y")
        self.yLabel.setGLViewWidget(self.parent)
        self.parent.addItem(self.yLabel)
        #Z label
        self.zLabel = CustomTextItem(X=-x/20, Y=-y/20, Z=z/2, text="Z")
        self.zLabel.setGLViewWidget(self.parent)
        self.parent.addItem(self.zLabel)

    def add_tick_values(self, xticks=[], yticks=[], zticks=[]):
        """Adds ticks values."""
        x,y,z = self.size()
        xtpos = np.linspace(0, x, len(xticks))
        ytpos = np.linspace(0, y, len(yticks))
        ztpos = np.linspace(0, z, len(zticks))
        #X label
        for i, xt in enumerate(xticks):
            val = CustomTextItem(X=xtpos[i], Y=-y/20, Z=-z/20, text=str(xt))
            val.setGLViewWidget(self.parent)
            self.parent.addItem(val)
        #Y label
        for i, yt in enumerate(yticks):
            val = CustomTextItem(X=-x/20, Y=ytpos[i], Z=-z/20, text=str(yt))
            val.setGLViewWidget(self.parent)
            self.parent.addItem(val)
        #Z label
        for i, zt in enumerate(zticks):
            val = CustomTextItem(X=-x/20, Y=-y/20, Z=ztpos[i], text=str(zt))
            val.setGLViewWidget(self.parent)
            self.parent.addItem(val)

    def paint(self):
        self.setupGLState()
        if self.antialias:
            ogl.glEnable(ogl.GL_LINE_SMOOTH)
            ogl.glHint(ogl.GL_LINE_SMOOTH_HINT, ogl.GL_NICEST)
        ogl.glBegin(ogl.GL_LINES)

        x,y,z = self.size()
        #Draw Z
        ogl.glColor4f(self.c[0], self.c[1], self.c[2], self.c[3])
        ogl.glVertex3f(0, 0, 0)
        ogl.glVertex3f(0, 0, z)
        #Draw Y
        ogl.glColor4f(self.c[0], self.c[1], self.c[2], self.c[3])
        ogl.glVertex3f(0, 0, 0)
        ogl.glVertex3f(0, y, 0)
        #Draw X
        ogl.glColor4f(self.c[0], self.c[1], self.c[2], self.c[3])
        ogl.glVertex3f(0, 0, 0)
        ogl.glVertex3f(x, 0, 0)
        ogl.glEnd()





app = QtGui.QApplication([])
w = gl.GLViewWidget()

w.showMaximized()

background_color = app.palette().color(QtGui.QPalette.Background,)
#w.setBackgroundColor(background_color)

w.opts['distance'] = 20
w.setWindowTitle('pyqtgraph example: GLLinePlotItem')
w.show()
g = gl.GLGridItem()
g.setSize(x=20, y=10, z=10)
tr = Transform3D(1, 0, 0, +10,
                 0, 1, 0, 0,
                 0, 0, 1, 0,
                 0, 0, 0, 1)
g.setTransform(tr)

axis = Custom3DAxis(w, color=(255, 255, 255, 1))
axis.setSize(x=1, y=2, z=0)
axis.add_tick_values(xticks=[0, 1], yticks=[0, 1, 2])
w.addItem(axis)

# x축의 사이즈가 g.setsize와 다른듯

#axis.setSize(x=20, y=10, z=10)

set_space = 1
g.setSpacing(x=set_space, y=set_space, z=set_space)
w.addItem(g)

#pos1 = [0, 0, 0]
pos2 = [1.0, 1.0, 0.0]
'''
pos3 = [2.0, 2.0, 0.0]
pos4 = [3.0, 3.0, 0.0]
pos5 = [4.0, 4.0, 0.0]
pos_temp = np.vstack([pos1, pos2])
pos_temp = np.vstack([pos_temp, pos3])
pos_temp = np.vstack([pos_temp, pos4])
pos_temp = np.vstack([pos_temp, pos5])
pos_temp = pos_temp * set_space
'''
pos = pos2
sp2 = gl.GLScatterPlotItem(pos=pos)
w.addItem(sp2)


#generate a color opacity gradient

'''
color = np.zeros((pos.shape[0],4), dtype=np.float32)
color[:, 0] = 1
color[:, 1] = 0
color[:, 2] = 0.5
color[0:100, 3] = np.arange(0, 100)/100.

def update():
    ## update volume colors
    global color
    color = np.roll(color,1, axis=0)
    sp2.setData(color=color)
'''


t = QtCore.QTimer()
#t.timeout.connect(update)
t.start(50)


## Start Qt event loop unless running in interactive mode.
if __name__ == '__main__':
    import sys
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()
