#include "mailsmodel.h"

#include <QPixmap>

MailsModel::MailsModel(QObject *parent) : QAbstractTableModel(parent)
{
}

void MailsModel::setEMails(const QVector<EMail> &emails)
{
    beginResetModel();
    _emails = emails;
    endResetModel();
}

int MailsModel::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;
    return _emails.size();
}

int MailsModel::columnCount(const QModelIndex &) const
{
    return cCount;
}

QVariant MailsModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() > _emails.size())
        return QVariant();
    const EMail &email = _emails[index.row()];

    if (role == Qt::DecorationRole)
        return QPixmap(16, 16);

    switch (role) {
    case FromRole:
        return QVariant(email.from);
    case ToRole:
        return QVariant(email.to);
    case SubjectRole:
        return QVariant(email.subject);
    case AnnotationRole:
        return QVariant(email.anno);
    case DateRole:
        return QVariant(email.dateTime.toString("dd.MM.yyyy HH:mm"));
    default:
        break;
    }
    return QVariant();
}

QVariant MailsModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case cFrom:
            return tr("From");
        case cTo:
            return tr("To");
        case cSubject:
            return tr("Subject");
        case cAnno:
            return tr("Annotation");
        case cDate:
            return tr("Date");
        }
    }
    return QVariant();
}

QHash<int, QByteArray> MailsModel::roleNames() const
{
    QHash<int, QByteArray> roles = QAbstractTableModel::roleNames();
    roles[FromRole] = "cFrom";
    roles[ToRole] = "cTo";
    roles[SubjectRole] = "cSubject";
    roles[AnnotationRole] = "cAnno";
    roles[DateRole] = "cDate";
    roles[FlagAnsweredRole] = "cFlagAnswered";
    roles[FlagAttachment] = "cFlagAttachment";
    roles[FlagRedirected] = "cFlagRedirected";
    roles[ObjectStateRole] = "objectState";

    return roles;
}
