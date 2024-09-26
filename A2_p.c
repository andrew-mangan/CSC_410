#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
//#include <sys/wait.h>

// Starting shield power level
int shield_power = 50;  

int main() {
int Luke_power = shield_power;
int Han_power = shield_power;
int Chewy_power = shield_power;
int Leia_power = shield_power;

printf("Millennium Falcon: Initial shield power level: %d%%\n\n", shield_power);

for (int i = 0; i < 4; i++) {
    pid_t pid = fork();
       if (pid == 0) {

                    if (i==0){
                    printf("Luke. Adjusting shield power. %d \n", i);

                    printf("Han. Adjusting shield power.%d \n", i);
                    printf("Chewbacca. Adjusting shield power.%d \n", i);
                    printf("Leia. Adjusting shield power.%d \n", i);}
                    Luke_power += 25;
                    Han_power += 20;
                    Chewy_power += 30;
                    Leia_power += 25;
                    printf("Luke. power %d. \n", Luke_power);
                    printf("Han. power %d.\n", Han_power);
                    printf("Chewbacca. Power %d \n", Chewy_power);
                    printf("Leia. power %d. \n", Leia_power);
                    return 0;
            }
    }

    // Create 4 child processes - 4 different characters adjusting shield power

            // Luke increases the shield power by 25
            // Han increases the shield power by 20
            // Chewbacca increases the shield power by 30
            // Leia increases the shield power by 15
               

    // Check if process creation failed
     
        

    // Make parent process wait for all child processes to complete
        // -----> Write you code here 
    while (wait(NULL) > 0);
    printf("\nFinal shield power level on the Millennium Falcon: %d%%\n", shield_power);
    // Parent process reports final state
    
    printf("\nMay the forks be with you!\n");
    return 0;
}