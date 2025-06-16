#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QGraphicsRectItem>
#include <QBrush>
#include <QRandomGenerator>
#include <QTimer>
#include <QThread>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_spinBox_n_valueChanged(ui->spinBox_n->value());
    on_spinBox_delay_valueChanged(ui->spinBox_delay->value());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::arrayToScene(QVector<int> & data, QSet<int> & look, QSet<int> & good, unsigned read, unsigned write, unsigned compare){
    if (abort) return;
    ui->label_read->setText(QString::number(read));
    ui->label_write->setText(QString::number(write));
    ui->label_compare->setText(QString::number(compare));

    QGraphicsView *view = ui->graphicsView;
    QGraphicsScene *scene = new QGraphicsScene(this);
    view->setScene(scene);

    int barWidth;
    if      (size <= 50)  barWidth = 20;
    else if (size <= 53)  barWidth = 19;
    else if (size <= 56)  barWidth = 18;
    else if (size <= 59)  barWidth = 17;
    else if (size <= 63)  barWidth = 16;
    else if (size <= 67)  barWidth = 15;
    else if (size <= 72)  barWidth = 14;
    else if (size <= 77)  barWidth = 13;
    else if (size <= 84)  barWidth = 12;
    else if (size <= 91)  barWidth = 11;
    else if (size <= 100) barWidth = 10;
    else if (size <= 112) barWidth =  9;
    else if (size <= 126) barWidth =  8;
    else if (size <= 144) barWidth =  7;
    else if (size <= 168) barWidth =  6;
    else if (size <= 201) barWidth =  5;
    else if (size <= 252) barWidth =  4;
    else if (size <= 336) barWidth =  3;
    else                  barWidth =  2;
    int xPos = 0;
    int height;
    int n = size;
    for (int i = 0; i < data.size(); ++i)
    {
        height = 1. * (view->height() - 10) / n * data[i];
        QGraphicsRectItem *bar = new QGraphicsRectItem(xPos, -height, barWidth, height);
        if (look.contains(i))
            bar->setBrush(QBrush(Qt::red));
        else if (good.contains(i))
            bar->setBrush(QBrush(Qt::green));
        else
            bar->setBrush(QBrush(Qt::yellow));
        scene->addItem(bar);
        xPos += barWidth;
    }
}

void MainWindow::on_spinBox_n_valueChanged(int arg1)
{
    size = arg1;
}

void MainWindow::on_comboBox_rand_activated(int index)
{
    rand = index;
}

QVector<int> MainWindow::generateVec(int n, int r){
    QVector<int> result;
    if (r == 0) {
        for (int i = 1; i <= n; ++i) {
            result.append(i);
        }
        std::random_shuffle(result.begin(), result.end());
    } else
        if (r == 1) { //low
            int number1, number2, number3;
            for (int i = 0; i < n; ++i) {
                number1 = QRandomGenerator::global()->bounded(1, n + 1);
                number2 = QRandomGenerator::global()->bounded(1, n + 1);
                number3 = QRandomGenerator::global()->bounded(1, n + 1);
                result.append(qMin(number1, qMin(number2, number3)));
            }
        } else
            if (r == 2) { //high
                int number1, number2, number3;
                for (int i = 0; i < n; ++i) {
                    number1 = QRandomGenerator::global()->bounded(1, n + 1);
                    number2 = QRandomGenerator::global()->bounded(1, n + 1);
                    number3 = QRandomGenerator::global()->bounded(1, n + 1);
                    result.append(qMax(number1, qMax(number2, number3)));
                }
            } else
                if (r == 3) {  //norm
                    int number;
                    for (int i = 0; i < n; ++i) {
                        number = QRandomGenerator::global()->bounded(1, n + 1);
                        result.append(number);
                    }
                }
    return result;

}

void MainWindow::on_spinBox_delay_valueChanged(int arg1)
{
    delay = arg1 - 1;
}

void MainWindow::on_pushButton_proc_clicked()
{
    auto a = generateVec(size, rand);
    pause = false;
    abort = false;
    if (abort == false){
        ui->comboBox_sort->setEnabled(false);
        ui->comboBox_rand->setEnabled(false);
        ui->spinBox_n->setEnabled(false);
    }
    switch(sort){
    case 0: bubble_sorter(a); break;
    case 1: cocktail_sorter(a); break;
    case 2: comb_sorter(a); break;
    case 3: insertion_sorter(a); break;
    case 4: gnome_sorter(a); break;
    case 5: counting_sorter(a); break;
    case 6: bucket_sorter(a); break;
    case 7: bogo_sorter(a); break;
    case 8: rearragement_sorter(a); break;
    case 9: tim_sorter(a); break;
    }
    if (abort == true){
        ui->comboBox_sort->setEnabled(true);
        ui->comboBox_rand->setEnabled(true);
        ui->spinBox_n->setEnabled(true);
    }
}

