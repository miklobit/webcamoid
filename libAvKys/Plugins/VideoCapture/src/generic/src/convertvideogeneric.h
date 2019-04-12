/* Webcamoid, webcam capture application.
 * Copyright (C) 2016  Gonzalo Exequiel Pedone
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

#ifndef CONVERTVIDEOFFMPEG_H
#define CONVERTVIDEOFFMPEG_H

#include "convertvideo.h"

class ConvertVideoGenericPrivate;

class ConvertVideoGeneric: public ConvertVideo
{
    Q_OBJECT

    public:
        ConvertVideoGeneric(QObject *parent=nullptr);
        ~ConvertVideoGeneric();

        Q_INVOKABLE void packetEnqueue(const AkPacket &packet);
        Q_INVOKABLE bool init(const AkCaps &caps);
        Q_INVOKABLE void uninit();

    private:
        ConvertVideoGenericPrivate *d;

        friend class ConvertVideoFFmpegPrivate;
};

#endif // CONVERTVIDEOFFMPEG_H