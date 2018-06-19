/***************************************************************************
    This file is part of Project Lemon
    Copyright (C) 2011 Zhipeng Jia

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
***************************************************************************/

#include <QtGui/QApplication>
#include <iostream>
#include "qtsingleapplication/qtsingleapplication.h"
#include "lemon.h"

int main(int argc, char *argv[])
{
#ifdef Q_WS_X11
    qputenv("LIBOVERLAY_SCROLLBAR", 0);
#endif

    QtSingleApplication a(argc, argv);

    //a.setStyle(new QCleanlooksStyle());
    
    if (a.sendMessage("")) {
        a.activateWindow();
        return 0;
    }
    QPixmap pixmap(":/logo/proj.png");  
    QSplashScreen screen(pixmap);  
    screen.show();  

    qint64 startTime = QDateTime::currentMSecsSinceEpoch();
    do{  
        a.processEvents();  
    } while (QDateTime::currentMSecsSinceEpoch() - startTime <= 800);//5为需要延时的秒数  


    Lemon w;
    a.setActivationWindow(&w);
    
    w.show();
    w.move ((QApplication::desktop()->width() - w.width())/2,(QApplication::desktop()->height() - w.height())/2);

    screen.finish(&w);
    w.welcome();
    
    return a.exec();
}
