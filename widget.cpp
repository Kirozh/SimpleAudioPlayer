#include "widget.h"
#include "ui_widget.h"
#include <QFileDialog>
#include <QToolButton>
#include <QDir>
#include <QGraphicsDropShadowEffect>
#include <QMediaMetaData>
#include <QLabel>
#include "stylehelper.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),
  m_leftMouseButtonPressed(None)
{
    ui->setupUi(this);
   // ui->setStyleSheet("background-color:white;");
    this->setWindowFlags(Qt::FramelessWindowHint);      // Отключаем оформление окна
    //this->setAttribute(Qt::WA_TranslucentBackground);   // Делаем фон главного виджета прозрачным
    //this->setStyleSheet(StyleHelper::getWindowStyleSheet());    // Устанавливаем стиль виджета
    this->setMouseTracking(true);

    // Создаём эффект тени
    QGraphicsDropShadowEffect *shadowEffect = new QGraphicsDropShadowEffect(this);
    shadowEffect->setBlurRadius(9); // Устанавливаем радиус размытия
    shadowEffect->setOffset(0);     // Устанавливаем смещение тени


    //оформление кнопок
    ui->label->setText("Fake Player");                        //название
    ui->label->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    ui->time->setText("Time");
        //ui->currentTrack->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->label->setStyleSheet(StyleHelper::getLabelStyleSheet());
    ui->btn_close->setStyleSheet(StyleHelper::getCloseStyleSheet());
    ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
    ui->btn_minimize->setStyleSheet(StyleHelper::getMinimizeStyleSheet());
    ui->btn_next->setStyleSheet(StyleHelper::getNextStyleSheet());
    ui->btn_prev->setStyleSheet(StyleHelper::getPreviousStyleSheet());
    ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
    ui->btn_sound->setStyleSheet(StyleHelper::getSoundStyleSheet());
    ui->btn_repeat->setStyleSheet(StyleHelper::getRepeatStyleSheet());
    ui->btn_stop->setStyleSheet(StyleHelper::getStopStyleSheet());
    ui->btn_menu->setStyleSheet(StyleHelper::getMenuStyleSheet());
        //ui->btn_add->setStyleSheet(StyleHelper::getMenuStyleSheet());
        //ui->playlistView->setStyleSheet(StyleHelper::getTableViewStyleSheet());
        //ui->btn_add->setText(tr("Добавить"));

    //устанавливаем курсор в виде руки
    ui->btn_next->setCursor(Qt::PointingHandCursor);
    ui->btn_prev->setCursor(Qt::PointingHandCursor);
    ui->btn_play->setCursor(Qt::PointingHandCursor);
    ui->btn_repeat->setCursor(Qt::PointingHandCursor);
    ui->btn_sound->setCursor(Qt::PointingHandCursor);
    ui->btn_stop->setCursor(Qt::PointingHandCursor);
    ui->btn_menu->setCursor(Qt::PointingHandCursor);
        // ui->horizontalLayout->setSpacing(6);


    // Настройка таблицы плейлиста
    m_playListModel = new QStandardItemModel(this);
    ui->playlistView->setModel(m_playListModel);    // Устанавливаем модель данных в TableView


    // Устанавливаем заголовки таблицы
    m_playListModel->setHorizontalHeaderLabels(QStringList()  << tr("Audio Track")<< tr("File Path"));
    ui->playlistView->hideColumn(1);    // Скрываем колонку, в которой хранится путь к файлу
    ui->playlistView->verticalHeader()->setVisible(false);                  // Скрываем нумерацию строк
    ui->playlistView->setSelectionBehavior(QAbstractItemView::SelectRows);  // Включаем выделение строк
    ui->playlistView->setSelectionMode(QAbstractItemView::SingleSelection); // Разрешаем выделять только одну строку
    ui->playlistView->setEditTriggers(QAbstractItemView::NoEditTriggers);   // Отключаем редактирование
    // Включаем подгонку размера последней видимой колонки к ширине TableView
    ui->playlistView->horizontalHeader()->setStretchLastSection(true);



    //начальные настройки
    ui->track->setVisible(false);
    ui->time->setVisible(false);
      // Инициализируем плейлист

    m_player = new QMediaPlayer(this);    // Инициализируем плеер
    m_playlist = new QMediaPlaylist(m_player);
    m_player->setPlaylist(m_playlist);          // Устанавливаем плейлист в плеер
    m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
    m_player->setVolume(50);                    // Устанавливаем громкость воспроизведения треков
    ui->soundSlider->setSliderPosition(46);// начальное положение бегунка звука



    // При даблклике по треку в таблице устанавливаем трек в плейлисте
    connect(ui->playlistView, &QTableView::doubleClicked, [this](const QModelIndex &index){
      m_playlist->setCurrentIndex(index.row());
      //ui->time->setVisible(true);ui->time->setText(m_playListModel->data(m_playListModel->index(index, 2)).toString());
    });

    connect(m_player, SIGNAL(positionChanged(qint64)), this, SLOT(setPositionSlider(qint64)));//изменение позиции временного бегунка

 // при изменении индекса текущего трека в плейлисте, устанавливаем название файла в специальном лейбле
    connect(m_playlist, &QMediaPlaylist::currentIndexChanged, [this](int index){
        ui->track->setVisible(true);ui->track->setText(m_playListModel->data(m_playListModel->index(index, 0)).toString());
        //ui->time->setVisible(true);ui->time->setText((m_playListModel->data(m_playListModel->index(index, 2))).toString()); //пытался вывести длительность аудио
        //ui->time->setVisible(true);ui->time->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);ui->time->setNum((m_playListModel->data(m_playListModel->index(index, 2))).toInt());
        //ui->time->setVisible(true);ui->time->setText(QString::number((m_playListModel->data(m_playListModel->index(index, 2))).toInt(), 10));
    });

    /*qint64 duration;
    m_player->durationChanged(duration); //еще одна неудачная попытка вывести длительность
    ui->time->setVisible(true);ui->time->setText(QString::number(duration));*/


    connect(ui->btn_prev, &QToolButton::clicked, m_playlist, &QMediaPlaylist::previous);
    connect(ui->btn_next, &QToolButton::clicked, m_playlist, &QMediaPlaylist::next);


    /*
        /// коннекты для кнопок сворачивания/максимизации/минимизации/закрытия
            // Сворачивание окна приложения в панель задач
            connect(ui->btn_minimize, &QToolButton::clicked, this, &QWidget::showMinimized);
            connect(ui->btn_maximize, &QToolButton::clicked, [this](){
                // При нажатии на кнопку максимизации/нормализации окна
                // Делаем проверку на то, в каком состоянии находится окно и переключаем его режим
                if (this->isMaximized()) {
                    // Заметьте, каждый раз устанавливаем новый стиль в эту кнопку
                    ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
                    //this->layout()->setMargin(9);
                    this->showNormal();
                } else {
                    ui->btn_maximize->setStyleSheet(StyleHelper::getRestoreStyleSheet());
                   // this->layout()->setMargin(0);
                    this->showMaximized();
                }
            });
    */

            // Закрытие окна приложения
           // connect(ui->btn_close, &QToolButton::clicked, this, &QWidget::close);

}

