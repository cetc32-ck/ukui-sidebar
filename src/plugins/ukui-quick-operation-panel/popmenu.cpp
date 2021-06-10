#include "popmenu.h"
#include <QProcess>
#include <QDebug>
#include <QApplication>

//extern void qt_blurImage(QImage &blurImage, qreal radius, bool quality, int transposed);

PopMenu::PopMenu(QWidget *parent)
{
    //setFixedSize(120,70);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    this->setStyleSheet("QMenu{ "
                  "background-color: rgb(255, 255, 255);"
                  "border-radius: 20px; "
                  "}"
                  "QMenu::item { background-color: transparent;"
                  "padding:3px 20px;"
                  "margin:5px 10px;"
                  "}"
                  "QMenu::item:selected { background-color: gray; }"
                  );

    
    //getTransParency();
    createAction();


}
void PopMenu::createAction()
{
    //添加菜单项，指定图标、名称、响应函数
    this->addAction(QIcon(SETTING_ICON), QStringLiteral(SETTING_NAME),this,[=](){
        QProcess p(0);
        p.startDetached("ukui-control-center");
        p.waitForStarted();
    });
    this->addSeparator();
    this->addAction(QIcon(EDIT_ICON), QStringLiteral(EDIT_NAME),this,[=](){

    });
    this->exec(QCursor::pos());//在鼠标位置显示

}

// 获取当前的透明底，并计算当前透明度匹配值
void PopMenu::getTransParency()
{
    if (QGSettings::isSchemaInstalled(UKUI_TRANSPARENCY_SETTING)) {
        m_pTransparency = new QGSettings(UKUI_TRANSPARENCY_SETTING);
        if (nullptr != m_pTransparency) {
            m_dtranSparency = m_pTransparency->get("transparency").toDouble();
            setTransParency();
            connect(m_pTransparency, &QGSettings::changed, this, [=](QString key) {
                if (key == "transparency") {
                    m_dtranSparency = m_pTransparency->get("transparency").toDouble();
                    setTransParency();
                }
            });
        }
    }
}

/* 设置当前匹配的透明度值
  设计要求，快速操作面板比通知中心透明度高0.3；
  思路如下:
  由于窗口透明度叠加，所以只能通过算比例;
  相当于100束光照进来，透明度为0.3，则剩下的光就是70束；
  在透过第二层为0.6的玻璃时，光束就只剩下28束，但是我们想要的是没有通过第一层过滤的，直接得到40束，表达式如下：
  100*(1 - 通知中心透明度) * X(所求的比例) = 100 * (1 - (通知中心透明度 + 0.3));
  当比例大于0.7小于0.9时，俩个透明度的比例差为0.1；
  当大于0.9.就直接将透明度设置为1，俩层叠加，视觉效果较明显
 */
void PopMenu::setTransParency()
{
//    qDebug() << "透明度123123213" << m_dtranSparency << 1- (m_dtranSparency + 0.3) << 1.0 - m_dtranSparency;
    if (m_dtranSparency >= 0.7 && m_dtranSparency < 0.9) {
        m_dtranSparency = (1 - (m_dtranSparency + 0.1)) / (1.0 - m_dtranSparency);
    } else if (m_dtranSparency < 0.7) {
        m_dtranSparency = (1 - (m_dtranSparency + 0.3)) / (1.0 - m_dtranSparency);
    } else {
        m_dtranSparency = 1;
    }
    return;
}

//重新绘制背景色
//void PopMenu::paintEvent(QPaintEvent *event)
//{
//    QPainter p(this);
//    p.setRenderHint(QPainter::Antialiasing);
//    QPainterPath rectPath;
//    rectPath.addRoundedRect(this->rect().adjusted(0, 8, 0, 0), 12, 12);

//    QPixmap pixmap(this->rect().size());
//    pixmap.fill(Qt::transparent);
//    QPainter pixmapPainter(&pixmap);
//    pixmapPainter.setRenderHint(QPainter::Antialiasing);
//    pixmapPainter.setPen(Qt::transparent);
//    pixmapPainter.setBrush(Qt::black);
//    pixmapPainter.drawPath(rectPath);
//    pixmapPainter.end();

//    QImage img = pixmap.toImage();
//    qt_blurImage(img, 4, false, false);

//    pixmap = QPixmap::fromImage(img);
//    QPainter pixmapPainter2(&pixmap);
//    pixmapPainter2.setRenderHint(QPainter::Antialiasing);
//    pixmapPainter2.setCompositionMode(QPainter::CompositionMode_Clear);
//    pixmapPainter2.setPen(Qt::transparent);
//    pixmapPainter2.setBrush(Qt::transparent);
//    pixmapPainter2.drawPath(rectPath);
//    p.setOpacity(m_dtranSparency);
//    p.drawPixmap(this->rect(), pixmap, pixmap.rect());
//    p.save();
//    p.fillPath(rectPath, qApp->palette().color(QPalette::Base));
//    p.restore();
//    QWidget::paintEvent(event);
//}
