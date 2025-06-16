#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_spinBox_n_valueChanged(int arg1);

    void on_comboBox_rand_activated(int index);

    void on_pushButton_proc_clicked();

    void on_spinBox_delay_valueChanged(int arg1);

    void on_comboBox_sort_activated(int index);

    void on_pushButton_pause_clicked();

    void on_pushButton_abort_clicked();

private:
    Ui::MainWindow *ui;
    void arrayToScene(QVector<int> &, QSet<int> &, QSet<int> &, unsigned, unsigned, unsigned);
    QVector<int> generateVec(int, int);
    int size, rand = 0, delay = 10, sort = 0;
    bool pause = false, abort = false;
    void bubble_sorter(QVector<int> &);
    void cocktail_sorter(QVector<int> &);
    void comb_sorter(QVector<int> &);
    void insertion_sorter(QVector<int> &);
    void gnome_sorter(QVector<int> &);
    void counting_sorter(QVector<int> &);
    void bucket_sorter(QVector<int> &);
    void bogo_sorter(QVector<int> &);
    void rearragement_sorter(QVector<int> &);
    void tim_sorter(QVector<int> &);
    void merge_timsort(QVector<int> & data, int l, int m, int r, unsigned &, unsigned &, unsigned &, QSet<int> &);
    void insertionSort_timsort(QVector<int> &, int, int, unsigned &, unsigned &, unsigned &);
};
#endif // MAINWINDOW_H
