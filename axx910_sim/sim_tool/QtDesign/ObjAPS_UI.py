# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ObjAPS.ui'
#
# Created by: PyQt5 UI code generator 5.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")
        Form.resize(734, 600)
        self.gridLayout = QtWidgets.QGridLayout(Form)
        self.gridLayout.setObjectName("gridLayout")
        self.widget = QtWidgets.QWidget(Form)
        self.widget.setObjectName("widget")

        self.gridLayout_4 = QtWidgets.QGridLayout(self.widget)
        self.gridLayout_4.setObjectName("gridLayout_4")

        self.gridLayout_3 = QtWidgets.QGridLayout()
        self.gridLayout_3.setObjectName("gridLayout_3")

        self.pushButton_LRR = QtWidgets.QPushButton(self.widget)
        self.pushButton_LRR.setObjectName("pushButton_LRR")
        self.gridLayout_3.addWidget(self.pushButton_LRR, 2, 1)
        #self.gridLayout_3.addWidget(self.pushButton_LRR, 2, 1, 1, 1)


        self.pushButton_MRR = QtWidgets.QPushButton(self.widget)
        self.pushButton_MRR.setObjectName("pushButton_MRR")
        self.gridLayout_3.addWidget(self.pushButton_MRR, 2, 2)
        #self.gridLayout_3.addWidget(self.pushButton_MRR, 2, 3, 1, 1)

        self.pushButton_SRR = QtWidgets.QPushButton(self.widget)
        self.pushButton_SRR.setObjectName("pushButton_SRR")
        self.gridLayout_3.addWidget(self.pushButton_SRR, 2, 3)
        #self.gridLayout_3.addWidget(self.pushButton_SRR, 2, 4, 1, 1)

        #self.graphicsView = PlotWidget(self.widget)
        self.graphicsView = MatplotWidget(self.widget)
        self.graphicsView.setObjectName("graphicsView")
        self.gridLayout_3.addWidget(self.graphicsView, 3, 0, 1, 6)

        self.label_R = QtWidgets.QLabel(self.widget)
        self.label_R.setObjectName("label_R")
        self.gridLayout_3.addWidget(self.label_R, 0, 1, 1, 1)

        self.label_D = QtWidgets.QLabel(self.widget)
        self.label_D.setObjectName("label_D")
        self.gridLayout_3.addWidget(self.label_D, 0, 2, 1, 1)

        self.label = QtWidgets.QLabel(self.widget)
        self.label.setObjectName("label")
        self.gridLayout_3.addWidget(self.label, 0, 3, 1, 1)


        self.lineEdit_R = QtWidgets.QLineEdit(self.widget)
        self.lineEdit_R.setObjectName("lineEdit_R")
        self.gridLayout_3.addWidget(self.lineEdit_R, 1, 1, 1, 1)

        self.lineEdit_D = QtWidgets.QLineEdit(self.widget)
        self.lineEdit_D.setObjectName("lineEdit_D")
        self.gridLayout_3.addWidget(self.lineEdit_D, 1, 2, 1, 1)

        self.lineEdit = QtWidgets.QLineEdit(self.widget)
        self.lineEdit.setObjectName("lineEdit_D")
        self.gridLayout_3.addWidget(self.lineEdit, 1, 3, 1, 1)

        self.gridLayout_4.addLayout(self.gridLayout_3, 1, 0, 1, 1)
        self.gridLayout.addWidget(self.widget, 0, 0, 1, 1)

        self.retranslateUi(Form)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Object Anagulr Power Spectrum"))
        self.pushButton_LRR.setText(_translate("Form", "LRR"))
        self.pushButton_MRR.setText(_translate("Form", "MRR"))
        self.pushButton_SRR.setText(_translate("Form", "SRR"))
        self.label_D.setText(_translate("Form", "Doppler FreqIdx"))
        self.label_R.setText(_translate("Form", "Range FreqIdx"))
        self.label.setText(_translate("Form", "Harmonic idx"))

from pyqtgraph import PlotWidget
from qtmatplot import MatplotWidget