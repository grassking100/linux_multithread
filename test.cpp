#include <stdio.h>
#include <pthread.h>
#include <random>
#include <unistd.h>

struct InputData{
    static const int SIZE=5;
    int id;
    int arr[SIZE];
    InputData(){
        id=0;
        for(int i = 0;i<SIZE;i++) arr[i] = 0;
    }
    InputData(int id_){
        id = id_;
    }
};

void* calc_sum(void *args)
{
    InputData *ptr =  (InputData*)args;
    int result = 0;
    for(int i = 0;i<ptr->SIZE;i++){
        result += ptr->arr[i];
    }
    sleep(rand()%5);
    printf("Sleep and calculate summation of data[%d]: %d\n",ptr->id,result);
    
    pthread_exit((void *) result);
}

int main()
{
    const int NUM = 10;
    pthread_t ids[NUM];
    int result[NUM];
    InputData input_data_list[NUM];
    int status;
    printf("Create 10 random integer list of size 5(from 0 to 9)\n");
    for(int i = 0 ;i<NUM;i++){
        input_data_list[i] = InputData(i);
        for(int j = 0;j<input_data_list[i].SIZE;j++){
            input_data_list[i].arr[j] = rand()%10;
        }
        status = pthread_create(&ids[i],NULL,calc_sum,&input_data_list[i]);
        if(status!=0)
        {
            printf("Create pthread error!\n");
            return 1;
        }
    }
    for(int i = 0 ;i<NUM;i++){
        pthread_join(ids[i],(void**)&result[i]);
    }
    printf("Get result\n");
    for(int i = 0 ;i<NUM;i++){
        printf("Result[%d]: %d\n",input_data_list[i].id,result[i]);
    }
    return 0;
}
