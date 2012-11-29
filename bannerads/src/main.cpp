/* Copyright (c) 2012 Research In Motion Limited.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <QLocale>
#include <QTranslator>

#include <bb/cascades/Application>
#include <bb/cascades/QmlDocument>
#include <bb/cascades/AbstractPane>

#include <bb/cascades/advertisement/Banner>

using namespace bb::cascades;
using namespace bb::cascades::advertisement;

/**
 * This sample application shows some basic
 * usage of the Banner API, such as the creation
 * of a Banner, zone id configuration and its display on the screen.
 */
Q_DECL_EXPORT int main(int argc, char **argv) {
    // this is where the server is started etc
    Application app(argc, argv);

    // localization support
    QTranslator translator;
    QString locale_string = QLocale().name();
    QString filename = QString("bbads_sample_qml_%1").arg(locale_string);
    if (translator.load(filename, "app/native/qm")) {
        app.installTranslator(&translator);
    }

    const char *uri = "bb.cascades.advertisement";
    qmlRegisterType<bb::cascades::advertisement::Banner>(uri, 1, 0, "Banner");

    // create scene document from main.qml asset
    // set parent to created document to ensure it exists for the whole application lifetime
    QmlDocument *qml = QmlDocument::create("asset:///main.qml").parent(&app);
    // create root object for the UI
    AbstractPane *root = qml->createRootObject<AbstractPane>();
    // set created root object as a scene
    app.setScene(root);

    // we complete the transaction started in the app constructor and start the client event loop here
    return Application::exec();
    // when loop is exited the Application deletes the scene which deletes all its children (per qt rules for children)
}
