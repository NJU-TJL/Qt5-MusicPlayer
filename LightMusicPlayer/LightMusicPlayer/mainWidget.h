#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMenu>
#include <QSystemTrayIcon>
#include "MusicList.h"
#include "LyricWidget.h"
#include <QCloseEvent>


namespace Ui {
class Widget;
}

class MainWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit MainWidget(QWidget *parent = nullptr);
    ~MainWidget() override;
    
private:
    Ui::Widget *ui;
    void paintEvent(QPaintEvent *event) override;
    
    //UI组件额外的一些处理
    void init_UI();
    
    //当前播放器
    QMediaPlayer *player;
    //当前播放列表
    QMediaPlaylist *playlist;
    //初始化一些成员变量以及connect连接
    void init_play();
    //更新播放信息相关（进度、信息等）
    void updatePosition(qint64 position);
    void updateDuration(qint64 duration);
    void setPosition(int position);
    void updateInfo();
    void updatePlayBtn();
    
    //系统托盘
    QSystemTrayIcon *mySystemTray;
    QAction *action_systemTray_play;
    QAction *action_systemTray_playmode;
    //响应系统托盘的动作（双击等）
    void systemTrayIcon_activated(QSystemTrayIcon::ActivationReason reason);
    //退出应用
    void quitMusicPlayer();
    //系统托盘初始化
    void init_systemTrayIcon();
    
    //数据库初始化
    void init_sqlite();
    //配置初始化（配置文件读取）
    void init_settings();
    //“本地音乐”、“我喜欢”等歌单的初始化
    void init_musicList();
    
    //歌单
    vector<MusicList> musiclist;
    //用于标识现在展示的是哪个歌单
    int musiclist_index=-1;
    //更新展示歌单名字的listwidget
    void namelist_refresh();
    //用于更新展示歌单内容的listwidget
    void musicListWidget_refresh();   
    
    /*右键菜单*/
    //菜单项的初始化
    void init_actions();
    //“当前播放”列表的右键菜单
    QMenu *menu_playlist;
    //“本地音乐”列表的右键菜单
    QMenu *menu_locallist;
    //“我喜欢”列表的右键菜单
    QMenu *menu_favorlist;
    //“歌单名列表”的右键菜单
    QMenu *menu_namelist;
    //“歌单展示列表”的右键菜单
    QMenu *menu_musiclist;
    //更换皮肤的菜单
    QMenu *menu_changeSkin; 

protected:
    //窗口拖动时记录的起始点
    QPoint offset;
    /*重写Widget的一些方法*/
    //实现窗口可拖动
    void mousePressEvent(QMouseEvent *event) override; 
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    //关闭时不退出，而是到系统托盘
    void closeEvent(QCloseEvent *event) override;
    //拖拽文件进入
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private slots:
    /*部分右键菜单项对应的操作（即对应QAction连接的槽函数）*/
    void playlist_removeMusic();//当前播放列表-右键菜单 移除歌曲
    void play_to_favor();//从当前播放添加到我喜欢
    void local_to_favor();//从本地音乐添加到我喜欢
    void local_to_playlist();//从本地音乐添加到当前播放列表
    void favor_to_playlist();//从我喜欢添加到当前播放列表
    void namelist_delete();//移除歌单
    void musiclist_removeMusic();//从歌单展示列表移除歌曲
    void musiclist_to_favor();//从当前歌单添加到我喜欢
    void musiclist_to_playlist();//从当前歌单添加到正在播放
    void background_to_default();//换到默认背景
    void background_setting();//自定义背景
    
    /*一些点击事件的响应（使用.ui中的部件“转到槽”自动生成）*/
    void on_btnCurMusic_clicked();
    void on_btnLocalMusic_clicked();
    void on_btnFavorMusic_clicked();
    void on_btnQuit_clicked();    
    void on_btnMin_clicked();    
    void on_btnPlay_clicked();
    void on_btnNext_clicked();
    void on_btnPre_clicked();
    void on_btnPlayMode_clicked();
    void on_btnAdd_clicked();
    void on_btnVolume_clicked();
    void on_volumeSlider_valueChanged(int value);
    void on_btnAddMusicList_clicked();
    void on_playListWidget_doubleClicked(const QModelIndex &index);
    void on_localMusicWidget_doubleClicked(const QModelIndex &index);
    void on_favorMusicWidget_doubleClicked(const QModelIndex &index);
    void on_playListWidget_customContextMenuRequested(const QPoint &pos);
    void on_localMusicWidget_customContextMenuRequested(const QPoint &pos);
    void on_favorMusicWidget_customContextMenuRequested(const QPoint &pos);
    void on_nameListWidget_customContextMenuRequested(const QPoint &pos);
    void on_nameListWidget_doubleClicked(const QModelIndex &index);
    void on_btnSkin_clicked();
    void on_btnAddtoMusicList_clicked();
    void on_musicListWidget_doubleClicked(const QModelIndex &index);
    void on_musicListWidget_customContextMenuRequested(const QPoint &pos);
    void on_btnAddtoFavor_clicked();
    void on_btnNeaten_clicked();//整理歌单按钮
    void on_btnNeaten_2_clicked();
    void on_btnNeaten_3_clicked();
    void on_btnTitle_clicked();
    void on_btnLyric_clicked();
    void on_btnClear_clicked();//清空
    void on_btnClear_2_clicked();
    void on_btnClear_3_clicked();
    void on_btnClear_4_clicked();
    void on_btnAbout_clicked();
    void on_btnSortSinger_clicked();//歌单排序
    void on_btnSortTitle_clicked();
    void on_btnSortDuration_clicked();
    void on_btnSortSinger_2_clicked();
    void on_btnSortTitle_2_clicked();
    void on_btnSortDuration_2_clicked();
    void on_btnSortSinger_4_clicked();
    void on_btnSortTitle_4_clicked();
    void on_btnSortDuration_4_clicked();
};

#endif // MAINWIDGET_H
