#pragma once

#include <QCryptographicHash>
#include <QFile>
#include <QString>

class FileManager {

public:
    static QString calculateFileHash(const QString& filePath);
};



