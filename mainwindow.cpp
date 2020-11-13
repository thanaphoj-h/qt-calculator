#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <iomanip>
#include <QLabel>
#include <QPushButton>
#include <QDebug>
#include <QAbstractButton>
#include <QLocale>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /* pad Number */
    connect(ui->pad_0,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_1,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_2,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_3,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_4,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_5,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_6,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_7,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_8,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_9,SIGNAL(released()),this,SLOT(send_number()));
    connect(ui->pad_decimal,SIGNAL(released()),this,SLOT(send_number()));

    /* Pad Operator */
    connect(ui->pad_add,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_minus,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_multipy,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_divide,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_clear,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_equal,SIGNAL(released()),this,SLOT(send_operator()));
    connect(ui->pad_plus_minus,SIGNAL(released()),this,SLOT(send_operator()));

    /* Set Start Applicaiotn to Initial State*/
    Initial();

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::send_number(){
    QPushButton* button = (QPushButton*)sender(); // Check which button is push
    QString input = button->text(); // Get the text from push button
    number_append(input);
}

void MainWindow::send_operator(){
    QPushButton* button = (QPushButton*)sender(); // Check which button is push
    QString input = button->text(); // Get the text from push button
    check_operator(input);
}

/* Set display Function*/
void MainWindow::set_main_display(QString input_str){
    ui->main_display->setText(input_str);
}
void MainWindow::set_operator_display(QString input_str){
    ui->operation_display->setText(input_str);
}

/* Number Input Process */
void MainWindow::number_append(QString input_number){
    /* if input number chnage the initial state */
    initial_s = false;

    /* Get stiring and Merge String */
    if(str_input_number.size() >= digit){
        /* Number is over 10 digits */
        str_input_number = str_prv_number; // set number to equal previous number (number at 10 digits)
    }
    else{
        /* Number less than 10 digits */
        if(input_number == "."){
            /* Input found "." Decmial */
            if(str_input_number.contains(".")){
                /* If Input already contain "." Decimal */
                str_input_number = str_input_number; // Use same input as previous
            }
            else{
                /* Input still not contain "." decimal */
                str_input_number += input_number; // Append Number to input number
                str_prv_number = str_input_number; // Copy the current number to previous number
            }
        }
        else{
            /* Input not found "." decimal */
            str_input_number += input_number; // Append Number to input Number
            str_prv_number = str_input_number; // Copy the current number to previous number
        }
    }
    set_main_display(str_input_number); // Display Input
    final_input_number = str_input_number.toDouble(); // Convert String input to double
    check_number_state(final_input_number); // Send number to next process (Check number state)
}

void MainWindow::check_number_state(double input_number){
    if(initial_s == false && fnum_s == false && snum_s == false && operator_s == false && result_s == true){
        result_s = false; // set result state back to true
        if(operator_s == true){
            /* If got result and pressed the operation*/
            first_number = answer; // Set first number as result number
            snum_s = true; // set second number state to true
            check_state_flag();
        }
        else{
            /* If got result and not pressed the operation */
            snum_s = false;  // Set second number input to true
            first_number = input_number; // set first number from input number (from number_append function)
            check_state_flag();
        }
    }
    else{
        /* Process before get 1st result */
        if(initial_s == false && fnum_s == false && snum_s == false && operator_s == true && result_s == false){
            operator_s = false;
            snum_s = true;
            /* Operation is insert and waiting for second number */
            second_number = input_number; // set second number from input number (from number_append function)
            check_state_flag();
        }
        else if(initial_s == true && fnum_s == false && snum_s == false && operator_s == false && result_s == false){
            initial_s = false;
            fnum_s = true;
            first_number = input_number; // set first number from input number (from number_append function)
            check_state_flag();
        }
        else{
            // Impossible to get to this condition
        }
    }
}

void MainWindow::check_operator(QString op_input){
    if(initial_s == false && fnum_s == true && snum_s == false && operator_s == false && result_s == false){
        QString display_sign;
        fnum_s = false;
        /* Add Operation */
        if(op_input == "+"){
            operators = op_input;
            display_sign = op_input;
            operator_s = true;
        }
        /* Subtract operation */
        else if (op_input == "-"){
            operators = op_input;
            display_sign = op_input;
            operator_s = true;
        }
        /* Multiply operation */
        else if (op_input == "x"){
            operators = "*";
            display_sign = "x";
            operator_s = true;
        }
        /* Divide operation */
        else if (op_input == "÷"){
            operators = "/";
            display_sign = "÷";
            operator_s = true;
        }
        /* Plus/Minus Operation */
        else if(op_input == "+/-"){
            plus_minus();
        }
        /* Clear Operation */
        else if(op_input == "C"){
            Initial();
        }
        else{

        }
        str_input_number = "";
        set_operator_display(display_sign);
        check_state_flag();
    }
    else if(initial_s == false && fnum_s == false && snum_s == true && operator_s == false && result_s == false){
        /* Equal operation */
        if(op_input == "="){
            Calculate();
        }
        /* Clear Operation */
        else if(op_input == "C"){
            Initial();
        }
    }
    else if(op_input == "C"){
        Initial();
    }
    else{
        set_main_display("Initial State");
        Initial();
    }
}

