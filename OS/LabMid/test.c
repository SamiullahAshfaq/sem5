#include <stdio.h>                                                              
                                                                                
#include <stdlib.h>                                                             
                                                                                
#include <unistd.h>                                                             
                                                                                
                                                                                
                                                                                
void perform_arithmetic(int num1, int num2) {                                   
                                                                                
    printf("Arithmetic operation performed by child 1: %d + %d = %d\n", num1,   
num2, num1 + num2);                                                             
                                                                                
}                                                                               
                                                                                
                                                                                
                                                                                
int main() {                                                                    
                                                                                
    pid_t pid1, pid2;                                                           
                                                                                
                                                                                
                                                                                
    // Create the first child process                                           
                                                                                
    pid1 = fork();                                                              
                                                                                
    if (pid1 == -1) {                                                           
                                                                                
        perror("fork");                                                         
                                                                                
        exit(1);                                                                
                                                                                
    } else if (pid1 == 0) {                                                     
                                                                                
                                                                                                                                                                                              
        printf("Enter two numbers for arithmetic operation: ");                                                                                                                               
                                                                                                                                                                                              
        scanf("%d %d", &num1, &num2);                                                                                                                                                         
                                                                                                                                                                                              
        perform_arithmetic(num1, num2);                                                                                                                                                       
                                                                                                                                                                                              
        exit(0);                                                                                                                                                                              
                                                                                                                                                                                              
    }                                                                                                                                                                                         
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
    // Create the second child process                                                                                                                                                        
                                                                                                                                                                                              
    pid2 = fork();                                                                                                                                                                            
                                                                                                                                                                                              
    if (pid2 == -1) {                                                                                                                                                                         
                                                                                                                                                                                              
        perror("fork");                                                                                                                                                                       
                                                                                                                                                                                              
        exit(1);                                                                                                                                                                              
                                                                                                                                                                                              
    } else if (pid2 == 0) {                                                                                                                                                                   
                                                                                                                                                                                              
        char dir_name[] = "new_directory";                                                                                                                                                    
                                                                                                                                                                                              
        mkdir(dir_name, 0755);                                                                                                                                                                
                                                                                                                                                                                              
        printf("Directory created by child 2: %s\n", dir_name);                                                                                                                               
                                                                                                                                                                                              
        exit(0);                                                                                                                                                                              
                                                                                                                                                                                              
    }                                                                                                                                                                                         
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
    // Parent process                                                                                                                                                                         
                                                                                                                                                                                              
    int status;                                                                                                                                                                               
                                                                                                                                                                                              
    waitpid(pid1, &status, 0);                                                                                                                                                                
                                                                                                                                                                                              
    waitpid(pid2, &status, 0);                                                                                                                                                                
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
    printf("Parent process PID: %d\n", getpid());                                                                                                                                             
                                                                                                                                                                                              
    printf("Child 1 PID: %d\n", pid1);                                                                                                                                                        
                                                                                                                                                                                              
    printf("Child 2 PID: %d\n", pid2);                                                                                                                                                        
                                                                                                                                                                                              
                                                                                                                                                                                              
                                                                                                                                                                                              
    return 0;                                                                                                                                                                                 
                                                                                                                                                                                              
}    