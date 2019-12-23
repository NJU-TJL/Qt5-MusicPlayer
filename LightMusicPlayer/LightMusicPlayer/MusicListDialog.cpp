#include "MusicListDialog.h"
#include "ui_MusicListDialog.h"

MusicListDialog::MusicListDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MusicListDialog)
{
    ui->setupUi(this);
}

MusicListDialog::~MusicListDialog()
{
    delete ui;
}

void MusicListDialog::setMusicList(MusicList &ilist, bool *results)
{
    selected_flag=results;
    ui->listWidget->setIcon(QIcon(":/image/image/image/dialog-music.png"));
    ilist.addToListWidget(ui->listWidget);
    num=ui->listWidget->count();
    
}

void MusicListDialog::on_buttonBox_accepted()
{
    for(int i=0;i<num;i++){
        selected_flag[i]=ui->listWidget->item(i)->isSelected();
    }
}
