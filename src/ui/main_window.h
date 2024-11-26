#ifndef HER_PLAYER_MAIN_WINDOW_H
#define HER_PLAYER_MAIN_WINDOW_H

#include <QListWidget>
#include <QPushButton>
#include <QSlider>
#include <QWidget>

class main_window final : public QWidget {
  Q_OBJECT
  QPushButton *playButton;
  QPushButton *pauseButton;
  QSlider *progressSlider;
  QSlider *volumeSlider;
  QListWidget *songListWidget;

 public:
  explicit main_window(QWidget *parent = nullptr);
  ~main_window() override;

 private slots:
  void playSong();                               // 播放歌曲
  void pauseSong();                              // 暂停歌曲
  void seekSong(int);                            // 跳转进度
  void setVolume(int);                           // 设置音量
  void loadSongFromList(QListWidgetItem *item);  // 加载选择的歌曲
};

#endif  // HER_PLAYER_MAIN_WINDOW_H
