#include "drawcontour.h"
#include "./ui_widget_contour.h"

DrawContour::DrawContour(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DrawContour)
{
    ui->setupUi(this);
    label = new Label(ui->frame_label);
    label->setGeometry(0,0,ui->frame_label->width()-1,
                       ui->frame_label->height()-1);
    label->setStyleSheet("QLabel{border-style:solid;border-width:1px;}");

    connect(ui->pushButton_clear, &QPushButton::clicked, label, &Label::clear);


    connect(ui->pushButton_open,&QPushButton::clicked,this,[this]{
       file = QFileDialog::getOpenFileName(this,"file",".","all files(*.*)");
       if(file.isNull()) return;
       label->img.load(file);
    });



    connect(ui->pushButton_save,&QPushButton::clicked,this,[this]{
        std::vector<std::vector<cv::Point>> c;

        //QMap->QList->vector
        for (int i = 0; i < label->contours.size(); i++) {
            std::vector<cv::Point> data;
            QList curr = label->contours[i];
            for (int j = 0; j < curr.size(); j++) {
                data.push_back(cv::Point(curr[j].x(), curr[j].y()));
            }
            c.push_back(data);
        }

        cv::Mat img = cv::imread(file.toStdString());

        cv::Mat mask(img.rows, img.cols, CV_8UC1,cv::Scalar(0));
        cv::drawContours(mask,c,-1,cv::Scalar(255),-1);
        cv::Mat out;
        img.copyTo(out, mask);

        cv::cvtColor(out, out, 6);
        cv::threshold(out, out, 1, 255, cv::THRESH_BINARY);
        std::vector<std::vector<cv::Point>> contour;
        cv::Mat t;
        cv::findContours(out, contour, cv::noArray(), cv::RETR_EXTERNAL, cv::CHAIN_APPROX_NONE);
        for (size_t i = 0; i < contour.size(); i++)
        {
            cv::Rect area_rectx = cv::boundingRect(contour[i]);
            t = img(area_rectx);
            cv::imwrite("C:\\Users\\DongSheng\\Desktop\\err\\test"+std::to_string(i+1) + ".bmp", t);
        }
        
    });
}

DrawContour::~DrawContour()
{
    delete ui;
}

