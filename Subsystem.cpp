 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: Subsystem.c
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

#include "Subsystem.h"
#include "Subsystem_private.h"

/* Block signals (default storage) */
B_Subsystem_T Subsystem_B;

/* Continuous states */
X_Subsystem_T Subsystem_X;

/* External inputs (root inport signals with default storage) */
ExtU_Subsystem_T Subsystem_U;

/* External outputs (root outports fed by signals with default storage) */
ExtY_Subsystem_T Subsystem_Y;

/* Real-time model */
static RT_MODEL_Subsystem_T Subsystem_M_;
RT_MODEL_Subsystem_T *const Subsystem_M = &Subsystem_M_;

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 4;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  Subsystem_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; ++i) {
    x[i] += h * f0[i];
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model step function */
void Subsystem_step(void)
{
  real_T rtb_Gain12[3];
  int32_T i;
  if (rtmIsMajorTimeStep(Subsystem_M)) {
    /* set solver stop time */
    rtsiSetSolverStopTime(&Subsystem_M->solverInfo,
                          ((Subsystem_M->Timing.clockTick0+1)*
      Subsystem_M->Timing.stepSize0));
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(Subsystem_M)) {
    Subsystem_M->Timing.t[0] = rtsiGetT(&Subsystem_M->solverInfo);
  }

  /* Outport: '<Root>/vitesse_estimee' incorporates:
   *  Integrator: '<S2>/x_est'
   */
  Subsystem_Y.vitesse_estimee = Subsystem_X.x_est_CSTATE[0];

  /* Saturate: '<S1>/Saturation1' incorporates:
   *  Gain: '<S2>/Gain11'
   *  Inport: '<Root>/position'
   *  Integrator: '<S2>/x_est'
   *  Sum: '<S2>/Sum6'
   */
  Subsystem_Y.tension_commandee = Subsystem_U.position - ((Subsystem_P.C_bar[0] *
    Subsystem_X.x_est_CSTATE[0] + Subsystem_P.C_bar[1] *
    Subsystem_X.x_est_CSTATE[1]) + Subsystem_P.C_bar[2] *
    Subsystem_X.x_est_CSTATE[2]);

  /* Gain: '<S2>/Gain12' */
  rtb_Gain12[0] = Subsystem_P.L_bar[0] * Subsystem_Y.tension_commandee;
  rtb_Gain12[1] = Subsystem_P.L_bar[1] * Subsystem_Y.tension_commandee;
  rtb_Gain12[2] = Subsystem_P.L_bar[2] * Subsystem_Y.tension_commandee;

  /* Saturate: '<S1>/Saturation1' incorporates:
   *  Gain: '<S1>/Gain1'
   *  Gain: '<S1>/Gain2'
   *  Integrator: '<S1>/Integrator1'
   *  Integrator: '<S2>/x_est'
   *  Sum: '<S1>/Sum2'
   */
  Subsystem_Y.tension_commandee = (0.0 - Subsystem_P.Ki *
    Subsystem_X.Integrator1_CSTATE) - Subsystem_P.Kx * Subsystem_X.x_est_CSTATE
    [0];

  /* Saturate: '<S1>/Saturation1' */
  if (Subsystem_Y.tension_commandee > Subsystem_P.Saturation1_UpperSat) {
    /* Saturate: '<S1>/Saturation1' */
    Subsystem_Y.tension_commandee = Subsystem_P.Saturation1_UpperSat;
  } else {
    if (Subsystem_Y.tension_commandee < Subsystem_P.Saturation1_LowerSat) {
      /* Saturate: '<S1>/Saturation1' */
      Subsystem_Y.tension_commandee = Subsystem_P.Saturation1_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Saturation1' */
  for (i = 0; i < 3; i++) {
    /* Sum: '<S2>/Sum5' incorporates:
     *  Gain: '<S2>/Gain10'
     *  Gain: '<S2>/Gain9'
     *  Integrator: '<S2>/x_est'
     */
    Subsystem_B.dx_est[i] = ((Subsystem_P.A_bar[i + 3] *
      Subsystem_X.x_est_CSTATE[1] + Subsystem_P.A_bar[i] *
      Subsystem_X.x_est_CSTATE[0]) + Subsystem_P.A_bar[i + 6] *
      Subsystem_X.x_est_CSTATE[2]) + (Subsystem_P.B_bar[i] *
      Subsystem_Y.tension_commandee + rtb_Gain12[i]);
  }

  /* Sum: '<S1>/Sum1' incorporates:
   *  Inport: '<Root>/vitesse_souhaitee'
   *  Integrator: '<S2>/x_est'
   */
  Subsystem_B.Sum1 = Subsystem_U.vitesse_souhaitee - Subsystem_X.x_est_CSTATE[0];
  if (rtmIsMajorTimeStep(Subsystem_M)) {
    rt_ertODEUpdateContinuousStates(&Subsystem_M->solverInfo);

    /* Update absolute time for base rate */
    /* The "clockTick0" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick0"
     * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
     * overflow during the application lifespan selected.
     */
    ++Subsystem_M->Timing.clockTick0;
    Subsystem_M->Timing.t[0] = rtsiGetSolverStopTime(&Subsystem_M->solverInfo);

    {
      /* Update absolute timer for sample time: [0.005s, 0.0s] */
      /* The "clockTick1" counts the number of times the code of this task has
       * been executed. The resolution of this integer timer is 0.005, which is the step size
       * of the task. Size of "clockTick1" ensures timer will not overflow during the
       * application lifespan selected.
       */
      Subsystem_M->Timing.clockTick1++;
    }
  }                                    /* end MajorTimeStep */
}

/* Derivatives for root system: '<Root>' */
void Subsystem_derivatives(void)
{
  XDot_Subsystem_T *_rtXdot;
  _rtXdot = ((XDot_Subsystem_T *) Subsystem_M->derivs);

  /* Derivatives for Integrator: '<S2>/x_est' */
  _rtXdot->x_est_CSTATE[0] = Subsystem_B.dx_est[0];
  _rtXdot->x_est_CSTATE[1] = Subsystem_B.dx_est[1];
  _rtXdot->x_est_CSTATE[2] = Subsystem_B.dx_est[2];

  /* Derivatives for Integrator: '<S1>/Integrator1' */
  _rtXdot->Integrator1_CSTATE = Subsystem_B.Sum1;
}

/* Model initialize function */
void Subsystem_initialize(void)
{
  /* Registration code */
  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&Subsystem_M->solverInfo,
                          &Subsystem_M->Timing.simTimeStep);
    rtsiSetTPtr(&Subsystem_M->solverInfo, &rtmGetTPtr(Subsystem_M));
    rtsiSetStepSizePtr(&Subsystem_M->solverInfo, &Subsystem_M->Timing.stepSize0);
    rtsiSetdXPtr(&Subsystem_M->solverInfo, &Subsystem_M->derivs);
    rtsiSetContStatesPtr(&Subsystem_M->solverInfo, (real_T **)
                         &Subsystem_M->contStates);
    rtsiSetNumContStatesPtr(&Subsystem_M->solverInfo,
      &Subsystem_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&Subsystem_M->solverInfo,
      &Subsystem_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&Subsystem_M->solverInfo,
      &Subsystem_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&Subsystem_M->solverInfo,
      &Subsystem_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&Subsystem_M->solverInfo, (&rtmGetErrorStatus
      (Subsystem_M)));
    rtsiSetRTModelPtr(&Subsystem_M->solverInfo, Subsystem_M);
  }

  rtsiSetSimTimeStep(&Subsystem_M->solverInfo, MAJOR_TIME_STEP);
  Subsystem_M->intgData.f[0] = Subsystem_M->odeF[0];
  Subsystem_M->contStates = ((X_Subsystem_T *) &Subsystem_X);
  rtsiSetSolverData(&Subsystem_M->solverInfo, (void *)&Subsystem_M->intgData);
  rtsiSetSolverName(&Subsystem_M->solverInfo,"ode1");
  rtmSetTPtr(Subsystem_M, &Subsystem_M->Timing.tArray[0]);
  Subsystem_M->Timing.stepSize0 = 0.005;

  /* InitializeConditions for Integrator: '<S2>/x_est' */
  Subsystem_X.x_est_CSTATE[0] = Subsystem_P.x_est_IC;
  Subsystem_X.x_est_CSTATE[1] = Subsystem_P.x_est_IC;
  Subsystem_X.x_est_CSTATE[2] = Subsystem_P.x_est_IC;

  /* InitializeConditions for Integrator: '<S1>/Integrator1' */
  Subsystem_X.Integrator1_CSTATE = Subsystem_P.Integrator1_IC;
}

/* Model terminate function */
void Subsystem_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
