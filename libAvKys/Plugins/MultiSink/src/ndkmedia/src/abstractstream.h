/* Webcamoid, webcam capture application.
 * Copyright (C) 2019  Gonzalo Exequiel Pedone
 *
 * Webcamoid is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Webcamoid is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Webcamoid. If not, see <http://www.gnu.org/licenses/>.
 *
 * Web-Site: http://webcamoid.github.io/
 */

#ifndef ABSTRACTSTREAM_H
#define ABSTRACTSTREAM_H

#include <QVariantMap>

#define THREAD_WAIT_LIMIT 500

class AbstractStream;
class AbstractStreamPrivate;
class MediaWriterNDKMedia;
class AkCaps;
class AkPacket;
struct AMediaMuxer;
struct AMediaFormat;
struct AMediaCodec;
using AbstractStreamPtr = QSharedPointer<AbstractStream>;

class AbstractStream: public QObject
{
    Q_OBJECT

    public:
        AbstractStream(AMediaMuxer *mediaMuxer=nullptr,
                       uint index=0, int streamIndex=-1,
                       const QVariantMap &configs={},
                       MediaWriterNDKMedia *mediaWriter=nullptr,
                       QObject *parent=nullptr);
        virtual ~AbstractStream();

        Q_INVOKABLE uint index() const;
        Q_INVOKABLE int streamIndex() const;
        Q_INVOKABLE QString mimeType() const;
        Q_INVOKABLE AMediaCodec *codec() const;
        Q_INVOKABLE AMediaFormat *mediaFormat() const;
        Q_INVOKABLE AkCaps caps() const;
        Q_INVOKABLE void packetEnqueue(const AkPacket &packet);

    protected:
        int m_maxPacketQueueSize;

        virtual void convertPacket(const AkPacket &packet);
        virtual bool encodeData(bool eos=false);
        virtual AkPacket avPacketDequeue();

    private:
        AbstractStreamPrivate *d;

    signals:
        void packetReady(const AkPacket &packet);

    public slots:
        virtual bool init();
        virtual void uninit();

        friend class AbstractStreamPrivate;
};

#endif // ABSTRACTSTREAM_H