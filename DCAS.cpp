/*#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <bits/stdc++.h>
#include <semaphore.h>*/

#include "myhdr.h"
using namespace std;

struct dronedata
{
  int id;
  sem_t * map_protect;
  int start_row;
  int start_col;
  int target_row;
  int target_col;

};

#define NUMTHRDS 3
struct dronedata dronedata_array[NUMTHRDS];
pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutextarget;
int array1[100][100];
int n,m;

void print_grid(){

    //sleep(1);

    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            printf("%d",array1[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
    //sleep(1);
}
void *droneprocess(void *dronearg)
{
    int drone_id;
    sem_t *drone_sem;
    int drone_start_row;
    int drone_start_col;
    int drone_target_row;
    int drone_target_col;
    struct dronedata *my_drone;
    //sleep(3);

    my_drone = (struct dronedata*)dronearg;
    drone_id = my_drone->id;
    drone_start_row =  my_drone->start_row;
    drone_start_col =  my_drone->start_col;
    drone_target_row = my_drone->target_row;
    drone_target_col = my_drone->target_col;
    drone_sem = my_drone->map_protect;
    sem_wait(drone_sem);
    printf("\nDrone %d starting...Target for drone: (row,col):(%d,%d)\n",drone_id,drone_target_row,drone_target_col);
    sem_post(drone_sem);
    int k=0,l=0;
    int x,y,v;
    x=0;
    y=0;
    v=rand()%100+1;
    for(x=0; x<n; x+=1){
        sem_wait(drone_sem);
        if(v==1)x+=1;
        if(array1[x+1][y]!=0){
            y=y+2;
            array1[x][y]=drone_id;
            array1[x][y-2]=0;
            print_grid();
            y=y-2;
            array1[x][y]=drone_id;
            array1[x][y+2]=0;
            print_grid();
        }
        if(x>=1)
            array1[x-1][y] = 0;
        array1[x][y] = drone_id;
        print_grid();
        sem_post(drone_sem);
        if(x==drone_target_row-1){
            sem_post(drone_sem);
            break;
        }
    }
    for(y=0;y<m; y+=1){
        sem_wait(drone_sem);
        if(v==1)x+=2;
        if(array1[x][y+1]!=0){
            x=x-1;
            array1[x][y]=drone_id;
            array1[x+1][y]=0;
            print_grid();
            x=x+1;
            array1[x][y]=drone_id;
            array1[x-1][y]=0;
            print_grid();
        }
        if(y>=1)
            array1[drone_target_row-1][y-1]=0;
        array1[drone_target_row-1][y]=drone_id;
        print_grid();
        sem_post(drone_sem);
        if(y== drone_target_col-1){
            sem_post(drone_sem);
            break;

        }
    }
    x=drone_target_row-1;
    y=drone_target_col-1;
    pthread_mutex_lock (&mutextarget);
    sem_wait(drone_sem);
    printf("\nDrone id: %d reached target (row,col)=(%d,%d)\n",drone_id,drone_target_row,drone_target_col);
    print_grid();
    sem_post(drone_sem);
    //print_grid();
    pthread_mutex_unlock (&mutextarget);
    for(l=y; l>0; l-=1){
        sem_wait(drone_sem);
        if(array1[drone_target_row-1][l]!=0 && array1[drone_target_row-1][l]!=drone_id){
            sleep(1);
            printf("\nDrone id: %d detected collision at (row,col)=(%d,%d) and stopped to let other drone pass by.\n",drone_id,drone_target_row-1,l+1);
            printf("\nDrone id: %d has avoided collision at (row,col)=(%d,%d) and reaching for point of launch.\n",drone_id,drone_target_row-1,l+1);
            drone_target_row = drone_target_row-1;

            //array1[drone_target_row][l]=drone_id;
            //array1[drone_target_row-1][l]=0;
            //sleep(2);
            //array1[drone_target_row-1][l-2]=drone_id;
            //array1[drone_target_row-1][l]=0;
        }
        array1[drone_target_row-1][l]=drone_id;
        array1[drone_target_row-1][l+1]=0;
        if(l==1)
            array1[drone_target_row-1][1]=0;
        print_grid();
        sem_post(drone_sem);
        //print_grid();
    }
    x=drone_target_row-1;
    y=0;
    for(k=x; k>0; k-=1){
        sem_wait(drone_sem);
        //if(array1[k][0]!=0 && array1[k][0]!=drone_id){
        if(array1[k][y]!=0 && array1[k][y]!=drone_id){
            //sleep(1);
            printf("\nDrone id: %d detected collision at (row,col)=(%d,%d) and stopped to let other drone pass by.\n",drone_id,k,1);
            printf("\nDrone id: %d avoided collision at (row,col)=(%d,%d) and reaching for point of launch.\n",drone_id,k,1);
            y=y+2;
            sleep(2);
            array1[k][y]=drone_id;
            array1[k][y-2]=0;
            print_grid();
            y=y-2;
            array1[k][y+2]=0;
            array1[k][y]=drone_id;
            print_grid();
            continue;
        }
        array1[k][y]=drone_id;
        array1[k+1][y]=0;
        /*if(k==0){
            y=y-2;
            array1[k][y]=drone_id;
            array1[k+1][y]=0;
        }*/
        print_grid();
        sem_post(drone_sem);
        //print_grid();
    }
    if(k==0 && l==0){
        sem_wait(drone_sem);
        //array1[0][0]=0;
        //array1[1][0]=0;
        //array1[2][0]=0;
        printf("\nDrone id: %d reached the point of launch (row,col)=(%d,%d)\n",drone_id,k+1,l+1);
        for(int i=0; i<10; i++){
            for(int j=0; j<10; j++){
                array1[i][j]=0;
            }
        }
        //array1[10][10]=0;
        print_grid();
        sem_post(drone_sem);

    }
    pthread_mutex_unlock (&mutextarget);
    //printf("\nThread id: %d reached the point of launch (row,col)=(%d,%d)\n",drone_id,k+1,l+1);

    pthread_exit((void*)0);
}


int main (int argc, char *argv[])
{

  void *status;
  pthread_attr_t attr;
  sem_t map_sem;
  int err = sem_init(&map_sem,0,1);
  if(err < 0){
    printf("error in initializing semaphore.");
    return 1;

  }

  cin>>n>>m;

  pthread_mutex_init(&mutextarget, NULL);
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(int i=0; i<NUMTHRDS; i++)
    {
        dronedata_array[i].map_protect = &map_sem;
        dronedata_array[i].id = i+1;
        dronedata_array[i].start_row=0;
        dronedata_array[i].start_col=0;
        dronedata_array[i].target_row=rand()%n;
        if(dronedata_array[i].target_row==0)dronedata_array[i].target_row=1;
        dronedata_array[i].target_col=rand()%m;
        if(dronedata_array[i].target_col==0)dronedata_array[i].target_col=1;

      //pthread_create(&callThd[i], &attr, droneprocess, (void *)&dronedata_array[i]);
      pthread_create(&callThd[i], NULL, droneprocess, (void *)&dronedata_array[i]);
      //pthread_join(callThd[i], &status);
    }

  pthread_attr_destroy(&attr);

  pthread_mutex_destroy(&mutextarget);
  pthread_exit(NULL);
}
