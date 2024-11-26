#include "main_window.h"

#include <QDebug>
#include <QHBoxLayout>
#include <QLabel>
#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QVBoxLayout>
#include <QWidget>

main_window::main_window(QWidget *parent) : QWidget(parent) {
  // 设置窗口标题和大小
  setWindowTitle("Simple Music Player");
  resize(600, 400);

  // 创建主布局
  QVBoxLayout *mainLayout = new QVBoxLayout(this);

  // 歌曲列表
  songListWidget = new QListWidget(this);
  songListWidget->addItem("Song 1");
  songListWidget->addItem("Song 2");
  songListWidget->addItem("Song 3");
  mainLayout->addWidget(songListWidget);

  // 创建水平布局，用于放置进度条和音量条
  QHBoxLayout *controlLayout = new QHBoxLayout();

  // 歌曲进度条
  progressSlider = new QSlider(Qt::Horizontal, this);
  progressSlider->setRange(0, 100);  // 设置范围，0-100%
  progressSlider->setValue(0);       // 初始值为0
  controlLayout->addWidget(new QLabel("Progress:"));
  controlLayout->addWidget(progressSlider);

  // 音量控制
  volumeSlider = new QSlider(Qt::Horizontal, this);
  volumeSlider->setRange(0, 100);  // 设置音量范围
  volumeSlider->setValue(50);      // 初始音量为50%
  controlLayout->addWidget(new QLabel("Volume:"));
  controlLayout->addWidget(volumeSlider);

  mainLayout->addLayout(controlLayout);

  // 播放/暂停按钮
  QHBoxLayout *buttonLayout = new QHBoxLayout();
  playButton                = new QPushButton("Play", this);
  pauseButton               = new QPushButton("Pause", this);
  buttonLayout->addWidget(playButton);
  buttonLayout->addWidget(pauseButton);
  mainLayout->addLayout(buttonLayout);

  // 信号与槽连接
  connect(playButton, &QPushButton::clicked, this, &main_window::playSong);
  connect(pauseButton, &QPushButton::clicked, this, &main_window::pauseSong);
  connect(progressSlider, &QSlider::sliderMoved, this, &main_window::seekSong);
  connect(volumeSlider, &QSlider::valueChanged, this, &main_window::setVolume);
  connect(songListWidget, &QListWidget::itemDoubleClicked, this, &main_window::loadSongFromList);
}

main_window::~main_window() {
  // 析构函数，清理资源
}

void main_window::playSong() {
  // 播放音乐的实现
  qDebug() << "Play button clicked";
}

void main_window::pauseSong() {
  // 暂停音乐的实现
  qDebug() << "Pause button clicked";
}

void main_window::seekSong(int position) {
  // 跳转进度条的实现
  qDebug() << "Seek to position: " << position;
}

void main_window::setVolume(int volume) {
    // 设置音量的实现
    qDebug() << "Set volume to: " << volume;
}

void main_window::loadSongFromList(QListWidgetItem *item) {
    // 加载选择的歌曲
    qDebug() << "Load song: " << item->text();
}
