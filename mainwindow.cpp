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
    if(result_s == true){
        /* Process After get 1st result */
        result_s = false; // set result state back to true
        if(operator_s == true){
            /* If got result and pressed the operation*/
            first_number = answer; // Set first number as result number
            snum_s = true; // set second number state to true
        }
        else{
            /* If got result and not pressed the operation */
            snum_s = false;  // Set second number input to true
            first_number = input_number; // set first number from input number (from number_append function)
        }
    }
    else{
        /* Process before get 1st result */
        if(fnum_s == false && snum_s == true ){
            /* Operation is insert and waiting for second number */
            second_number = input_number; // set second number from input number (from number_append function)
            show_state();
        }
        else if(fnum_s == true && snum_s == false){
            first_number = input_number; // set first number from input number (from number_append function)
            show_state();
        }
        else{
            // Impossible to get to this condition
        }
    }
}

void MainWindow::check_operator(QString op_input){
    if(initial_s == false){
        QString display_sign;
        /* Add Operation */
        if(op_input == "+"){
            operators = op_input;
            display_sign = op_input;
            operator_s = true;
            fnum_s = false;
            snum_s = true;
        }
        /* Subtract operation */
        else if (op_input == "-"){
            operators = op_input;
            display_sign = op_input;
            operator_s = true;
            snum_s = true;
        }
        /* Multiply operation */
        else if (op_input == "x"){
            operators = "*";
            display_sign = "x";
            operator_s = true;
            snum_s = true;
        }
        /* Divide operation */
        else if (op_input == "÷"){
            operators = "/";
            display_sign = "÷";
            operator_s = true;
            snum_s = true;
        }
        /* Equal operation */
        else if (op_input == "="){
            operator_s = true;
            snum_s = true;
            Calculate();
        }
        /* Clear operation */
        else if (op_input == "C"){
            operator_s = false;
            snum_s = false;
            Initial();
        }
        /* Plus/Minus Operation */
        else if(op_input == "+/-"){
            operator_s = false;
            plus_minus();
        }
        else{

        }
        str_input_number = "";
        set_operator_display(display_sign);
        show_state();
    }
    else{
        set_main_display("Initial State");
        Initial();
    }
}

void MainWindow::Initial(){
    /* Set Flag to Initial*/
    initial_s = true;
    fnum_s = true;
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

    show_state();

}

