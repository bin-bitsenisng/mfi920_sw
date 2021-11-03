# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'PowerSpectrum2D.ui'
#
# Created by: PyQt5 UI code generator 5.11.2
#
# WARNING! All changes made in this file will be lost!

from PyQt5 import QtCore, QtGui, QtWidgets

class Ui_Form(object):
    def setupUi(self, Form):
        Form.setObjectName("Form")

        Form.resize(2000, 1200)
        self.gridLayout_2 = QtWidgets.QGridLayout(Form)
        self.gridLayout_2.setObjectName("gridLayout_2")

        self.tabWidget = QtWidgets.QTabWidget(Form)
        self.tabWidget.setObjectName("tabWidget")

        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.gridLayout = QtWidgets.QGridLayout(self.tab)
        self.gridLayout.setObjectName("gridLayout")
        self.graphicsView = MatplotWidget(self.tab)
        self.graphicsView.setObjectName("graphicsView")
        self.gridLayout.addWidget(self.graphicsView, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab, "")

        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.tab_2)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.graphicsView_2 = MatplotWidget(self.tab_2)
        self.graphicsView_2.setObjectName("graphicsView_2")
        self.gridLayout_3.addWidget(self.graphicsView_2, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_2, "")

        self.tab_3 = QtWidgets.QWidget()
        self.tab_3.setObjectName("tab_3")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.tab_3)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.graphicsView_3 = MatplotWidget(self.tab_3)
        self.graphicsView_3.setObjectName("graphicsView_3")
        self.gridLayout_4.addWidget(self.graphicsView_3, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_3, "")

        self.tab_4 = QtWidgets.QWidget()
        self.tab_4.setObjectName("tab_4")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.tab_4)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.graphicsView_4 = MatplotWidget(self.tab_4)
        self.graphicsView_4.setObjectName("graphicsView_4")
        self.gridLayout_5.addWidget(self.graphicsView_4, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_4, "")

        ##########

        self.tab_5 = QtWidgets.QWidget()
        self.tab_5.setObjectName("tab_5")
        self.gridLayout_6 = QtWidgets.QGridLayout(self.tab_5)
        self.gridLayout_6.setObjectName("gridLayout_6")
        self.graphicsView_5 = MatplotWidget(self.tab_5)
        self.graphicsView_5.setObjectName("graphicsView_4")
        self.gridLayout_6.addWidget(self.graphicsView_5, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_5, "")

        self.tab_6 = QtWidgets.QWidget()
        self.tab_6.setObjectName("tab_6")
        self.gridLayout_7 = QtWidgets.QGridLayout(self.tab_6)
        self.gridLayout_7.setObjectName("gridLayout_7")
        self.graphicsView_6 = MatplotWidget(self.tab_6)
        self.graphicsView_6.setObjectName("graphicsView_5")
        self.gridLayout_7.addWidget(self.graphicsView_6, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_6, "")

        self.tab_7 = QtWidgets.QWidget()
        self.tab_7.setObjectName("tab_7")
        self.gridLayout_8 = QtWidgets.QGridLayout(self.tab_7)
        self.gridLayout_8.setObjectName("gridLayout_8")
        self.graphicsView_7 = MatplotWidget(self.tab_7)
        self.graphicsView_7.setObjectName("graphicsView_6")
        self.gridLayout_8.addWidget(self.graphicsView_7, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_7, "")

        self.tab_8 = QtWidgets.QWidget()
        self.tab_8.setObjectName("tab_8")
        self.gridLayout_9 = QtWidgets.QGridLayout(self.tab_8)
        self.gridLayout_9.setObjectName("gridLayout_9")
        self.graphicsView_8 = MatplotWidget(self.tab_8)
        self.graphicsView_8.setObjectName("graphicsView_7")
        self.gridLayout_9.addWidget(self.graphicsView_8, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_8, "")

        self.tab_9 = QtWidgets.QWidget()
        self.tab_9.setObjectName("tab_9")
        self.gridLayout_10 = QtWidgets.QGridLayout(self.tab_9)
        self.gridLayout_10.setObjectName("gridLayout_10")
        self.graphicsView_9 = MatplotWidget(self.tab_9)
        self.graphicsView_9.setObjectName("graphicsView_8")
        self.gridLayout_10.addWidget(self.graphicsView_9, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_9, "")

        self.tab_10 = QtWidgets.QWidget()
        self.tab_10.setObjectName("tab_10")
        self.gridLayout_11 = QtWidgets.QGridLayout(self.tab_10)
        self.gridLayout_11.setObjectName("gridLayout_11")
        self.graphicsView_10 = MatplotWidget(self.tab_10)
        self.graphicsView_10.setObjectName("graphicsView_9")
        self.gridLayout_11.addWidget(self.graphicsView_10, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_10, "")

        self.tab_11 = QtWidgets.QWidget()
        self.tab_11.setObjectName("tab_11")
        self.gridLayout_12 = QtWidgets.QGridLayout(self.tab_11)
        self.gridLayout_12.setObjectName("gridLayout_12")
        self.graphicsView_11 = MatplotWidget(self.tab_11)
        self.graphicsView_11.setObjectName("graphicsView_10")
        self.gridLayout_12.addWidget(self.graphicsView_11, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_11, "")

        self.tab_12 = QtWidgets.QWidget()
        self.tab_12.setObjectName("tab_12")
        self.gridLayout_13 = QtWidgets.QGridLayout(self.tab_12)
        self.gridLayout_13.setObjectName("gridLayout_13")
        self.graphicsView_12 = MatplotWidget(self.tab_12)
        self.graphicsView_12.setObjectName("graphicsView_11")
        self.gridLayout_13.addWidget(self.graphicsView_12, 0, 0, 1, 1)
        self.tabWidget.addTab(self.tab_12, "")

        self.gridLayout_2.addWidget(self.tabWidget, 0, 0, 1, 1)

        self.retranslateUi(Form)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(Form)

    def retranslateUi(self, Form):
        _translate = QtCore.QCoreApplication.translate
        Form.setWindowTitle(_translate("Form", "Form"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("Form", "LR"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("Form", "MR"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_3), _translate("Form", "SR"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_4), _translate("Form", "RM"))

        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_5), _translate("Form", "LR(Log)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_6), _translate("Form", "MR(Log)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_7), _translate("Form", "SR(Log)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_8), _translate("Form", "RM(Log)"))

        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_9), _translate("Form", "LR(Mask)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_10), _translate("Form", "MR(Mask)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_11), _translate("Form", "SR(Mask)"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_12), _translate("Form", "RM(Mask)"))


from qtmatplot import MatplotWidget
