// SPDX-FileCopyrightText: 2024 Gary Wang <git@blumia.net>
//
// SPDX-License-Identifier: MIT

#pragma once

#include <QHash>
#include <QList>
#include <QLoggingCategory>
#include <QObject>

Q_DECLARE_LOGGING_CATEGORY(lcLyrics)
Q_DECLARE_LOGGING_CATEGORY(lcLyricsParser)

class LyricsManager : public QObject
{
    Q_OBJECT
public:
    explicit LyricsManager(QObject *parent);
    ~LyricsManager();

    bool loadLyrics(QString filepath);
    bool hasLyrics() const;
    void updateCurrentTimeMs(int curTimeMs, int totalTimeMs);
    QString lyrics(int lineOffset = 0) const;
    double maskPercent(int curTimeMs);
    void setTimeOffset(int offset);

protected:


private:
    void reset();
    int currentLyricsTime() const;
    int nextLyricsTime() const;

    QHash<int, QString> m_lyricsMap;
    QList<int> m_timestampList;
    int m_currentLyricsTime = 0;
    int m_nextLyricsTime = 0;
    int m_timeOffset = 0;
};
