#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /* Set testing function*/
    void set_first_number(double input = 0);
    void set_second_number(double input = 0);
    void set_initial_s(bool input = false);
    void set_operators(bool input = false);
    void set_snum_s(bool input = false);
    void set_result_(bool input = false);

    /* Get testing function */
    double get_first_number();
    double get_second_number();
    double get_answer();
    QString get_operators();
    bool get_initial_s();
    bool get_operator_s();
    bool get_snum_s();
    bool get_result_();

    /* Testing Function */
    QString test_calculate(double fnum, double snum , QString sign); // Calculate testing
    QString check_state_flag(); // flag checking
    QString test_state_flag(QString input); // testing function for flag
    QString check_operation_input(QString input_operators); // testing function for testing input number
    QString check_number_input(QString input_num); // testing function for testing input operation

private:
    const int digit = 8;
    const int precision = 5;
    Ui::MainWindow *ui;

    /* Number Variable double and string */
    double first_number = 0;
    double second_number = 0;
    double answer = 0;
    double final_input_number = 0;

    QString str_input_number;
    QString str_prv_number;
    QString str_answer;
    QString operators;

    /* State Check Variable */
    bool initial_s = false;
    bool operator_s = false;
    bool snum_s = false;
    bool result_s = false;

    /* Append text to number */
    void number_append(QString input_number);

    /* Check the operation */
    void check_operator(QString op_input);

    /* Check 1st number, 2nd number and result*/
    void check_number_state(double input_number);
    QString check_result_precision(double input_number);

    /* Core Function */
    void Initial(); // Initial State
    void Calculate(); // Calculate State
    void plus_minus(); // Plus and Minus Function

    /* set display function */
    void set_main_display(QString input_str);
    void set_operator_display(QString input_str);


private slots:
    /* send number from gui */
    void send_number();
    void send_operator();

};

#endif // MAINWINDOW_H
