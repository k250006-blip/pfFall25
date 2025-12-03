#include<stdio.h>
float calculateRepayment(float loan, float interestRate, int years){
    float installment=15000, remainingLoan, interest_loan, totalrepayment=0, additional_payment, newinstallment; 
    if (years==0)
    {
        return 0;
    }
    //this will end when year bcms 0

    printf("\nEnter additional payment for year %d IF there: ",years);
    scanf("%f",&additional_payment);
    //i give amount if i want to

    //if will be executed if i enter any valid amount
    if (additional_payment<=10000 && additional_payment>=0)
    {
        newinstallment= installment+additional_payment;
        remainingLoan= loan-newinstallment;   //paid each year
        interest_loan= remainingLoan * interestRate + (remainingLoan);  //interest on remaining loan
    }
    //if no amount then this block will be executed
    else{
        newinstallment= installment;
        remainingLoan= loan-newinstallment;   //paid each year
        interest_loan= remainingLoan * interestRate + (remainingLoan);  //interest on remaining loan 
    }
    //final calc
    totalrepayment= calculateRepayment(interest_loan,interestRate,years-1); //recursion statement
    printf("\nYear %d: Remaining loan = %.2f",years,interest_loan);  //prints years with remaining loan
    return totalrepayment+newinstallment;   //function calls itself...recursion occurs
}

int main()
{
    int years=3;
    float amount=100000,rate=0.05; 
    float repay=calculateRepayment(amount,rate,years);
    printf("\nTotal Repaid loan: %.2f\n\n",repay);
    return 0;
}
