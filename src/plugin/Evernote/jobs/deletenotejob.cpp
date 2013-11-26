/*
 * Copyright: 2013 Canonical, Ltd
 *
 * This file is part of reminders-app
 *
 * reminders-app is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * reminders-app is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * Authors: Michael Zanetti <michael.zanetti@canonical.com>
 */

#include "deletenotejob.h"

DeleteNoteJob::DeleteNoteJob(const QString &guid, QObject *parent):
    EvernoteJob(parent),
    m_guid(guid)
{
}

void DeleteNoteJob::run()
{
    NotesStore::ErrorCode errorCode = NotesStore::ErrorCodeNoError;
    try {
        client()->deleteNote(token().toStdString(), m_guid.toStdString());
    } catch(...) {
        catchTransportException();
    }
    emit resultReady(errorCode, m_guid);
}
