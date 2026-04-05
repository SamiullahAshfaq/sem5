#include<iostream>
#include<pthread.h>
using namespace std;
bool flag[3] = {false, false, false}; 
int turn = 1;
int counter = 0;
void *Thread1(void* args)
{
   ////////////////////////////// cs1 //////////////////////////////
    flag[1] = true;
    turn = 2;
    while (flag[2] && turn == 2); // Entry Code
    for (int i = 0; i <= 5000000; i++)
    {
        counter++;
        if (counter % 1000000 == 0)
            cout << "Value of Counter from Thread 1 is " << counter << endl;
    }
    flag[1] = false; // Exit code
    ////////////////////////////// cs2 //////////////////////////////
    flag[1] = true;
    turn = 2;
    while (flag[2] && turn == 2); // Entry Code
    for (int i = 0; i <= 5000000; i++)
    {
        counter++;
        if (counter % 1000000 == 0)
            cout << "Value of Counter from Thread 1 is " << counter << endl;
    }
    flag[1] = false; // Exit code
    ////////////////////////////// cs3 //////////////////////////////
    flag[1] = true;
    turn = 2;
    while (flag[2] && turn == 2); // Entry Code
    for (int i = 0; i <= 5000000; i++)
    {
        counter++;
        if (counter % 1000000 == 0)
            cout << "Value of Counter from Thread 1 is " << counter << endl;
    }
    flag[1] = false; // Exit code
    pthread_exit(NULL);
}
void *Thread2(void* args)
{
    flag[2] = true;
    turn = 1;
    while(flag[1] && turn == 1); // Entry Code
    for(int i=0; i<=5000000; i++)
    {
        counter--;
        if(counter%1000000==0)
            cout<<"Value of Counter from Thread 2 is "<<counter<<endl;
    }
    flag[2] = false; //Exit code
    pthread_exit(NULL);
}
int main()
{
    pthread_t t1, t2;
    pthread_create(&t1, NULL, Thread1, NULL);
    pthread_create(&t2, NULL, Thread2, NULL);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    cout<<"The final value of counter is: "<<counter<<endl;
    return 0;
}