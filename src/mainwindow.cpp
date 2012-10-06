#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    if (ui->comboBox->currentIndex()==0){
        _type = GraphicsScene::HeadToHead;
    }else if (ui->comboBox->currentIndex()==1){
        _type = GraphicsScene::HumanVsMachine;
    }else if (ui->comboBox->currentIndex()==2){
        _type = GraphicsScene::MachineVsMachine;
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{

    int fszX = ui->fieldSizeX->value();
    int fszY = ui->fieldSizeY->value();

    QRect sceneSize(0,0,600,600);
    _gamePlayScene = new GraphicsScene(_type, QSize(fszX, fszY), sceneSize);
    _gamePlayView = new GraphicsView(_gamePlayScene);

    // no resize allowed:
    _gamePlayView->setMinimumSize(_gamePlayView->size());
    _gamePlayView->setMaximumSize(_gamePlayView->size());

    //_gamePlayView->setViewport(new QGLWidget(QGLFormat(QGL::SampleBuffers)));
    //_gamePlayView->setViewportUpdateMode(QGraphicsView::FullViewportUpdate);
    //_gamePlayView->setScene();

    connect(_gamePlayView,SIGNAL(sendClosed()),SLOT(onGamePlayExit()),Qt::QueuedConnection);

    _gamePlayView->show();

    this->hide();
}


void MainWindow::onGamePlayExit()
{
    if (_gamePlayView!=NULL ){
        delete _gamePlayView;
        _gamePlayView = NULL;
    }

    if (_gamePlayScene!=NULL){
        delete _gamePlayScene;
        _gamePlayScene = NULL;
    }

    this->show();
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if (index == 0){ // Head to Head
        ui->player1TypeL->setText("Head 1 =");
        ui->player2TypeL->setText("Head 2 =");
        _type = GraphicsScene::HeadToHead;
    }else if (index == 1){ // Human vs PC
        ui->player1TypeL->setText("Head 1 =");
        ui->player2TypeL->setText("PC =");
        _type = GraphicsScene::HumanVsMachine;
    }else if (index == 2){ // PC vs PC
        ui->player1TypeL->setText("PC =");
        ui->player2TypeL->setText("PC =");
        _type = GraphicsScene::MachineVsMachine;
    }
}

void MainWindow::on_swapB_clicked()
{
    QString s = ui->player1ColorLE->text();
    ui->player1ColorLE->setText(ui->player2ColorLE->text());
    ui->player2ColorLE->setText(s);
    GraphicsScene::GameType type = _type;

    if (type == GraphicsScene::HumanVsMachine){
        _type = GraphicsScene::MachineVsHuman;
    }else if (type == GraphicsScene::MachineVsHuman){
        _type = GraphicsScene::HumanVsMachine;
    }

}
