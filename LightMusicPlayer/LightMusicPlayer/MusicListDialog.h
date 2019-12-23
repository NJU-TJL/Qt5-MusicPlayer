#ifndef MUSICLISTDIALOG_H
#define MUSICLISTDIALOG_H

#include <QDialog>
#include "MusicList.h"
#include "MusicListWidget.h"

namespace Ui {
class MusicListDialog;
}

class MusicListDialog : public QDialog
{
    Q_OBJECT
    //歌曲数量
    int num; 
    //存放歌曲条目是否被选择（用于返回选择结果）
    bool *selected_flag;
public:
    explicit MusicListDialog(QWidget *parent = nullptr);
    ~MusicListDialog();
    
    //设定对话框展示出的歌单以及选择结果存放的地方
    void setMusicList(MusicList& ilist, bool *results);
    
private slots:
    
    void on_buttonBox_accepted();
    
private:
    Ui::MusicListDialog *ui;
};

#endif // MUSICLISTDIALOG_H
