# -*- coding: utf-8 -*-
"""
This example demonstrates the use of pyqtgraph's parametertree system. This provides
a simple way to generate user interfaces that control sets of parameters. The example
demonstrates a variety of different parameter types (int, float, list, etc.)
as well as some customized parameter types

"""

from pyqtgraph.Qt import QtCore, QtGui
from pyqtgraph.parametertree import Parameter, ParameterTree
import Qt_TimeData
import Qt_FFTMag
import Qt_FFTChMag
import Qt_PowerSpectrum
import Qt_PowerSpectrum2D
import Qt_ObjAPS
import Qt_ObjGhost



app = QtGui.QApplication([])

class ParamTree:
    def __init__(self):

        self.qtUiDic = {}
        self.checkBoxState = {}
        self.pTree = self.initSetting()

        for topLayer in self.qtUiDic:
            self.checkBoxState[topLayer] = False

        self.pTree.sigTreeStateChanged.connect(self.change)
        self.ScanData = [None] * 1

        # Create ParameterTree widget
        t = ParameterTree()
        t.setParameters(self.pTree, showTop=False)
        t.setWindowTitle('Parameter Tree')

        self.win = QtGui.QWidget()
        layout = QtGui.QGridLayout()
        self.win.setLayout(layout)
        layout.addWidget(t)
        self.win.show()
        self.win.resize(500, 800)


    def initSetting(self):

        # Create tree of Parameter objects
        p = Parameter.create(name='params', type='group', children=[])

        # Generation Parameters & function Connection
        #######################################
        GName = 'Time Signal'
        group = p.addChild({'name': GName, 'type': 'group'})

        PName = 'RawData'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_TimeData.TimeData_UI(0, title=PName)

        #######################################
        GName = 'FFT Mag Signal'
        group = p.addChild({'name': GName, 'type': 'group'})

        PName = 'FFT Mag'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_FFTMag.FFTMag_UI(0, title=PName)

        #######################################
        GName = 'FFT Sum Signal'
        group = p.addChild({'name': GName, 'type': 'group'})

        PName = 'Power Spectrum - 2D Contour'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_PowerSpectrum2D.PowSpec2D_UI(0, title=PName)

        PName = 'Power Spectrum - 1D Slice'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_PowerSpectrum.PowSpec_UI(0, title=PName)

        #######################################
        GName = 'Object Information'
        group = p.addChild({'name': GName, 'type': 'group'})

        PName = 'Object Angular PowerSpectrum'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_ObjAPS.ObjAPS_UI(0)

        PName = 'GhostFilter RawData'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})
        key = GName + '.' + PName
        self.qtUiDic[key] = Qt_ObjGhost.ObjGhost_UI(0)

        GName = '3d Visualization'
        group = p.addChild({'name': GName, 'type': 'group'})
        PName = '3d view'
        group.addChild({'name': PName, 'type': 'bool', 'value': False})

        '''
        temp_py = os.system("plot_3d_scatter.py")
        if temp_py is 3:
            print('Display fail.')
            sys.exit()
        '''
        #######################################

        return p



    # If anything changes in the tree, print a message
    def change(self, param, changes):
        print("tree changes:")
        for param, change, data in changes:
            path = self.pTree.childPath(param)
            if path is not None:
                childName = '.'.join(path)
            else:
                childName = param.name()
            print('  parameter: %s' % childName)
            print('  change:    %s' % change)
            print('  data:      %s' % str(data))
            print('  ----------')

            if data:
                self.qtUiDic[childName].SetData(self.ScanData)
                self.qtUiDic[childName].Form.show()
            else:
                self.qtUiDic[childName].Form.hide()

            self.checkBoxState[childName] = data



    def SetData(self, Data):
        self.ScanData = Data

        for key, state in self.checkBoxState.items():
            if state:
                self.qtUiDic[key].SetData(Data)




# Start Qt event loop unless running in interactive mode or using pyside.
if __name__ == '__main__':
    import sys

    Test = ParamTree()
    if (sys.flags.interactive != 1) or not hasattr(QtCore, 'PYQT_VERSION'):
        QtGui.QApplication.instance().exec_()

