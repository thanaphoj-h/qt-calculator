#include "mainwindow.h"
#include <QApplication>
#include <QTimer>
#include "gtest/gtest.h"

#define TEST_ENABLED 1

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

#if TEST_ENABLED
    QTimer::singleShot(0, [&]()
    {
        ::testing::InitGoogleTest(&argc, argv);
        auto testResult = RUN_ALL_TESTS();
        a.exit(testResult);
    });
#endif

    return a.exec();
}

TEST(Calulator, Addition_Positive){
    QString sign = "+";
    MainWindow w;
    /* POS + POS = POS*/
    ASSERT_EQ(w.test_calculate(1,4,sign), "5");
    ASSERT_EQ(w.test_calculate(5,10,sign), "15");
    ASSERT_EQ(w.test_calculate(50,60,sign), "110");
    ASSERT_EQ(w.test_calculate(400,600,sign), "1000");
    ASSERT_EQ(w.test_calculate(8000,4000,sign), "12000");
    ASSERT_EQ(w.test_calculate(50000, 70000,sign), "120000");
    ASSERT_EQ(w.test_calculate(900000, 500000,sign), "1400000");

    /* NEG + NEG = NEG */
    ASSERT_EQ(w.test_calculate(-1,-4,sign), "-5");
    ASSERT_EQ(w.test_calculate(-5,-10,sign), "-15");
    ASSERT_EQ(w.test_calculate(-50,-60,sign), "-110");
    ASSERT_EQ(w.test_calculate(-400,-600,sign), "-1000");
    ASSERT_EQ(w.test_calculate(-8000,-4000,sign), "-12000");
    ASSERT_EQ(w.test_calculate(-50000, -70000,sign), "-120000");

    /* POS + NEG = POS */
    ASSERT_EQ(w.test_calculate(5,-1,sign), "4");
    ASSERT_EQ(w.test_calculate(60,-40,sign), "20");
    ASSERT_EQ(w.test_calculate(500,-300,sign), "200");
    ASSERT_EQ(w.test_calculate(1500,-400,sign), "1100");
    ASSERT_EQ(w.test_calculate(14000,-4000,sign), "10000");
    ASSERT_EQ(w.test_calculate(14000,-4000,sign), "10000");


    /* POS + NEG = NEG */

}

TEST(Calculator, Addtition_Negative){
    QString sign = "+";
    MainWindow w;
    /* POS + POS = ERROR (Over 8 digit) */
    ASSERT_EQ(w.test_calculate(5000000, 7000000,sign), "Display Error");
    /* NEG + NEG = ERROR (Over 8 digit) */
    ASSERT_EQ(w.test_calculate(-900000, -500000,sign), "-1400000");
}


//TEST(Calculator, Number_Input_GUI_Positive){
//    MainWindow w;
//    ASSERT_EQ(w.check_number_input("0"), "0");
//    ASSERT_EQ(w.check_number_input("1"), "1");
//    ASSERT_EQ(w.check_number_input("2"), "2");
//    ASSERT_EQ(w.check_number_input("3"), "3");
//    ASSERT_EQ(w.check_number_input("4"), "4");
//    ASSERT_EQ(w.check_number_input("5"), "5");
//    ASSERT_EQ(w.check_number_input("6"), "6");
//    ASSERT_EQ(w.check_number_input("7"), "7");
//    ASSERT_EQ(w.check_number_input("8"), "8");
//    ASSERT_EQ(w.check_number_input("9"), "9");
//    ASSERT_EQ(w.check_number_input("."), ".");
//}
//TEST(Calculator, Number_Input_GUI_Negative){
//    MainWindow w;
//    ASSERT_EQ(w.check_number_input("*"), "Invalid");
//    ASSERT_EQ(w.check_number_input("c"), "Invalid");
//}

