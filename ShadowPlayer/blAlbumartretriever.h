#ifndef ALBUMARTRETRIEVER_H
#define ALBUMARTRETRIEVER_H

#include <QtCore>

class AlbumArtRetriever : public QObject
{
    Q_OBJECT
public:
    explicit AlbumArtRetriever(QObject *parent = 0);

    Q_INVOKABLE QString getPath(QString artist, QString albumName);

signals:

public slots:

};

#endif // ALBUMARTRETRIEVER_H