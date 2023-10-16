#include "IOThread.hpp"
#include <QFile>
#include <QDebug>

namespace sfmdataentity
{

void IOThread::read(const QUrl& source)
{
    _source = source;
    start();
}

void IOThread::run()
{
    // ensure file exists and is valid
    if (!_source.isValid() || !QFile::exists(_source.toLocalFile()))
        return;

    QMutexLocker lock(&_mutex);
    if (!aliceVision::sfmDataIO::Load(_sfmData, _source.toLocalFile().toStdString(),
                                      aliceVision::sfmDataIO::ESfMData(aliceVision::sfmDataIO::ESfMData::VIEWS |
                                                                       aliceVision::sfmDataIO::ESfMData::INTRINSICS |
                                                                       aliceVision::sfmDataIO::ESfMData::EXTRINSICS |
                                                                       aliceVision::sfmDataIO::ESfMData::STRUCTURE)))
    {
        qDebug() << "[QtAliceVision] Failed to load sfmData: " << _source << ".";
    }
}

void IOThread::clear()
{
    QMutexLocker lock(&_mutex);
    _sfmData = aliceVision::sfmData::SfMData();
}

const aliceVision::sfmData::SfMData & IOThread::getSfmData() const
{
    // mutex is mutable and can be locked in const methods
    QMutexLocker lock(&_mutex);
    return _sfmData;
}

}  // namespace sfmdataentity
