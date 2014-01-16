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

#ifndef NOTEBOOK_H
#define NOTEBOOK_H

#include <QObject>

class Notebook : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString guid READ guid CONSTANT)
    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(int noteCount READ noteCount NOTIFY noteCountChanged)
    Q_PROPERTY(bool published READ published NOTIFY publishedChanged)

public:
    explicit Notebook(QString guid, QObject *parent = 0);

    QString guid() const;

    QString name() const;
    void setName(const QString &name);

    int noteCount() const;

    bool published() const;
    void setPublished(bool published);

signals:
    void nameChanged();
    void noteCountChanged();
    void publishedChanged();

private slots:
    void noteAdded(const QString &noteGuid, const QString &notebookGuid);
    void noteRemoved(const QString &noteGuid, const QString &notebookGuid);

private:
    QString m_guid;
    QString m_name;
    int m_noteCount;
    bool m_published;
};

#endif // NOTEBOOK_H