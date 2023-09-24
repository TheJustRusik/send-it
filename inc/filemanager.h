#pragma once

#include <QCryptographicHash>
#include <QFile>
#include <QString>

class FileManager {
    QString file_name;
    QString file_hash;
    qint64 file_size;

public:
    static QString calculate_file_hash(const QString& filePath);
    
};



