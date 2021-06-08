/*******************************************************************************
*
*   phoneTrc.c -    A program implementing the phone system (PragmaDev Studio
*                                                             tutorial)
*
*   Notes:                Error checking omitted...
*
*******************************************************************************/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include "phtrdsMsgLyr.h" /* pthreads message layer fucntion prototypes,
                                              constants and structs */

#define NUM_PHONE 5

static void *pLocal(void *arg_ptr);   /* pLocal process code */
static void *pCentral(void *arg_ptr); /* pCentral process code */
static void *pEnvironment(void *arg); /* environment proces code */





int main(void)
{

  FILE *fpt;
  fpt = fopen("MyFile.csv", "w+");
  fprintf(fpt,"ID, Medicamento,ranBPM,ranSPO2,bpmSENSOR,spo2SENSOR\n");
  fclose(fpt);

  pthread_t env_tid;      /* Env tid */
  pthread_t pCentral_tid; /* pCentral process tid */

  /* Create queues */
  initialiseQueues();

  /* Create threads */
  pthread_create(&pCentral_tid, NULL, pCentral, NULL);
  pthread_create(&env_tid, NULL, pEnvironment, NULL);

  /* Wait for threads to finish */
  pthread_join(env_tid, NULL);
  pthread_join(pCentral_tid, NULL);

  /* Destroy queues */
  destroyQueues();

  return (0);
}

/* Environment thread */
static void *pEnvironment(void *arg)
{
  char line[100];
  int choice,
      cedula,
      cod_med;

  double range_bpm,
      range_spo2,
      sensor_bpm,
      sensor_spo2;

  msg_t OutMsg;

  sleep(6);
  for (;;)
  {
    choice = 1;
    /*
    printf("1. Register Patient\n");
    fflush(stdout);
    fflush(stdin);
    fgets(line, sizeof(line), stdin);
    sscanf(line, "%d", &choice);*/
    switch (choice)
    {
    case 1:
      printf("Enter patient id: ");
      cedula = (rand() % (NUM_PHONE)) + 1;
      printf("%d\n",cedula);

      printf("Enter medicine code: ");
      //sscanf(line, "%d", &cod_med);
      cod_med = (rand() % (100)) + 1;
      printf("%d\n",cod_med);

      printf("Enter expected bpm range: ");
      //sscanf(line, "%lf", &range_bpm);
      range_bpm = (rand() % (100 - 80 + 1)) + 80;
      printf("%lf\n",range_bpm);

      printf("Enter expected spo2 range: ");
      /*sscanf(line, "%lf", &range_spo2);*/
      range_spo2 = (rand() % (100 - 80 + 1)) + 80;
      printf("%lf\n",range_spo2);


      printf("Enter sensor_bpm: ");
      /*sscanf(line, "%lf", &sensor_bpm);*/
      sensor_bpm = (rand() % (100 - 80 + 1)) + 80;
      printf("%lf\n",sensor_bpm);

      printf("Enter sensor_spo2: ");
      /*sscanf(line, "%lf", &sensor_spo2);*/
      sensor_spo2 = (rand() % (100 - 80 + 1)) + 80;
      printf("%lf\n",sensor_spo2);
    

      OutMsg.signal = (int)sPaciente;
      OutMsg.cedula_real = cedula;
      OutMsg.medicamento = cod_med;
      OutMsg.ranBPM = range_bpm;
      OutMsg.ranSPO2 = range_spo2;
      OutMsg.bpmSENSOR = sensor_bpm;
      OutMsg.spo2SENSOR = sensor_spo2;

      sendMessage(&(queue[cedula]), OutMsg); /* send message to A subscriber */
      sleep(1);
      printf("\n");
      break;
    default:
      break;
    }
  }

  return (NULL);
}

/* pCentral process thread */
static void *pCentral(void *arg_ptr)
{
  CENTRAL_STATES state,
      state_next;
  msg_t InMsg,
      OutMsg;
  pthread_t pLocals[NUM_PHONE + 1];

  int index;

  int SenderQ;

  for (index = 1; index <= NUM_PHONE; index++)
  {
    pthread_create(&pLocals[index], NULL, pLocal, (void *)&index);
    sleep(1);
  }

  printf("\t\t\t\tsReady\n"); /* "send" message to environment */
  fflush(stdout);

  for (index = 1; index <= NUM_PHONE; index++)
    pthread_join(pLocals[index], NULL);

  return (NULL);
}

/* pLocal process thread */
static void *pLocal(void *arg_ptr)
{
  LOCAL_STATES state,
      state_next;
  msg_t InMsg,
      OutMsg;

  int queueNo,
      *data_ptr;

  int calledNumber,
      remotePId,
      whoami,
      senderQ;

  /*tmp data receivers*/
  int rec_cedula_real;
  int rec_medicamento;
  double rec_ranBPM;
  double rec_ranSPO2;
  double rec_bpmSENSOR;
  double rec_spo2SENSOR;

  data_ptr = (int *)arg_ptr;
  queueNo = whoami = *data_ptr;

  printf("\t\t\t\tAvaliable %d for patient ...\n", whoami);
  fflush(stdout);

  state_next = IdleL;




  for (;;)
  {
    state = state_next;
    InMsg = receiveMessage(&(queue[queueNo]));
    switch (state)
    {
    case IdleL:
      switch (InMsg.signal)
      {
      case sPaciente:

        rec_cedula_real = InMsg.cedula_real;
        rec_medicamento = InMsg.medicamento;
        rec_ranBPM = InMsg.ranBPM;
        rec_ranSPO2 = InMsg.ranSPO2;
        rec_bpmSENSOR = InMsg.bpmSENSOR;
        rec_spo2SENSOR = InMsg.spo2SENSOR;

        /*
        printf("rec_cedula_real: %d\n", rec_cedula_real);
        printf("rec_medicamento: %d\n", rec_medicamento);
        printf("rec_ranBPM: %lf\n", rec_ranBPM);
        printf("rec_ranSPO2: %lf\n", rec_ranSPO2);
        printf("rec_bpmSENSOR: %lf\n", rec_bpmSENSOR);
        printf("rec_spo2SENSOR: %lf\n", rec_spo2SENSOR);*/

        FILE *fpt;

        fpt = fopen("MyFile.csv", "a");
        
        fprintf(fpt,"%d,%d,%lf,%lf,%lf,%lf\n",rec_cedula_real,rec_medicamento,rec_ranBPM,rec_ranSPO2,rec_bpmSENSOR,rec_spo2SENSOR);
        fclose(fpt);

        if (rec_bpmSENSOR >= rec_ranBPM - 5 && rec_bpmSENSOR <= rec_ranBPM + 5)
        {

          if (rec_spo2SENSOR >= rec_ranSPO2 - 5 && rec_spo2SENSOR <= rec_ranSPO2 + 5)
          {
            printf("BPM & SPO2 are in normal range!! \n");
          }

          else
          {
            printf("BPM is OK but SPO2 is not!!\n");
          }
        }

        else
        {
          if (rec_spo2SENSOR >= rec_ranSPO2 - 5 && rec_spo2SENSOR <= rec_ranSPO2 + 5)
          {
            printf("BPM is wrong but SPO2 is ok \n");
          }

          else
          {
            printf("BPM & SPO2 are not in normal range!! \n");
          }
        }
        state_next = IdleL;



      break;
      default: break;
      }
    }

    
  }
  return (NULL);
}
