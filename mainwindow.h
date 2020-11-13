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

    /* State Debug */
    void show_state();

    /* Set Variable Function */
    /* Double Variable */
    void set_first_number(double input_number = 0); // Function to set the input of First Number
    void set_second_number(double input_number = 0); // Function to set the input of Second Number Number

    /* QString Variable */
    void set_operators(QString input_string);

    /* Boolean Variable */
    void set_initial_s(bool input = false); // Function to set the input of Initial State Flag
    void set_second_number_s(bool input = false); // Function to set the input of Second Number State Flag
    void set_operation_s(bool input = false); // Function to set the input of Operation State Flag
    void set_result_s(bool input = false); // Function to set the input of Result State Flag

    /* Get Variable Function*/
    /* Double Variable */
    double get_first_number();
    double get_second_number();
    double get_answer();

    /* QString Variable */
    QString get_operators();

    /* Boolean Variable */
    bool get_initial_s();
    bool get_second_number_s();
    bool get_operation_s();
    bool get_result_s();

    /* Check Flag Function*/
    QString check_state_flag();

    /* Tesing Function */
    void test_gui_number_input(QString input_str);
    void test_gui_operators_input(QString input_str);
    void test_calculator(double input_fnum, double input_snum, QString input_operators);


private:
    const int digit = 10;
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
