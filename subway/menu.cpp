#include "menu.h"
#include "ui_menu.h"
#include <QDesktopServices>
MainWindow* menu::mw;
//创建了一个新的窗口（主界面）

class UrlLabel: public QLabel{
    // Q_OBJECT

public:
    UrlLabel(const QUrl &url, QWidget *parent = nullptr) : QLabel(parent), url_(url) {
        // 设置标签为空文本，或者设置为透明背景的图片等
        // setText("");
        // 你可以设置固定的尺寸，或者根据需要进行调整
        // setFixedSize(100, 50); // 示例尺寸
        // 设置样式，例如背景色等
        setStyleSheet("background-image:url(:/images/src/combined.png);");
        setAlignment(Qt::AlignCenter);
    }

protected:
    QUrl url_;
    void mousePressEvent(QMouseEvent *event) override{
        // QLabel::mousePressEvent(event);
        // 打开网页
        QDesktopServices::openUrl(url_);
    }
};

menu::menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::menu)
{
    ui->setupUi(this);

    // ui->label_3->setScaledContents(true);
    // ui->label_3->setAlignment(Qt::AlignCenter);
    // ui->label_3->setStyleSheet("background-image:url(:/images/src/combined.png);");
    QString url = "https://github.com/imv05/QT";
    QLabel* background = new UrlLabel(url, this);
    background->setGeometry(1,0,875,572);
    background->lower();
    // qDebug() << children();
}

menu::~menu()
{
    delete ui;
}

void menu::on_pushButton_clicked()
{
    delete this;
    mw=new MainWindow;
    mw->show();
}


void menu::on_pushButton_2_clicked()
{
    QApplication::quit();
}

