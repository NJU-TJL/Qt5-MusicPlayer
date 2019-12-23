#include "MusicListWidget.h"

MusicListWidget::MusicListWidget(QWidget *parent)
    :QListWidget (parent)
{
    
}

void MusicListWidget::refresh()
{
    clear();//先清空
    musicList.addToListWidget(this);    
}

void MusicListWidget::setMusicList(const MusicList &music)
{
    musicList=music;
    refresh();
}

void MusicListWidget::setMusicList_playing(const MusicList &music)
{
    musicList=music;
    musicList.setSQL(false);
    refresh();
}

void MusicListWidget::removeMusic()
{
    int pos=currentRow();    
    //移除
    musicList.removeMusic(pos);
    //实测这里如果直接使用removeMedia会导致当前播放的歌曲乱跳...（所以这里只能从更上层调用的地方来移除正在播放的歌曲）
    //playlist->removeMedia(pos);
    
    //从ListWidget中移除
    QListWidgetItem *tempItem=takeItem(pos);
    removeItemWidget(tempItem);
    delete tempItem;
}

void MusicListWidget::showInExplorer()
{
    int pos=currentRow();
    musicList.showInExplorer(pos);
}

void MusicListWidget::detail()
{
    int pos=currentRow();
    musicList.detail(pos);
}
