#include "mailsmodel.h"

#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QDateTime>
#include <QItemSelectionModel>
#include <QDebug>
#include <QtWidgets/QPushButton>

#include <random>

static EMail generateEmail(const QString &word)
{
    return EMail({"to_" + word, "from_" + word, "cc_" + word, "bcc_" + word, "subject_" + word,
                  "anno_" + word, QDateTime::currentDateTime()});
}

static QString getRandomString(int len)
{
    static std::mt19937 rng = std::mt19937(std::random_device()());
    QString result;
    result.reserve(len);
    std::uniform_int_distribution<char> uni('A', 'Z');
    for (int i = 0; i < len; ++i)
        result.push_back(uni(rng));
    return result;
}

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<MailsModel>("MailsModel", 1, 0, "MailsModel");

    QQmlApplicationEngine engine;

    MailsModel *model = new MailsModel(nullptr);
    QItemSelectionModel *selection = new QItemSelectionModel(nullptr);
    selection->setModel(model);
    QObject *printer = new QObject(nullptr);
    printer->connect(selection, &QItemSelectionModel::currentChanged,
                     [](const QModelIndex &c, const QModelIndex &p) {
                         qDebug() << "currentRowChanged" << c << p;
                     });
    // Data
    const int emailsSize = 500;
    const int emailLength = 200;
    QVector<EMail> emails;
    emails.reserve(emailsSize);
    for (int i = 0; i < emailsSize; ++i)
        emails.push_back(generateEmail(getRandomString(emailLength)));
    // /Data

    model->setEMails(emails);

    engine.rootContext()->setContextProperty("selectionModel", selection);
    engine.rootContext()->setContextProperty("mailsModel", model);
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    QPushButton *pb = new QPushButton(QString("clear"), nullptr);
    pb->setMinimumSize(200, 50);
    pb->show();
    pb->connect(pb, &QPushButton::clicked, [&engine, selection]() {
        qDebug() << "click";
        selection->clear();
    });

    if (engine.rootObjects().isEmpty())
        return -1;
    return app.exec();
}