void MainWindow::bubble_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - 1 - i; ++j) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(j);
            look.insert(j + 1);
            if (data[j] > data[j + 1]) {
                qSwap(data[j], data[j+1]);
                w += 2;
            }
            r += 2;
            ++c;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        good.insert(size - i - 1);
    }
    good.insert(0);
    look.clear();
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}

void MainWindow::cocktail_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    int start = 0;
    int end = size - 1;
    int control = size - 1;
    int prStart, prEnd;

    while (start < end) {
        prStart = start, prEnd = end;
        for (int i = start; i < end; ++i) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i + 1);
            if (data[i] > data[i + 1]) {
                qSwap(data[i], data[i + 1]);
                control = i;
                w += 2;
            }
            r += 2;
            ++c;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }

        if (start >= end)
            break;

        end = control;
        for (int i = end; i <= prEnd; ++i) good.insert(i);

        for (int i = end; i > start; --i) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i - 1);
            if (data[i] < data[i - 1]) {
                qSwap(data[i], data[i - 1]);
                control = i;
                w += 2;
            }
            r += 2;
            ++c;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        start = control;
        for (int i = prStart; i < start; ++i) good.insert(i);
    }
    good.insert(0);
    look.clear();
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}

void MainWindow::comb_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    double factor = 1.25;
    int step = size - 1;
    while (step >= 1)
    {
        for (int i = 0; i + step < data.size(); i++)
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(i + step);
            if (data[i] > data[i + step])
            {
                qSwap(data[i], data[i + step]);
                w += 2;
            }
            r += 2;
            ++c;
            if (step / factor < 1) good.insert(i);
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        step /= factor;
    }
    look.clear();
    good.insert(size - 1);
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}

