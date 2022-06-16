/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.h
 *
 * Code generated for Simulink model 'Subsystem'.
 *
 * Model version                  : 1.3
 * Simulink Coder version         : 9.4 (R2020b) 29-Jul-2020
 * C/C++ source code generated on : Wed Jun 15 14:40:11 2022
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_Subsystem_h_
#define RTW_HEADER_Subsystem_h_
#ifndef Subsystem_COMMON_INCLUDES_
#define Subsystem_COMMON_INCLUDES_
#include "rtwtypes.h"
#include "rtw_continuous.h"
#include "rtw_solver.h"
#endif                                 /* Subsystem_COMMON_INCLUDES_ */

#include "Subsystem_types.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
#define rtmGetErrorStatus(rtm)         ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
#define rtmSetErrorStatus(rtm, val)    ((rtm)->errorStatus = (val))
#endif

#ifndef rtmGetStopRequested
#define rtmGetStopRequested(rtm)       ((rtm)->Timing.stopRequestedFlag)
#endif

#ifndef rtmSetStopRequested
#define rtmSetStopRequested(rtm, val)  ((rtm)->Timing.stopRequestedFlag = (val))
#endif

#ifndef rtmGetStopRequestedPtr
#define rtmGetStopRequestedPtr(rtm)    (&((rtm)->Timing.stopRequestedFlag))
#endif

#ifndef rtmGetT
#define rtmGetT(rtm)                   (rtmGetTPtr((rtm))[0])
#endif

#ifndef rtmGetTPtr
#define rtmGetTPtr(rtm)                ((rtm)->Timing.t)
#endif

/* Block signals (default storage) */
typedef struct {
  real_T dx_est[3];                    /* '<S2>/Sum5' */
  real_T Sum1;                         /* '<S1>/Sum1' */
} B_Subsystem_T;

/* Continuous states (default storage) */
typedef struct {
  real_T x_est_CSTATE[3];              /* '<S2>/x_est' */
  real_T Integrator1_CSTATE;           /* '<S1>/Integrator1' */
} X_Subsystem_T;

/* State derivatives (default storage) */
typedef struct {
  real_T x_est_CSTATE[3];              /* '<S2>/x_est' */
  real_T Integrator1_CSTATE;           /* '<S1>/Integrator1' */
} XDot_Subsystem_T;

/* State disabled  */
typedef struct {
  boolean_T x_est_CSTATE[3];           /* '<S2>/x_est' */
  boolean_T Integrator1_CSTATE;        /* '<S1>/Integrator1' */
} XDis_Subsystem_T;

#ifndef ODE1_INTG
#define ODE1_INTG

/* ODE1 Integration Data */
typedef struct {
  real_T *f[1];                        /* derivatives */
} ODE1_IntgData;

#endif

/* External inputs (root inport signals with default storage) */
typedef struct {
  real_T position;                     /* '<Root>/position' */
  real_T vitesse_souhaitee;            /* '<Root>/vitesse_souhaitee' */
} ExtU_Subsystem_T;

/* External outputs (root outports fed by signals with default storage) */
typedef struct {
  real_T vitesse_estimee;              /* '<Root>/vitesse_estimee' */
  real_T tension_commandee;            /* '<Root>/tension_commandee' */
} ExtY_Subsystem_T;

/* Parameters (default storage) */
struct P_Subsystem_T_ {
  real_T A_bar[9];                     /* Variable: A_bar
                                        * Referenced by: '<S2>/Gain10'
                                        */
  real_T B_bar[3];                     /* Variable: B_bar
                                        * Referenced by: '<S2>/Gain9'
                                        */
  real_T C_bar[3];                     /* Variable: C_bar
                                        * Referenced by: '<S2>/Gain11'
                                        */
  real_T Ki;                           /* Variable: Ki
                                        * Referenced by: '<S1>/Gain2'
                                        */
  real_T Kx;                           /* Variable: Kx
                                        * Referenced by: '<S1>/Gain1'
                                        */
  real_T L_bar[3];                     /* Variable: L_bar
                                        * Referenced by: '<S2>/Gain12'
                                        */
  real_T x_est_IC;                     /* Expression: 0
                                        * Referenced by: '<S2>/x_est'
                                        */
  real_T Integrator1_IC;               /* Expression: 0
                                        * Referenced by: '<S1>/Integrator1'
                                        */
  real_T Saturation1_UpperSat;         /* Expression: 9
                                        * Referenced by: '<S1>/Saturation1'
                                        */
  real_T Saturation1_LowerSat;         /* Expression: -9
                                        * Referenced by: '<S1>/Saturation1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Subsystem_T {
  const char_T *errorStatus;
  RTWSolverInfo solverInfo;
  X_Subsystem_T *contStates;
  int_T *periodicContStateIndices;
  real_T *periodicContStateRanges;
  real_T *derivs;
  boolean_T *contStateDisabled;
  boolean_T zCCacheNeedsReset;
  boolean_T derivCacheNeedsReset;
  boolean_T CTOutputIncnstWithState;
  real_T odeF[1][4];
  ODE1_IntgData intgData;

  /*
   * Sizes:
   * The following substructure contains sizes information
   * for many of the model attributes such as inputs, outputs,
   * dwork, sample times, etc.
   */
  struct {
    int_T numContStates;
    int_T numPeriodicContStates;
    int_T numSampTimes;
  } Sizes;

  /*
   * Timing:
   * The following substructure contains information regarding
   * the timing information for the model.
   */
  struct {
    uint32_T clockTick0;
    time_T stepSize0;
    uint32_T clockTick1;
    SimTimeStep simTimeStep;
    boolean_T stopRequestedFlag;
    time_T *t;
    time_T tArray[2];
  } Timing;
};

/* Block parameters (default storage) */
extern P_Subsystem_T Subsystem_P;

/* Block signals (default storage) */
extern B_Subsystem_T Subsystem_B;

/* Continuous states (default storage) */
extern X_Subsystem_T Subsystem_X;

/* External inputs (root inport signals with default storage) */
extern ExtU_Subsystem_T Subsystem_U;

/* External outputs (root outports fed by signals with default storage) */
extern ExtY_Subsystem_T Subsystem_Y;

/* Model entry point functions */
extern void Subsystem_initialize(void);
extern void Subsystem_step(void);
extern void Subsystem_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Subsystem_T *const Subsystem_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('conversion_vitesse_tension_moteur/Subsystem')    - opens subsystem conversion_vitesse_tension_moteur/Subsystem
 * hilite_system('conversion_vitesse_tension_moteur/Subsystem/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'conversion_vitesse_tension_moteur'
 * '<S1>'   : 'conversion_vitesse_tension_moteur/Subsystem'
 * '<S2>'   : 'conversion_vitesse_tension_moteur/Subsystem/Observateur étendu1'
 */
#endif                                 /* RTW_HEADER_Subsystem_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
