/**
@brief GUI App For AI Project
@date 2020-03-20
@author juanli
@link lj.succ@gmail.com
@copyright zoomlion company
**/

#include <QApplication>
#include <QSqlDatabase>
#include <ros/ros.h>
#include "gui_ui/BaseWidget.h"
#include "gui_ui/AppMainWindow.h"
#include "gui_ui/AppInit.h"
#include "platform/GlobalCfg.h"
#include "platform/GlobalDB.h"
#include "platform/MGLogger.h"

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_EnableHighDpiScaling);    
    a.setWindowIcon(QIcon(":/images/main.ico"));

    ros::init(argc,argv,"ros_gui_node");
    ros::Time::init();
    if (!AppInit::Ins().checkRosMaster())
        return 0;
    MGLogger::installLogHandler();

    BaseWidget::setCode();
    BaseWidget::setTranslator(":/trans/gui_en_EN.qm");
    if (GlobalCfg::Ins().readConfig() == false)
    {
        return 0;
    }
    GlobalDB::Ins().openDB(EDBType::DB_SQLITE);

    AppInit::Ins().setSystemFont();

    AppMainWindow w;
    w.init();
    w.move(0,0);
    w.show();


    return a.exec();
}