void MainWindow::plus_minus(){
    if(initial_s == false){
        if(fnum_s == true && snum_s == false){
            /* Second Number not get */
            first_number = first_number * -1;
            set_main_display(QString::number(first_number));
        }
        else if(fnum_s == false && snum_s == true){
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
    if(operator_s == true && snum_s == true){ // Check Nhave operator
        operator_s = false; // Clear Operator Flag
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
    }
    else{
        set_main_display("Inset OP");
    }
}


/* Testing Section */
void MainWindow::show_state(){

    qDebug() << "[INI / OP / SNUM / RES ] -> " << initial_s << operator_s << snum_s << result_s;
    if(initial_s == true && operator_s == false && snum_s == false && result_s == false){
        qDebug() << "[Initial State]";
    }
    else if(initial_s == false && operator_s == false && snum_s == false && result_s == false){
        qDebug() << "[Get 1st Number State]";
    }
    else if(initial_s == false && operator_s == true && snum_s == true && result_s == false){
        qDebug() << "[Get Operation State]";
    }
}

///* <!--- Function for testing ---!>*/

///* SET value Function*/
//void MainWindow::set_first_number(double input_num){
//    first_number = input_num;
//}
//void MainWindow::set_second_number(double input_num){
//    second_number = input_num;
//}
//void MainWindow::set_initial_s(bool init){
//    initial_s = init;
//}
//void MainWindow::set_operator_s(bool op){
//    operator_s = op;
//}
//void MainWindow::set_snum_s(bool snum){
//    snum_s = snum;
//}
//void MainWindow::set_result_s(bool res){
//    result_s = res;
//}
//void MainWindow::set_state(bool init, bool op, bool snum, bool res){
//    initial_s = init;
//    operator_s = op;
//    snum_s = snum;
//    result_s = res;
//}

///* GET value Function */
//bool MainWindow::get_initial_s(){
//    return initial_s;
//}
//bool MainWindow::get_operator_s(){
//    return operator_s;
//}
//bool MainWindow::get_snum_s(){
//    return snum_s;
//}
//bool MainWindow::get_result_s(){
//    return result_s;
//}
//double MainWindow::get_result_number(){
//    return result_number;
//}
//QString MainWindow::get_str_input_number(){
//    return str_input_number;
//}
//QString MainWindow::get_operation(){
//    return operation;
//}

///* Test Function */
//QString MainWindow::check_number_input(QString input_num){
//    QString input = input_num;
//    if(input == "0"){
//        return "0";
//    }
//    else if(input == "1"){
//        return "1";
//    }
//    else if(input == "2"){
//        return "2";
//    }
//    else if(input == "3"){
//        return "3";
//    }
//    else if(input == "4"){
//        return "4";
//    }
//    else if(input == "5"){
//        return "5";
//    }
//    else if(input == "6"){
//        return "6";
//    }
//    else if(input == "7"){
//        return "7";
//    }
//    else if(input == "8"){
//        return "8";
//    }
//    else if(input == "9"){
//        return "9";
//    }
//    else if(input == "."){
//        return ".";
//    }
//    else{
//        return "Invalid";
//    }
//}

//QString MainWindow::check_operation_input(QString input_operation){
//    QString input = input_operation;
//    if(input == "+"){
//        return "Plus";
//    }
//    else if(input == "-"){
//        return "Minus";
//    }
//    else if(input == "*"){
//        return "Multiply";
//    }
//    else if(input == "/"){
//        return "Divide";
//    }
//    else if(input == "C"){
//        return "Clear";
//    }
//    else if(input == "="){
//        return "Equal";
//    }
//    else{
//        return "Invalid";
//    }
//}

//double MainWindow::test_input_number(QString input_number){
//    QString input = input_number;

//    //    number_append(input);
//    int len_input = input.size() - 1;

//    for(int i = 0; i <= len_input; i++){
//        number_append(input.data()[i]);
//    }
//    str_input_number = "";
//    return final_input_number;
//}

//QString MainWindow::test_input_operation(QString input_operation){
//    QString input = input_operation;
//    operation_append(input);
//    return operation;
//}

//double MainWindow::test_calculate_result(double fnum, double snum, QString op){

//    /* Set State for testing*/
//    initial_s = false;
//    operation = true;

//    /* Set Variable for test */
//    QString input = "=";
//    first_number = fnum;
//    second_number = snum;
//    operation = op;

//    /* Test Function*/
//    calculate_result(input);

//    return result_number;
//}

//QString MainWindow::state_checker(){
//    if(initial_s == true && operator_s == false && snum_s == false && result_s == false){
//        return "initial_s";
//    }
//    else if(initial_s == false && operator_s == false && snum_s == false && result_s == false){
//        return "Get_First_Num_State";
//    }
//    else if(initial_s == false && operator_s == true && snum_s == true && result_s == false){
//        return "Get_operator_s";
//    }
//    else if(initial_s == false && operator_s == true && snum_s == false && result_s == false){
//        return "Get_snum_s";
//    }
//    else if(initial_s == false && operator_s == false && snum_s == true && result_s == true){
//        return "Get_result_s";
//    }
//    else{
//        return "Invalid_State";
//    }
//}

//QString MainWindow::test_state(QString test_case){
//    QString input = test_case;
//    if(input == "T1"){ /* Initi -> get_number */
//        number_append("10"); // Input Number to test
//        return state_checker();
//    }
//    else if(input == "T2"){ /* Initi -> Clear */
//        Initial("C"); // Use Clear to test
//        return state_checker();
//    }
//    else if(input == "T3"){ /* Initi -> get_result */
//        calculate_result("="); // Use Clear to test
//        return state_checker();
//    }
//    else if(input == "T4"){ /*get_number -> get_operation*/
//        number_append("10");
//        operation_append("+");
//        return state_checker();
//    }
//    else if(input == "T5"){ /*get_second_number -> get_result */

//        number_append("10");
//        operation_append("+");
//        number_append("10");
//        calculate_result("=");

//        return state_checker();
//    }

//    /*Clear State*/
//    else if(input == "T6"){
//        number_append("10");
//        Initial("C");
//        return state_checker();
//    }
//    else if(input == "T7"){
//        number_append("10");
//        operation_append("+");
//        Initial("C");
//        return state_checker();
//    }
//    else if(input == "T8"){
//        number_append("10");
//        operation_append("+");
//        number_append("10");
//        Initial("C");
//        return state_checker();
//    }
//    else if(input == "T9"){ /**/
//        number_append("10");
//        operation_append("+");
//        number_append("10");
//        calculate_result("=");
//        Initial("C");
//        return state_checker();
//    }

//    /* Operation State*/

//    else if(input == "T10"){
//        set_state(false, true, true, false);
//        number_append("10");
//        return state_checker();
//    }
//}
