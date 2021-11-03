
class lineEdit_DnD():
    def __init__(self, lineEdit):
        self.lineEdit = lineEdit
        self.inject_dragFile()

    def inject_dragFile( self ):
        self.lineEdit.setDragEnabled(True)
        self.lineEdit.dragEnterEvent = self._dragEnterEvent
        self.lineEdit.dragMoveEvent = self._dragMoveEvent
        self.lineEdit.dropEvent = self._dropEvent

    def _dragEnterEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            event.acceptProposedAction()

    def _dragMoveEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            event.acceptProposedAction()

    def _dropEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            # for some reason, this doubles up the intro slash
            filepath = str(urls[0].path())[1:]
            self.lineEdit.setText(filepath)


class listWidget_DnD():
    def __init__(self, listwidget, AddWords=False):
        self.listwidget = listwidget
        self.inject_dragFile()
        self.AddWords = AddWords


    def inject_dragFile( self ):
        self.listwidget.setDragEnabled(True)
        self.listwidget.setAcceptDrops(True)
        self.listwidget.dragEnterEvent = self._dragEnterEvent
        self.listwidget.dragMoveEvent = self._dragMoveEvent
        self.listwidget.dropEvent = self._dropEvent

    def _dragEnterEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            event.acceptProposedAction()

    def _dragMoveEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            event.acceptProposedAction()

    def _dropEvent( self, event ):
        data = event.mimeData()
        urls = data.urls()
        if ( urls and urls[0].scheme() == 'file' ):
            # for some reason, this doubles up the intro slash
            filepath = str(urls[0].path())[1:]
            if self.AddWords:
                self.listwidget.addItem(filepath+self.AddWords)
            else:
                self.listwidget.addItem(filepath)