//TEST(Calculator, Operator_Input_GUI_Positive){
//    MainWindow w;
//    ASSERT_EQ(w.check_operation_input("+"), "Plus");
//    ASSERT_EQ(w.check_operation_input("-"), "Minus");
//    ASSERT_EQ(w.check_operation_input("*"), "Multiply");
//    ASSERT_EQ(w.check_operation_input("/"), "Divide");
//    ASSERT_EQ(w.check_operation_input("C"), "Clear");
//    ASSERT_EQ(w.check_operation_input("="), "Equal");
//}
//TEST(Calculator, Operator_Input_GUI_Negative){
//    MainWindow w;
//    ASSERT_EQ(w.check_operation_input("?"), "Invalid");
//    ASSERT_EQ(w.check_operation_input("x"), "Invalid");
//}

//TEST(Calculator, Number_Input){
//    MainWindow w;
//    /* Real Number Test*/
//    ASSERT_EQ(w.test_input_number("1"), 1);
//    ASSERT_EQ(w.test_input_number("50"), 50);
//    ASSERT_EQ(w.test_input_number("16984984"), 16984984);
//    /* Decimal Test*/
//    ASSERT_FLOAT_EQ(w.test_input_number("0.1"), 0.1);
//    ASSERT_FLOAT_EQ(w.test_input_number("0..163"), 0.163);
//    ASSERT_FLOAT_EQ(w.test_input_number("0.1.2"), 0.12);
//    ASSERT_FLOAT_EQ(w.test_input_number("0.58.69.5"), 0.58695);
//}

//TEST(Calculator, Operator_Input){
//    MainWindow w;
//    ASSERT_EQ(w.test_input_operation("+"), "+");
//    ASSERT_EQ(w.test_input_operation("-"), "-");
//    ASSERT_EQ(w.test_input_operation("*"), "*");
//    ASSERT_EQ(w.test_input_operation("/"), "/");
//}

/* Arithmetic Test Case */

/* Addition Test*/
//TEST(CALCULATOR, ADDITION_INTEGER_POSITIVE_TEST_CASE){
//    MainWindow w;

//    /*Integer [Positive + Positive = Positive] */
//    ASSERT_EQ(); // 1 Digits
//    ASSERT_EQ(); // 2 Digits
//    ASSERT_EQ(); // 3 Digits
//    ASSERT_EQ(); // 4 Digits
//    ASSERT_EQ(); // 5 Digits
//    ASSERT_EQ(); // 6 Digits
//    ASSERT_EQ(); // 7 Digits
//    ASSERT_EQ(); // 8 Digits
//    ASSERT_EQ(); // 8 Digits

//    /*Integer [Negative + Positive = Positive] */
//    ASSERT_EQ(); // 1 Digits
//    ASSERT_EQ(); // 2 Digits
//    ASSERT_EQ(); // 3 Digits
//    ASSERT_EQ(); // 4 Digits
//    ASSERT_EQ(); // 5 Digits
//    ASSERT_EQ(); // 6 Digits
//    ASSERT_EQ(); // 7 Digits
//    ASSERT_EQ(); // 8 Digits
//    ASSERT_EQ(); // 8 Digits

//    /*Integer [Negative + Positive = Negative] */
//    ASSERT_EQ(); // 1 Digits
//    ASSERT_EQ(); // 2 Digits
//    ASSERT_EQ(); // 3 Digits
//    ASSERT_EQ(); // 4 Digits
//    ASSERT_EQ(); // 5 Digits
//    ASSERT_EQ(); // 6 Digits
//    ASSERT_EQ(); // 7 Digits
//    ASSERT_EQ(); // 8 Digits
//    ASSERT_EQ(); // 8 Digits
//}

//TEST(Calculatorn, ADDITION_INTEGER_NEGATIVE_TEST_CASE){
//    MainWindow w;
//    /*Integer [Positive + Positive = Positive] */
//    ASSERT_EQ(); // 9 Digits

//    /*Integer [Negative + Positive = Positive] */
//    ASSERT_EQ(); // 9 Digits

//    /*Integer [Negative + Positive = Negative] */
//    ASSERT_EQ(); // 9 Digits
//}

//TEST(Calculator, Add){
//    QString sign = "+";