void MainWindow::insertion_sorter(QVector<int> & data){
    QSet<int> look, good, f;
    unsigned r = 0, w = 0, c = 0;
    int key;
    for (int i = 0, j; i < size; ++i) {
        f.insert(i);
        key = data[i];
        ++r;
        j = i;
        while (j > 0 && data[j - 1] > key){
            ++c;
            ++r;
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(j - 1);
            data[j] = data[j - 1];
            ++w;
            --j;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        data[j] = key;
        ++w;
    }
    look.clear();
    arrayToScene(data, look, f, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}

void MainWindow::gnome_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    int index = 0;
    while (size != 1 && index < size) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(index);
        look.insert(index - 1);
        if (index == 0)
            ++index;
        ++c;
        r += 2;
        if (data[index] >= data[index - 1])
            ++index;
        else {
            qSwap(data[index], data[index - 1]);
            w += 2;
            --index;
        }
        arrayToScene(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    look.clear();
    for (int i = 0; i < size; ++i) {
        good.insert(i);
    }
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}

void MainWindow::counting_sorter(QVector<int> & data){
    QSet<int> look, good, f;
    QMap<int, int> count;
    auto data1 = data;
    unsigned r = 0, w = 0, c = 0;

    look.clear();
    for (int i = 0; i < size; ++i) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(i);
        good.insert(i);
        ++count[data[i]];
        ++r;
        arrayToScene(data, look, f, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    look.clear();
    data.clear();
    for (int i = 0; i <= size; ++i){
        data.insert(data.cend(), count[i], i);
        w += count[i];
        if (!data.empty())
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            for (int j = 1; j <= count[i]; ++j) {
                look.insert(data.size() - j);
            }
            data1 = data;
            // data1.insert(data1.cend(), count[i], /*size - data1.size()*/0);
            arrayToScene(data1, look, f, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
    }
    look.clear();
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
void MainWindow::bucket_sorter(QVector<int> & data){
    QSet<int> look, good, f;
    unsigned r = 0, w = 0, c = 0;
    QVector<QVector <int>> bucket(10);
    int d = 1, dd = size, cnt = 0, l;
    while(dd > 0)
    {
        cnt++;
        dd /= 10;
    }
    for(int m = 0; m < cnt; m++)
    {
        for (int i = 0; i < 10; ++i) {
            bucket[i].clear();
        }
        for(int i = 0; i < size; i++)
        {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            bucket[(data[i] / d) % 10].push_back(data[i]);
            ++r;
            look.clear();
            look.insert(i);
            arrayToScene(data, look, f, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }

        l = 0;
        for(int i = 0; i < 10; i++)
        {
            for(int k = 0; k < bucket[i].size(); k++)
            {
                data[l] = bucket[i][k];
                ++l;
                ++w;
                look.clear();
                look.insert(l);
                while (pause && !abort) {
                    QCoreApplication::processEvents();
                }
                if (abort) return;
                arrayToScene(data, look, f, r, w, c);
                QCoreApplication::processEvents();
                QThread::msleep(delay);
            }
        }
        d *= 10;
        look.clear();
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        arrayToScene(data, look, f, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    for (int i = 0; i < size; ++i) {
        good.insert(i);
    }
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    QThread::msleep(delay);
    abort = true;
}
void MainWindow::bogo_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    bool correct = size == 1;
    int i = 0, j;
    while (!correct){
        good.clear();
        for (i = 0; i < size; ++i){
            look.clear();
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            j = QRandomGenerator::global()->bounded(0, size);
            look.insert(i);
            look.insert(j);
            qSwap(data[i], data[j]);
            w += 2;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        look.clear();
        --i;
        correct = true;
        while (i > 0){
            ++r;
            ++c;
            if (data[i - 1] > data[i]){
                correct = false;
                break;
            }
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            good.insert(i);
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
            --i;
        }
    }

    good.insert(i);
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
void MainWindow::rearragement_sorter(QVector<int> & data){
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    bool correct = false;
    int i, j, n, start, end;
    while (!correct)
    {
        n = data.size();
        i = n - 2;
        while (i >= 0 && data[i] >= data[i+1]) {
            i--;
        }
        if (i >= 0) {
            j = n - 1;
            while (j >= 0 && data[j] <= data[i]) {
                j--;
            }
            qSwap(data[i], data[j]);
        }
        start = i + 1;
        end = n - 1;
        while (start < end) {
            qSwap(data[start], data[end]);
            start++;
            end--;
        }
        correct = true;
        good.clear();
        i = size - 1;
        while (i > 0){
            ++r;
            ++c;
            if (data[i - 1] > data[i]){
                correct = false;
                break;
            }
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            good.insert(i);
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
            --i;
        }
    }
    good.insert(0);
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    abort = true;
}
void MainWindow::insertionSort_timsort(QVector<int> & data, int left, int right, unsigned & r, unsigned & w, unsigned & c)
{
    QSet<int> look, good;
    for (int i = left + 1, j, temp; i <= right; i++) {
        ++r;
        temp = data[i];
        j = i - 1;
        while (j >= left && data[j] > temp) {
            while (pause && !abort) {
                QCoreApplication::processEvents();
            }
            if (abort) return;
            look.clear();
            look.insert(i);
            look.insert(j - 1);
            data[j + 1] = data[j];
            j--;
            ++w;
            ++c;
            ++r;
            arrayToScene(data, look, good, r, w, c);
            QCoreApplication::processEvents();
            QThread::msleep(delay);
        }
        data[j + 1] = temp;
        ++w;
    }
}

void MainWindow::merge_timsort(QVector<int> & data, int l, int m, int r, unsigned & read, unsigned & w, unsigned & c, QSet<int> & good)
{
    QSet<int> look;
    int len1 = m - l + 1, len2 = r - m;
    int left[len1], right[len2];
    for (int i = 0; i < len1; i++){
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(l + i);
        left[i] = data[l + i];
        ++read;
        arrayToScene(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
    for (int i = 0; i < len2; i++){
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(m + 1 + i);
        right[i] = data[m + 1 + i];
        ++read;
        arrayToScene(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    int i = 0;
    int j = 0;
    int k = l;

    while (i < len1 && j < len2) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        ++c;
        ++w;
        if (left[i] <= right[j]) {
            data[k] = left[i];
            i++;
        }
        else {
            data[k] = right[j];
            j++;
        }
        k++;
        arrayToScene(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    while (i < len1) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        data[k] = left[i];
        ++w;
        k++;
        i++;
        arrayToScene(data, look, good, read, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    while (j < len2) {
        while (pause && !abort) {
            QCoreApplication::processEvents();
        }
        if (abort) return;
        look.clear();
        look.insert(k);
        ++w;
        data[k] = right[j];
        k++;
        j++;
        arrayToScene(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }
}

void MainWindow::tim_sorter(QVector<int> & data)
{
    QSet<int> look, good;
    unsigned r = 0, w = 0, c = 0;
    for (int i = 0; i < size; i += 16) {
        insertionSort_timsort(data, i, qMin((i + 16 - 1), (size - 1)), r, w, c);
        arrayToScene(data, look, good, r, w, c);
        QCoreApplication::processEvents();
        QThread::msleep(delay);
    }

    for (int size1 = 16; size1 < size; size1 = 2 * size1) {

        for (int left = 0; left < size; left += 2 * size1) {

            int mid = left + size1 - 1;
            int right = qMin((left + 2 * size1 - 1), (size - 1));

            if (mid < right)
                merge_timsort(data, left, mid, right, r, w, c, look);
        }
    }
    for (int i = 0; i < size; ++i)
        good.insert(i);
    arrayToScene(data, look, good, r, w, c);
    QCoreApplication::processEvents();
    QThread::msleep(delay);
    abort = true;
}

void MainWindow::on_comboBox_sort_activated(int index)
{
    sort = index;
}


void MainWindow::on_pushButton_pause_clicked()
{
    pause = !pause;
}


void MainWindow::on_pushButton_abort_clicked()
{
    abort = true;
}