void MainWindow::Initial(){
    /* Set Flag to Initial*/
    initial_s = true;
    fnum_s = false;
    snum_s = false;
    operator_s = false;
    result_s = false;

    /* Clear Display */
    set_main_display("0"); // Clear main display
    set_operator_display(" "); // clear operation display

    /* Clear First Number, Second Number and Output */
    first_number = 0; // Clear First Number
    second_number = 0; // Clear Second Number
    answer = 0; // Clear Result Number

    str_input_number = "";

    /* Clear Operation*/
    operators = ""; // Clear operation variable;

    check_state_flag();

}

void MainWindow::plus_minus(){
    if(initial_s == false){
        if(snum_s == false){
            /* Second Number not get */
            first_number = first_number * -1;
            set_main_display(QString::number(first_number));
        }
        else if(snum_s == true){
            /* get second Number */
            second_number = second_number * -1;
            set_main_display(QString::number(second_number));
        }
        else{
            // Impossible to get this condition
        }
    }
    else{
        set_main_display("Insert Number");
    }
}

QString MainWindow::check_result_precision(double input_number){
    /* Find fraction and Fraction size*/
    double int_part, fraction_part;
    fraction_part = modf(input_number, &int_part);
    double fraction_size = QString::number(fraction_part).size() - 2;
    //    qDebug() << "Fraction :" << fraction_part << "| Fraction size :" << fraction_size - 2;

    if(input_number > 999999999){
        /*Input have more than 10 digit*/
        return "Display Error";
    }
    else{
        if(fraction_part == 0){
            /* Not have Fraction */
            return QString::number(input_number, 'f', 0);
        }
        else{
            /* Have Fraction */
            if(fraction_size > 5){
                /* Fraction more than 5 digit */
                return QString::number(input_number, 'f', 5);
            }
            else{
                /* Fraction less than 5 digit */
                return QString::number(input_number, 'f', fraction_size);
            }
        }
    }
}

void MainWindow::Calculate(){
    if(initial_s == false && fnum_s == false && snum_s == true && operator_s == false && result_s == false){ // Check Nhave operator
        snum_s = false;
        str_input_number = ""; // Clear str_input_number
        if(operators == "+"){
            answer = first_number + second_number;
            str_answer = check_result_precision(answer);
            result_s = true;
        }
        else if(operators == "-"){
            answer = first_number - second_number;
            str_answer = check_result_precision(answer);
            result_s = true;
        }
        else if(operators == "*"){
            answer = first_number * second_number;
            str_answer = check_result_precision(answer);
            result_s = true;

        }
        else if(operators == "/"){
            if(second_number == 0){
                /* Check Second Number equal to 0 (Number divide by 0 is INF.) */
                str_answer = "Math Error";
                Initial();
            }
            else{
                /* Second number is equal to 0 */
                answer = first_number / second_number;
                str_answer = check_result_precision(answer);
                result_s = true;
            }
        }
        else{
            result_s = false;
        }
        set_main_display(str_answer);
        check_state_flag();
    }
    else{
        set_main_display("Inset OP");
    }
}

/* Testing Section */
/* Set Variable Function */
void MainWindow::set_first_number(double input_number){ first_number = input_number; }
void MainWindow::set_second_number(double input_number){ second_number = input_number; }
void MainWindow::set_operators(QString input_string){ operators = input_string; }
void MainWindow::set_initial_s(bool input){ initial_s = input; }
void MainWindow::set_second_number_s(bool input){ snum_s = input; }
void MainWindow::set_operation_s(bool input){ operators = input; }
void MainWindow::set_result_s(bool input){ result_s = input; }

/* GET Variable Function*/
double MainWindow::get_answer(){ return answer; }
double MainWindow::get_first_number(){ return first_number; }
double MainWindow::get_second_number(){ return second_number; }
QString MainWindow::get_operators(){ return operators; }
bool MainWindow::get_initial_s(){ return initial_s; }
bool MainWindow::get_second_number_s(){ return snum_s; }
bool MainWindow::get_operation_s(){ return operator_s; }
bool MainWindow::get_result_s(){ return result_s; }

/* Testing Function */
QString MainWindow::check_state_flag(){
    QString output = "";

    qDebug("INI : %d | FNUM : %d | SNUM : %d | OP : %d | RES : %d ", initial_s, fnum_s, snum_s, operator_s, result_s);

    if(initial_s == true && fnum_s == false && snum_s == false && operator_s == false && result_s == false){
        output = "Initial State";
    }
    else if(initial_s == false && fnum_s == true && snum_s == false && operator_s == false && result_s == false){
        output = "First Number State";
    }
    else if(initial_s == false && fnum_s == false && snum_s == false && operator_s == true && result_s == false){
        output = "Operator State";
    }
    else if(initial_s == false && fnum_s == false && snum_s == true && operator_s == false && result_s == false){
        output = "Second Number State";
    }
    else if(initial_s == false && fnum_s == false && snum_s == false && operator_s == false && result_s == true){
        output = "Calculate State";
    }
    qDebug() << output;
    return output;
}
