//TAO HU 23655842
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <math.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#define MAX_LINES 12000
#define MAX_LEN 1000
int InpArray[12000];
int sumArra[12];//SUM   array
float productSArra[12];// root of sum square array
float GEOM_AVG[12];//GEOMETRIC_AVERAGE  array
// grandchild process 1
void *MAX_OF_SUM(void *param)//first function for SUM 
{
    sleep(1);
    int index = *(int *)(param); // deal param as int, use *(int*) instead of atoi(), because atoi we keey using 1 as int number for each thread
    int sum;
    int lower = 0;
    int upper = 1000;
    for (int j = 0; j < 12; j++)//first round save calculation result of sum[0]+...sum[999] in to int sumArra[0], 1000-1999 to sumArra[1] etc...
    {
        sum = 0;//reset sum
        for (int lower; lower < upper; lower++)
        {
            sum = sum + InpArray[lower];
        }
        lower += 1000;//increment by 1000, both upper bound and lower bound
        upper += 1000;
        sumArra[j] = sum;
    }
    printf("This thread id is:%ld and Sum of this thread number is: %d \n", pthread_self(), sumArra[index]);//get currrent thread status
    pthread_exit(0);
}


// grandchild process 2
void *ROOT_SUM_SQUARES(void *param)//2nd function for ROOT_SUM_SQUARES, As an example for 3 numbers x, y, and z:    ( x^2 + y^2 + z^2) ^ (1/2)
{
    sleep(1);
    int index = *(int *)(param); // deal param as int, use *(int*) instead of atoi(), because atoi we keey using 1 as int number for each thread

    float sqrtsum;
    int lower = 0;
    int upper = 1000;
    float RootSumSquares;
    for (int j = 0; j < 12; j++)
    { // save each sum to sumArra, example sumArra[0] is sum of orignalArray[0]-orignalArray[999], product sum of n number is array[0]/sum * array[1]/sum ... array [n]/sum
        sqrtsum = 0.00;//float number reset
        for (int lower; lower < upper; lower++)
        {
            sqrtsum = sqrtsum + InpArray[lower] * InpArray[lower]; // 0 = 0 + 344*344
        }                                                          // 344^2 = 344^2 + 176*176
        lower += 1000;//increment by 1000, both upper bound and lower bound
        upper += 1000;
        RootSumSquares = sqrt((sqrtsum));
        productSArra[j] = RootSumSquares; // number's length is too long,  so some of them displayed as negative,but we can display them in excel
    }
    printf("This thread id is:%ld and RootSumSquares of this array is: %f \n", pthread_self(), productSArra[index]);//get currrent thread status

    pthread_exit(0);
}
// grandchild process 2
void *MAX_OF_GEOM_AVG(void *param)//2nd function for MAX_OF_GEOM_AVGS, As an example for 1000 sqrt x0*x1*x2*x3...x999
{ 
    sleep(1);
    int index = atoi(param); // deal param as int
    float GEOMETRIC_AVERAGE;
    int lower = 0;
    int upper = 1000;
    for (int j = 0; j < 12; j++)//  1000√x0*x2*x3 ...x1000 = 1000√x1 * 1000√ x2 ... 1000√ x999  
    { 
        GEOMETRIC_AVERAGE = 1.0; //float number reset
        for (int lower; lower < upper; lower++)
        {
            GEOMETRIC_AVERAGE = GEOMETRIC_AVERAGE * powf(InpArray[lower], 1.0f / 1000.0f); //powf(base number ,  power of root) powf(4,1/2) = 2 becuase 2*2 = 4
        }
        lower += 1000;//increment by 1000, both upper bound and lower bound
        upper += 1000;
        GEOM_AVG[j] = GEOMETRIC_AVERAGE;
    }

    printf("This thread id is:%ld and GEOMETRIC_AVERAGE of this array is: %f \n", pthread_self(), GEOM_AVG[index]);//get currrent thread status

    pthread_exit(0);
}

