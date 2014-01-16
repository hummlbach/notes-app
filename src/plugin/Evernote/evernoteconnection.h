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

#ifndef EVERNOTECONNECTION_H
#define EVERNOTECONNECTION_H

#include <boost/shared_ptr.hpp>

// Thrift
#include <transport/THttpClient.h>

#include <QObject>

namespace evernote {
namespace edam {
class NoteStoreClient;
class UserStoreClient;
}
}

using namespace apache::thrift::transport;

class EvernoteJob;

class EvernoteConnection : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)

    friend class NotesStoreJob;
    friend class UserStoreJob;

public:
    enum ErrorCode {
        ErrorCodeNoError,
        ErrorCodeUserException,
        ErrorCodeSystemException,
        ErrorCodeNotFoundExcpetion,
        ErrorCodeConnectionLost
    };

    static EvernoteConnection* instance();
    ~EvernoteConnection();

    QString token() const;
    void setToken(const QString &token);

    void enqueue(EvernoteJob *job);

signals:
    void tokenChanged();

private slots:
    void startJobQueue();
    void startNextJob();

private:
    explicit EvernoteConnection(QObject *parent = 0);
    static EvernoteConnection *s_instance;

    bool setupUserStore();
    bool setupNotesStore();

    bool m_useSSL;

    QString m_token;

    // There must be only one job running at a time
    // Do not start jobs other than with startJobQueue()
    QList<EvernoteJob*> m_jobQueue;
    EvernoteJob *m_currentJob;

    // Those 4 are accessed from the job thread.
    // Make sure to not access them while any jobs are running
    // or we need to mutex them.
    evernote::edam::NoteStoreClient *m_notesStoreClient;
    boost::shared_ptr<THttpClient> m_notesStoreHttpClient;

    evernote::edam::UserStoreClient *m_userstoreClient;
    boost::shared_ptr<THttpClient> m_userStoreHttpClient;

};

#endif // EVERNOTECONNECTION_H