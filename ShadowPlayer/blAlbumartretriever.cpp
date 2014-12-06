#include "blAlbumartretriever.h"

const QString illegalCharacters(QLatin1String("\\(.*\\)|\\{.*\\}|\\[.*\\]|<.*>|[\\(\\)_\\{\\}\\[\\]\\!@#$\\^&\\*\\+\\=\\|\\\\/\"'\\?~`]"));



AlbumArtRetriever::AlbumArtRetriever(QObject *parent) :
    QObject(parent)
{

}

QString AlbumArtRetriever::getPath(QString artist, QString albumName)
{
    QString artistHash = QCryptographicHash::hash(artist.toLower().remove(illegalCharacters).simplified().toUtf8(), QCryptographicHash::Md5).toHex();

    QString albumHash = QCryptographicHash::hash(albumName.toLower()
                                                          .remove(illegalCharacters).simplified().toUtf8(),
                                                          QCryptographicHash::Md5).toHex();
    QString fileName = "/home/user"
                         + QLatin1String("/.cache/media-art/album-")
                         + artistHash
                         + QLatin1Char('-')
                         + albumHash
                         + QLatin1String(".jpeg");
    return fileName;


}