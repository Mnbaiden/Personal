#include <stdio.h>
/**
 * BMI = weight_kg / (height_m * height_m)
 * if BMI < 18 = underweight
 * if BMI 18 ... 25 = normal
 * if BMI 25 ... 29 = overweight
 * if BMI > 30 = obesity
 */
 int main(void)
 {
     int weight, height, bmi;

     /* Enter the Paramaters; weight and height */
     printf("Please enter your Weight(kg): \n");
     scanf("%d", &weight);
     printf("Please enter your Height (m): \n");
     scanf("%d", &height);

     bmi = weight / (height * height);
     printf("Your BMI is %d. \n", bmi);

     if (bmi < 18.5)
        printf("BMI falls within the Underweight range.\n");
     else if (bmi >= 18.5 && bmi <= 24.9)
        printf("Your BMI falls within the Healthy Weight range.\n");
     else if (bmi >= 25.0 && bmi <= 29.9)
        printf("Your BMI falls within the Overweight range.\n");
     else if (bmi > 29.9)
        printf("Your BMI falls within the Obese range.\n");
        else if (bmi >= 30.0 && bmi <= 34.9)
            printf("Class 1, Low-Risk Obesity.\n");
        else if (bmi >= 35.0 && bmi <= 39.9)
            printf("Class 2, Moderate-risk Obesity.\n");
        else
            printf("Class 3, High-risk Obesity.\n");
     return (0);
 }
