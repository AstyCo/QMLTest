#ifndef MAILSMODEL_H
#define MAILSMODEL_H

#include <QAbstractTableModel>
#include <QString>
#include <QVector>
#include <QDateTime>

struct EMail
{
    QString to;
    QString from;
    QString cc;
    QString bcc;
    QString subject;
    QString anno;
    QDateTime dateTime;
};

class MailsModel : public QAbstractTableModel
{
public:
    // Роли для получения кастомных данных
    enum MailRole {
        EmailRole = Qt::UserRole + 1, // роль для получения элемента датасорса (EmailItem *)
        EmailItemUID = Qt::UserRole + 2, // роль для получения UID'а письма
        FromRole,
        ToRole,
        SubjectRole,
        AnnotationRole,
        DateRole,
        FlagAnsweredRole,
        FlagAttachment,
        FlagRedirected,
        ObjectStateRole
    };
    enum Columns { cFrom, cTo, cSubject, cAnno, cDate, cCount };

public:
    MailsModel(QObject *parent = nullptr);

    void setEMails(const QVector<EMail> &emails);

private:
    QVector<EMail> _emails;

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    QHash<int, QByteArray> roleNames() const;
};

#endif // MAILSMODEL_H
