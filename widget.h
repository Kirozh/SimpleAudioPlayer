#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QStandardItemModel>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QMouseEvent>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

    // Свойство с точкой предыдущей позиции мыши
        // Относительно данной точки идёт пересчёт позиции окна
        // Или размеров окна. При этом свойство устанавливается при нажатии мыши
        // по окну и в ряде иных случаев
        Q_PROPERTY(QPoint previousPosition READ previousPosition WRITE setPreviousPosition NOTIFY previousPositionChanged)

        // тип клика мыши, при перемещении курсора по этому типу будем определять
        // что именно нужно сделать, перенести окно, или изменить его размер с одной из сторон
        enum MouseType {
            None = 0,
            Top,
            Bottom,
            Left,
            Right,
            Move
        };



public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
        QPoint previousPosition() const;

public slots:
    void setPreviousPosition(QPoint previousPosition);

signals:
    void previousPositionChanged(QPoint previousPosition);

private slots:

    void on_btn_library_clicked();

    void on_btn_repeat_clicked();

    void on_btn_play_clicked();

    void on_btn_close_clicked();

    void on_btn_minimize_clicked();

    void on_btn_maximize_clicked();

    void on_btn_next_clicked();

    void on_btn_prev_clicked();

    void on_btn_menu_clicked();

    void on_btn_stop_clicked();

    void on_btn_sound_clicked();

    void on_soundSlider_sliderMoved(int position);

    void setPositionSlider(qint64 i);

    void on_timeSlider_sliderMoved(int position);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);


private:
    Ui::Widget *ui;
    QStandardItemModel  *m_playListModel;
    QStandardItemModel  *m_recentPlayListModel;// Модель данных плейлиста для отображения
    QMediaPlayer        *m_player;          // Проигрыватель треков
    QMediaPlaylist      *m_playlist;        // Плейлиста проигрывателя

    // Переменная, от которой будем отталкиваться при работе с перемещением и изменением размера окна
        MouseType m_leftMouseButtonPressed;
        QPoint m_previousPosition;

        MouseType checkResizableField(QMouseEvent *event);
};

#endif // WIDGET_H