//    MainWindow w;
//    /* Number Test*/
//    ASSERT_EQ(w.test_calculate_result(200, 565,sign), 765); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(627, 9758,sign), 10385); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(-54441, 94020,sign), 39579); // Neg + Pos
//    ASSERT_EQ(w.test_calculate_result(-79244, 12318,sign), -66926); // Neg + Pos

//    /* Decimal Test */
//    ASSERT_FLOAT_EQ(w.test_calculate_result(79.183, 9.51790,sign), 88.7009); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(9.00598, 66.2611,sign), 75.26708); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-23.7278, 871.406,sign), 847.6782); // Neg + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-357.756, 87.1533,sign), -270.6027); // Neg + Pos
//}

//TEST(Calculator, Subtract){
//    QString sign = "-";

//    MainWindow w;
//    /* Number Test*/
//    ASSERT_EQ(w.test_calculate_result(100, 8,sign), 92); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(9758, 627,sign), 9131); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(-54441, 94020,sign), -148461); // Neg + Pos
//    ASSERT_EQ(w.test_calculate_result(-79244, 12318,sign), -91562); // Neg + Pos

//    /* Decimal Test */
//    ASSERT_FLOAT_EQ(w.test_calculate_result(79.183, 9.51790,sign), 69.6651); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(9.00598, 66.2611,sign), -57.25512); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-23.7278, 871.406,sign), -895.1338); // Neg + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-357.756, 87.1533,sign), -444.9093); // Neg + Pos
//}

//TEST(Calculator, Multiply){
//    QString sign = "*";

//    MainWindow w;
//    /* Number Test*/
//    ASSERT_EQ(w.test_calculate_result(10, 9,sign), 90); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(9758, 627,sign), 6118266); // Pos + Pos
//    ASSERT_EQ(w.test_calculate_result(-5441, 920,sign), -5005720); // Neg + Pos
//    ASSERT_EQ(w.test_calculate_result(-7944, 121,sign), -961224); // Neg + Pos

//    /* Decimal Test */
//    ASSERT_FLOAT_EQ(w.test_calculate_result(79.183, 9.51790,sign), 753.65588); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(9.00598, 66.2611,sign), 596.74614); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-23.7278, 81.406,sign), -1931.58529); // Neg + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-357.756, 87.1533,sign), -31179.61599); // Neg + Pos
//}

//TEST(Calculator, Divide){
//    QString sign = "/";

//    MainWindow w;
//    /* Number Test*/
//    ASSERT_FLOAT_EQ(w.test_calculate_result(5, 2,sign), 2.5); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(6305, 200,sign),31.525); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-520, 5,sign), -104); // Neg + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-7944, 121,sign), -65.652897); // Neg + Pos

//    /* Decimal Test */
//    ASSERT_FLOAT_EQ(w.test_calculate_result(79.183, 9.51790,sign), 8.31938); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(9.00598, 6.2611,sign), 1.4384022); // Pos + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-23.7278, 81.406,sign), -0.29147482); // Neg + Pos
//    ASSERT_FLOAT_EQ(w.test_calculate_result(-357.756, 87.1533,sign), -4.1049047); // Neg + Pos
//}

/* State test case */
//TEST(Calculator, state){
//    MainWindow w;
//    /* Initial State Test */
//    ASSERT_EQ(w.test_state("T1"), "Get_First_Num_State");
//    ASSERT_EQ(w.test_state("T2"), "Initial_State");
//    ASSERT_EQ(w.test_state("T3"), "Initial_State");

//    /* Clear State Test*/
//    ASSERT_EQ(w.test_state("T6"), "Initial_State");
//    ASSERT_EQ(w.test_state("T7"), "Initial_State");
//    ASSERT_EQ(w.test_state("T8"), "Initial_State");
//    ASSERT_EQ(w.test_state("T9"), "Initial_State");

//    /* Get Number Test*/
//    ASSERT_EQ(w.test_state("T4"), "Get_Operation_State");
//    ASSERT_EQ(w.test_state("T5"), "Get_Result_State");

//    /*Get Operation test*/
//    ASSERT_EQ(w.test_state("T10"), "Get_Second_Number_State");
//}