void *Runner(void *param)  // 12 worker threads
{                        
    /*for 1  thread only
        sleep(1);
        int index = *(int*)(param);//deal param as int, use *(int*) instead of atoi(), because atoi we keey using 1 as int number for each thread

    //child process 1
    int sum;
    int lower = 0;//set lower bound as 0 upper bound to 1000, we split 12000 number into 12 array, each array include 1000 numbers
    int upper = 1000;
    for(int j = 0; j <12; j++){//save each sum to sumArra, example sumArra[0] is sum of orignalArray[0]-orignalArray[999]
        sum = 0;
        for(int lower; lower < upper; lower++){
            sum = sum + InpArray[lower];
        }
        lower+=1000;
        upper+=1000;
        sumArra[j] = sum;
    }

        printf("This thread id is:%ld and number is: %d \n", pthread_self(),sumArra[index]);
        pthread_exit(0);*/
    int index = *(int *)(param); // deal param as int

    int *tochild = malloc(sizeof(int));// allocate memory
    *tochild = index;
    pthread_t sumthread[3];
    pthread_t pSumthread[3];
    pthread_t gSumthread[3];
 
    // create 3 child threads under worker threads
    int i = 0;
    pthread_create(&sumthread[i], NULL, &MAX_OF_SUM, tochild); // call 3 child thread to process function
    pthread_create(&pSumthread[i], NULL, &ROOT_SUM_SQUARES, tochild);
    pthread_create(&gSumthread[i], NULL, &MAX_OF_GEOM_AVG, tochild);
    pthread_join(sumthread[i], NULL);       //join thread
    pthread_join(pSumthread[i], NULL);
    pthread_join(gSumthread[i], NULL);
    sleep(1);       //wait 

    pthread_exit(0); //12 worker threads done
}

int main(int argc, char *argv[])
{
    pthread_t th[12];///12 initilze 12 threads size

    char str[12000];//12000 number, we give 12001 buf size
    FILE *file;
    file = fopen(argv[1], "r");
    if (file == NULL)
    { // read file error, exit 
        printf("file open error.\n");
        return 1;
    }
    int wordcount = 0;
    while (fgets(str, 10, file) != NULL)
    { // read file and save 12000 chara as int into InpArray[12000]
        InpArray[wordcount] = atoi(str);
        wordcount++;
    }
    fclose(file);//read done, all number saved in to InpArray into global scope


    int i;
    for (i = 0; i < 12; i++)//create 12 worker threads
    {
        int *a = malloc(sizeof(int));
        *a = i;
        if (pthread_create(&th[i], NULL, &Runner, a) != 0) // a pass value to param
        {
            perror("Failed to created thread");//perror debug 
        }
    }
    for (i = 0; i < 12; i++)//join 12 worker threads
    {
        if (pthread_join(th[i], NULL) != 0)
        {
            perror("Failed to join thread");//perror debug 
        }
    }
    // calculate MAX of each required result by processed array in grandchild thread, they saved in global scope
    int MaxOfSum = 0; // max of sum, when new array element greater then sum, asign it to sum
    for (int k = 0; k < 12; k++)
    {
        if (MaxOfSum < sumArra[k]){
            MaxOfSum = sumArra[k];
        }
    }
    float MaxOfRoot = 0; //Max root of the sum of the squares,when new array element greater then MaxOfRoot, asign it to MaxOfRoot
    for (int k = 0; k < 12; k++)
    {
        if (MaxOfRoot < productSArra[k]){
            MaxOfRoot = productSArra[k];
        }
    }
    float MaxOfGEOM = 0;//Max geometric mean, when new array element greater then MaxOfGEOM, asign it to MaxOfGEOM
    for (int k = 0; k < 12; k++)
    {if (MaxOfGEOM < GEOM_AVG[k])
        {
            MaxOfGEOM = GEOM_AVG[k];
        }
    }
    //write output into file 
    char buf[200];//initial buffer size
    FILE *fp2;//create file 2
    fp2 = fopen("HU_23655842.out", "wb");//wb means Open for writing  
    if (fp2 == NULL)//error check,null mean open file failed 
    {
        printf("file couldn't be opened\n");
        exit(1);
    }
    for (int i = 0; i < 12; i++) // snprintf store integer and chara in to string then write into file by loop
    {
        snprintf(buf, 200, "Worker Child Pthread Number = %d : \t  Sum = %d \t  Root of the Sum of Squares = %f  \t Geometric Average = %f \n", i, sumArra[i], productSArra[i], GEOM_AVG[i]); 
        fwrite(buf, 1, strlen(buf), fp2);                                                                                                                                                     
    }
    snprintf(buf, 70, "Max of the Sums = %d\n", MaxOfSum); // puts string into buffer
    fwrite(buf, 1, strlen(buf), fp2);
    snprintf(buf, 70, "Max of the root of the sum of the squares = %f\n", MaxOfRoot); // puts string into buffer
    fwrite(buf, 1, strlen(buf), fp2);
    snprintf(buf, 70, "Max of the Geometric Averages = %f\n", MaxOfGEOM); // puts string into buffer
    fwrite(buf, 1, strlen(buf), fp2);

    char str2[] = "Terminating. \n"; //close file
    fwrite(str2, 1, strlen(str2), fp2);

    fclose(fp2);
}
