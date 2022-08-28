#include <QGuiApplication>
#include <QApplication>
#include <QQmlApplicationEngine>
#include <QImage>
#include <QPixmap>
#include <QSplashScreen>
#include <QLabel>
#include <QDebug>
#include <QTimer>
#include <iostream>
#include <QQmlEngine>
#include "ros_topic.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QApplication app(argc, argv);
    Ros_topic ros_topic;
    ros_topic.getRosInit(argc,argv);
    ros_topic.update_thread();
    
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
    qmlRegisterType<Ros_topic>("Ros_topic", 1, 0, "Ros_topic");
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                   &app, [url](QObject *obj, const QUrl &objUrl)
  {
  if (!obj && url == objUrl)
      QCoreApplication::exit(-1);
  }, Qt::QueuedConnection);
  engine.load(url);
  try{
  return app.exec();
  }
  catch(...)
  {
       std::cout<<"Successfully Catched"<<std::endl;
  }




return 0;
}