void Widget::setPositionSlider(qint64 i) //позиция бегунка временной шкалы
{
    if (i != 0)
        ui->timeSlider->setValue(i*80 / (m_player->duration() ) );
}

QPoint Widget::previousPosition() const // предыдущая позиция курсора
{
    return m_previousPosition;
}

void Widget::setPreviousPosition(QPoint previousPosition)
{
    if (m_previousPosition == previousPosition)
        return;

    m_previousPosition = previousPosition;
    emit previousPositionChanged(previousPosition);
}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // При клике левой кнопкой мыши
    if (event->button() == Qt::LeftButton ) {
        // Определяем, в какой области произошёл клик
        m_leftMouseButtonPressed = checkResizableField(event);
        setPreviousPosition(event->pos()); // и устанавливаем позицию клика
    }
    return QWidget::mousePressEvent(event);
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    // При отпускании левой кнопки мыши сбрасываем состояние клика
    if (event->button() == Qt::LeftButton) {
        m_leftMouseButtonPressed = None;
    }
    return QWidget::mouseReleaseEvent(event);
}

void Widget::mouseMoveEvent(QMouseEvent *event) //определяение места клика мыши
{
    // При перемещении мыши, проверяем статус нажатия левой кнопки мыши
    switch (m_leftMouseButtonPressed) {
    case Move: {
        // При этом проверяем, не максимизировано ли окно
        if (isMaximized()) {
            // При перемещении из максимизированного состояния
            // Необходимо вернуть окно в нормальное состояние и установить стили кнопки
            // А также путём нехитрых вычислений пересчитать позицию окна,
            // чтобы оно оказалось под курсором
            ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
            //this->layout()->setMargin(9);
            auto part = event->screenPos().x() / width();
            this->showNormal();
            auto offsetX = width() * part;
            setGeometry(event->screenPos().x() - offsetX, 0, width(), height());
            setPreviousPosition(QPoint(offsetX, event->y()));
        } else {
            // Если окно не максимизировано, то просто перемещаем его относительно
            // последней запомненной позиции, пока не отпустим кнопку мыши
            auto dx = event->x() - m_previousPosition.x();
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x() + dx, y() + dy, width(), height());
        }
        break;
    }
    case Top: {
        // Для изменения размеров также проверяем на максимизацию
        // поскольку мы же не можем изменить размеры у максимизированного окна
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y() + dy, width(), height()- dy);
        }
        break;
    }
    case Bottom: {
        if (!isMaximized()) {
            auto dy = event->y() - m_previousPosition.y();
            setGeometry(x(), y(), width(), height() + dy);
            setPreviousPosition(event->pos());
        }
        break;
    }
    case Left: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x() + dx, y(), width() - dx, height());
        }
        break;
    }
    case Right: {
        if (!isMaximized()) {
            auto dx = event->x() - m_previousPosition.x();
            setGeometry(x(), y(), width() + dx, height());
            setPreviousPosition(event->pos());
        }
        break;
    }
    default:
        // Если курсор перемещается по окну без зажатой кнопки,
        // то просто отслеживаем в какой области он находится
        // и изменяем его курсор
        checkResizableField(event);
        break;
    }
    return QWidget::mouseMoveEvent(event);
}

