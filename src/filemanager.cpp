#include "../inc/filemanager.h"

QString FileManager::calculateFileHash(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return {};
    }
    QCryptographicHash hash(QCryptographicHash::Md5);
    while (!file.atEnd()) {
        QByteArray data = file.read(8192);
        hash.addData(data);
    }
    file.close();
    return hash.result().toHex();
}
