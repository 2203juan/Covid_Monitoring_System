/*******************************************************************************
*
*  msgq_usr.h - Manifest Constants and Types for concurrent access to a
*                   circular buffer modelling a message queue
*
*   Notes:          User defined according to application
*
*******************************************************************************/

#define     BUFSIZE     8     /* number of slots in queues */
#define     NUM_QUEUES  6     /* number of queues */
#define     CENTRAL_Q   0     /* queue 0: pCentral process */
#define     LOCAL1_Q    1     /* queue 1: pLocal1 process */
#define     LOCAL2_Q    2     /* queue 2: pLocal2 process */
#define     LOCAL3_Q    3     /* queue 3: pLocal3 process */
#define     LOCAL4_Q    4     /* queue 4: pLocal4 process */
#define     LOCAL5_Q    5     /* queue 5: pLocal5 process */

/***( message structure )******************************************************/

typedef struct
{
  int   signal;
  int cedula_real;
  int   medicamento;
  double   ranBPM;
  double ranSPO2;
  double bpmSENSOR;
  double spo2SENSOR; 
} msg_t;


/*
typedef struct
{
  int   signal;
  int   value;
  int   sender;
} msg_t;*/

/*
typedef struct
{
  int  signal;
  void *data_ptr;
  int  sender;
} msg_t;
*/

/***( signals )****************************************************************/

typedef enum
{
  sResultado
} TO_CENTRAL;                             /* Signals sent from process pLocal
                                            to process pCentral */

typedef enum
{
  sPaciente
} TO_LOCAL;                               /* Signals sent to process pLocal */

/***( EFSM states )************************************************************/

typedef enum
{
  IdleL,
  GettingId,
  Connecting,
  Connected,
  Disconnecting
} LOCAL_STATES;                            /* EFSM states for process pLocal */

typedef enum
{
  IdleC
} CENTRAL_STATES;                            /* EFSM states for process pCentral */