Widget::MouseType Widget::checkResizableField(QMouseEvent *event) //изменение размеров экрана
{
    QPointF position = event->screenPos();  // Определяем позицию курсора на экране
    qreal x = this->x();                    // координаты окна приложения, ...
    qreal y = this->y();                    // ... то есть координату левого верхнего угла окна
    qreal width = this->width();            // А также ширину ...
    qreal height = this->height();          // ... и высоту окна

    // Определяем области, в которых может находиться курсор мыши
    // По ним будет определён статус клика
    QRectF rectTop(x + 9, y, width - 18, 7);
    QRectF rectBottom(x + 9, y + height - 7, width - 18, 7);
    QRectF rectLeft(x, y + 9, 7, height - 18);
    QRectF rectRight(x + width - 7, y + 9, 7, height - 18);
    QRectF rectInterface(x + 9, y + 9, width - 18, height - 18);

    // И в зависимости от области, в которой находится курсор
    // устанавливаем внешний вид курсора и возвращаем его статус
    if (rectTop.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Top;
    } else if (rectBottom.contains(position)) {
        setCursor(Qt::SizeVerCursor);
        return Bottom;
    } else if (rectLeft.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Left;
    } else if (rectRight.contains(position)) {
        setCursor(Qt::SizeHorCursor);
        return Right;
    } else if (rectInterface.contains(position)){
        setCursor(QCursor());
        return Move;
    } else {
        setCursor(QCursor());
        return None;
    }
}

void Widget::on_btn_close_clicked() //закрытие
{
    Widget::close();
}

