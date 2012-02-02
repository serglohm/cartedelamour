#include <QtGui/QApplication>
#include <QDeclarativeEngine>
#include <QDeclarativeContext>
#include "qmlapplicationviewer.h"
#include "fruititem.h"

#include "ptsengine.h"


ListModel* createModel() {
    ListModel *model = new ListModel(new FruitItem, qApp);
    model->appendRow(new FruitItem("Apple", "medium", model));
    model->appendRow(new FruitItem("PineApple", "big", model));
    model->appendRow(new FruitItem("Grape", "small", model));
    return model;
}

Q_DECL_EXPORT int main(int argc, char *argv[])
{
    QScopedPointer<QApplication> app(createApplication(argc, argv));

    QmlApplicationViewer viewer;

    PTSEngine* engine = new PTSEngine(viewer);

    viewer.rootContext()->setContextProperty("qtengine", engine);
    viewer.rootContext()->setContextProperty("fruitsModel", createModel());
    viewer.engine()->addImageProvider(QLatin1String("pushthescreen"), engine->getImageProvider());
    viewer.setMainQmlFile(QLatin1String("qml/QMLSis/main.qml"));
    viewer.showExpanded();

    return app->exec();
}
