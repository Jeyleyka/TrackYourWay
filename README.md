#  Track_Your_Way
**Track_Your_Way** - journaling project to increase discipline by completing daily tasks assigned for the day and check 

### The programm is written in Qt
Install the current version of [Qt](https://www.qt.io/download-dev)
___
### Highlights
This application works with text files that store data thanks to the **QFile** module

``` C++
QFile file("###");

    if (!file.exists()) {
        qDebug() << "File does not exist.";
        QMessageBox::critical(nullptr, "File Error", "File not found.");
        return false;
    }
```

This application doesn't have a basic program form thanks to the **QRegion** and **QPainter** modules
``` cpp
void MainWindow::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing); 

    QPainterPath path;
    path.setFillRule(Qt::WindingFill); 

    int radius = 20; 
    path.addRoundedRect(0, 0, width(), height(), radius, radius); 

    painter.setClipPath(path);
    painter.fillRect(rect(), currentBackgroundColor); 

    QRegion region(path.toFillPolygon().toPolygon());
    setMask(region);  
}
```