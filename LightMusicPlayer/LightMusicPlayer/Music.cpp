#include "Music.h"
#include <QMediaPlayer>
#include <QCoreApplication>
#include <QMessageBox>
#include <QtSql>

Music::Music(QUrl iurl)
{
    url=iurl;
    refreshInfo();
}

extern QString formatTime(qint64 timeMilliSeconds);
void Music::refreshInfo()
{
    QMediaPlayer tempPlayer;
    tempPlayer.setMedia(url);
    //元数据的解析需要时间，所以这里需要循环等待（但同时需要保持Qt事件处理机制在运行）
    while(!tempPlayer.isMetaDataAvailable()){
        QCoreApplication::processEvents();
    }
    QStringList list=tempPlayer.availableMetaData();//调试时查看有哪些元数据可用
    if(tempPlayer.isMetaDataAvailable()){
        //歌曲信息
        author = tempPlayer.metaData(QStringLiteral("Author")).toStringList().join(",");
        //author = tempPlayer.metaData(QStringLiteral("Author")).toString(); //查手册发现，这里返回的是StringList
        //author=tempPlayer.metaData(QStringLiteral("ContributingArtist")).toStringList().join(","); //另一种元数据
        title = tempPlayer.metaData(QStringLiteral("Title")).toString();
        albumTitle = tempPlayer.metaData(QStringLiteral("AlbumTitle")).toString();
        audioBitRate = tempPlayer.metaData(QStringLiteral("AudioBitRate")).toInt();
        duration=tempPlayer.duration();
    }
}

QString Music::getLyricFile()
{
    QString mp3FilePath=url.toLocalFile();
    mp3FilePath.replace(".mp3",".lrc");
    mp3FilePath.replace(".flac",".lrc");
    mp3FilePath.replace(".mpga",".lrc");
    return mp3FilePath;
}

QString Music::getInfo() const
{
    return author+" - "+title+" ["+formatTime(duration)+"]";
}

void Music::detail()
{
    QString info("歌曲名：%1\n艺术家：%2\n时长：%3\n唱片集：%4\n比特率：%5\n文件路径：%6");
    info=info.arg(title,author,formatTime(duration),albumTitle,QString::number(audioBitRate)+"bps",url.toString());
    QMessageBox::about(Q_NULLPTR,"歌曲信息",info);
}

void Music::insertSQL(const QString &name)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into MusicInfo values (?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(name);
    sql_query.addBindValue(url.toString());
    sql_query.addBindValue(author);
    sql_query.addBindValue(title);
    sql_query.addBindValue(duration);
    sql_query.addBindValue(albumTitle);
    sql_query.addBindValue(audioBitRate);
    sql_query.exec();
}

bool MusicCompare::operator()(const Music &A, const Music &B)
{
    switch (key) {
    case TITLE:
        return A.title<B.title;
    case AUTHOR:
        return A.author<B.author;
    case DURATION:
        return A.duration<B.duration;
    case EQUALITY:
        return A.getUrl()==B.getUrl();
    default:
        return A.getInfo()<B.getInfo();
    }
}