void Widget::on_btn_minimize_clicked() //сворачивание
{
    Widget::showMinimized();
}
/*
void Widget::on_btn_maximize_clicked()
{
    if (this->isMaximized())
    {
        ui->btn_maximize->setStyleSheet(StyleHelper::getMaximizeStyleSheet());
        Widget::showNormal();
    }
    else
    {
        ui->btn_maximize->setStyleSheet(StyleHelper::getRestoreStyleSheet());
         Widget::showMaximized();
    }

}
*/
void Widget::on_btn_next_clicked() //следующий в плейлисте
{
    m_playlist->next();
}

void Widget::on_btn_prev_clicked() //предыдущий трек в плейлисте
{
    m_playlist->previous();
}


void Widget::on_btn_menu_clicked() //в меню пока только добавление файлов в плейлист
{
    QStringList files = QFileDialog::getOpenFileNames(this,
                                                      tr("Open files"),
                                                      QString(),
                                                      tr("Audio Files (*.mp3 *.ogg *wav)"));

    // Далее устанавливаем данные по именам и пути к файлам
    // в плейлист и таблицу отображающую плейлист
    QList<QStandardItem *> items;
    foreach (QString filePath, files) {

        items.append(new QStandardItem(QDir(filePath).dirName()));
        items.append(new QStandardItem(filePath));
        items.append(new QStandardItem(QMediaMetaData::Duration));
        m_playListModel->appendRow(items);
        m_playlist->addMedia(QUrl(filePath));
    }
    //ui->time->setVisible(true);
    //ui->time->setText(QString(items.value(0));
}

void Widget::on_btn_repeat_clicked() //повтор
{

   //connect(m_playlist, &QMediaPlaylist::playbackModeChanged(), m_playlist, &QMediaPlaylist::setPlaybackMode(QMediaPlaylist::Loop));

    if (m_playlist->playbackMode() == QMediaPlaylist::CurrentItemOnce)
    {
        m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
        ui->btn_repeat->setStyleSheet(StyleHelper::getRepeatCurrentStyleSheet());
    }
        else
        if (m_playlist->playbackMode() == QMediaPlaylist::CurrentItemInLoop)
           {
                m_playlist->setPlaybackMode(QMediaPlaylist::Loop);
                ui->btn_repeat->setStyleSheet(StyleHelper::getRepeatStyleSheet());
           }
    else
            if (m_playlist->playbackMode() == QMediaPlaylist::Loop)
           {
              m_playlist->setPlaybackMode(QMediaPlaylist::CurrentItemOnce);
              ui->btn_repeat->setStyleSheet(StyleHelper::getRepeatStyleSheet());
             }
}

void Widget::on_btn_play_clicked()
{

    if (m_player->state() == QMediaPlayer::StoppedState || m_player->state() == QMediaPlayer::PausedState )
    {
        //ui->btn_play->setIcon(QIcon("D:/Buttons/pause.jpg"));
        //ui->btn_play->setIconSize(QSize(65,65));
        m_player->play();
        ui->btn_play->setStyleSheet(StyleHelper::getPauseStyleSheet());

    }
    else
        if (m_player->state() == QMediaPlayer::PlayingState)
        {
        m_player->pause();
        ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
        }


}

void Widget::on_btn_stop_clicked()
{
    m_player->stop();
    ui->btn_play->setStyleSheet(StyleHelper::getPlayStyleSheet());
}

Widget::~Widget()
{
    delete ui;
    delete m_playListModel;
    delete m_playlist;
    delete m_player;
}

void Widget::on_btn_sound_clicked()//со звуком/без звука
{
    if (m_player->isMuted())
    {
         ui->btn_sound->setStyleSheet(StyleHelper::getSoundStyleSheet());
         m_player->setMuted(false);
         m_player->setVolume(50);
    }
    else
    {
        ui->btn_sound->setStyleSheet(StyleHelper::getMuteStyleSheet());
        m_player->setMuted(true);
    }
}

void Widget::on_soundSlider_sliderMoved(int position) //установить громкость
{

    m_player->setVolume(position);
}

void Widget::on_timeSlider_sliderMoved(int position_) //передвинуть бегунок времени на position
{
    if (m_player->isSeekable())
    {
        m_player->setPosition(1000);
    }
}
